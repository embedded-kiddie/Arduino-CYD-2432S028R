/*--------------------------------------------------------------------------------
 * LVGL file system interfaces for handling an image file on SD card
 * https://github.com/lvgl/lvgl/blob/master/src/libs/fsdrv/lv_fs_arduino_sd.cpp
 * NOTE: uncomment the followings to use SdFat
 *  "#define SDFATFS_USED" in CYD_Audio.h
 *  "#define USE_UTF8_LONG_NAMES 1" in SdFatConfig.h
 *--------------------------------------------------------------------------------*/
#ifndef _SDFS_H_
#define _SDFS_H_

#if   true

#define DISABLE_FS_H_WARNING
#include <FS.h>
#include <SdFat.h>

#define USE_SDFAT
#define FS_MODE   int
#define FS_CONFIG SD_CS, SD_CLOCK

// alternatives to FS.h definitions
#define MY_FILE_READ    (O_RDONLY)
#define MY_FILE_WRITE   (O_RDWR | O_CREAT | O_TRUNC)
#define MY_FILE_APPEND  (O_RDWR | O_CREAT | O_AT_END)

typedef FsFile MyFile;

extern SdFat SD;

#else

#include <FS.h>
#include <SD.h>

#define FS_MODE   const char *
#define FS_CONFIG SD_CS //, SPI, SD_CLOCK

#define MY_FILE_APPEND  FILE_APPEND
#define MY_FILE_WRITE   FILE_WRITE
#define MY_FILE_READ    FILE_READ

typedef File MyFile;

#endif // SdFat or SD

#define SD_CLOCK  25000000 // The maximum SD SPI clock of ESP32-2432S028 would be 24 MHz
#define SD_CS     SS

/*--------------------------------------------------------------------------------
 * MY_USE_FS_ARDUINO_SD:
 *  0: Load binary  on flash rom    (LV_USE_[TJPGD|BMP] in lv_conf.h must be 0)
 *  1: Load jpg/bmp on SD w/o cache (LV_USE_[TJPGD|BMP] in lv_conf.h must be 1)
 *  2: Load jpg/bmp on SD w   cache (LV_USE_[TJPGD|BMP] in lv_conf.h must be 1)
 * Refer To: https://github.com/lvgl/lvgl/tree/master/src/libs/tjpgd
 *--------------------------------------------------------------------------------*/
#include <lvgl.h>

// Avoid conflicts with 'LV_USE_FS_...' defined in lvgl.h
#if (LV_USE_FS_ARDUINO_ESP_LITTLEFS == 1)
  #include <LittleFS.h>
  #define MY_FS_ARDUINO_INIT()
  #define MY_FS_ARDUINO_PREFIX  "L:/"
  #define MY_FS_ARDUINO_ESP_LITTLEFS_LETTER 'L'
  #define FORMAT_LITTLEFS_IF_FAILED true
#elif (LV_USE_FS_ARDUINO_SD == 0)
  #if (LV_USE_TJPGD == 0) && (LV_USE_BMP == 0)
    #define MY_USE_FS_ARDUINO_SD 0  // variable in '.c'
    #define MY_FS_ARDUINO_INIT()
  #else
    #define MY_USE_FS_ARDUINO_SD 2  // 1: without cache, 2: with cache
    #define MY_FS_ARDUINO_PREFIX  "S:/MP3/"
    #define MY_FS_ARDUINO_SD_LETTER 'S'
    #define MY_FS_ARDUINO_INIT()  lv_fs_arduino_sd_init()
    void lv_fs_arduino_sd_init(void);
  #endif
#endif

#endif // _SDFS_H_