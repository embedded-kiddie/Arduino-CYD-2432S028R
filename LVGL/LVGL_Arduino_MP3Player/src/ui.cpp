//================================================================================
// MP3 Music Player for CYD - User Interface
// LVGL version: 9.2.2 and up
//================================================================================
#include "ui.h"
#include "peripherals.h"
#include <string.h> // for strncpy(), strrchr()

////////////////////// GLOBAL VARIABLES /////////////////////
UI_State_t ui_state;
UI_Option_t ui_option = { .shuffle = true, .selectBacklight = 1 };
UI_Control_t ui_control;

////////////////////// LOCAL VARIABLES //////////////////////
#include "../CYD_MP3Player.h"
static CYD_MP3Player player;

static bool saveID3tags;
static ID3Tags_t id3tags;
static UI_State_t nextState;

////////////////////////// UI LOOP //////////////////////////
// https://embedded-kiddie.github.io/2024/07/22/
#define DO_EVERY(period, prev) \
static uint32_t prev = 0; for (uint32_t now = millis(); now - prev >= period; prev = now)

#define PERIOD_TAKS1 1000 // [msec]
#define PERIOD_TAKS2 100  // [msec]

/////////////////////////// STYLES //////////////////////////
static constexpr lv_style_const_prop_t style_prop_picture[] = {
  LV_STYLE_CONST_SHADOW_WIDTH(10),
  LV_STYLE_CONST_SHADOW_OFFSET_Y(5),
  LV_STYLE_CONST_SHADOW_OPA(LV_OPA_40),
  LV_STYLE_CONST_PROPS_END
};
static LV_STYLE_CONST_INIT(style_picture, (void*)style_prop_picture);

/////////////////////////// IMAGES //////////////////////////
#if (LV_USE_FS_ARDUINO_SD == 0) && (MY_USE_FS_ARDUINO_SD == 0)
#include "_pictures.h"
#endif

////////////////////// HELPER FUNCTION //////////////////////
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
    change_screen(&ui_ScreenOptions, anim, &ui_ScreenOptions_screen_init);
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

void ui_event_GoToOptions(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  change_screen(&ui_ScreenOptions, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, &ui_ScreenOptions_screen_init);
}

void ui_event_Favorite(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  lv_obj_t *obj = lv_event_get_target_obj(e);
  ui_option.favorite = (lv_obj_get_state(obj) & LV_STATE_CHECKED ? true : false);
}

void ui_event_Repeat(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  lv_obj_t *obj = lv_event_get_target_obj(e);
  ui_option.repeat = (uint8_t)(lv_obj_get_state(obj) & LV_STATE_CHECKED ? true : false);
}

void ui_event_Shuffle(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  lv_obj_t *obj = lv_event_get_target_obj(e);
  ui_option.shuffle = (lv_obj_get_state(obj) & LV_STATE_CHECKED ? true : false);
}

void ui_event_ButtonPlay(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  lv_state_t state = lv_obj_get_state(ui_ButtonPlay);
  ui_state = (state & LV_STATE_CHECKED ? UI_STATE_RESUME : UI_STATE_PAUSE);
}

void ui_event_ButtonNext(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  ui_state = UI_STATE_NEXT;
  bitSet(ui_option.repeat, 7); // force to set the bit temporarily
}

void ui_event_ButtonPrev(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

  ui_state = UI_STATE_PREV;
  bitSet(ui_option.repeat, 7); // force to set the bit temporarily
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
    uint32_t elapsed = lv_slider_get_value(ui_ElapsedBar);
    audioSetElapsedTime(elapsed);
  }
}

//--------------------------------------------------------------------------------
// Event handlers for Screen Option
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
    lv_screen_load_anim_t anim = (dir == LV_DIR_RIGHT ? LV_SCR_LOAD_ANIM_MOVE_RIGHT : LV_SCR_LOAD_ANIM_MOVE_LEFT);
    change_screen(&ui_ScreenMain, anim, &ui_ScreenMain_screen_init);
  }

  else if (event_code == LV_EVENT_SCREEN_LOADED) {
    // increase free memory
    // lv_fs_clear_cache(); // sdfs.{h|cpp}

    // stop playing to avoid conflict with image loading
    if (ui_state != UI_STATE_IDLE) {
      lv_obj_set_state(ui_ButtonPlay, LV_STATE_CHECKED, false);
      ui_state = UI_STATE_PAUSE;
    }

    ui_ScreenAlbumList_create_list((void*)player.m_tree);
  }

  else if (event_code == LV_EVENT_SCREEN_UNLOADED) {
    // Make album list and playlist clean
    ui_ScreenAlbumList_screen_deinit();
    player.ClearAudioFiles();

    lv_obj_set_state(ui_ButtonPlay, LV_STATE_CHECKED, true);
    ui_state = UI_STATE_START;
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

  MetaData_t meta;
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
    saveID3tags = true;
  }
}

//--------------------------------------------------------------------------------
// Event handlers for Screen Options
//--------------------------------------------------------------------------------
void ui_event_ScreenOptions(lv_event_t *e) {
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
    ui_ScreenOptions_screen_deinit();
  }
}

