/*--------------------------------------------------------------------------------
 * CYD_MP3Player class definition
 *--------------------------------------------------------------------------------*/
#ifndef _CYD_MP3PLAYER_H_
#define _CYD_MP3PLAYER_H_

#include "CYD28_audio.h"
#include "sdfs.h"

/*--------------------------------------------------------------------------------
 * Audio file root folder
 *--------------------------------------------------------------------------------*/
#define MP3_PATH_ROOT "/MP3/"
#define MP3_PATH_LEVEL 2
#define MP3_PATH_CONFIG MP3_PATH_ROOT, MP3_PATH_LEVEL

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
#define PICTURE_FILE  "@picture.txt"
#if MY_USE_FS_ARDUINO_SD != 0
  #if LV_USE_BMP
    #define PICTURE_EXT   "bmp"
  #elif LV_USE_TJPGD
    #define PICTURE_EXT   "jpg"
  #endif
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
  std::string path;
} PlayList_t;

typedef struct {
  MetaData_t meta;
  std::string title;
  std::string artist;
  std::string album;
} ID3Tags_t;

class CYD_MP3Player {
private:
  uint32_t m_playNo = 0;
  std::string m_error = "";
  std::string m_root = "/";
  std::vector<PlayList_t> m_list = {};

  PlayList_t* GetPlayList   (uint32_t playNo);
  const char* GetMetaPath   (const char *path);
  void        LoadMetaData  (const char *path, MetaData_t *meta);
  bool        SaveMetaData  (const char *path, MetaData_t *meta);
  bool        CheckExtension(const char *path);

public:
  bool        begin(const char *root, uint8_t vol = MP3_VOLUME_INI);
  uint32_t    GetPlayNo(void) { return m_playNo; }
  uint32_t    GetCounts(void) { return m_list.size(); }
  bool        ScanFileList(const char *dirname, uint8_t levels);
  uint32_t    ScanFileList(uint8_t levels, bool shuffle = true);
  uint32_t    SortFileList(bool shuffle = true);
  uint32_t    GetPictureNo(uint32_t playNo);
  void        GetFilePath (uint32_t playNo, char *buf, int len);
  void        GetID3Tags  (uint32_t playNo, ID3Tags_t &tags);
  void        GetMetaData (uint32_t playNo, MetaData_t *meta);
  bool        PutMetaData (uint32_t playNo, MetaData_t *meta);
  bool        UpdateMetaData(void);
  const char* GetError(void);

  void        SetVolume(uint8_t vol);
  uint8_t     GetVolumePerCent(void);
  bool        IsPlaying(void);
  bool        IsLastSong(void);
  bool        FilePlay(const char *path);
  void        StopPlay(void);
  void        PauseResume(void);
  void        SetPlayNo(uint32_t playNo, bool stop = true);
  void        PlayNext(bool stop = true);
  void        PlayPrev(bool stop = true);
  bool        IsSelected(void);
  bool        NextSelected(bool next, bool loop, bool stop = true);
  bool        AutoPlay(void);
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
#endif  // _CYD_MP3PLAYER_H_