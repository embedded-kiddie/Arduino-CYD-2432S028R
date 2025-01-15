# TFT_graphicstest_PDQ

## Test environments

### Hardware

- ESP32-2432S028 (ESP-WROOM-32) USB x 2 type
    - Panel driver: ST7789

### Software

- Arduino IDE: Version 2.3.4
- ESP32 board package: [v3.1.1][1]
    - Board type: ESP32-2432S028R CYD
    - [pins_arduino.h][2]
- Bodmer/TFT_eSPI: [V2.5.43][3]
- lovyan03/LovyanGFX: [1.2.0][4]

## Results

| Benchmark               |   TFT_eSPI |  LovyanGFX |
| ----------------------- | ----------:| ----------:|
| HaD pushColor           |   265251   | **258483** |
| Screen fill             |    15805   |  **15505** |
| Text                    |  **11764** |    18605   |
| Pixels                  | **177756** |   180681   |
| Lines                   |   196744   | **186382** |
| Horiz/Vert Lines        |     8059   |   **7645** |
| Rectangles (outline)    |     4954   |   **4682** |
| Rectangles (filled)     |   164526   | **161637** |
| Circles (filled)        |  **29643** |    37775   |
| Circles (outline)       |    19708   |  **19009** |
| Triangles (outline)     |    12291   |  **11030** |
| Triangles (filled)      |    61018   |  **57283** |
| Rounded rects (outline) |    11387   |   **8205** |
| Rounded rects (filled)  |   167503   | **164477** |

Unit: milliseconds

[1]: https://github.com/espressif/arduino-esp32/releases/tag/3.1.1 "Release Arduino Release v3.1.1 based on ESP-IDF v5.3.2 · espressif/arduino-esp32"
[2]: https://github.com/espressif/arduino-esp32/tree/master/variants/jczn_2432s028r "arduino-esp32/variants/jczn_2432s028r at master · espressif/arduino-esp32"
[3]: https://github.com/Bodmer/TFT_eSPI/releases/tag/V2.5.43 "Release Bug fixes · Bodmer/TFT_eSPI"
[4]: https://github.com/lovyan03/LovyanGFX/releases/tag/1.2.0 "Release 1.2.0 · lovyan03/LovyanGFX"
