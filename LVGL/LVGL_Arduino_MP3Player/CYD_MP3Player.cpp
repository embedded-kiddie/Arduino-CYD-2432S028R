//================================================================================
// CYD_MP3Player class definition
//================================================================================
#include "CYD28_audio.h"
#include "CYD_MP3Player.h"

#include <ctype.h>    // isdigit(), isprint()
#include <stdlib.h>   // atoi()
#include <string.h>   // strncpy(), strtok_r(), strrchr()
#include <string>     // std::string
#include <random>     // std::mt19937
#include <algorithm>  // std::shuffle, std::sort
#include <functional> // std::hash

//--------------------------------------------------------------------------------
// Begin with SD or SdFat
//--------------------------------------------------------------------------------
bool CYD_MP3Player::begin(const char *root, uint8_t volume) {
  // Set root path
  m_base = root;
  if (m_base.back() != '/') {
    m_base.append("/");
  }

  m_root = m_base; // mainly m_root is used

  // Initialize SD card
  if (!SD.begin(SD_CONFIG)) {
    m_error = "failed to mount: " + m_root;
    DBG_EXEC(printf("%s\n", m_error.c_str()));
    return false;
  }

#if MY_USE_FS_ARDUINO_SD
  // LVGL SD File System for displaying cover pictures
  lv_fs_arduino_sd_init();
#endif

  SetVolume(volume);
  return true;
}

//--------------------------------------------------------------------------------
// Get the play list for a specified track
//--------------------------------------------------------------------------------
MP3List_t* CYD_MP3Player::GetPlayList(uint32_t playNo) {
  if (m_list.size()) {
    return & m_list[playNo];
  } else {
    return NULL;
  }
}

//--------------------------------------------------------------------------------
// Get path to the audio file
//--------------------------------------------------------------------------------
std::string CYD_MP3Player::GetDirPath(uint32_t playNo) {
  MP3List_t *list = GetPlayList(playNo);
  if (list) {
    return m_tree->find_path(list->parent) + "/";
  } else {
    return "";
  }
}

std::string CYD_MP3Player::GetFilePath(uint32_t playNo) {
  MP3List_t *list = GetPlayList(playNo);
  if (list) {
    return m_tree->find_path(list->parent) + "/" + list->name;
  } else {
    return "";
  }
}

bool CYD_MP3Player::SaveMetaData(uint32_t playNo, MetaData_t *meta) {
  if (audioIsPlaying()) {
    return false;
  }

  MP3List_t *list = GetPlayList(playNo); // Never NULL
  std::string path = m_tree->find_path(list->parent);
  std::string data = path + "/" ALBUM_META_FILE;

  File fd = SD.open(data.c_str(), FILE_READ);
  if (fd) {
    const size_t size = fd.SDFS_SIZE();
    const size_t n = size / sizeof(MetaHash_t);
    MetaHash_t *album = new MetaHash_t[n];
    if (!album) {
      fd.close();
      return false;
    }

    fd.read((SDFS_VOID*)album, size);
    fd.close();

    // Functional object to make a hash
    std::hash<std::string> MakeHash;

    // Search for meta data with matching hash
    size_t hash = MakeHash(list->name);
    for (int i = 0; i < n; i++) {
      if (hash == album[i].hash) {
        meta->saved = meta->selected; // Mark 'selected' as saved
        album[i].meta = *meta;
        break;
      }
    }

    fd = SD.open(data.c_str(), FILE_WRITE);
    if (fd) {
      fd.seek(0);
      fd.write((SDFS_VOID*)album, size); // should check return value!
      fd.close();
    }

    DBG_EXEC(printf("SaveMetaData: %s\n", list->name.c_str()));

    delete[] album;
    return true;
  }

  return false;
}

//--------------------------------------------------------------------------------
// Get metadata from play list and save it to a dedicated file
//--------------------------------------------------------------------------------
void CYD_MP3Player::GetMetaData(uint32_t playNo, MetaData_t *meta) {
  MP3List_t *list = GetPlayList(playNo);
  if (list) {
    *meta = list->meta;
  } else {
    *meta = {}; // Never get here
  }
}

