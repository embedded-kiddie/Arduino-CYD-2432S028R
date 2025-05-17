/*--------------------------------------------------------------------------------
 * CYD_MP3Player class definition
 *--------------------------------------------------------------------------------*/
#ifndef _CYD_MP3PLAYER_
#define _CYD_MP3PLAYER_

#include "CYD28_audio.h"

/*--------------------------------------------------------------------------------
 * Possible values ​​for `SetVolume()`
 *--------------------------------------------------------------------------------*/
#define MP3_VOLUME_MIN  0
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
  std::string path;
  bool selected;
} PlayList_t;

typedef struct {
  std::string title;
  std::string artist;
  std::string album;
  uint32_t    duration;
  bool        selected;
} ID3Tags_t;

/*--------------------------------------------------------------------------------
 * Definition of SPI file system for audio files
 * NOTE: uncomment the followings to use SdFat 
 *  "#define SDFATFS_USED" in CYD_Audio.h
 *  "#define USE_UTF8_LONG_NAMES 1" in SdFatConfig.h
 *--------------------------------------------------------------------------------*/
#define SD_CLOCK  20000000  // 1MHz --> 20MHz and up
#define SD_CS     SS

#if defined (SDFATFS_USED)  // defined in CYD_Audio.h
#define FS_DEV    SD_SDFAT  // defined in CYD_Audio.cpp
#define FS_CONFIG SD_CS, SD_CLOCK
#define BUF_SIZE  64
#elif defined (_SD_H_)
#define FS_DEV    SD
#define FS_CONFIG SD_CS, SPI, SD_CLOCK
#endif

class CYD_MP3Player {
private:
  int m_playNo = 0;
  bool m_selected = false;
  fs::FS & m_fs = FS_DEV;
  std::vector<PlayList_t> m_files = {};
  const ID3Tags_t m_empty = {};

  bool CheckExtension(const char* path);

public:
  bool      begin(void);
  uint32_t  GetCounts(void) { return m_files.size(); }
  ID3Tags_t GetID3Tags(std::string path);
  ID3Tags_t GetID3Tags(uint32_t n) { return n < m_files.size() ? GetID3Tags(m_files[n].path) : m_empty; }
  void      ScanFileList(const char *dirname, uint8_t levels);
  void      SortFileList(bool shuffle = false);

  uint8_t   GetVolumePerCent(void);
  void      SetVolume(uint8_t vol);
  void      PauseResume(void);
  void      StopPlay(void);
  void      SetPlayNo(int playNo);
  void      PlayNext(void);
  void      PlayPrev(void);
  bool      FilePlay(const char* path);
  bool      IsPlaying(void);
  bool      AutoPlay(bool selected = false);
  void      SetIDd3TagsCallback(void (*callback)(ID3Tags_t*), ID3Tags_t*);
};

void audio_info(const char *info);
void audio_id3data(const char *info);
void audio_eof_mp3(const char *info);
void audio_showstation(const char *info);
void audio_showstreamtitle(const char *info);
void audio_bitrate(const char *info);
void audio_commercial(const char *info);
void audio_icyurl(const char *info);
void audio_lasthost(const char *info);

#endif // _CYD_MP3PLAYER_