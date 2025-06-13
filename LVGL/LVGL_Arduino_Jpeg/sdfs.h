/*--------------------------------------------------------------------------------
 * LVGL file system interfaces for handling an image file on SD card
 * https://github.com/lvgl/lvgl/blob/master/src/libs/fsdrv/lv_fs_arduino_sd.cpp
 * NOTE: uncomment the followings to use SdFat
 *  "#define USE_UTF8_LONG_NAMES 1" in SdFatConfig.h
 *--------------------------------------------------------------------------------*/
#ifndef _SDFS_H_
#define _SDFS_H_

#if true

#include "SdFat.h"

#define USE_SDFAT
#define FS_DEV    SD
#define FS_TYPE   SdFat
#define FS_FILE   File
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
#define FS_TYPE   SDFS
#define FS_FILE   File
#define FS_MODE   const char *
#define FS_CONFIG SD_CS //, SPI, SD_CLOCK

#endif // SdFat or SD

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
#include "lvgl.h"

// Avoid conflicts with 'LV_USE_FS_...' defined in lvgl.h
#if LV_USE_FS_ARDUINO_SD == 0
  #if (LV_USE_TJPGD == 0) && (LV_USE_BMP == 0)
    #error "LV_USE_TJPGD or LV_USE_BMP in lv_conf.h should be defined as 1."
  #else
    #define MY_USE_FS_ARDUINO_SD 2
    #define MY_FS_ARDUINO_SD_LETTER 'S'
    void lv_fs_arduino_sd_init(void);
  #endif
#endif

#endif // _SDFS_H_