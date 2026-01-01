# CYD MP3 Music Player

![CYD MP3 Music Player](assets/CYD-MP3Player.gif)

## 1. Feature

- GUI by [LVGL][1]
- Built-in DAC and amplifier can directly drive a speaker connected to CYD
- Can manage approximately 3,000 music files [^1]
- Can display the cover photo for each album
- "**Playlist**" to display music titles, artist names, and album names
- "**Album List**" to manage the albums you want to play
- Heart-shaped "**Favorites**" button to play only selected files
- Power saving mode to turn off the LCD after a set time, and a sleep timer to shut down the device

## 2. Screens

![CYD-MP3Player - Screens](assets/CYD-MP3Player-Screens.png)

- **Screen: Main**  
  Controls the playback of audio files included in the playlist.

- **Screen: Playlist**  
  A list of audio file titles, artists, and album names.

- **Screen: Album List**  
  Manages "albums" that contain audio files recorded on a single CD. Albums with a check mark will be included in the playlist.  
  
  In addition to the default list "All", you can create new some lists.

- **Screen: Setting**  
  The number of audio files that can be included in a playlist is limited to approximately 750.   
  
  By creating and switching between several subfolders (called "**Partition**" in this application) on the SD card, you can manage a total of over 3000 files.  
  
  You can also set the time until the backlight turns off and the sleep timer.

## 3. Hardware Requirements


## 4. Software Requirements

### 4.1. Arduino IDE
| Name                       | Version      |
| -------------------------- | ------------ |
| Arduino IDE                | 2.3.4 and up |


### 4.2. Platform board package
| Name                       | Version     |
| -------------------------- | ----------- |
| esp32 by Espressif Systems | 2.0.17 [^2] |

Select [ESP32 Dev Module][2] or [ESP32-2432S028R CYD][3] as a board type to fit your board.

### 4.3. Libraries
| Name                                | Version      | 
| ----------------------------------- | ------------ | 
| [LVGL][4] by kisvegabor             | 9.2.2 and up | 
| [LovyanGFX][5] by lovyan03          | 1.2.7        | 
| [SdFat][6] by Bill Greiman          | 2.3.0        | 
| [ArduinoJson][7] by Benoit Blanchon | 7.4.2        | 

### 4.4. Library configuration

- **LVGL**  
  After installing LVGL, configure `lv_conf.h` by referring to the official document "[Configure LVGL][8]". Some samples of `lv_conf.h` for this application are provided in the [lv_conf directory](lv_conf). For details, see [README.md](lv_conf/README.md).

- **SdFat**  
  To handle long filenames and multibyte characters, uncomment the definition of the symbol `USE_UTF8_LONG_NAMES` in [libraries/SdFat/src/SdFatConfig.h][9] under your sketchbook folder.

## 5. Configuration and Compile / Upload

### 5.1. Edit config.h

Open [`config.h`](config.h) in the Arduino IDE and follow the comments to modify the default settings as desired.

### 5.2. Compile / Upload
Set the following two items from the "Tools" menu in the Arduino IDE.

| Item             | Selection                             | 
| ---------------- |-------------------------------------- |
| Partition Scheme | **"Huge App (3MB No OTA/1MB SPIFFS)"** |
| Upload Speed     |**"460800"**                           |

## 6. How To Use
This application is designed to take albums ripped from CDs and save them directly to your SD card. In addition to `.mp3`, the `.m4a` and `.wav` audio file formats are supported.

### 6.1. About "Partition"
Due to the SRAM capacity of the MCU, if you plan to store a large number of albums, it is recommended that you create subfolders (up to 5) and limit the number of albums to arround 50 titles and the number of audio files to arround 750, in each subfolder.

In this application, such subfolder is named as "Partition" and can be selected in the **"Setting"** screen.

**Note:** If you have more than 750+α (α is around 10), audio files, they will no longer fit in the playlist and management will become a hassle.

### 6.2. Shuffle Mode
"**Shuffle**" works as bellow:

