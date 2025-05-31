/*--------------------------------------------------------------------------------
 * CYD_MP3Player class definition
 *--------------------------------------------------------------------------------*/
#include "CYD_MP3Player.h"
#include "MD5.h"

/*--------------------------------------------------------------------------------
 * Begin with SD or SdFat
 *--------------------------------------------------------------------------------*/
bool CYD_MP3Player::begin(const char *root) {
  // set root path
  m_root = root;
  if (m_root.back() != '/') {
    m_root += "/";
  }

  // initialize SD card
  if (!FS_DEV.begin(FS_CONFIG)) {
    Serial.println("Failed to mount the file system.");
    return false;
  }

  // create directories for metadata
  std::string path = m_root + META_DATA_DIR;
  if (!FS_DEV.exists(path.c_str())) {
    if (!FS_DEV.mkdir(path.c_str())) {
      Serial.printf("mkdir %s failes\n", path.c_str());
      return false;
    }
  }

  constexpr char* dirs[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"};
  for (int i = 0; i < sizeof(dirs) / sizeof(char*); i++) {
    path = m_root + META_DATA_DIR + dirs[i];
    if (!FS_DEV.exists(path.c_str())) {
      if (!FS_DEV.mkdir(path.c_str())) {
        Serial.printf("mkdir %s failes\n", path.c_str());
        return false;
      }
    }
  }

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
  MD5::make_hash(path, hex);
  MD5::make_digest(hex, 5); // get 5 x 2 characters of string

  hex.digest[1] = '/';
  static std::string file = m_root + META_DATA_DIR + hex.digest + META_DATA_EXT;
  return file.c_str();
}

/*--------------------------------------------------------------------------------
 * Load/Save meta data (favorite, duration)
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::LoadMetaData(const char *path, MetaData_t *meta) {
  if (!audioIsPlaying()) {
    const char *file = MetaDataPath(path);
    File fd = FS_DEV.open(file, O_READ);
    if (fd) {
      fd.read((void*)meta, sizeof(MetaData_t));
      fd.close();
    }
  }
  *meta = {};
}

bool CYD_MP3Player::SaveMetaData(const char *path, MetaData_t *meta) {
  if (!audioIsPlaying()) {
    const char *file = MetaDataPath(path);
    File fd = FS_DEV.open(file, O_RDWR | O_CREAT | O_TRUNC);
    if (fd) {
      fd.write((void*)meta, sizeof(MetaData_t));
      fd.close();
      return true;
    }
  }
  return false;
}

/*--------------------------------------------------------------------------------
 * Get the playlist for the specified track
 *--------------------------------------------------------------------------------*/
PlayList_t* CYD_MP3Player::GetPlayList(uint32_t playNo) {
  if (m_files.size()) {
    return &m_files[playNo];
  } else {
    return NULL;
  }
}

/*--------------------------------------------------------------------------------
 * Scan and create a list of audio m_files in a specified directory.
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::ScanFileList(uint8_t levels) {
  ScanFileList(m_root.c_str(), levels);
}

void CYD_MP3Player::ScanFileList(const char *dirname, uint8_t levels) {
  File root = m_fs.open(dirname);
  if (!root) {
    Serial.printf("Failed to open %s.\n", dirname);
    return;
  }
  if (!root.isDirectory()) {
    Serial.printf("Not a directory.\n");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    // Serial.printf("%s\n", file.path());
    bool isDir = file.isDirectory();

    // skip dot file
#ifdef SDFATFS_USED
    char name[FS_BUF_SIZE];
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
          MetaData_t meta;
          LoadMetaData(path.c_str(), &meta);
          m_files.push_back({meta, path});
        }
#else
        if (CheckExtension(file.path())) {
          MetaData_t meta;
          LoadMetaData(file.path(), &meta);
          m_files.push_back({meta, file.path()});
        }
#endif
      } catch (const std::exception &e) {
        Serial.printf("Exception: %s\n", e.what());
        return;
      }
    }

    file = root.openNextFile();
  }
}

/*--------------------------------------------------------------------------------
 * Sort file list
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::SortFileList(bool shuffle) {
  if (shuffle) {
    std::mt19937 engine(esp_random());
    std::shuffle(m_files.begin(), m_files.end(), engine);
  } else {
    std::sort(m_files.begin(), m_files.end(), [](PlayList_t &a, PlayList_t &b) {
      return a.path.compare(b.path) > 0 ? true : false;
    });
  }

  for (auto& file : m_files) {
    Serial.println(file.path.c_str());
  }
  Serial.printf("Total: %d\n", m_files.size());
}

/*--------------------------------------------------------------------------------
 * Get/Put ID3 tags (title, album, artist) from the file specified by id
 *--------------------------------------------------------------------------------*/
void CYD_MP3Player::GetID3Tags(uint32_t playNo, ID3Tags_t &tags) {
  PlayList_t *list = GetPlayList(playNo);
  if (list) {
    char *ptr, *token, *tmp[8], copy[FS_BUF_SIZE];
    const char *path = list->path.c_str();

    tags.meta = list->meta;

    if (strlen(path) < sizeof(copy)) {
      strcpy(copy, path);
    } else {
      // Copy a string including the null character from the end
      strcpy(copy, path + strlen(path) + 1 - sizeof(copy));
    }

    int n = 0;
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
    tags = {};
  }
}

void CYD_MP3Player::PutID3Tags(uint32_t playNo, ID3Tags_t &tags) {
  PlayList_t *list = GetPlayList(playNo);
  if (list) {
    const char *path = list->path.c_str();
    MetaData_t *meta = &tags.meta;
    SaveMetaData(path, meta);
  }
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
    Serial.printf("Cannot play %s\n", path);
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

bool CYD_MP3Player::AutoPlay(bool selectedOnly) {
  if (!audioIsPlaying() && m_files.size()) {
    // Play all or selected only
    bool play = (!selectedOnly || m_files[m_playNo].meta.selected);
    if (play && !audioConnecttoSD(m_files[m_playNo].path.c_str())) {
      Serial.printf("skip: %s\n", m_files[m_playNo].path.c_str()); // Something is wrong, so skip it
      return false;
    } else {
      return true;
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