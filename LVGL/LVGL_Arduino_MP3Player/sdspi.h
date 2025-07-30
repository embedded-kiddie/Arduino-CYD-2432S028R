/*--------------------------------------------------------------------------------
 * LVGL file system interfaces for handling an image file on SD card
 * https://github.com/lvgl/lvgl/blob/master/src/libs/fsdrv/lv_fs_arduino_sd.cpp
 * NOTE: uncomment the followings to use SdFat
 *  "#define SDFATFS_USED" in CYD_Audio.h
 *  "#define USE_UTF8_LONG_NAMES 1" in SdFatConfig.h
 *--------------------------------------------------------------------------------*/
#ifndef _SDSPI_H_
#define _SDSPI_H_

#ifdef  SDFATFS_USED  // defined in CYD_Audio.h

#define USE_SDFAT

#include "SdFat.h"

#define SD_CONFIG SD_CS, SD_CLOCK

// alternatives to FS.h definitions
#undef  FILE_APPEND
#define FILE_APPEND (O_RDWR | O_CREAT | O_AT_END)
#undef  FILE_WRITE
#define FILE_WRITE  (O_RDWR | O_CREAT | O_TRUNC)

#else

#include "SPI.h"

#define SD_CONFIG SD_CS, SPI, SD_CLOCK

#endif // SdFat or SD

#define SD_CS     SS
#define SD_CLOCK  25000000 // The maximum SD SPI clock of ESP32-2432S028 would be 24 MHz

/*--------------------------------------------------------------------------------
 * Temporary buffer size
 * at least 97 = title(30) + "/" + artist(30) + "/" + album(30) + ".mp3" + '\0'
 *--------------------------------------------------------------------------------*/
#define BUF_SIZE 128

#endif // _SDSPI_H_