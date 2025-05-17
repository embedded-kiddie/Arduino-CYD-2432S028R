/*--------------------------------------------------------------------------------
 * CYD_MP3Player class definition
 *--------------------------------------------------------------------------------*/
#include "CYD_MP3Player.h"

static ID3Tags_t* id3data_ptr = NULL;
static void (*id3data_callback)(ID3Tags_t*) = NULL;

/*--------------------------------------------------------------------------------
 * Begin with SD or SdFat
 *--------------------------------------------------------------------------------*/
bool CYD_MP3Player::begin() {
  if (FS_DEV.begin(FS_CONFIG)) {
    return true;
  } else {
    Serial.println("Failed to mount the file system.");
    return false;
  }
}

/*--------------------------------------------------------------------------------
 * Verify file extension. (mp3, m4a, aac, wav, flac, opus, ogg, oga)
 *--------------------------------------------------------------------------------*/
bool CYD_MP3Player::CheckExtension(const char* path) {
  const char* ext[] = {".mp3", ".m4a", ".wav"};
  for (int i = 0; i < sizeof(ext) / sizeof(ext[0]); i++) {
    if (strcmp(&path[strlen(path) - strlen(ext[i])], ext[i]) == 0) {
      return true;
    }
  }
  return false;
}

/*--------------------------------------------------------------------------------
 * Get file information with ID3 tags (title, album, artist)
 *--------------------------------------------------------------------------------*/
ID3Tags_t CYD_MP3Player::GetID3Tags(std::string path) {
  int n = 0;
  char *ptr, *token, *tmp[8], copy[256];
  ID3Tags_t tags = m_empty;

  if (path.size() < sizeof(copy)) {
    strcpy(copy, path.c_str());
  } else {
    // Copy a string including the null character from the end
    strcpy(copy, path.c_str() + path.size() + 1 - sizeof(copy));
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
      tags.title = std::string(ptr);
    } else {
      tags.title = std::string(tmp[n]);
    }
    if (--n >= 0) {
      tags.album = std::string(tmp[n]);
      if (--n >= 0) {
        tags.artist = std::string(tmp[n]);
      }
    }
  }

  return tags;
}

/*--------------------------------------------------------------------------------
 * Scan and create a list of audio m_files in a specified directory.
 *--------------------------------------------------------------------------------*/
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
          m_files.push_back({path});
        }
#else
        if (CheckExtension(file.path())) {
          m_files.push_back({file.path()});
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

#if   true
  ID3Tags_t tags;
  for (auto& file : m_files) {
    tags = GetID3Tags(file.path);
    Serial.printf("title: %s, album: %s, artist: %s\n", tags.title.c_str(), tags.album.c_str(), tags.artist.c_str());
  }
  Serial.printf("total: %d\n", m_files.size());
#endif
}

/*--------------------------------------------------------------------------------
 * Operation
 *--------------------------------------------------------------------------------*/
uint8_t CYD_MP3Player::GetVolumePerCent(void) {
  return audioGetVolumePerCent();
}

void CYD_MP3Player::SetVolume(uint8_t vol) {
  audioSetVolume(vol);
}

void CYD_MP3Player::PauseResume(void) {
  audioPauseResume();
}

void CYD_MP3Player::StopPlay(void) {
  audioStopSong();
}

void CYD_MP3Player::SetPlayNo(int playNo) {
  audioStopSong();
  m_playNo = playNo;
}

void CYD_MP3Player::PlayNext(void) {
  audioStopSong();
}

void CYD_MP3Player::PlayPrev(void) {
  SetPlayNo((m_playNo - 2 + m_files.size()) % m_files.size());
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

bool CYD_MP3Player::IsPlaying(void) {
  return audioIsPlaying();
}

void CYD_MP3Player::SetIDd3TagsCallback(void (*callback)(ID3Tags_t*), ID3Tags_t* ptr) {
  id3data_callback = callback;
  id3data_ptr = ptr;
}

bool CYD_MP3Player::AutoPlay(bool selected) {
  if (!audioIsPlaying() && m_files.size()) {
    // Play all or only selected
    bool play = !selected || m_files[m_playNo].selected;

    if (play && !audioConnecttoSD(m_files[m_playNo].path.c_str())) {
      // Something is wrong, so skip it
      Serial.printf("skip %s\n", m_files[m_playNo].path.c_str());
      play = false;
    } else {
      play = true;
    }

    // Update for the next play
    m_playNo = (m_playNo + 1) % m_files.size();
    return play;
  }

  return true;
}

/*--------------------------------------------------------------------------------
 * Optional functions for audio-I2S
 *--------------------------------------------------------------------------------*/
void audio_id3data(const char *info) {  //id3 metadata
  if (id3data_callback && id3data_ptr) {
    char *p;
    if (p = strstr(info, "Title: ")) {
      id3data_ptr->title = p + 7;
    } else
    if (p = strstr(info, "Artist: ")) {
      id3data_ptr->artist = p + 8;
    } else
    if (p = strstr(info, "Album: ")) {
      id3data_ptr->album = p + 7;
      id3data_callback(id3data_ptr);
    }
  }
//Serial.print("id3data     ");
//Serial.println(info);
}
#if   false
void audio_info(const char *info) {
  Serial.print("info        ");
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