bool CYD_MP3Player::PutMetaData(uint32_t playNo, MetaData_t *meta) {
  MP3List_t *list = GetPlayList(playNo);
  if (list) {
    list->meta = *meta;
    return SaveMetaData(playNo, meta);
  }
  return false; // Never get here
}

bool CYD_MP3Player::UpdateMetaData(void) {
  bool ret = true;
  int i = 0;
  for (auto& list : m_list) {
    if (list.meta.saved != list.meta.selected) {
      ret &= SaveMetaData(i, &list.meta);
    }
    ++i;
  }
  return ret;
}

//--------------------------------------------------------------------------------
// Scan and create a list of audio m_list in a specified directory.
//--------------------------------------------------------------------------------
uint32_t CYD_MP3Player::ScanPlayList(void) {
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

  DBG_EXEC({
    m_tree->dump_tree();
  });

  return m_tree->get_n_leafs();
}

//--------------------------------------------------------------------------------
// Randomly scan a specified number of audio files
//--------------------------------------------------------------------------------
uint32_t CYD_MP3Player::ScanAudioRandom(uint32_t max_files) {
  DBG_ASSERT(m_tree && m_list.size() == 0);

  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());

  const size_t n = m_tree->get_n_leafs();
  #define MIN(a, b) ((a) < (b) ? (a) : (b))
  max_files = MIN(max_files, n);

  while (max_files-- > 0) {
    uint32_t R = engine() % n;
    std::string path = m_tree->find_path(R);
    Node *node = m_tree->get_node();
    DBG_ASSERT(node);

    // Read audio files in specified album folder
    std::vector<std::string> names;
    File fd, dir = SD.open(path.c_str());
    while (fd = dir.openNextFile()) {
      std::string name;
      if (check_mp3(fd, name)) {
        names.push_back(name);
      }
      fd.close();
    }
    dir.close();

    if (names.size()) {
      uint32_t r = engine() % names.size();
      append(names[r].c_str(), R);
    }
  }

  DBG_EXEC({
    dump_files();
  });

  return m_list.size();
}

//--------------------------------------------------------------------------------
// Scan audio files and make a play list
//--------------------------------------------------------------------------------
uint32_t CYD_MP3Player::ScanAudioFiles(bool shuffle) {
  DBG_ASSERT(m_tree && m_list.size() == 0);

  // Functional object to make a hash
  std::hash<std::string> MakeHash;

  // Extract audio files in the parents directory
  const size_t n = m_tree->get_n_leafs();
  for (int p = 0, parent = 0; parent < n; parent++) {
    std::string path = m_tree->find_path(parent);
    Node *node = m_tree->get_node();
    DBG_ASSERT(node);
    node->n_files = 0;

    File fd, dir = SD.open(path.c_str());
    while (fd = dir.openNextFile()) {
      std::string name;
      if (check_mp3(fd, name)) {
        ++node->n_files; // count audio files
        if (node->meta.checked == LEAF_SELECTED) {
          append(name.c_str(), parent);
        }
      }
      fd.close();
    }
    dir.close();

    // If the album is not selected then proceed next
    if (node->meta.checked != LEAF_SELECTED) {
      continue;
    }

    std::sort(m_list.begin() + p, m_list.end(), [](MP3List_t &a, MP3List_t &b) {
      return a.name.compare(b.name) < 0 ? true : false; // Ascending order
    });

    const int n = m_list.size() - p;
    MetaHash_t *album_src = new MetaHash_t[n];
    DBG_ASSERT(album_src); // Out of memory

    if (album_src) {
      size_t src = sizeof(MetaHash_t) * n;
      memset((void*)album_src, 0, src);
      for (int i = 0; i < n; i++) {
        album_src[i].hash = MakeHash(m_list[p + i].name);
      }

      // Read an existing meta data file
      int counts = 0;
      size_t dst = 0;
      std::string meta = path + "/" ALBUM_META_FILE;
      fd = SD.open(meta.c_str(), FILE_READ);

      if (fd) {
        dst = fd.SDFS_SIZE();
        const int m = dst / sizeof(MetaHash_t);
        MetaHash_t *album_dst = new MetaHash_t[m];
        DBG_ASSERT(album_dst); // Out of memory

        if (album_dst) {
          dst = fd.read((SDFS_VOID*)album_dst, dst);

          // Find a matching hash and update meta data
          for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
              if (album_src[i].hash == album_dst[j].hash) {
                m_list[p + i].meta = album_src[i].meta = album_dst[j].meta;
                ++counts;
                break;
              }
            }
          }

          delete[] album_dst;
        }

        fd.close();
      }

      // Update if mismatched
      if (src != dst || n != counts) {
        if (fd = SD.open(meta.c_str(), FILE_WRITE)) {
          fd.seek(0);
          fd.write((SDFS_VOID*)album_src, src);
          fd.close();
        }
      }

      delete[] album_src;
    }

    p = m_list.size();
  }

  if (m_list.size() == 0) {
    m_error = "No music to play";
  }

  else if (shuffle) {
    ShuffleAudioFiles();
  }

  DBG_EXEC({
    dump_files();
  });

  return m_list.size();
}