- (a) continues to randomly select and add albums to the playlist until the total number of audio files exceeds 750
- (b) and finally randomly sorts the playlist again.

However, due to the "750" limit for audio files, when "**Shuffle**" is OFF, the behavior will differ depending on whether you select an individual partition or "All".

When you select an individual partition, albums will be added to the playlist in ascending order, but when you select "All", only (a) will be performed.

### 6.3. Album List
Pressing the "Keyboard" button under the dropdown will create an empty list, so enter a list name, close the keyboard, select the album you want to add, and finally press the "Save" button.

![Album List](assets/CYD-MP3Player-AlbumList.gif)

The "Keyboard" button is also used to edit an existing list.

### 6.4. Album Cover Photo
The "**Main Screen**" displays one of the 10 default images randomly selected. Besides the default image, you can add an album cover photo named `@photo.jpg` to your album folder.

Due to memory capacity limitations of the MCU, this `@photo.jpg` must be 96x96 and its size must be 6KB or less.

To generate the `@photo.jpg` image, use something like [GIMP][10] and it's good to set the compression rate to around 50-75%.

### 6.5. Backlight / Sleep Timer
The "**Backlight**" setting not only turns off the LCD illumination but also stops the clock to the LCD, reducing power consumption by approximately 40%.

The "**Sleep Timer**" will put the MCU into deep sleep mode after the set time has elapsed. To recover from this state, press the reset button or cycle the power.

### 6.6. Auto Saving
Some UI-related parameters (e.g. "**Shuffle**", "**Favorite**", "**Partition**" and so on) are automatically saved to the SD card between songs or when you pause playback, and are restored when you power cycle the device.

## Known Issues

- When using the built-in DAC and amplifier, there will be a "click" sound when powering up and when pausing/resume playback.

- This application is designed to save memory, but it may occasionally crash 😅. If this occurs frequently, try reducing the value of `MP3_PERTITION_FILES` (default is 750) in [MP3Player.h](MP3Player.h).

## Have Fun!
If you find any issues or have suggestions, please report in [Issues][11] or [Discussions][12] 🥰

----------

[^1]: Estimated number of audio files that can be stored on a 32GB microSD card.

[^2]: In version 3.x, the I2S driver for the internal DAC is deprecated and does not work properly.

[1]: https://lvgl.io/ "LVGL — Light and Versatile Embedded Graphics Library"
[2]: https://github.com/espressif/arduino-esp32/tree/master/variants/esp32 "arduino-esp32/variants/esp32 at master · espressif/arduino-esp32"
[3]: https://github.com/espressif/arduino-esp32/tree/master/variants/jczn_2432s028r "arduino-esp32/variants/jczn_2432s028r at master · espressif/arduino-esp32"
[4]: https://github.com/lvgl/lvgl "lvgl/lvgl: Embedded graphics library to create beautiful UIs for any MCU, MPU and display type."
[5]: https://github.com/lovyan03/LovyanGFX "lovyan03/LovyanGFX: SPI LCD graphics library for ESP32 (ESP-IDF/ArduinoESP32) / ESP8266 (ArduinoESP8266) / SAMD51(Seeed ArduinoSAMD51)"
[6]: https://github.com/greiman/SdFat "greiman/SdFat: Arduino FAT16/FAT32 exFAT Library"
[7]: https://github.com/bblanchon/ArduinoJson "bblanchon/ArduinoJson: 📟 JSON library for Arduino and embedded C++. Simple and efficient."
[8]: https://github.com/greiman/SdFat/blob/master/src/SdFatConfig.h#L34-L35 "SdFat/src/SdFatConfig.h at master · greiman/SdFat"
[9]: https://docs.lvgl.io/master/integration/frameworks/arduino.html#configure-lvgl "Arduino - LVGL 9.5 documentation"
[10]: https://www.gimp.org/ "GIMP - GNU Image Manipulation Program"
[11]: https://google.com/
[12]: https://google.com/
