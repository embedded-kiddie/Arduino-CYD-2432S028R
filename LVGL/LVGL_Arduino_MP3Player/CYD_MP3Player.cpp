/*--------------------------------------------------------------------------------
 * CYD_MP3Player class definition
 *--------------------------------------------------------------------------------*/
#include "CYD_MP3Player.h"
#include "sdfs.h"
#include "MD5.h"

/*--------------------------------------------------------------------------------
 * Begin with SD or SdFat
 *--------------------------------------------------------------------------------*/
bool CYD_MP3Player::begin(const char *root, uint8_t volume) {
  // set root path
  m_root = root;
  if (m_root.back() != '/') {
    m_root += "/";
  }
  
  // initialize SD card
  if (!SD.begin(FS_CONFIG)) {
    m_error = "failed to mount: " + m_root;
    return false;
  }

  // create directories for metadata
  std::string path = m_root + META_DATA_DIR;
  if (!SD.exists(path.c_str())) {
    if (!SD.mkdir(path.c_str())) {
      m_error = "mkdir failed: " + path;
      return false;
    }
  }

  const char* dirs[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f" };
  for (int i = 0; i < sizeof(dirs) / sizeof(char*); i++) {
    path = m_root + META_DATA_DIR + dirs[i];
    if (!SD.exists(path.c_str())) {
      if (!SD.mkdir(path.c_str())) {
      m_error = "mkdir failed: " + path;
        return false;
      }
    }
  }

  SetVolume(volume);

#if MY_USE_FS_ARDUINO_SD != 0
  // Arduino SD File System for image
  lv_fs_arduino_sd_init();
#endif

  return true;
}

/*--------------------------------------------------------------------------------
 * Verify file extension. (mp3, m4a, aac, wav, flac, opus, ogg, oga)
 *--------------------------------------------------------------------------------*/
bool CYD_MP3Player::CheckExtension(const char *path) {
  const char* ext[] = {".mp3", ".m4a", ".wav"};
  for (int i = 0; i < sizeof(ext) / sizeof(ext[0]); i++) {
    if (strcmp(&path[strlen(path) - strlen(ext[i])], ext[i]) == 0) {
      return true;
    }
  }
  return false;
}

/*--------------------------------------------------------------------------------
 * Generate a path to the metadata file
 *--------------------------------------------------------------------------------*/
const char* CYD_MP3Player::MetaDataPath(const char *path) {
  MD5Hex_t hex;
  MD5::make_hash(&path[strlen(MP3_PATH_ROOT)], hex);
  MD5::make_digest(hex, 5); // e.g. "0123456789" (get 5 x 2 characters of string)
  hex.digest[1] = '/';      // e.g. "0/23456789"

  static std::string file;
  file = m_root + META_DATA_DIR + hex.digest + META_DATA_EXT;
  return file.c_str();
}

/*--------------------------------------------------------------------------------
 * Load/Save meta data (favorite, duration)
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::LoadMetaData(const char *path, MetaData_t *meta) {
  if (!audioIsPlaying()) {
    const char *file = MetaDataPath(path);
    File fd = SD.open(file, FILE_READ);
    if (fd) {
      fd.read((uint8_t*)meta, sizeof(MetaData_t));
      fd.close();
    }
  }
}

bool CYD_MP3Player::SaveMetaData(const char *path, MetaData_t *meta) {
  if (!audioIsPlaying()) {
    const char *file = MetaDataPath(path);
    File fd = SD.open(file, FILE_WRITE);
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
 * Get the playlist for a specified track
 *--------------------------------------------------------------------------------*/
PlayList_t* CYD_MP3Player::GetPlayList(uint32_t playNo) {
  if (m_files.size()) {
    return & m_files[playNo];
  } else {
    return NULL;
  }
}

/*--------------------------------------------------------------------------------
 * Scan and create a list of audio m_files in a specified directory.
 *--------------------------------------------------------------------------------*/
bool CYD_MP3Player::ScanFileList(const char *dirname, uint8_t levels) {
  File root = m_fs.open(dirname);
  if (!root) {
    m_error = std::string("Failed to open ") + dirname;
    return false;
  }

  if (!root.isDirectory()) {
    m_error = dirname + std::string("is not a directory.");
    return false;
  }

  File file = root.openNextFile();
  while (file) {
    bool isDir = file.isDirectory();

    // skip dot file
#ifdef SDFATFS_USED
    char name[BUF_SIZE];
    file.getName(name, sizeof(name));
    std::string path = std::string(dirname);
    path += (path.at(path.size() - 1) == '/' ? "" : "/") + std::string(name);
    if (file.isHidden()) {
      // Serial.printf("%s is skipped.\n", name);
    }
#else
    const char *p = strrchr(file.path(), '/');
    if (p[p ? 1 : 0] == '.') {
      // Serial.printf("%s is skipped.\n", file.path());
    }
#endif

    else if (isDir && levels) {
#ifdef SDFATFS_USED
      ScanFileList(path.c_str(), levels - 1);
#else
      ScanFileList(file.path(), levels - 1);
#endif
    }

    else if (!isDir) {
      try {
#ifdef SDFATFS_USED
        if (CheckExtension(path.c_str())) {
          MetaData_t meta = {};
          LoadMetaData(path.c_str(), &meta);
          m_files.push_back({meta, path});
        }
#else
        if (CheckExtension(file.path())) {
          MetaData_t meta = {};
          LoadMetaData(file.path(), &meta);
          m_files.push_back({meta, file.path()});
        }
#endif
      } catch (const std::exception &e) {
        m_error = std::string("Exception: ") + e.what();
        return false;
      }
    }

    file = root.openNextFile();
  }

  return (m_error == "");
}

uint32_t CYD_MP3Player::ScanFileList(uint8_t levels, bool shuffle) {
  if (ScanFileList(m_root.c_str(), levels)) {
    return SortFileList(shuffle);
  } else {
    return false;
  }
}

/*--------------------------------------------------------------------------------
 * Sort file list
 *--------------------------------------------------------------------------------*/
uint32_t CYD_MP3Player::SortFileList(bool shuffle) {
  if (shuffle) {
    std::mt19937 engine(esp_random());
    std::shuffle(m_files.begin(), m_files.end(), engine);
  } else {
    std::sort(m_files.begin(), m_files.end(), [](PlayList_t &a, PlayList_t &b) {
      return a.path.compare(b.path) < 0 ? true : false; // ascending order
    });
  }

  for (auto& file : m_files) {
    Serial.printf("%d/%d, %2d, %3d, %s\n", file.meta.saved, file.meta.selected, file.meta.pictureNo, file.meta.duration, file.path.c_str());
  }
  Serial.printf("Total: %d\n", m_files.size());
  return m_files.size();
}

/*--------------------------------------------------------------------------------
 * Load the picture number stored in the metadata on the SD card
 *--------------------------------------------------------------------------------*/
uint32_t CYD_MP3Player::GetPictureNo(uint32_t playNo) {
  uint32_t pictNo = 0;
  char buf[BUF_SIZE], *ptr;

  // gets the picture number recorded in PICTURE_FILE.
  GetFilePath(playNo, buf, sizeof(buf));
  if (ptr = strrchr(buf, '/')) {
    strcpy(ptr + 1, PICTURE_FILE);

    if (SD.exists(buf)) {
      File file = SD.open(buf, FILE_READ);

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
        file.read((uint8_t*)buf, sizeof(buf));
        file.close();
        buf[sizeof(buf) - 1] = '\0';
        if (isdigit(buf[0])) {
          pictNo = atoi(buf);
        }
#endif // SdFat or SD
      }
    }
  }

  return pictNo;
}