//--------------------------------------------------------------------------------
// Sort file list
//--------------------------------------------------------------------------------
void CYD_MP3Player::ShuffleAudioFiles(void) {
  std::mt19937 engine(esp_random());
  std::shuffle(m_list.begin(), m_list.end(), engine);
}

//--------------------------------------------------------------------------------
// Clear all the nodes in tree
//--------------------------------------------------------------------------------
void CYD_MP3Player::ClearAudioFiles(void) {
  m_list.clear();
}

//--------------------------------------------------------------------------------
// Load the picture number stored in the metadata on the SD card
//--------------------------------------------------------------------------------
uint32_t CYD_MP3Player::GetPictureNo(uint32_t playNo) {
  uint32_t pictNo = 0;

  // Gets the picture number recorded in PICTURE_FILE.
  std::string path = GetDirPath(playNo);
  path.append(ALBUM_PHOTO_FILE "txt");

  File fd = SD.open(path.c_str(), FILE_READ);
  if (fd) {
#ifdef  SDFATFS_USED
    String n = "";
    while (fd.available()) {
      n += fd.readString();
    }
    fd.close();
    if (isdigit(n[0])) {
      pictNo = atoi(n.c_str());
    }
#else // SD
    char buf[BUF_SIZE];
    fd.read((uint8_t*)buf, sizeof(buf));
    fd.close();
    buf[sizeof(buf) - 1] = '\0';
    if (isdigit(buf[0])) {
      pictNo = atoi(buf);
    }
#endif // SdFat or SD
  }

  return pictNo;
}

//--------------------------------------------------------------------------------
// Get ID3 tags (title, album, artist) from the play list
//--------------------------------------------------------------------------------
void CYD_MP3Player::GetID3Tags(uint32_t playNo, ID3Tags_t &tags) {
  MP3List_t *list = GetPlayList(playNo);
  if (list) {
    tags.meta = list->meta;

    int n = 0;
    char *ptr, *token, *tmp[8], copy[BUF_SIZE];
    std::string path = GetFilePath(playNo);

    // UTF-8 multibyte characters should be handled correctly
    strncpy(copy, path.c_str(), sizeof(copy));
    copy[sizeof(copy) - 1] = '\0';

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

//--------------------------------------------------------------------------------
// Get error message
//--------------------------------------------------------------------------------
const char* CYD_MP3Player::GetError(void) {
  return m_error.c_str();
}

//--------------------------------------------------------------------------------
// Operation
//--------------------------------------------------------------------------------
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
      MP3List_t *list = GetPlayList(i);
      if (list->meta.selected) {
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

//--------------------------------------------------------------------------------
// Check if the next song is selected
//--------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------
// Optional functions for audio-I2S (defined in CYD_Audio.h as a weak function)
//--------------------------------------------------------------------------------
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