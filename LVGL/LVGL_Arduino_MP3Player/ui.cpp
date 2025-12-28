//================================================================================
// MP3 Music Player for CYD - User Interface
// LVGL version: 9.2.2 and up
//================================================================================
#include "ui.h"
#include "json.hpp"
#include <string.h> // for strncpy(), strrchr()

////////////////////// GLOBAL VARIABLES /////////////////////
UI_State_t   ui_state;
UI_Control_t ui_control;
UI_Setting_t ui_setting = {
  .shuffle = true,
  .selectBacklight = 1,
};

////////////////////// LOCAL VARIABLES //////////////////////
#include "MP3Player.h"
static MP3Player player;

static bool       id3tagsSave;
static MP3Tags_t  id3tags;
static UI_State_t nextState;

/////////////////////////// IMAGES //////////////////////////
#include "src/_pictures.h"

////////////////////////// UI LOOP //////////////////////////
// https://embedded-kiddie.github.io/2024/07/22/
#define DO_EVERY(period, prev) \
static uint32_t prev = 0; for (uint32_t now = millis(); now - prev >= period; prev = now)

#define PERIOD_TAKS1 1000 // [msec]
#define PERIOD_TAKS2 100  // [msec]

////////////////////// LOCAL FUNCTIONS //////////////////////

//--------------------------------------------------------------------------------
// Display a covoer picture on SD or flash
//--------------------------------------------------------------------------------
static void display_picture(uint32_t playNo) {
  static constexpr lv_style_const_prop_t style_prop_picture[] = {
    LV_STYLE_CONST_SHADOW_WIDTH(10),
    LV_STYLE_CONST_SHADOW_OFFSET_Y(5),
    LV_STYLE_CONST_SHADOW_OPA(LV_OPA_40),
    LV_STYLE_CONST_PROPS_END
  };
  static LV_STYLE_CONST_INIT(style_picture, (void*)style_prop_picture);

  // Display an image file on SD card
  char buf[BUF_SIZE], *ptr;
  buf[0] = MY_FS_ARDUINO_SD_LETTER;
  buf[1] = ':';

  // Skip drive letter "S:"
  std::string dir = player.GetFilePath(playNo);
  strncpy(&buf[2], dir.c_str(), sizeof(buf) - 2);
  buf[sizeof(buf) - 1] = '\0';

  // @photo.jpg
  if (ptr = strrchr(buf, '/')) {
    strcpy(ptr + 1, ALBUM_PHOTO_FILE ALBUM_PHOTO_EXT);
    if (SD.exists(buf + 2)) {
      lv_image_set_src(ui_AlbumImage, buf);
      lv_obj_add_style(ui_AlbumImage, &style_picture, 0);
      return;
    }
  }

  // title.jpg
  if (ptr = strrchr(buf, '.')) {
    strncpy(ptr, ALBUM_PHOTO_EXT, sizeof(ALBUM_PHOTO_EXT));
    if (SD.exists(buf + 2)) {
      lv_image_set_src(ui_AlbumImage, buf);
      lv_obj_add_style(ui_AlbumImage, &style_picture, 0);
      return;
    }
  }

#ifdef _PICTURES_H_
  #if true
    // Display an image file on flash ROM at random
    int pictNo = millis() % (N_PICTURES - 1) + 1;
    lv_image_set_src(ui_AlbumImage, pictures[pictNo]);
    lv_obj_add_style(ui_AlbumImage, &style_picture, 0);
  #else
    // Display an image specified by the number in @picture.txt
    int pictNo = player.GetPictureNo(playNo);
    if (0 < pictNo && pictNo < N_PICTURES) {
      lv_image_set_src(ui_AlbumImage, pictures[pictNo]);
      lv_obj_add_style(ui_AlbumImage, &style_picture, 0);
    } else {
      lv_image_set_src    (ui_AlbumImage, &img_album);
      lv_obj_remove_style (ui_AlbumImage, &style_picture, 0);
    }
  #endif
#endif
}