/*--------------------------------------------------------------------------------
 * Gets the path to a specified track
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::GetFilePath(uint32_t playNo, char *buf, int len) {
  PlayList_t *list = GetPlayList(playNo);
  if (list) {
    strncpy(buf, list->path.c_str(), len);
    buf[len - 1] = '\0';
  } else {
    *buf = '\0';
  }
}

/*--------------------------------------------------------------------------------
 * Get ID3 tags (title, album, artist) from the playlist
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::GetID3Tags(uint32_t playNo, ID3Tags_t &tags) {
  PlayList_t *list = GetPlayList(playNo);
  if (list) {
    tags.meta = list->meta;

    int n = 0;
    char *ptr, *token, *tmp[8], copy[BUF_SIZE];
    const char *path = list->path.c_str();

    if (strlen(path) < sizeof(copy)) {
      strcpy(copy, path);
    } else {
      // Copy a string including the null character from the end
      strcpy(copy, path + strlen(path) + 1 - sizeof(copy));
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
    tags = {}; // never reach this line
  }
}

/*--------------------------------------------------------------------------------
 * Get metadata from playlists and save it to a dedicated file
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::GetMetaData(uint32_t playNo, MetaData_t *meta) {
  PlayList_t *list = GetPlayList(playNo);
  if (list) {
    *meta = list->meta;
  } else {
    *meta = {}; // never reach this line
  }
}

bool CYD_MP3Player::PutMetaData(uint32_t playNo, MetaData_t *meta) {
  PlayList_t *list = GetPlayList(playNo);
  if (list) {
    list->meta = *meta;
    return SaveMetaData(list->path.c_str(), meta);
  }
  return false; // never reach this line
}

bool CYD_MP3Player::UpdateMetaData(void) {
  bool ret = true;
  for (auto& file : m_files) {
    if (file.meta.saved != file.meta.selected) {
      ret &= SaveMetaData(file.path.c_str(), &file.meta);
    }
  }
  return ret;
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

bool CYD_MP3Player::IsLastSong(void) {
  return m_playNo == m_files.size() - 1;
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
  uint32_t size = m_files.size();
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
  if (m_files.size()) {
    return m_files[m_playNo].meta.selected;
  } else {
    return false;
  }
}

/*--------------------------------------------------------------------------------
 * Check if the next song is selected
 *--------------------------------------------------------------------------------*/
bool CYD_MP3Player::NextSelected(bool next, bool loop, bool stop) {
  const int N = m_files.size();
  const int m = (m_playNo + (next ? 1 : -1) + N) % N;
  const int n = N - (loop ? 0 : m);

  for (int i = 0; i < n; i++) {
    int j = (m + (next ? i : -i) + N) % N;
    if (m_files[j].meta.selected) {
      SetPlayNo(j, stop);
      return true;
    }
  }

  return false;
}

bool CYD_MP3Player::AutoPlay(void) {
  if (!audioIsPlaying() && m_files.size()) {
    if (!audioConnecttoSD(m_files[m_playNo].path.c_str())) {
      m_error = "Failed to play " + m_files[m_playNo].path;
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
void audio_id3data(const char *info) {  //id3 metadata
  Serial.print("id3tags     ");
  Serial.println(info);
}
void audio_eof_mp3(const char *info) {  //end of file
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
void audio_commercial(const char *info) {  //duration in sec
  Serial.print("commercial  ");
  Serial.println(info);
}
void audio_icyurl(const char *info) {  //homepage
  Serial.print("icyurl      ");
  Serial.println(info);
}
void audio_lasthost(const char *info) {  //stream URL played
  Serial.print("lasthost    ");
  Serial.println(info);
}
#endif