//====================================================================
// SD file system configuration
//====================================================================
#ifndef _SDSPI_H_
#define _SDSPI_H_

// #define USE_SDFAT

#ifdef  USE_SDFAT
//--------------------------------------------------------------------
// SdFat library
// https://github.com/greiman/SdFat
//--------------------------------------------------------------------
#include "SdFat.h"

extern SdFat SD;

// SPI bus configuration
// Note: It assumes that the LCD is assigned to HSPI.
#if   1
#define SD_SPI_BUS sd_spi
#define SD_CONFIG SdSpiConfig((SdCsPin_t)SS, DEDICATED_SPI, SD_SPI_CLOCK, &SD_SPI_BUS)
#define DECLARE_SD_SPI_BUS SPIClass SD_SPI_BUS = SPIClass(VSPI)
#else
#define SD_CONFIG SD_CS, SD_SPI_CLOCK
#endif

// alternatives to FS.h definitions
#undef  FILE_APPEND
#define FILE_APPEND (O_RDWR | O_CREAT | O_AT_END)
#undef  FILE_WRITE
#define FILE_WRITE  (O_RDWR | O_CREAT | O_TRUNC)

#else
//--------------------------------------------------------------------
// Standard SD library
// https://github.com/espressif/arduino-esp32/tree/master/libraries/SD
//--------------------------------------------------------------------
#include "SD.h"

// SPI bus configuration
#if   1
#define SD_CONFIG SD_CS, SPI, SD_SPI_CLOCK
#else
#define SD_CONFIG
#endif

#endif // SdFat or SD

//--------------------------------------------------------------------
// Chip select pin and SPI clock frequency
//--------------------------------------------------------------------
#define SD_CS SS
#define SD_SPI_CLOCK 25000000 // The maximum SD SPI clock of ESP32-2432S028 would be 24 MHz

//--------------------------------------------------------------------
// Temporary buffer size for file path
// title(30) + "/" + artist(30) + "/" + album(30) + ".mp3" + '\0'
//--------------------------------------------------------------------
#define BUF_SIZE 128

#endif  // _SDSPI_H_