//--------------------------------------------------------------------------------
// Control next/previous play or stop/continuous play
//--------------------------------------------------------------------------------
static bool play_next(bool next) {
  if (ui_ScreenPlayList) {
    ui_list_update_cell(ui_control.focusNo, false);
    ui_list_update_icon(ui_control.playNo,  false);
  }

  bool ret = true;
  if (ui_setting.favorite) {
    ret = player.NextSelected(next, (ui_setting.repeat ? true : false));
  } else {
    if (next) {
      player.PlayNext();
    } else {
      player.PlayPrev();
    }
  }

  bitClear(ui_setting.repeat, 7); // clear the bit that has been temporarily forced set

  ui_control.playNo = ui_control.focusNo = player.GetPlayNo();
  display_picture(ui_control.playNo);

  // Update ui_control and look of the play button
  lv_obj_set_state(ui_ButtonPlay, LV_STATE_CHECKED, true);

  if (ui_ScreenPlayList) {
    ui_list_update_play(ui_control.playNo, true);
  }

  return ret;
}

static void play_stop(void) {
  lv_obj_set_state(ui_ButtonPlay, LV_STATE_CHECKED, false);
  player.StopPlay();
}

//--------------------------------------------------------------------------------
// Update bar and label according to elapsed time
//--------------------------------------------------------------------------------
static void update_elapsed_time(void) {
  uint32_t duration = audioGetDuration();
  uint32_t elapsed  = audioGetElapsedTime();

  if (duration < elapsed) {
    duration = elapsed;
  }

  if (duration) {
    id3tags.meta.duration = duration;
  }

  lv_slider_set_range(ui_ElapsedBar, 0, duration);
  lv_slider_set_value(ui_ElapsedBar, elapsed, LV_ANIM_OFF);

  lv_label_set_text_fmt(ui_ElapsedStart, "%" LV_PRIu32 ":%02" LV_PRIu32, elapsed  / 60, elapsed  % 60);
  lv_label_set_text_fmt(ui_ElapsedEnd,   "%" LV_PRIu32 ":%02" LV_PRIu32, duration / 60, duration % 60);
}

//--------------------------------------------------------------------------------
// Check and update the metadata when playback finishes
//--------------------------------------------------------------------------------
static void update_metadata(void) {
  MP3Meta_t meta;
  uint32_t playNo = player.GetPlayNo();
  player.GetMetaData(playNo, &meta);

  if (meta.duration < id3tags.meta.duration || id3tagsSave == true) {
    // Prevent input while saving metadata to SD card
    lv_indev_enable(NULL, false);

    if (player.IsPlaying()) {
      player.PauseResume();
    }

    // Update all Favorites that have been modified during playback
    if (id3tagsSave == true) {
      if (player.UpdateMetaData()) {
        id3tagsSave = false;
      }
    }

    bool update = false;

    // Update the playback duration at the end of file
    // Note: When the Elapse bar is operated by hand, the elapsed time will be shifted.
    if (abs(meta.duration - id3tags.meta.duration) >= 3 /* [sec] */) {
      meta.duration = id3tags.meta.duration;
      ui_list_update_duration(playNo, meta.duration);
      update = true;
    }

    if (update) {
      player.PutMetaData(playNo, &meta);
    }

    if (!player.IsPlaying()) {
      player.PauseResume();
    }

    lv_indev_enable(NULL, true);
  }
}

//--------------------------------------------------------------------------------
// Check out the favorite playlists
//--------------------------------------------------------------------------------
static bool check_favorite(void) {
  return !ui_setting.favorite || player.IsPlaying() || player.IsSelected();
}

//--------------------------------------------------------------------------------
// Save / Load settings in SD
//--------------------------------------------------------------------------------
static bool save_setting(void) {
  // Save partition
  File fd = SD.open(MP3_ROOT_PATH MP3_SETTING_FILE, FILE_WRITE);
  if (fd) {
    fd.write((uint8_t *)&ui_setting, sizeof(ui_setting));
    fd.close();
    return true;
  } else {
    return false;
  }
}

static void load_setting(void) {
  File fd = SD.open(MP3_ROOT_PATH MP3_SETTING_FILE, FILE_READ);
  if (fd) {
    fd.read((uint8_t *)&ui_setting, sizeof(ui_setting));
    fd.close();
  }

  bool save = false;

  // Check if the partition exists
  char buf[BUF_SIZE];
  uint8_t partition_max = 0;
  for (int i = 1; i <= PARTITION_MAX; i++) {
    snprintf(buf, sizeof(buf), MP3_ROOT_PATH PARTITION_PATH, i);
    buf[sizeof(buf) - 1] = '\0';
    if (SD.exists(buf)) {
      partition_max = i;
    } else {
      break;
    }
  }

  if (ui_setting.partition_max != partition_max) {
    ui_setting.partition_max = partition_max;
    save = true;
  }

  // Just in case
  if (ui_setting.partition_id > ui_setting.partition_max) {
    ui_setting.partition_id = 0;
    save = true;
  }

  if (save) {
    save_setting();
  }

  // Change the root folder with the current partition
  if (ui_setting.partition_max && ui_setting.partition_id) {
    snprintf(buf, sizeof(buf), PARTITION_PATH, ui_setting.partition_id);
    buf[sizeof(buf) - 1] = '\0';
    player.SetSubDir(buf);
  } else {
    player.SetSubDir("");
  }

  // Update UI
  lv_obj_set_state(ui_Shuffle, LV_STATE_CHECKED, ui_setting.shuffle);

  // Rewind
  ui_control.playNo = ui_control.focusNo = 0;
}

