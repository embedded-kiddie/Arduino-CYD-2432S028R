/*
 * pin 1 - not used          |  Micro SD card     |
 * pin 2 - CS (SS)           |                   /
 * pin 3 - DI (MOSI)         |                  |__
 * pin 4 - VDD (3.3V)        |                    |
 * pin 5 - SCK (SCLK)        | 8 7 6 5 4 3 2 1   /
 * pin 6 - VSS (GND)         | ▄ ▄ ▄ ▄ ▄ ▄ ▄ ▄  /
 * pin 7 - DO (MISO)         | ▀ ▀ █ ▀ █ ▀ ▀ ▀ |
 * pin 8 - not used          |_________________|
 *                             ║ ║ ║ ║ ║ ║ ║ ║
 *                     ╔═══════╝ ║ ║ ║ ║ ║ ║ ╚═════════╗
 *                     ║         ║ ║ ║ ║ ║ ╚══════╗    ║
 *                     ║   ╔═════╝ ║ ║ ║ ╚═════╗  ║    ║
 * Connections for     ║   ║   ╔═══╩═║═║═══╗   ║  ║    ║
 * full-sized          ║   ║   ║   ╔═╝ ║   ║   ║  ║    ║
 * SD card             ║   ║   ║   ║   ║   ║   ║  ║    ║
 * Pin name         |  -  DO  VSS SCK VDD VSS DI CS    -  |
 * SD pin number    |  8   7   6   5   4   3   2   1   9 /
 *                  |                                  █/
 *                  |__▍___▊___█___█___█___█___█___█___/
 *
 * Note:  The SPI pins can be manually configured by using `SPI.begin(sck, miso, mosi, cs).`
 *        Alternatively, you can change the CS pin and use the other default settings by using `SD.begin(cs)`.
 *
 * +--------------+---------+-------+----------+----------+----------+----------+----------+
 * | SPI Pin Name | ESP8266 | ESP32 | ESP32‑S2 | ESP32‑S3 | ESP32‑C3 | ESP32‑C6 | ESP32‑H2 |
 * +==============+=========+=======+==========+==========+==========+==========+==========+
 * | CS (SS)      | GPIO15  | GPIO5 | GPIO34   | GPIO10   | GPIO7    | GPIO18   | GPIO0    |
 * +--------------+---------+-------+----------+----------+----------+----------+----------+
 * | DI (MOSI)    | GPIO13  | GPIO23| GPIO35   | GPIO11   | GPIO6    | GPIO19   | GPIO25   |
 * +--------------+---------+-------+----------+----------+----------+----------+----------+
 * | DO (MISO)    | GPIO12  | GPIO19| GPIO37   | GPIO13   | GPIO5    | GPIO20   | GPIO11   |
 * +--------------+---------+-------+----------+----------+----------+----------+----------+
 * | SCK (SCLK)   | GPIO14  | GPIO18| GPIO36   | GPIO12   | GPIO4    | GPIO21   | GPIO10   |
 * +--------------+---------+-------+----------+----------+----------+----------+----------+
 *
 * For more info see file README.md in this library or on URL:
 * https://github.com/espressif/arduino-esp32/tree/master/libraries/SD
 */
#ifndef _SDCARD_HPP_
#define _SDCARD_HPP_

// #define USE_SDFAT

/*--------------------------------------------------------------------------------
 * SD library
 *--------------------------------------------------------------------------------*/
#ifdef USE_SDFAT

#include "SdFat.h"
#include "SPI.h"

#undef  FILE_APPEND
#define FILE_APPEND (O_RDWR | O_CREAT | O_AT_END)
#undef  FILE_WRITE
#define FILE_WRITE  (O_RDWR | O_CREAT | O_TRUNC)

// The maximum SD SPI clock of ESP32-2432S028 would be 24 MHz
#define SD_SPI_CLOCK 25000000

#ifndef SDFATFS_USED
  SdFat SD; // Instance of SdFat
  #define FS_TYPE SdFat
  #ifndef SD_CONFIG
    #define USE_DEDICATED_SPI 1
    #if USE_DEDICATED_SPI
      #define SD_CONFIG SdSpiConfig((SdCsPin_t)SS, DEDICATED_SPI, SD_SPI_CLOCK, &sd_spi) // OK
      SPIClass sd_spi = SPIClass(VSPI);
    #elif 1
      #define SD_CONFIG SdSpiConfig((SdCsPin_t)SS, SHARED_SPI, SD_SPI_CLOCK, &SPI) // OK
    #elif 0
      #define SD_CONFIG SdSpiConfig((SdCsPin_t)SS, SD_SPI_CLOCK) // NG
    #elif 0
      #define SD_CONFIG (SdCsPin_t)SS // NG
    #else
      #define SD_CONFIG // NG
    #endif // USE_DEDICATED_SPI
  #endif
