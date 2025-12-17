//================================================================================
// LVGL file system interfaces for handling an image file on SD card
// NOTE: uncomment the followings to use SdFat
//  "#define SDFATFS_USED" in CYD_Audio.h
//  "#define USE_UTF8_LONG_NAMES 1" in SdFatConfig.h
//================================================================================
#ifndef _SDSPI_H_
#define _SDSPI_H_

#ifdef  SDFATFS_USED  // defined in CYD_Audio.h

#define USE_SDFAT
//--------------------------------------------------------------------------------
// SdFat library
// https://github.com/greiman/SdFat
//--------------------------------------------------------------------------------
#define DISABLE_FS_H_WARNING
#include <SdFat.h>

// extern SdFat SD;

// SPI bus configuration
// Note: It assumes that the LCD is assigned to HSPI.
#if   0
#define SD_SPI_BUS sd_spi
#define SD_CONFIG SdSpiConfig((SdCsPin_t)SS, DEDICATED_SPI, SD_SPI_CLOCK, &SD_SPI_BUS)
#define DECLARE_SD_SPI_BUS SPIClass SD_SPI_BUS = SPIClass(VSPI)
#else
#define SD_CONFIG SD_CS, SD_SPI_CLOCK
#endif

// Alternatives to FS.h definitions
// File fd = SD.open((FS_VOID*)path, (FS_MODE)FILE_READ);
// size_t size = fd.FS_SIZE();
#define FS_MODE int
#define FS_VOID void
#define FS_SIZE fileSize

#undef  FILE_READ
#undef  FILE_WRITE
#undef  FILE_APPEND
#define FILE_READ   (O_RDONLY)
#define FILE_APPEND (O_RDWR | O_CREAT | O_AT_END)
#define FILE_WRITE  (O_RDWR | O_CREAT | O_TRUNC)

enum SeekMode {
  SeekSet = 0,
  SeekCur = 1,
  SeekEnd = 2
};

#else
//--------------------------------------------------------------------------------
// Standard SD library
// https://github.com/espressif/arduino-esp32/tree/master/libraries/SD
//--------------------------------------------------------------------------------
#include <SD.h>

// SPI bus configuration
#if   1
#define SD_CONFIG SD_CS, SPI, SD_SPI_CLOCK
#else
#define SD_CONFIG
#endif

// File fd = SD.open((FS_VOID*)path, (FS_MODE)FILE_READ);
// size_t size = fd.FS_SIZE();
#define FS_MODE const char *
#define FS_VOID uint8_t
#define FS_SIZE size

#endif // SdFat or SD

//--------------------------------------------------------------------------------
// Chip select pin and SPI clock frequency
//--------------------------------------------------------------------------------
#define SD_CS         SS
#define SD_SPI_CLOCK  24000000 // The maximum SD SPI clock of ESP32-2432S028 would be 24 MHz

//--------------------------------------------------------------------------------
// Temporary buffer size for file path
// title(30) + "/" + artist(30) + "/" + album(30) + ".mp3" + '\0'
//--------------------------------------------------------------------------------
#define BUF_SIZE 256

#endif // _SDSPI_H_