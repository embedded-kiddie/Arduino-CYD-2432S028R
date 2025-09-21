/*--------------------------------------------------------------------------------
 * CYD_MP3Player class definition
 *--------------------------------------------------------------------------------*/
#include <ctype.h>  // isdigit(), isprint()
#include <stdlib.h> // atoi()
#include <string.h> // strcpy(), strtok_r(), strrchr()
#include <string>
#include <random>

#include "CYD_MP3Player.h"
#include "MD5.h"

/*--------------------------------------------------------------------------------
 * Begin with SD or SdFat
 *--------------------------------------------------------------------------------*/
bool CYD_MP3Player::begin(const char *root, uint8_t volume) {
  // Set root path
  m_root = root;
  if (m_root.back() != '/') {
    m_root.append("/");
  }

  // Initialize SD card
  if (!SD.begin(SD_CONFIG)) {
    m_error = "failed to mount: " + m_root;
    DBG_EXEC(printf("%s\n", m_error.c_str()));
    return false;
  }

#if   0
  // Create directories for metadata
  std::string path = m_root + META_DATA_DIR;
  if (!SD.exists(path.c_str()) && !SD.mkdir(path.c_str())) {
    m_error = "mkdir failed: " + path;
    DBG_EXEC(printf("%s\n", m_error.c_str()));
    return false;
  }
#endif

#if MY_USE_FS_ARDUINO_SD != 0
  lv_fs_arduino_sd_init(); // Arduino SD File System for image
#endif

  SetVolume(volume);
  return true;
}

/*--------------------------------------------------------------------------------
 * Get the play list for a specified track
 *--------------------------------------------------------------------------------*/
MP3File_t* CYD_MP3Player::GetPlayList(uint32_t playNo) {
  if (m_list.size()) {
    return & m_list[playNo];
  } else {
    return NULL;
  }
}

/*--------------------------------------------------------------------------------
 * Get path to the audio file
 *--------------------------------------------------------------------------------*/
std::string CYD_MP3Player::GetDirPath(uint32_t playNo) {
  MP3File_t *file = GetPlayList(playNo);
  if (file) {
    std::string path = m_tree->find_path(file->parent);
    return path.append("/");
  } else {
    return "";
  }
}

std::string CYD_MP3Player::GetFilePath(uint32_t playNo) {
  MP3File_t *file = GetPlayList(playNo);
  if (file) {
    std::string path = m_tree->find_path(file->parent);
    return path.append("/").append(file->name);
  } else {
    return "";
  }
}

/*--------------------------------------------------------------------------------
 * Generate a path to the metadata file
 *--------------------------------------------------------------------------------*/
std::string CYD_MP3Player::GetMetaPath(uint32_t playNo) {
  std::string path = GetFilePath(playNo);
  size_t pos = path.find_last_of('/') + 1;

  MD5Hex_t hex;
  MD5::make_hash(&path[pos], hex);  // Skip leading '/'
  MD5::make_digest(hex, 4);         // e.g. "12345678" (get 4 x 2 characters of string)

  // parent_path/@meta/12345678.dat
  return path.substr(0, pos) + META_DATA_DIR + hex.digest + META_DATA_EXT;
}

/*--------------------------------------------------------------------------------
 * Load/Save meta data (favorite, duration)
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::LoadMetaData(uint32_t playNo, MetaData_t *meta) {
  if (!audioIsPlaying()) {
    std::string file = GetMetaPath(playNo);
    File fd = SD.open(file.c_str(), FILE_READ);
    if (fd) {
      fd.read((uint8_t*)meta, sizeof(MetaData_t));
      fd.close();
    }
  }
}

bool CYD_MP3Player::SaveMetaData(uint32_t playNo, MetaData_t *meta) {
  if (!audioIsPlaying()) {
    std::string file = GetMetaPath(playNo);

    // check if meta directory exists
    size_t pos = file.find_last_of('/') + 1;
    std::string dir = file.substr(0, pos);

    if (!SD.exists(dir.c_str()) && !SD.mkdir(dir.c_str())) {
      m_error = "mkdir failed: " + dir;
      DBG_EXEC(printf("%s\n", m_error.c_str()));
      return false;
    }

    File fd = SD.open(file.c_str(), FILE_WRITE);
    if (fd) {
      meta->saved = meta->selected;
      fd.write((uint8_t*)meta, sizeof(MetaData_t));
      fd.close();
      return true;
    }
  }
  return false;
}

/*--------------------------------------------------------------------------------
 * Get metadata from play list and save it to a dedicated file
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::GetMetaData(uint32_t playNo, MetaData_t *meta) {
  MP3File_t *file = GetPlayList(playNo);
  if (file) {
    *meta = file->meta;
  } else {
    *meta = {}; // Never get here
  }
}

bool CYD_MP3Player::PutMetaData(uint32_t playNo, MetaData_t *meta) {
  MP3File_t *file = GetPlayList(playNo);
  if (file) {
    file->meta = *meta;
    return SaveMetaData(playNo, meta);
  }
  return false; // Never get here
}

bool CYD_MP3Player::UpdateMetaData(void) {
  bool ret = true;
  int i = 0;
  for (auto& file : m_list) {
    if (file.meta.saved != file.meta.selected) {
      ret &= SaveMetaData(i, &file.meta);
    }
    i++;
  }
  return ret;
}

/*--------------------------------------------------------------------------------
 * Scan and create a list of audio m_list in a specified directory.
 *--------------------------------------------------------------------------------*/
