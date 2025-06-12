/*--------------------------------------------------------------------------------
 * LVGL file system interfaces for handling an image file with SD card
 * https://github.com/lvgl/lvgl/blob/master/src/libs/fsdrv/lv_fs_arduino_sd.cpp
 * NOTE: uncomment the followings to use SdFat
 *  "#define SDFATFS_USED" in CYD_Audio.h
 *  "#define USE_UTF8_LONG_NAMES 1" in SdFatConfig.h
 *--------------------------------------------------------------------------------*/
#ifndef _SDCARD_H_
#define _SDCARD_H_

#include "CYD28_audio.h"

#ifdef  SDFATFS_USED          // defined in CYD_Audio.h

#include "SdFat.h"

#define USE_SDFAT
#define FS_DEV    SD          // defined in CYD_Audio.cpp
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

#else

#include "FS.h"
#include "SD.h"

#define FS_DEV    SD
#define FS_TYPE   fs::SDFS  // SDFS 
#define FS_FILE   File
#define FS_MODE   const char *
#define FS_CONFIG SD_CS //, SPI, SD_CLOCK

#endif // SDFATFS_USED

#define SD_CLOCK  25000000 // The maximum SD SPI clock of ESP32-2432S028 would be 24 MHz
#define SD_CS     SS

extern FS_TYPE FS_DEV;

/*--------------------------------------------------------------------------------
 * Configure the method to display album pictures
 * MY_USE_FS_ARDUINO_SD:
 *  0: Load BIN   on flash rom    ('LV_USE_TJPGD' in lv_conf.h must be '0')
 *  1: Load TJPGD on SD w/o cache ('LV_USE_TJPGD' in lv_conf.h must be '1')
 *  2: Load TJPGD on SD w   cache ('LV_USE_TJPGD' in lv_conf.h must be '1')
 * Refer To: https://github.com/lvgl/lvgl/tree/master/src/libs/tjpgd
 *--------------------------------------------------------------------------------*/
// Avoid conflicts with 'LV_USE_FS_...' defined in lvgl.h
#if LV_USE_FS_ARDUINO_SD == 0
  #if LV_USE_TJPGD == 0
    #define MY_USE_FS_ARDUINO_SD 0
  #else
    #define MY_USE_FS_ARDUINO_SD 2
    #define MY_FS_ARDUINO_SD_LETTER 'S'
    void lv_fs_arduino_sd_init(void);
  #endif
#endif

#endif // _SDCARD_H_