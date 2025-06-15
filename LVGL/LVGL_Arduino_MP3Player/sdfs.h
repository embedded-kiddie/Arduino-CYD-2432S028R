/*--------------------------------------------------------------------------------
 * LVGL file system interfaces for handling an image file on SD card
 * https://github.com/lvgl/lvgl/blob/master/src/libs/fsdrv/lv_fs_arduino_sd.cpp
 * NOTE: uncomment the followings to use SdFat
 *  "#define SDFATFS_USED" in CYD_Audio.h
 *  "#define USE_UTF8_LONG_NAMES 1" in SdFatConfig.h
 *--------------------------------------------------------------------------------*/
#ifndef _SDFS_H_
#define _SDFS_H_

#include "CYD28_audio.h"

#ifdef  SDFATFS_USED          // defined in CYD_Audio.h

#include "SdFat.h"

#define USE_SDFAT
#define FS_DEV    SD          // instance in CYD_Audio.cpp
#define FS_TYPE   fs::SDFATFS // defined  in CYD_Audio.cpp
#define FS_FILE   FsFile      // File
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

#else

#include "FS.h"
#include "SD.h"

#define FS_DEV    SD          // instance in SD.cpp
#define FS_TYPE   fs::SDFS    // defined  in SD.h
#define FS_FILE   File        // FsFile
#define FS_MODE   const char *
#define FS_CONFIG SD_CS //, SPI, SD_CLOCK

#endif // SdFat or SD

#define SD_CLOCK  25000000 // The maximum SD SPI clock of ESP32-2432S028 would be 24 MHz
#define SD_CS     SS

extern FS_TYPE FS_DEV;

/*--------------------------------------------------------------------------------
 * MY_USE_FS_ARDUINO_SD:
 *  0: Load binary  on flash rom    (LV_USE_[TJPGD|BMP] in lv_conf.h must be 0)
 *  1: Load jpg/bmp on SD w/o cache (LV_USE_[TJPGD|BMP] in lv_conf.h must be 1)
 *  2: Load jpg/bmp on SD w   cache (LV_USE_[TJPGD|BMP] in lv_conf.h must be 1)
 * Refer To: https://github.com/lvgl/lvgl/tree/master/src/libs/tjpgd
 *--------------------------------------------------------------------------------*/
#include "lvgl.h"

// Avoid conflicts with 'LV_USE_FS_...' defined in lvgl.h
#if (LV_USE_FS_ARDUINO_SD == 0)
  #if (LV_USE_TJPGD == 0) && (LV_USE_BMP == 0)
    #define MY_USE_FS_ARDUINO_SD 0
  #else
    #define MY_USE_FS_ARDUINO_SD 2
    #define MY_FS_ARDUINO_SD_LETTER 'S'
    void lv_fs_arduino_sd_init(void);
  #endif
#endif

#endif // _SDFS_H_