uint32_t CYD_MP3Player::ScanPlayList(bool shuffle) {
  if (m_tree == NULL) {
    File dir = SD.open(m_root.c_str());
    if (!dir) {
      m_error = "Can't open " + m_root;
      return 0;
    }

    m_tree = new Node(m_root.c_str());
    m_tree->scan_dir(dir);
    dir.close();
  }

  if (m_list.size() == 0) {
    scan_audio_files(m_tree);
    int i = 0;
    for (auto &list : m_list) {
      LoadMetaData(i++, &list.meta);
    }

    SortPlayList(shuffle);
  }

  if (m_list.size() == 0) {
    m_error = "No music to play";
  }

  return m_list.size();
}

/*--------------------------------------------------------------------------------
 * Clear all the nodes in tree
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::ClearPlayList(void) {
  m_list.clear();
}

/*--------------------------------------------------------------------------------
 * Sort file list
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::SortPlayList(bool shuffle) {
  if (shuffle) {
    std::mt19937 engine(esp_random());
    std::shuffle(m_list.begin(), m_list.end(), engine);
  }

  DBG_EXEC({
    m_tree->print_tree();
    print_files(m_tree);
    printf("Total: %d\n", m_list.size());
  });
}

/*--------------------------------------------------------------------------------
 * Load the picture number stored in the metadata on the SD card
 *--------------------------------------------------------------------------------*/
uint32_t CYD_MP3Player::GetPictureNo(uint32_t playNo) {
  uint32_t pictNo = 0;

  // Gets the picture number recorded in PICTURE_FILE.
  std::string path = GetDirPath(playNo);
  path.append(PICTURE_BASE "txt");

  File file = SD.open(path.c_str(), FILE_READ);
  if (file) {
#ifdef  SDFATFS_USED
    String n = "";
    while (file.available()) {
      n += file.readString();
    }
    file.close();
    if (isdigit(n[0])) {
      pictNo = atoi(n.c_str());
    }
#else // SD
    char buf[BUF_SIZE];
    file.read((uint8_t*)buf, sizeof(buf));
    file.close();
    buf[sizeof(buf) - 1] = '\0';
    if (isdigit(buf[0])) {
      pictNo = atoi(buf);
    }
#endif // SdFat or SD
  }

  return pictNo;
}

/*--------------------------------------------------------------------------------
 * Get ID3 tags (title, album, artist) from the play list
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::GetID3Tags(uint32_t playNo, ID3Tags_t &tags) {
  MP3File_t *file = GetPlayList(playNo);
  if (file) {
    tags.meta = file->meta;

    int n = 0;
    char *ptr, *token, *tmp[8], copy[BUF_SIZE];
    std::string path = GetFilePath(playNo);

    if (path.size() < sizeof(copy)) {
      strcpy(copy, path.c_str());
    } else {
      // Copy a string including the null character from the end
      strcpy(copy, path.c_str() + path.size() + 1 - sizeof(copy));
      if (!isprint(copy[0])) {
        copy[0] = ' ';
      }
    }

    token = strtok_r(copy, "/", &ptr);
    while (token != NULL && n < 8) {
      tmp[n++] = token;
      token = strtok_r(NULL, "/", &ptr);
    }

    if (--n >= 0) {
      ptr = strrchr(tmp[n], '.'); // ".mp3", ".m4a", ".wav"
      if (ptr) {
        *ptr = '\0';
      }
      if (isdigit(*tmp[n])) { // "1-01 title"
        ptr = strchr(tmp[n], ' ');
        ptr = ptr ? ptr + 1 : tmp[n];
        tags.title = ptr;
      } else {
        tags.title = tmp[n];
      }
      if (--n >= 0) {
        tags.album = tmp[n];
        if (--n >= 0) {
          tags.artist = tmp[n];
        }
      }
    }
  } else {
    tags = {}; // Never get here
  }
}

/*--------------------------------------------------------------------------------
 * Get error message
 *--------------------------------------------------------------------------------*/
