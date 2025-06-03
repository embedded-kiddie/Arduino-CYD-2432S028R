/*--------------------------------------------------------------------------------
 * Definition of SPI file system for audio files
 * NOTE: uncomment the followings to use SdFat 
 *  "#define SDFATFS_USED" in CYD_Audio.h
 *  "#define USE_UTF8_LONG_NAMES 1" in SdFatConfig.h
 *--------------------------------------------------------------------------------*/
#ifndef _SDCARD_H_
#define _SDCARD_H_

#ifdef  SDFATFS_USED
#define USE_SDFAT
#include "SdFat.h"
#else
#include "FS.h"
#include "SD.h"
#endif

#ifdef  SDFATFS_USED          // defined in CYD_Audio.h
#define FS_DEV    SD_SDFAT    // defined in CYD_Audio.cpp
#define FS_TYPE   fs::SDFATFS // SdFat
#define FS_FILE   FsFile
#define FS_MODE   int
#define FS_CONFIG SD_CS, SD_CLOCK

// alternatives to FS.h definitions
#undef  FILE_APPEND
#define FILE_APPEND (O_RDWR | O_CREAT | O_AT_END)
#undef  FILE_WRITE
#define FILE_WRITE  (O_RDWR | O_CREAT | O_TRUNC)

enum SeekMode {
  SeekSet = 0,
  SeekCur = 1,
  SeekEnd = 2
};

#elif defined (_SD_H_)
#define FS_DEV    SD
#define FS_TYPE   SDFS // fs::SDFS
#define FS_FILE   File
#define FS_MODE   const char *
#define FS_CONFIG SD_CS //, SPI, SD_CLOCK
#endif

#define SD_CLOCK  25000000 // The maximum SD SPI clock of ESP32-2432S028 would be 24 MHz
#define SD_CS     SS

extern FS_TYPE FS_DEV;
void lv_fs_arduino_sd_init(void);

#endif // _SDCARD_H_