/////////////////// LOCAL FUNCTIONS //////////////////
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
  MetaData_t meta;
  uint32_t playNo = player.GetPlayNo();
  player.GetMetaData(playNo, &meta);

  if (meta.duration < id3tags.meta.duration || saveID3tags == true) {
    // prevent input while saving metadata to SD card
    lv_indev_enable(NULL, false);

    if (player.IsPlaying()) {
      player.PauseResume();
    }

    // update all Favorites that have been modified during playback
    if (saveID3tags == true) {
      if (player.UpdateMetaData()) {
        saveID3tags = false;
      }
    }

    bool update = false;

    // update the playback duration at the end of file
    if (meta.duration < id3tags.meta.duration) {
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
// Display a covoer picture on SD or flash
//--------------------------------------------------------------------------------
static void display_picture(uint32_t playNo) {
#if (LV_USE_FS_ARDUINO_SD != 0) || (MY_USE_FS_ARDUINO_SD != 0)

  // displaying an image file on SD card
  char buf[BUF_SIZE], *ptr;
  buf[0] = MY_FS_ARDUINO_SD_LETTER;
  buf[1] = ':';

  // skip drive letter "S:"
  std::string dir = player.GetFilePath(playNo);
  strncpy(&buf[2], dir.c_str(), sizeof(buf) - 2);
  buf[sizeof(buf) - 1] = '\0';

  // title.[bmp|jpg]
  if (ptr = strrchr(buf, '.')) {
    strcpy(ptr + 1, PICTURE_EXT);
    if (SD.exists(buf + 2)) {
      lv_image_set_src(ui_AlbumImage, buf);
      lv_obj_add_style(ui_AlbumImage, &style_picture, 0);
      return;
    }
  }

  // @picture.[bmp|jpg]
  if (ptr = strrchr(buf, '/')) {
    strcpy(ptr + 1, PICTURE_BASE PICTURE_EXT);
    if (SD.exists(buf + 2)) {
      lv_image_set_src(ui_AlbumImage, buf);
      lv_obj_add_style(ui_AlbumImage, &style_picture, 0);
      return;
    }
  }

  lv_image_set_src    (ui_AlbumImage, &img_album);
  lv_obj_remove_style (ui_AlbumImage, &style_picture, 0);

#else // MY_USE_FS_ARDUINO_SD == 0

  // displaying an image file on flash ROM
  int pictNo = player.GetPictureNo(playNo);

  if (0 < pictNo && pictNo < N_PICTURES) {
    lv_image_set_src(ui_AlbumImage, pictures[pictNo]);
    lv_obj_add_style(ui_AlbumImage, &style_picture, 0);
  } else {
    lv_image_set_src    (ui_AlbumImage, &img_album);
    lv_obj_remove_style (ui_AlbumImage, &style_picture, 0);
  }

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
  if (ui_option.favorite) {
    ret = player.NextSelected(next, (ui_option.repeat ? true : false));
  } else {
    if (next) {
      player.PlayNext();
    } else {
      player.PlayPrev();
    }
  }

  bitClear(ui_option.repeat, 7); // clear the bit that has been temporarily forced set

  ui_control.playNo = ui_control.focusNo = player.GetPlayNo();
  display_picture(ui_control.playNo);

  // update ui_control and look of the play button
  lv_obj_set_state(ui_ButtonPlay, LV_STATE_CHECKED, true);

  if (ui_ScreenPlayList) {
    ui_list_update_play(ui_control.playNo, true);
  }

  return ret;
}

//--------------------------------------------------------------------------------
// Check out the favorite playlists
//--------------------------------------------------------------------------------
static bool check_favorite(void) {
  return !ui_option.favorite || player.IsPlaying() || player.IsSelected();
}

////////////////// GLOBAL FUNCTIONS /////////////////
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
void ui_get_id3tags(uint32_t track_id, ID3Tags_t &tags) {
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
  if (!player.IsLastSong(ui_option.favorite) || ui_option.repeat) {
    nextState = UI_STATE_NEXT;
  } else {
    nextState = UI_STATE_STOP;
  }
}

//--------------------------------------------------------------------------------
// Load / Save options in SD
//--------------------------------------------------------------------------------
void ui_load_options(void) {
  ui_set_option_backlight();
  ui_set_option_sleeptime();
}

void ui_save_options(void) {
}

///////////////////// SCREENS ////////////////////
void ui_init(void) {
  ui_load_options();
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
      if (player.begin(MP3_PATH_ROOT, MP3_VOLUME_INI)) {
        lv_slider_set_value(ui_Volume, MP3_VOLUME_INI, LV_ANIM_OFF);
        ui_state = UI_STATE_START;
      } else {
        ui_state = UI_STATE_ERROR;
      }
      break;
    case UI_STATE_START:
      if (player.ScanPlayList(ui_option.shuffle)) {
        ui_set_playNo(ui_control.playNo);
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
      lv_obj_set_state(ui_ButtonPlay, LV_STATE_CHECKED, false);
      // no break
    case UI_STATE_PAUSE:
      player.PauseResume();
      ui_state = UI_STATE_IDLE;
      break;
    case UI_STATE_RESUME:
      player.PauseResume();
      ui_state = UI_STATE_PLAY;
      break;
    case UI_STATE_NEXT:
      if (play_next(true)) {
        ui_state = UI_STATE_PLAY;
      } else {
        ui_state = UI_STATE_STOP;
      }
      break;
    case UI_STATE_PREV:
      if (play_next(false)) {
        ui_state = UI_STATE_PLAY;
      } else {
        ui_state = UI_STATE_STOP;
      }
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
    case UI_STATE_SLEEP:
      shutdown_peripherals();
      esp_deep_sleep_start();
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
    if (ui_option.selectSleepTimer) {
      if (millis() - ui_control.sleepStart > ui_control.sleepTimer) {
        ret = ui_state = UI_STATE_SLEEP; // enter deep sleep
      }
    }

    // Backlight control according to the duration of non-operation
    if (ui_option.selectBacklight && ret == UI_STATE_AWAKE) {
      if (lv_disp_get_inactive_time(NULL) > ui_control.backlightTimer) {
        ret = UI_STATE_BLOFF; // turn backlight off
      }
    }
  }

  return ret;
}