/*--------------------------------------------------------------------------------
 * A wrapper class that hides LittleFS
 * SdFat defines its own FS class, which conflicts with the definition in FS.h.
 * To avoid such conflict, this class is defined as a wrapper class of LittleFS.
 *--------------------------------------------------------------------------------*/
#include <LittleFS.h>
#include "flashfs.h"
#include "debug.h"

bool FlashFS::init(void) {
  if (!LittleFS.begin(true)) {
    DBG_EXEC(Serial.println("LittleFS Mount Failed"));
    return false;
  }
  return true;
}

void FlashFS::list(void) {
  listDir("/", 3);
  Serial.printf("Total: %d, Used: %d\n", LittleFS.totalBytes(), LittleFS.usedBytes());
}

bool FlashFS::format(void) {
  return LittleFS.format();
}

void FlashFS::listDir(const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\r\n", dirname);

  File root = LittleFS.open(dirname);
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
        listDir(file.path(), levels - 1);
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