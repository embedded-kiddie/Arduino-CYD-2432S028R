/*--------------------------------------------------------------------------------
 * LVGL file system interfaces for handling an image file on SD card
 * https://github.com/lvgl/lvgl/blob/master/src/libs/fsdrv/lv_fs_arduino_sd.cpp
 * NOTE: uncomment the followings to use SdFat
 *  "#define SDFATFS_USED" in CYD_Audio.h
 *  "#define USE_UTF8_LONG_NAMES 1" in SdFatConfig.h
 *--------------------------------------------------------------------------------*/
#ifndef _SDFS_H_
#define _SDFS_H_

#include "sdspi.h"

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