#else
  #define FS_TYPE fs::FS
  #ifndef SD_CONFIG
    #define SD_CONFIG SS, SD_SPI_CLOCK
  #endif
#endif

#ifndef BUF_SIZE
#define BUF_SIZE  128
#endif

#else // ! USE_SDFAT

#include "SD.h"

#define FS_TYPE fs::FS

// The maximum SD SPI clock of ESP32-2432S028 would be 24 MHz
#define SD_SPI_CLOCK 25000000

#ifndef SD_CONFIG
  #ifdef _TFT_eSPIH_
    #define SD_CONFIG SS, GFX_EXEC(getSPIinstance()), SD_SPI_CLOCK
  #elif defined (ARDUINO_ESP32_2432S028R) || defined (ARDUINO_ESP32_DEV)
    #define USE_DEDICATED_SPI 1
    #if USE_DEDICATED_SPI
      SPIClass sd_spi = SPIClass(VSPI);
      #define SD_CONFIG SS, sd_spi, SD_SPI_CLOCK
    #else
      #define SD_CONFIG SS, SPI, SD_SPI_CLOCK
    #endif
  #else
    #define SD_CONFIG SS
  #endif
#endif // SD_CONFIG

#endif // USE_SDFAT

/* Uncomment and set up if you want to use custom pins for the SPI communication
#define REASSIGN_PINS

// https://github.com/espressif/arduino-esp32/blob/master/variants/jczn_2432s028r/pins_arduino.h#L70C9-L70C28
int sck   = SCK;   // 18
int miso  = MISO;  // 19
int mosi  = MOSI;  // 23
int cs    = SS;    //  5
#define SD_CONFIG cs
//*/
/*--------------------------------------------------------------------------------
 * Basic file I/O and directory related functions
 * ex)  listDir(SD, "/", 0);
 *      createDir(SD, "/mydir");
 *--------------------------------------------------------------------------------*/
