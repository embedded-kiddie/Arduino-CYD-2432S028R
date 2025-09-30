/*--------------------------------------------------------------------------------
 * A wrapper class that hides LittleFS
 * SdFat defines its own FS class, which conflicts with the definition in FS.h.
 * To avoid such conflict, this class is defined as a wrapper class of LittleFS.
 *--------------------------------------------------------------------------------*/
#ifndef _FLASHFS_H_
#define _FLASHFS_H_

class FlashFS {
public:
  FlashFS();
  ~FlashFS();
  static bool init(void);
  static void list(void);
  static bool format(void);
private:
  static void listDir(const char *dirname, uint8_t levels);
};

#endif // _FLASHFS_H_