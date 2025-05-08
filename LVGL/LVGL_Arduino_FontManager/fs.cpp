//----------------------------------------------------------------------
// LittleFS テストプログラム
//----------------------------------------------------------------------
#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

#include "ui.h"

#define FORMAT_LITTLEFS_IF_FAILED true

// https://github.com/espressif/arduino-esp32/tree/master/libraries/LittleFS/examples/LITTLEFS_test
static void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\r\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("\tSIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

bool fs_init(void) {
  if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
    Serial.println("LittleFS Mount Failed");
    return false;
  } else {
    listDir(LittleFS, "/", 0); // アップロードされたデータを確認
    return true;
  }
}