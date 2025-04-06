#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include "CYD28_audio.h"

// Digital I/O used
#define SD_CS     SS    //  5
#define SPI_MOSI  MOSI  // 23
#define SPI_MISO  MISO  // 19
#define SPI_SCK   SCK   // 18

void setup() {
  Serial.begin(115200);
  while (millis() < 1000);

  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
  SPI.setFrequency(10000000); // 1MHz --> 10MHz or more?
  if (!SD.begin(SD_CS)) {
    Serial.println("Cannot begin SD.");
    while (1);
  }

  audioInit();
  delay(100); // Wait until the task on Core 1 is ready to receive a command
  audioConnecttoSD("/test.mp3");
}

void loop() {
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
