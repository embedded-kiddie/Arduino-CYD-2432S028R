/*--------------------------------------------------------------------------------
 * CYD_MP3Player class definition
 *--------------------------------------------------------------------------------*/
#ifndef _CYD_MP3PLAYER_H_
#define _CYD_MP3PLAYER_H_

#include "CYD28_audio.h"
#include "sdfs.h"

// at least 97 = title(30) + "/" + artist(30) + "/" + album(30) + ".mp3" + '\0'
#define FS_BUF_SIZE 128

/*--------------------------------------------------------------------------------
 * Metadata file
 *--------------------------------------------------------------------------------*/
#define META_DATA_DIR "@meta/"
#define META_DATA_EXT ".dat"
#define PICTURE_EXT   "jpg"
#define PICTURE_FILE  "@picture.txt"

/*--------------------------------------------------------------------------------
 * Possible values for `SetVolume()`
 *--------------------------------------------------------------------------------*/
#define MP3_VOLUME_MIN  0
#define MP3_VOLUME_INI  6
#define MP3_VOLUME_MAX  21

/*--------------------------------------------------------------------------------
 * File name and size for ScanFileList()
 *--------------------------------------------------------------------------------*/
#include <string.h>
#include <string>
#include <vector>
#include <random>
#include <exception>

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
  fs::FS & m_fs = FS_DEV;
  std::string m_error = "";
  std::string m_root = "/";
  std::vector<PlayList_t> m_files = {};

  bool        CheckExtension(const char *path);
  const char* MetaDataPath  (const char *path);
  void        LoadMetaData  (const char *path, MetaData_t *meta);
  bool        SaveMetaData  (const char *path, MetaData_t *meta);
  PlayList_t* GetPlayList   (uint32_t playNo);

public:
  bool        begin(const char *root, uint8_t vol = MP3_VOLUME_INI);
  uint32_t    GetPlayNo(void) { return m_playNo; }
  uint32_t    GetCounts(void) { return m_files.size(); }
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