//--------------------------------------------------------------------------------
// Scan SD card for audio files and create a playlist
//--------------------------------------------------------------------------------
static bool create_playlist(void) {
  // Setup UI setting
  load_setting();

  uint32_t time = lv_tick_get();

  // Scan SD card for album folders
  if (player.ScanAlbumDirs()) {

    printf("ScanAlbumDirs: %lu [msec]\n", lv_tick_elaps(time));
    time = lv_tick_get();

    // Load album list
    ui_album_load((void*)player.m_tree);

    // Scan audio files base on album list
    if (player.ScanAudioFiles(ui_setting.partition_id, ui_setting.shuffle)) {

      printf("ScanAudioFiles: %lu [msec]\n", lv_tick_elaps(time));

      ui_set_playNo(ui_control.playNo);
      return true;
    }
  }
  return false;
}

//--------------------------------------------------------------------------------
// Asynchronous function to reduce delays during screen transitions
//--------------------------------------------------------------------------------
static void stop_async(void *user_data) {
  if (ui_state != UI_STATE_IDLE) {
    ui_state = UI_STATE_STOP;
  }
}

//--------------------------------------------------------------------------------
// Helper function for screen transition
//--------------------------------------------------------------------------------
static void change_screen(lv_obj_t ** target, lv_screen_load_anim_t fademode, void (*target_init)(void)) {
  if(*target == NULL) {
    target_init();
  }
  lv_screen_load_anim(*target, fademode, 500, 0, false);
}

///////////////////// CALLBACK FUNCTIONS ////////////////////
//--------------------------------------------------------------------------------
// Event handlers for Screen Main
//--------------------------------------------------------------------------------
void ui_event_ScreenMain(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_GESTURE);

  lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());

  if (dir == LV_DIR_RIGHT) {
    change_screen(&ui_ScreenAlbumList, LV_SCR_LOAD_ANIM_MOVE_RIGHT, &ui_ScreenAlbumList_screen_init);
  }

  else if (dir == LV_DIR_LEFT) {
    change_screen(&ui_ScreenPlayList, LV_SCR_LOAD_ANIM_MOVE_LEFT, &ui_ScreenPlayList_screen_init);
    ui_list_focus_playing(player.GetPlayNo());
  }

  else if (dir == LV_DIR_TOP || dir == LV_DIR_BOTTOM) {
    lv_screen_load_anim_t anim = (dir == LV_DIR_TOP ? LV_SCR_LOAD_ANIM_MOVE_TOP : LV_SCR_LOAD_ANIM_MOVE_BOTTOM);
    change_screen(&ui_ScreenSettings, anim, &ui_ScreenSettings_screen_init);
  }
}

void ui_event_GoToAlbumList(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  change_screen(&ui_ScreenAlbumList, LV_SCR_LOAD_ANIM_MOVE_RIGHT, &ui_ScreenAlbumList_screen_init);
}

void ui_event_GoToPlayList(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  change_screen(&ui_ScreenPlayList, LV_SCR_LOAD_ANIM_MOVE_LEFT, &ui_ScreenPlayList_screen_init);
}

void ui_event_GoToSettings(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  change_screen(&ui_ScreenSettings, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, &ui_ScreenSettings_screen_init);
}

void ui_event_Favorite(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  lv_obj_t *obj = lv_event_get_target_obj(e);
  ui_setting.favorite = (lv_obj_get_state(obj) & LV_STATE_CHECKED ? true : false);
}

void ui_event_Repeat(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  lv_obj_t *obj = lv_event_get_target_obj(e);
  ui_setting.repeat = (uint8_t)(lv_obj_get_state(obj) & LV_STATE_CHECKED ? true : false);
}

