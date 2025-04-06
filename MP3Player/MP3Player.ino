// All necessary files are included
#include "CYD28_audio.h"

// 1MHz --> 10MHz or more?
#define SD_CLOCK  10000000
#define SD_CS     SS

// Defined in CYD_Audio.h
#ifdef SDFATFS_USED
#define SD        SD_SDFAT
#define SD_CONFIG SD_CS, SD_CLOCK
#else
#define SD_CONFIG SD_CS, SPI, SD_CLOCK
#endif

void setup() {
  Serial.begin(115200);
  while (millis() < 1000);

  if (!SD.begin(SD_CONFIG)) {
    Serial.println("Cannot begin SD.");
    while (1);
  }

  audioInit();
  delay(100); // Wait until the task on Core 1 is ready to receive a command
  audioConnecttoSD("/test.mp3");
}

void loop() {
  if (!audioIsPlaying()) {
    audioConnecttoSD("/test.mp3");
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
