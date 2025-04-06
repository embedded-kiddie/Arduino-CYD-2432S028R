// All necessary files are included
#include "CYD28_audio.h"

// 1MHz --> 10MHz or more?
#define SD_CLOCK  10000000
#define SD_CS     SS

// Define in CYD_Audio.h   '#define SDFATFS_USED'
// Define in SdFatConfig.h '#define USE_UTF8_LONG_NAMES 1'
#ifdef SDFATFS_USED
#define SD        SD_SDFAT
#define SD_CONFIG SD_CS, SD_CLOCK
#define BUF_SIZE  64
#else
#define SD_CONFIG SD_CS, SPI, SD_CLOCK
#endif

/*--------------------------------------------------------------------------------
 * File name and size for GetFileList()
 *--------------------------------------------------------------------------------*/
#include <string>
#include <vector>
#include <exception>

typedef struct {
  std::string path;
  size_t      size;
  bool        isDirectory;
  bool        isSelected;
} FileInfo_t;

static std::vector<FileInfo_t> files;
static int playNo = 0;

/*--------------------------------------------------------------------------------
 * A function to get a list of files in a specified directory.
 *--------------------------------------------------------------------------------*/
void GetFileList(fs::FS &fs, const char *dirname, uint8_t levels, std::vector<FileInfo_t> &files) {
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
      GetFileList(fs, path.c_str(), levels - 1, files);
#else
      GetFileList(fs, file.path(), levels - 1, files);
#endif
    }

    else if (!isDir) {
      // Add full path to vector
      // file.path(), file.name(), file.size()
      // https://cpprefjp.github.io/reference/exception/exception.html
      // https://stackoverflow.com/questions/27609839/about-c-vectorpush-back-exceptions-ellipsis-catch-useful
      try {
#ifdef SDFATFS_USED
        files.push_back({path, (size_t)file.fileSize(), isDir, false});
#else
        files.push_back({file.path(), file.size(), isDir, false});
#endif
      } catch (const std::exception &e) {
        Serial.printf("Exception: %s\n", e.what());
        return;
      }
    }

    file = root.openNextFile();
  }

  std::sort(files.begin(), files.end(), [](FileInfo_t &a, FileInfo_t &b) {
    return a.path.compare(b.path) > 0 ? true : false;
  });
}

void setup() {
  Serial.begin(115200);
  while (millis() < 1000);

  audioInit();

  if (!SD.begin(SD_CONFIG)) {
    Serial.println("Cannot begin SD.");
    while (1);
  }

  files.clear();
  GetFileList(SD, "/MP3Player", 2, files);
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

// optional
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