void ui_event_Shuffle(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  lv_obj_t *obj = lv_event_get_target_obj(e);
  ui_setting.shuffle = (lv_obj_get_state(obj) & LV_STATE_CHECKED ? true : false);
  player.StopPlay();
  player.ClearAudioFiles();
  save_setting();
  ui_state = UI_STATE_START;
}

void ui_event_ButtonPlay(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  lv_state_t state = lv_obj_get_state(ui_ButtonPlay);
  ui_state = (state & LV_STATE_CHECKED ? UI_STATE_RESUME : UI_STATE_PAUSE);
}

void ui_event_ButtonNext(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  ui_state = UI_STATE_NEXT;
  bitSet(ui_setting.repeat, 7); // Force to set the bit temporarily
}

void ui_event_ButtonPrev(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  ui_state = UI_STATE_PREV;
  bitSet(ui_setting.repeat, 7); // Force to set the bit temporarily
}

void ui_event_VolumeMax(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  int vol = lv_slider_get_value(ui_Volume) + 1;
  vol = constrain(vol, MP3_VOLUME_MIN, MP3_VOLUME_MAX);
  lv_slider_set_value(ui_Volume, vol, LV_ANIM_OFF);
  player.SetVolume(vol);
}

void ui_event_VolumeMin(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  int vol = lv_slider_get_value(ui_Volume) - 1;
  vol = constrain(vol, MP3_VOLUME_MIN, MP3_VOLUME_MAX);
  lv_slider_set_value(ui_Volume, vol, LV_ANIM_OFF);
  player.SetVolume(vol);
}

void ui_event_Volume(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED);

  int vol = lv_slider_get_value(ui_Volume);
  player.SetVolume(vol);
}

void ui_event_ElapsedBar(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED);

  if (player.IsPlaying()) {
    audioSetElapsedTime(lv_slider_get_value(ui_ElapsedBar));
  }
}

//--------------------------------------------------------------------------------
// Event handlers for Screen Album List
//--------------------------------------------------------------------------------
void ui_event_ScreenAlbumList(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  DBG_ASSERT(
    event_code == LV_EVENT_CLICKED ||
    event_code == LV_EVENT_GESTURE ||
    event_code == LV_EVENT_SCREEN_LOADED ||
    event_code == LV_EVENT_SCREEN_UNLOADED
  );

  if (event_code == LV_EVENT_CLICKED) {
    change_screen(&ui_ScreenMain, LV_SCR_LOAD_ANIM_MOVE_LEFT, &ui_ScreenMain_screen_init);
  }

  else if (event_code == LV_EVENT_GESTURE) {
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
    if (dir == LV_DIR_RIGHT || dir == LV_DIR_LEFT) {
      lv_screen_load_anim_t anim = (dir == LV_DIR_RIGHT ? LV_SCR_LOAD_ANIM_MOVE_RIGHT : LV_SCR_LOAD_ANIM_MOVE_LEFT);
      change_screen(&ui_ScreenMain, anim, &ui_ScreenMain_screen_init);
    }
  }

  else if (event_code == LV_EVENT_SCREEN_LOADED) {
    // Increase free memory
    // lv_fs_clear_cache(); // sdfs.{h|cpp}

    // Create album list (No need to access SD card)
    ui_album_create((void*)player.m_tree);

    // Stop playback to avoid conflict with SD access (async required)
    lv_async_call(stop_async, NULL);
  }

  else if (event_code == LV_EVENT_SCREEN_UNLOADED) {
    ui_ScreenAlbumList_screen_deinit();
    ui_state = UI_STATE_CLEAR;
  }
}

//--------------------------------------------------------------------------------
// Event handlers for Screen Playlist
//--------------------------------------------------------------------------------
void ui_event_ScreenPlayList(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  DBG_ASSERT(
    event_code == LV_EVENT_GESTURE ||
    event_code == LV_EVENT_SCREEN_UNLOADED
  );

  if (event_code == LV_EVENT_GESTURE) {
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
    lv_screen_load_anim_t anim = dir == LV_DIR_RIGHT ? LV_SCR_LOAD_ANIM_MOVE_RIGHT : LV_SCR_LOAD_ANIM_MOVE_LEFT;
    change_screen(&ui_ScreenMain, anim, &ui_ScreenMain_screen_init);
  }

  else if (event_code == LV_EVENT_SCREEN_UNLOADED) {
    ui_ScreenPlayList_screen_deinit();
  }
}

