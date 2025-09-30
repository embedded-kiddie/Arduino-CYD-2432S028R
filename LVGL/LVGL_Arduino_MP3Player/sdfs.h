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
#include "sdspi.h"

/*--------------------------------------------------------------------------------
 * MY_USE_FS_ARDUINO_SD:
 *  0: Load jpg/bmp on SD using LVGL library
 *  1: Load jpg/bmp on SD without cache
 *  2: Load jpg/bmp on SD with cache
 * Refer To: https://github.com/lvgl/lvgl/tree/master/src/libs/tjpgd
 *--------------------------------------------------------------------------------*/
#include <lvgl.h>

// Avoid conflicts with 'LV_USE_FS_...' defined in lvgl.h
#if (LV_USE_FS_ARDUINO_SD == 0)
  #define MY_USE_TJPGD ((LV_USE_TJPGD == 0) && (LV_USE_BMP == 0))
  #define MY_USE_FS_ARDUINO_SD 2  // 1:without cache, 2: with cache
  #define MY_FS_ARDUINO_SD_LETTER 'S'
  void lv_fs_arduino_sd_init(void);
  void lv_fs_clear_cache(void);
  void lv_tjpgd_init(void);
#else
  #define MY_USE_FS_ARDUINO_SD 0
  #define MY_FS_ARDUINO_SD_LETTER 'S'
#endif

#endif // _SDFS_H_