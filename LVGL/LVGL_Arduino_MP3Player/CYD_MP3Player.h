/*--------------------------------------------------------------------------------
 * CYD_MP3Player class definition
 *--------------------------------------------------------------------------------*/
#ifndef _CYD_MP3PLAYER_H_
#define _CYD_MP3PLAYER_H_

#include "CYD28_audio.h"
#include "sdfs.h"
#include "tree.hpp"
#include "debug.h"

/*--------------------------------------------------------------------------------
 * Audio file root folder
 *--------------------------------------------------------------------------------*/
#define MP3_PATH_ROOT "/MP3/"

/*--------------------------------------------------------------------------------
 * Possible values for `SetVolume()`
 *--------------------------------------------------------------------------------*/
#define MP3_VOLUME_MIN  0
#define MP3_VOLUME_INI  6
#define MP3_VOLUME_MAX  21

/*--------------------------------------------------------------------------------
 * Metadata file
 *--------------------------------------------------------------------------------*/
#define META_DATA_DIR "@meta/"
#define META_DATA_EXT ".dat"

/*--------------------------------------------------------------------------------
 * Thumnail of album picure
 *--------------------------------------------------------------------------------*/
#define PICTURE_BASE  "@picture."
#if MY_USE_FS_ARDUINO_SD
  #if LV_USE_BMP
    #define PICTURE_EXT "bmp" // 96x96 (must be RGB565)
  #elif LV_USE_TJPGD
    #define PICTURE_EXT "jpg" // 96x96
  #else
    #error "LV_USE_BMP or LV_USE_TJPGD should be enabled."
  #endif
#else
  #define PICTURE_EXT "txt" // image in flash
#endif

/*--------------------------------------------------------------------------------
 * Class definition
 *--------------------------------------------------------------------------------*/
#include <string>
#include <vector>

typedef struct {
  bool saved    : 4;
  bool selected : 4;
  uint8_t pictureNo;
  uint16_t duration;
} MetaData_t;

typedef struct {
  MetaData_t meta;
  std::string title;
  std::string artist;
  std::string album;
} ID3Tags_t;

/*----------------------------------------------------------------------
 * Play list for MP3 audio file
 *----------------------------------------------------------------------*/
typedef struct {
  MetaData_t meta;
  uint16_t parent;
  std::string name;
} MP3File_t;

typedef std::vector<MP3File_t> PlayList;

class CYD_MP3Player {
public:
  CYD_MP3Player() {}
  ~CYD_MP3Player() {
    if (m_tree) {
      delete m_tree;
      m_tree = NULL;
    }
  }

private:
  uint32_t m_playNo = 0;
  std::string m_error = "";
  std::string m_root = "/";
  Node *m_tree = NULL;
  PlayList m_list = {};

  MP3File_t*  GetPlayList (uint32_t playNo);
  std::string GetMetaPath (uint32_t playNo);
  void        LoadMetaData(uint32_t playNo, MetaData_t *meta);
  bool        SaveMetaData(uint32_t playNo, MetaData_t *meta);

public:
  bool        begin(const char *root, uint8_t vol = MP3_VOLUME_INI);
  uint32_t    GetPlayNo(void) { return m_playNo; }
  uint32_t    GetCounts(void) { return m_list.size(); }
  uint32_t    ScanPlayList(bool shuffle = true);
  uint32_t    SortPlayList(bool shuffle = true);
  std::string GetDirPath  (uint32_t playNo);
  std::string GetFilePath (uint32_t playNo);
  uint32_t    GetPictureNo(uint32_t playNo);
  void        GetID3Tags  (uint32_t playNo, ID3Tags_t &tags);
  void        GetMetaData (uint32_t playNo, MetaData_t *meta);
  bool        PutMetaData (uint32_t playNo, MetaData_t *meta);
  bool        UpdateMetaData(void);
  const char* GetError(void);

  void        SetVolume(uint8_t vol);
  uint8_t     GetVolumePerCent(void);
  bool        IsPlaying(void);
  bool        IsLastSong(bool selected);
  bool        FilePlay(const char *path);
  void        StopPlay(void);
  void        PauseResume(void);
  void        SetPlayNo(uint32_t playNo, bool stop = true);
  void        PlayNext(bool stop = true);
  void        PlayPrev(bool stop = true);
  bool        IsSelected(void);
  bool        NextSelected(bool next, bool loop, bool stop = true);
  bool        AutoPlay(void);

private:
  /*--------------------------------------------------------------------------------
   * Add audio file at the end of the play list
   *--------------------------------------------------------------------------------*/
  void append(const char * name, uint16_t parent) {
    try {
      m_list.push_back({
        .meta   = {},
        .parent = parent, 
        .name   = name
      });
    } catch (const std::exception &e) {
      assert(false); //  e.what()
    }
  }

  /*--------------------------------------------------------------------------------
   * Verify file extension. (mp3, m4a, aac, wav, flac, opus, ogg, oga)
   *--------------------------------------------------------------------------------*/
  bool check_mp3(const char *path) {
    const char* ext[] = {".mp3", ".m4a", ".wav"};
    for (int i = 0; i < sizeof(ext) / sizeof(ext[0]); i++) {
      if (strcmp(&path[strlen(path) - strlen(ext[i])], ext[i]) == 0) {
        return true;
      }
    }
    return false;
  }

  /*--------------------------------------------------------------------------------
   * Scan audio files and make a play list
   *--------------------------------------------------------------------------------*/
  void scan_file(Node* tree) {
    const size_t n = tree->size();

    // extract audio files in the parents directory
    for (int i = 0, parent = 0; parent < n; parent++) {
      std::string path = tree->find_path(parent);
      File file, dir = SD.open(path.c_str());

      while (file = dir.openNextFile()) {
#ifdef USE_SDFAT
        char buf[BUF_SIZE];
        file.getName(buf, sizeof(buf));
        if (check_mp3(buf)) {
          append(buf, parent);
        }
#else
        if (check_mp3(file.name())) {
          append(file.name(), parent);
        }
#endif
      }
      dir.close();

      std::sort(m_list.begin() + i, m_list.end(), [](MP3File_t &a, MP3File_t &b) {
        return a.name.compare(b.name) < 0 ? true : false; // ascending order
      });
      i = m_list.size();
    }
  }

  void print_files(Node* tree) {
    int i = 0; 
    for (auto &f : m_list) {
      std::string path = tree->find_path(f.parent);
      printf("No %3d: %d/%d, %2d, %3d, %s/%s\n", i++, f.meta.saved, f.meta.selected, f.meta.pictureNo, f.meta.duration, path.c_str(), f.name.c_str());
    }
  }
};
/*
void audio_info(const char *info);
void audio_id3data(const char *info);
void audio_eof_mp3(const char *info);
void audio_showstation(const char *info);
void audio_showstreamtitle(const char *info);
void audio_bitrate(const char *info);
void audio_commercial(const char *info);
void audio_icyurl(const char *info);
void audio_lasthost(const char *info);
*/
#endif // _CYD_MP3PLAYER_H_