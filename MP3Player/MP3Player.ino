// All necessary files are included
#include "CYD28_audio.h"

// 1MHz --> 10MHz or more?
#define SD_CLOCK  10000000
#define SD_CS     SS

// Uncomment the followings to use SdFat 
// "#define SDFATFS_USED" in CYD_Audio.h
// "#define USE_UTF8_LONG_NAMES 1" in SdFatConfig.h
#ifdef SDFATFS_USED
#define SD        SD_SDFAT
#define SD_CONFIG SD_CS, SD_CLOCK
#define BUF_SIZE  64
#else
#define SD_CONFIG SD_CS, SPI, SD_CLOCK
#endif

/*--------------------------------------------------------------------------------
 * File name and size for ScanFileList()
 *--------------------------------------------------------------------------------*/
#include <string.h>
#include <string>
#include <vector>
#include <random>
#include <exception>

typedef struct {
  std::string path;
  size_t      size;
  bool        isDirectory;
  bool        isSelected;
} FileInfo_t;

static std::vector<FileInfo_t> files = {};
static int playNo = 0;

/*--------------------------------------------------------------------------------
 * Verify file extension. (mp3, m4a, aac, wav, flac, opus, ogg, oga)
 *--------------------------------------------------------------------------------*/
bool VerifyExt(const char* file) {
  const char* ext[] = {".mp3", ".wav", ".ogg"};
  for (int i = 0; i < sizeof(ext) / sizeof(ext[0]); i++) {
    if (strcmp(&file[strlen(file) - strlen(ext[i])], ext[i]) == 0) {
      return true;
    }
  }
  return false;
}

/*--------------------------------------------------------------------------------
 * Scan and create a list of audio files in a specified directory.
 *--------------------------------------------------------------------------------*/
void ScanFileList(fs::FS &fs, const char *dirname, uint8_t levels, std::vector<FileInfo_t> &files) {
  File root = fs.open(dirname);
  if (!root) {
    Serial.printf("Failed to open %s.\n", dirname);
    return;
  }
  if (!root.isDirectory()) {
    Serial.printf("Not a directory.\n");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    // Serial.printf("%s\n", file.path());
    bool isDir = file.isDirectory();

    // skip dot file
#ifdef SDFATFS_USED
    char name[BUF_SIZE];
    file.getName(name, sizeof(name));
    std::string path = std::string(dirname) + "/" + std::string(name);
    if (file.isHidden()) {
      // Serial.printf("%s is skipped.\n", name);
    }
#else
    const char *p = strrchr(file.path(), '/');
    if (p[p ? 1 : 0] == '.') {
      // Serial.printf("%s is skipped.\n", file.path());
    }
#endif

    else if (isDir && levels) {
#ifdef SDFATFS_USED
      ScanFileList(fs, path.c_str(), levels - 1, files);
#else
      ScanFileList(fs, file.path(), levels - 1, files);
#endif
    }

    else if (!isDir) {
      try {
#ifdef SDFATFS_USED
        if (VerifyExt(path.c_str())) {
          files.push_back({path, (size_t)file.fileSize(), isDir, false});
        }
#else
        if (VerifyExt(file.path())) {
          files.push_back({file.path(), file.size(), isDir, false});
        }
#endif
      } catch (const std::exception &e) {
        Serial.printf("Exception: %s\n", e.what());
        return;
      }
    }

    file = root.openNextFile();
  }
}

/*--------------------------------------------------------------------------------
 * Sort file list
 *--------------------------------------------------------------------------------*/
void SortFileList(std::vector<FileInfo_t> &files, bool shuffle = false) {
  if (shuffle) {
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::shuffle(files.begin(), files.end(), engine);
  } else {
    std::sort(files.begin(), files.end(), [](FileInfo_t &a, FileInfo_t &b) {
      return a.path.compare(b.path) > 0 ? true : false;
    });
  }

  for (auto& file : files) {
    Serial.println(file.path.c_str());
  }
}

/*--------------------------------------------------------------------------------
 * Setup and Loop
 *--------------------------------------------------------------------------------*/
void setup() {
  Serial.begin(115200);
  while (millis() < 1000);

  audioInit();

  if (!SD.begin(SD_CONFIG)) {
    Serial.println("Cannot begin SD.");
    while (1);
  }

  ScanFileList(SD, "/", 3, files);
  SortFileList(files, true);
}

void loop() {
  if (!audioIsPlaying() && files.size()) {
    if (!audioConnecttoSD(files[playNo].path.c_str())) {
      files.erase(files.begin() + playNo);
    } else {
      playNo = (playNo + 1) % files.size();
    }
  }
}

/*--------------------------------------------------------------------------------
 * Optional
 *--------------------------------------------------------------------------------*/
void audio_info(const char *info) {
  Serial.print("info        ");
  Serial.println(info);
}
void audio_id3data(const char *info) {  //id3 metadata
  Serial.print("id3data     ");
  Serial.println(info);
}
void audio_eof_mp3(const char *info) {  //end of file
  Serial.print("eof_mp3     ");
  Serial.println(info);
}
void audio_showstation(const char *info) {
  Serial.print("station     ");
  Serial.println(info);
}
void audio_showstreamtitle(const char *info) {
  Serial.print("streamtitle ");
  Serial.println(info);
}
void audio_bitrate(const char *info) {
  Serial.print("bitrate     ");
  Serial.println(info);
}
void audio_commercial(const char *info) {  //duration in sec
  Serial.print("commercial  ");
  Serial.println(info);
}
void audio_icyurl(const char *info) {  //homepage
  Serial.print("icyurl      ");
  Serial.println(info);
}
void audio_lasthost(const char *info) {  //stream URL played
  Serial.print("lasthost    ");
  Serial.println(info);
}