void ui_event_PlayList_Play(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  ui_state = (ui_state == UI_STATE_PLAY ? UI_STATE_PAUSE : UI_STATE_RESUME);
  lv_obj_set_state(ui_ButtonPlay, LV_STATE_CHECKED, ui_state == UI_STATE_PAUSE ? false : true);
}

void ui_event_PlayList_Heart(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  MP3Meta_t meta;
  uint32_t track_id = (uint32_t)lv_event_get_user_data(e);
  player.GetMetaData(track_id, &meta);

  lv_obj_t *obj = (lv_obj_t*)lv_event_get_current_target(e);
  meta.selected = ui_list_get_heart_state(track_id);

  // prevent input while saving metadata to SD card
  lv_indev_enable(NULL, false);
  bool saved = player.PutMetaData(track_id, &meta);
  lv_indev_enable(NULL, true);

  // in case the metadata file cannot be saved, save it separately
  if (!saved) {
    id3tagsSave = true;
  }
}

//--------------------------------------------------------------------------------
// Event handlers for Screen Settings
//--------------------------------------------------------------------------------
void ui_event_ScreenSettings(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  DBG_ASSERT(
    event_code == LV_EVENT_CLICKED ||
    event_code == LV_EVENT_GESTURE ||
    event_code == LV_EVENT_SCREEN_UNLOADED
  );

  if (event_code == LV_EVENT_CLICKED) {
    change_screen(&ui_ScreenMain, LV_SCR_LOAD_ANIM_MOVE_TOP, &ui_ScreenMain_screen_init);
  }

  else if (event_code == LV_EVENT_GESTURE) {
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
    lv_screen_load_anim_t anim = (dir == LV_DIR_TOP ? LV_SCR_LOAD_ANIM_MOVE_TOP : LV_SCR_LOAD_ANIM_MOVE_BOTTOM);
    change_screen(&ui_ScreenMain, anim, &ui_ScreenMain_screen_init);
  }

  else if (event_code == LV_EVENT_SCREEN_UNLOADED) {
    ui_ScreenSettings_screen_deinit();

    if (ui_setting.partition_max) {
      // Update the partition ID if a different ID is selected
      uint32_t partition_id = *(uint32_t*)lv_event_get_user_data(e);
      if (ui_setting.partition_id != partition_id) {
        ui_setting.partition_id = partition_id;

        // Stop playback before saving settings to avoid conflict with SD access
        play_stop();

        save_setting();
        player.DeleteNodeTree();
        player.ClearAudioFiles();
        ui_state = UI_STATE_START;
      }
    }
  }
}

////////////////////// GLOBAL FUNCTIONS /////////////////////
//--------------------------------------------------------------------------------
// Redraw the display panel when waking up from sleep
//--------------------------------------------------------------------------------
void ui_redisplay(void) {
  lv_display_trigger_activity(NULL);
  lv_screen_load(lv_screen_active());
}

//--------------------------------------------------------------------------------
// Start to play with the specified track
//--------------------------------------------------------------------------------
void ui_set_playNo(uint32_t track_id) {
  // start the specified track to play
  player.SetPlayNo(track_id);

  // update ui_control
  ui_control.playNo = ui_control.focusNo = track_id;
  display_picture(track_id);

  // update the look of the play button
  if (ui_state != UI_STATE_PLAY) {
    lv_obj_set_state(ui_ButtonPlay, LV_STATE_CHECKED, true);
    ui_state = UI_STATE_PLAY;
  }
}

//--------------------------------------------------------------------------------
// Get the latest information on MP3Player
//--------------------------------------------------------------------------------
const uint32_t ui_get_playNo(void) {
  return player.GetPlayNo();
}

const uint32_t ui_get_counts(void) {
  return player.GetCounts();
}

//--------------------------------------------------------------------------------
// Get ID3 tags (title, album, artist) from the file specified by id
//--------------------------------------------------------------------------------
void ui_get_id3tags(uint32_t track_id, MP3Tags_t &tags) {
  player.GetID3Tags(track_id, tags);
}

