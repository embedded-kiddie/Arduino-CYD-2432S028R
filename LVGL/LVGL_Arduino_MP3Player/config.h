//================================================================================
// CYD_MP3Player Configration
//================================================================================
#ifndef _CONFIG_H_
#define _CONFIG_H_

//--------------------------------------------------------------------------------
// 1. TFT Screen configuration
//--------------------------------------------------------------------------------
#define TFT_WIDTH       240   // Portrait orientation default width
#define TFT_HEIGHT      320   // Portrait orientation default height
#define TFT_ROTATION    0     // 0: Portrait, 3: Portrait (Upside down)

//--------------------------------------------------------------------------------
// 2. Graphic library configuration
// Below are for the LovyanGFX library for the "ESP32-2432S028R" (aka CYD).
// If the LCD panel auto-detection feature does not work, define the panel type.
//--------------------------------------------------------------------------------
// true  : Use the LGFX auto-detect feature
// false : Define the appropriate LCD panel driver type to "DISPLAY_CYD_2USB"
#define USE_AUTODETECT  false

#if (USE_AUTODETECT == false)
// false: Panel driver: ILI9341 (micro-USB x 1 type)
// true : Panel driver: ST7789  (micro-USB x 1 + USB-C x 1 type)
#define DISPLAY_CYD_2USB  false
#endif

//--------------------------------------------------------------------------------
// 3. Touch panel calibration
// If there's some slippage with the default parameters, execute calibration and
// embed the results displayed on the serial monitor into "CYD_MP3Player.ino".
//--------------------------------------------------------------------------------
// true  : Use embedded data in "CYD_MP3Player.ino"
// false : Execute touch calibration at power-on
#define USE_CALIBRATED    true

//--------------------------------------------------------------------------------
// 4. Custom fonts configuration
// Configure the font for displaying artists, albums, and songs.
// For information on how to generate font data files, see "fonts/README.md".
//--------------------------------------------------------------------------------
#define USE_CUSTOM_FONTS  true

//--------------------------------------------------------------------------------
// 5. MP3 files in SD card
// Album cover photo files (e.g. "@photo.jpg") should preferably be 96x96,
// compress the file by 50-75%, and keep the file size to 5KB or less.
//--------------------------------------------------------------------------------
#define MP3_ROOT_PATH     "/MP3/"                       // Root folder for storing music files
#define MP3_FILE_EXT      {".m4a", ".mp3", ".wav"}      // Define the preferred extension first
#define ALBUM_PHOTO_EXT   ".jpg"                        // Album cover photo file name extension
#define ALBUM_PHOTO_FILE  "@photo"                      // Album cover photo file name body
#define ALBUM_META_FILE   "@meta.dat"                   // Album meta information file (binary data)
#define IS_VALID_FILE(f)  (*(f) != '@' && *(f) != '.')  // Folder/file name prefix (1 char) to exclude

//--------------------------------------------------------------------------------
// 6. Album list configuration under "PARTITION_PATH"
// The list to classify albums is saved under "PARTITION_PATH" as a text file.
// Also the configuration for each classification is saved as a JSON file.
//--------------------------------------------------------------------------------
#define ALBUM_CONF_PATH   "@conf/"          // Album list configuration folder
#define ALBUM_LIST_FILE   "@album.txt"      // Album list configuration file
#define ALBUM_LIST_JSON   ".json"           // Album list JSON file extension

//--------------------------------------------------------------------------------
// 7. Partitions under "MP3_ROOT_PATH"
// Please limit the number of songs in your playlist to a maximum of around 750.
// So you can make full use of your SD card capacity by creating subfolders
// (called partitions) under "MP3_ROOT_PATH". (e.g. "/MP3/1/", "/MP3/2/", ...)
//--------------------------------------------------------------------------------
#define PARTITION_MAX     5                 // Maximum number of partitions
#define PARTITION_PATH    "%d/"             // Partition folder name ("%d" : 1, 2, ... 5)
#define PARTITION_FILE    "@part.dat"       // Partition configuration file (binary data)

//================================================================================
// Here're examples of folders/files structure on an SD card.
//
// [WITHOUT PARTITION]            [WIDTH PARTITION]
// /MP3/                          /MP3/
// ├── @conf/                     ├── @part.dat
// │   ├── @album.txt             ├── 1/
// │   ├── 1.json                 │   ├── @conf/
// │   ├── 2.json                 │   │   ├── @album.txt
// │   └── ...                    │   │   ├── 1.json
// ├── Artist1/                   │   │   ├── 2.json
// │   ├── Arbum1.1/              │   │   └── ...
// │   │   ├── @meta.dat          │   ├── Artist1/
// │   │   ├── @photo.jpg         │   │   ├── Arbum1.1/
// │   │   ├── 01 title01.m4a     │   │   │   ├── @meta.dat
// │   │   ├── 02 title02.m4a     │   │   │   ├── @photo.jpg
// │   │   └── ...                │   │   │   ├── 01 title01.m4a
// │   ├── Arbum1.2/              │   │   │   ├── 02 title02.m4a
// │   │   └── ...                │   │   │   └── ...
// │   └── ...                    │   │   ├── Arbum1.2/
// ├── Artist2/                   │   │   │   └── ...
// │   ├── Arbum2.1               │   │   └── ...
// │   └──...                     │   ├── Artist2/
// └── ...                        │   │   ├── Arbum2.1/
//                                │   │   └── ...
//                                │   └── ...
//                                ├── 2/
//                                │   ├── ...
//================================================================================

#endif // _CONFIG_H_