void listDir(FS_TYPE &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

#ifdef USE_SDFAT
  char buf[BUF_SIZE];
#endif

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
#ifdef USE_SDFAT
      file.getName(buf, sizeof(buf));
      Serial.println(buf);
#else
      Serial.println(file.name());
#endif
      if (levels) {
#ifdef USE_SDFAT
        listDir(fs, buf, levels - 1);
#else
        listDir(fs, file.path(), levels - 1);
#endif
      }
    } else {
      Serial.print("  FILE: ");
#ifdef USE_SDFAT
      file.getName(buf, sizeof(buf));
      Serial.print(buf);
#else
      Serial.print(file.name());
#endif
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void createDir(FS_TYPE &fs, const char *path) {
  Serial.printf("Creating dir: %s\n", path);
  if (fs.mkdir(path)) {
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}

void removeDir(FS_TYPE &fs, const char *path) {
  Serial.printf("Removing dir: %s\n", path);
  if (fs.rmdir(path)) {
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}

void readFile(FS_TYPE &fs, const char *path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}

void writeFile(FS_TYPE &fs, const char *path, const char *message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(FS_TYPE &fs, const char *path, const char *message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void renameFile(FS_TYPE &fs, const char *path1, const char *path2) {
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}

void deleteFile(FS_TYPE &fs, const char *path) {
  Serial.printf("Deleting file: %s\n", path);
  if (fs.remove(path)) {
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}

void testFileIO(FS_TYPE &fs, const char *path) {
  static uint8_t buf[512];
  uint32_t time;

  File file = fs.open(path);
  if (file) {
    size_t len = file.size();
    size_t siz = len;
    time = millis();
    while (len) {
      size_t toRead = len;
      if (toRead > 512) {
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    time = millis() - time;
    Serial.printf("%u bytes read for %lu ms\n", siz, time);
    file.close();
  } else {
    Serial.println("Failed to open file for reading");
  }

  file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  size_t i;
  time = millis();
  for (i = 0; i < 2048; i++) {
    file.write(buf, 512);
  }
  time = millis() - time;
  Serial.printf("%u bytes written for %lu ms\n", 2048 * 512, time);
  file.close();
}

/*--------------------------------------------------------------------------------
 * Test basic functions
 *--------------------------------------------------------------------------------*/
void sdcard_test(void) {
#ifdef  USE_SDFAT

  Serial.print("SD card type: ");
  switch (SD.card()->type()) {
    case SD_CARD_TYPE_SD1:  Serial.println("SD1");       break;
    case SD_CARD_TYPE_SD2:  Serial.println("SD2");       break;
    case SD_CARD_TYPE_SDHC: Serial.println("SDHC/SDXC"); break;
    default:                Serial.println("unknown");   break;
  }

  Serial.print("FS type: ");
  switch (SD.vol()->fatType()) {
    case FAT_TYPE_EXFAT: Serial.println("exFat"); break;
    case FAT_TYPE_FAT32: Serial.println("FAT32"); break;
    case FAT_TYPE_FAT16: Serial.println("FAT16"); break;
    case FAT_TYPE_FAT12: Serial.println("FAT12"); break;
  }

  uint32_t cardSize = SD.card()->sectorCount() * 0.000512 + 0.5;
  Serial.printf("SD card Size: %dMB\n", cardSize);

#else

  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD card size: %lluMB\n", cardSize);

#endif // USE_SDFAT

  listDir(SD, "/", 0);
  createDir(SD, "/mydir");
  listDir(SD, "/", 0);
  removeDir(SD, "/mydir");
  listDir(SD, "/", 2);
  writeFile(SD, "/hello.txt", "Hello ");
  appendFile(SD, "/hello.txt", "World!\n");
  readFile(SD, "/hello.txt");
  deleteFile(SD, "/foo.txt");
  renameFile(SD, "/hello.txt", "/foo.txt");
  readFile(SD, "/foo.txt");
  testFileIO(SD, "/test.txt");

#ifdef  USE_SDFAT

  Serial.printf("Free space: %dMB\n", (SD.vol()->bytesPerCluster() * SD.vol()->freeClusterCount()) / (1024 * 1024));
  SD.ls(LS_R | LS_DATE | LS_SIZE);

#else

  Serial.printf("Number of sectors: %d\n", SD.numSectors());
  Serial.printf("Size of sector: %d\n", SD.sectorSize());
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));

#endif // USE_SDFAT
}

/*--------------------------------------------------------------------------------
 * Convert between RGB565 and RGB888
 *--------------------------------------------------------------------------------*/
#define RGB_SWAP(t, a, b) {t tmp = a; a = b; b = tmp;}
#define RGB565(r, g, b)   ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))

inline void color565toRGB(uint16_t color, uint8_t &r, uint8_t &g, uint8_t &b) __attribute__((always_inline));
inline void color565toRGB(uint16_t color, uint8_t &r, uint8_t &g, uint8_t &b) {
  r = (color>>8)&0x00F8;
  g = (color>>3)&0x00FC;
  b = (color<<3)&0x00F8;
}

/*--------------------------------------------------------------------------------
 * Correct color shift issue by TFT_eSPI on ESP32 2432S028R
 *--------------------------------------------------------------------------------*/
#if defined (_TFT_eSPIH_) && (DISPLAY_CYD_2USB == true)
#define RGB_CORRECTION    (1)
#else
#define RGB_CORRECTION    (0)
#endif

/*--------------------------------------------------------------------------------
 * LCD screen capture to save image to SD card
 *--------------------------------------------------------------------------------*/
// Graphics library
#if   defined (_TFT_eSPIH_)
#define GFX_TYPE  TFT_eSPI
#elif defined (LOVYANGFX_HPP_)
#define GFX_TYPE  LGFX
#endif

#if defined (GFX_TYPE)
bool SaveBMP24(FS_TYPE &fs, const char *path, GFX_TYPE &tft) {
  uint32_t start = millis();
  uint32_t w = tft.width();
  uint32_t h = tft.height();

#if   defined (LOVYANGFX_HPP_)

  lgfx::rgb888_t rgb[w];

#elif defined (_TFT_eSPIH_)

  uint8_t rgb[w * 3];

#endif // LovyanGFX or TFT_eSPI

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
#ifdef  USE_SDFAT
    Serial.printf("SdFat: open %s failed.\n", path);
#else
    Serial.printf("SD: open %s failed.\n", path);
#endif
    return false;
  } else {
    Serial.printf("saving %s\n", path);
  }

  unsigned char bmFlHdr[14] = {
    'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0
  };

  // set color depth to 24 as we're storing 8 bits for r-g-b
  unsigned char bmInHdr[40] = {
    40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0,
  };

  unsigned long fileSize = 3ul * h * w + 54;

  bmFlHdr[ 2] = (unsigned char)(fileSize);
  bmFlHdr[ 3] = (unsigned char)(fileSize >> 8);
  bmFlHdr[ 4] = (unsigned char)(fileSize >> 16);
  bmFlHdr[ 5] = (unsigned char)(fileSize >> 24);

  bmInHdr[ 4] = (unsigned char)(w);
  bmInHdr[ 5] = (unsigned char)(w >> 8);
  bmInHdr[ 6] = (unsigned char)(w >> 16);
  bmInHdr[ 7] = (unsigned char)(w >> 24);
  bmInHdr[ 8] = (unsigned char)(h);
  bmInHdr[ 9] = (unsigned char)(h >> 8);
  bmInHdr[10] = (unsigned char)(h >> 16);
  bmInHdr[11] = (unsigned char)(h >> 24);

  file.write(bmFlHdr, sizeof(bmFlHdr));
  file.write(bmInHdr, sizeof(bmInHdr));

  for (int y = h - 1; y >= 0; --y) {
    if (y % 10 == 0) {
      Serial.printf(".");
      yield(); // Prevent the watchdog from firing in core 0
    }

#if defined (LOVYANGFX_HPP_)

    tft.readRect(0, y, w, 1, rgb);

  #if RGB_CORRECTION
    for (int i = 0; i < w; ++i) {
      rgb[i].r <<= RGB_CORRECTION;
      rgb[i].g <<= RGB_CORRECTION;
      rgb[i].b <<= RGB_CORRECTION;
    }
  #endif

#else // TFT_eSPI

    tft.readRectRGB(0, y, w, 1, (uint8_t*)rgb);

    for (int i = 0; i < sizeof(rgb); i += 3) {
  #if defined (TFT_RGB_ORDER) && (TFT_RGB_ORDER == TFT_BGR)
      RGB_SWAP(uint8_t, rgb[i+1], rgb[i+2]);
  #else
      RGB_SWAP(uint8_t, rgb[i+0], rgb[i+2]);
  #endif

  #if RGB_CORRECTION
      rgb[i  ] <<= RGB_CORRECTION;
      rgb[i+1] <<= RGB_CORRECTION;
      rgb[i+2] <<= RGB_CORRECTION;
  #endif
    }

#endif // LovyanGFX or TFT_eSPI

    int len = file.write((uint8_t*)rgb, sizeof(rgb));

    if (file.getWriteError() != 0) {
      Serial.printf("SD write error: len: %d\n", len); // getWriteError() returns 1
      file.close();
      return false;
    };
  }

  file.close();
  start = millis() - start;
  Serial.printf("done (%d msec).\n", start);
//listDir(SD, "/", 0);
  return true;
}
#endif // GFX_TYPE

/*--------------------------------------------------------------------------------
 * Setup SD card (Mounting fails if card is not inserted)
 * Note the global variable 'SPI' is assigned to 'VSPI' same as 'sd_spi'.
 * https://github.com/espressif/arduino-esp32/blob/master/libraries/SPI/src/SPI.cpp#L333-L337
 *--------------------------------------------------------------------------------*/
void sdcard_setup(void) {
#ifdef  USE_SDFAT

#if USE_DEDICATED_SPI
  sd_spi.begin(SCK, MISO, MOSI, SS);
#endif

  if (!SD.begin(SD_CONFIG)) {
    Serial.println("SdFat: Card Mount Failed");
    return;
  }

#elif 0

#ifdef REASSIGN_PINS
  SPI.begin(sck, miso, mosi, cs);
#endif

  // this also works since the SD card is connected to the default SPI bus, VSPI
  // and when display and touch panel are connected to HSPI
  if (!SD.begin()) {
    Serial.println("SD: Card Mount Failed");
    return;
  }

#else

  if (!SD.begin(SD_CONFIG)) {
    Serial.println("SD: Card Mount Failed");
    return;
  }

#endif // USE_SDFAT
}
#endif // _SDCARD_HPP_