//--------------------------------------------------------------------------------
// Optional functions for audio-I2S (defined in CYD_Audio.h as a weak function)
// Note: These functions will be executed in the context of CORE 1.
//--------------------------------------------------------------------------------
void audio_id3data(const char *info) {
  // Avoid a race condition with ui_state set by audio_eof_mp3()
  if (ui_state == UI_STATE_PLAY) {
    char *p;
    if (p = strstr(info, "Title: ")) {
      id3tags.title = p + 7;
    } else
    if (p = strstr(info, "Artist: ")) {
      id3tags.artist = p + 8;
    } else
    if (p = strstr(info, "Album: ")) {
      id3tags.album = p + 7;
      ui_state = UI_STATE_ID3;
    }
  }
}

void audio_eof_mp3(const char *info) {
  ui_state = UI_STATE_EOF;
  if (!player.IsLastSong(ui_setting.favorite) || ui_setting.repeat) {
    nextState = UI_STATE_NEXT;
  } else {
    nextState = UI_STATE_STOP;
  }
}

//////////////////// UI STATE CONTROLLER ////////////////////
void ui_init(void) {
  ui_setting_set_backlight();
  ui_setting_set_sleeptime();
  ui_ScreenMain_screen_init();
  lv_screen_load(ui_ScreenMain);

  audioInit();
  ui_state = UI_STATE_INIT;
}

//--------------------------------------------------------------------------------
// A finite state machine that controls the overall operation
// The steady state can be either "UI_STATE_PLAY" or "UI_STATE_IDLE", 
// anything else is just a transient state that works as a command.
//--------------------------------------------------------------------------------
UI_State_t ui_loop(void) {
  switch (ui_state) {
    case UI_STATE_INIT:
      if (player.begin(MP3_ROOT_PATH, MP3_VOLUME_INI)) {
        lv_slider_set_value(ui_Volume, MP3_VOLUME_INI, LV_ANIM_OFF);
        ui_state = UI_STATE_START;
      } else {
        ui_state = UI_STATE_ERROR;
      }
      break;
    case UI_STATE_START:
      if (create_playlist()) {
        ui_state = UI_STATE_PLAY;
      } else {
        ui_state = UI_STATE_ERROR;
      }
      break;
    case UI_STATE_PLAY:
      if (!check_favorite()) {
        ui_state = UI_STATE_NEXT;
      } else if (!player.AutoPlay()) {
        ui_state = UI_STATE_ERROR;
      }
      break;
    case UI_STATE_STOP:
      play_stop();
      ui_state = UI_STATE_IDLE;
      break;
    case UI_STATE_PAUSE:
      player.PauseResume();
      ui_state = UI_STATE_IDLE;
      break;
    case UI_STATE_RESUME:
      player.PauseResume();
      ui_state = UI_STATE_PLAY;
      break;
    case UI_STATE_NEXT:
      ui_state = play_next(true)  ? UI_STATE_PLAY : UI_STATE_STOP;
      break;
    case UI_STATE_PREV:
      ui_state = play_next(false) ? UI_STATE_PLAY : UI_STATE_STOP;
      break;
    case UI_STATE_ID3:
      lv_label_set_text_fmt(ui_MusicTitle, "%s %s / %s / %s",
        LV_SYMBOL_AUDIO, id3tags.title.c_str(), id3tags.artist.c_str(), id3tags.album.c_str()
      );
      ui_state = UI_STATE_PLAY;
      break;
    case UI_STATE_EOF:
      update_metadata();
      ui_state = nextState;
      break;
    case UI_STATE_CLEAR:
      play_stop();
      player.ClearAudioFiles();
      ui_state = UI_STATE_START;
      break;
    case UI_STATE_ERROR:
      lv_label_set_text_fmt(ui_MusicTitle, "%s %s", LV_SYMBOL_WARNING, player.GetError());
      ui_state = UI_STATE_IDLE;
    case UI_STATE_IDLE:
    default:
      break;
  }

  UI_State_t ret = UI_STATE_AWAKE;

  // Periodical task
  DO_EVERY(PERIOD_TAKS1, task1Time) {
    // update elapsed time
    if (player.IsPlaying()) {
      update_elapsed_time();
    }

    // deep sleep
    if (ui_setting.selectSleepTimer) {
      if (millis() - ui_control.sleepStart > ui_control.sleepTimer) {
        ret = ui_state = UI_STATE_SLEEP; // enter deep sleep
      }
    }

    // Backlight control according to the duration of non-operation
    if (ui_setting.selectBacklight && ret == UI_STATE_AWAKE) {
      if (lv_disp_get_inactive_time(NULL) > ui_control.backlightTimer) {
        ret = UI_STATE_BLOFF; // turn backlight off
      }
    }
  }

  return ret;
}