const char* CYD_MP3Player::GetError(void) {
  return m_error.c_str();
}

/*--------------------------------------------------------------------------------
 * Operation
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::SetVolume(uint8_t vol) {
  audioSetVolume(vol);
}

uint8_t CYD_MP3Player::GetVolumePerCent(void) {
  return audioGetVolumePerCent();
}

bool CYD_MP3Player::IsPlaying(void) {
  return audioIsPlaying();
}

bool CYD_MP3Player::IsLastSong(bool selected) {
  const int n = m_list.size();
  if (selected) {
    for (int i = m_playNo + 1; i < n; i++) {
      MP3File_t* file = GetPlayList(i);
      if (file->meta.selected) {
        return false;
      }
    }
    return true;
  } else {
    return m_playNo == n - 1;
  }
}

bool CYD_MP3Player::FilePlay(const char* path) {
  audioStopSong();
  if (audioConnecttoSD(path)) {
    return true;
  } else {
    m_error = "Cannot play " + std::string(path);
    return false;
  }
}

void CYD_MP3Player::StopPlay(void) {
  audioStopSong();
}

void CYD_MP3Player::PauseResume(void) {
  audioPauseResume();
}

void CYD_MP3Player::SetPlayNo(uint32_t playNo, bool stop) {
  if (stop) {
    audioStopSong();
  }
  uint32_t size = m_list.size();
  if (size) {
    m_playNo = (playNo + size) % size;
  }
}

void CYD_MP3Player::PlayNext(bool stop) {
  SetPlayNo(m_playNo + 1, stop);
}

void CYD_MP3Player::PlayPrev(bool stop) {
  SetPlayNo(m_playNo - 1, stop);
}

bool CYD_MP3Player::IsSelected(void) {
  if (m_list.size()) {
    return m_list[m_playNo].meta.selected;
  } else {
    return false;
  }
}

/*--------------------------------------------------------------------------------
 * Check if the next song is selected
 *--------------------------------------------------------------------------------*/
bool CYD_MP3Player::NextSelected(bool next, bool loop, bool stop) {
  const int N = m_list.size();
  const int m = (m_playNo + (next ? 1 : -1) + N) % N;
  const int n = N - (loop ? 0 : m);

  for (int i = 0; i < n; i++) {
    int j = (m + (next ? i : -i) + N) % N;
    if (m_list[j].meta.selected) {
      SetPlayNo(j, stop);
      return true;
    }
  }

  return false;
}

bool CYD_MP3Player::AutoPlay(void) {
  if (!audioIsPlaying()) {
    std::string path = GetFilePath(m_playNo);
    if (!audioConnecttoSD(path.c_str())) {
      m_error = "Failed to play " + path;
      DBG_EXEC(printf("%s\n", m_error.c_str()));
      return false;
    }
  }
  return true;
}

/*--------------------------------------------------------------------------------
 * Optional functions for audio-I2S (defined in CYD_Audio.h as a weak function)
 *--------------------------------------------------------------------------------*/
#if   false
void audio_info(const char *info) {
  Serial.print("info        ");
  Serial.println(info);
}
void audio_id3data(const char *info) {  // id3 metadata
  Serial.print("id3tags     ");
  Serial.println(info);
}
void audio_eof_mp3(const char *info) {  // end of file
  Serial.print("eof_mp3     ");
  Serial.println(info);
}
void audio_showstation(const char *info) {
  Serial.print("station     ");
  Serial.println(info);
}
void audio_showstreamtitle(const char *info) {
  Serial.print("streamtitle ");
  Serial.println(info);
}
void audio_bitrate(const char *info) {
  Serial.print("bitrate     ");
  Serial.println(info);
}
void audio_commercial(const char *info) {  // duration in sec
  Serial.print("commercial  ");
  Serial.println(info);
}
void audio_icyurl(const char *info) {  // homepage
  Serial.print("icyurl      ");
  Serial.println(info);
}
void audio_lasthost(const char *info) {  // stream URL played
  Serial.print("lasthost    ");
  Serial.println(info);
}
#endif