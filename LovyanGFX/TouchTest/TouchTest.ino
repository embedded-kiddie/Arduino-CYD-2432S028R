/*================================================================================
 * Touch screen test sketch for LovyanGFX
 *================================================================================*/

// Auto-detect and manual configuration settings
#define USE_AUTODETECT true

#if USE_AUTODETECT
// Some devices do not support auto-detect since the panel ID cannot be read.
#define LGFX_AUTODETECT
#include <LovyanGFX.h>
#else
// false: Panel driver: ILI9341 (micro-USB x 1 type)
// true : Panel driver: ST7789  (micro-USB x 1 + USB-C x 1 type)
#define DISPLAY_CYD_2USB  true
#include "LGFX_ESP32_2432S028R_CYD.hpp"
#endif // USE_AUTODETECT

static LGFX tft;

// Set to your screen resolution and rotation
#define TFT_WIDTH     240 // Panel width
#define TFT_HEIGHT    320 // Panel height
#define TFT_ROTATION  0   // 0, 2: Portrait / 1, 3: Landscape

//----------------------------------------------------------------------
// SD card configuration
//----------------------------------------------------------------------
#define SCREENSHORT true
#if SCREENSHORT
// #define USE_SDFAT
#include "../../LVGL/src/sdcard.hpp"
#endif

void screendump(void) {
#if SCREENSHORT
  if (Serial.available()) {
    Serial.readStringUntil('\n');
    Serial.println("SCREENSHORT");
    sdcard_setup();
    SaveBMP24(SD, "/demo.bmp", tft);
  }
#endif
}

//----------------------------------------------------------------------
// Perform the touch panel calibration if it is set to true
//----------------------------------------------------------------------
#define EXEC_CALIBRATION true

#if EXEC_CALIBRATION
static void calibrate_touch(uint16_t cal[8]) {
  tft.clear(TFT_BLACK);                   // Clear screen with background color
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set foreground color, background color
  tft.setFont(&fonts::Font2);             // https://lang-ship.com/blog/files/LovyanGFX/font/

  // Draw guide text on the screen.
  tft.setTextDatum(textdatum_t::middle_center);
  tft.drawString  ("Touch the arrow tips in order", tft.width() >> 1, tft.height() >> 1);
  tft.setTextDatum(textdatum_t::top_left);

  uint16_t fg = TFT_WHITE;
  uint16_t bg = TFT_BLACK;

  // Electronic Paper Display
  if (tft.isEPD()) {
    std::swap(fg, bg);
  }

  // You will need to calibrate by touching the four corners of the screen.
  tft.calibrateTouch(cal, fg, bg, std::max(tft.width(), tft.height()) >> 3);

  Serial.print("\nconst uint16_t cal[8] = { ");
  for (int i = 0; i < 8; i++) {
    Serial.printf("%d%s", cal[i], (i < 7 ? ", " : " };\n"));
  }
}
#endif // EXEC_CALIBRATION

static void tft_init(void) {
  tft.init();
  tft.initDMA();
  tft.setColorDepth(16);                  // Set to 16-bit (RGB565)
  tft.setRotation(TFT_ROTATION);          // Set panel rotation

  if (tft.touch()) {
#if EXEC_CALIBRATION
    uint16_t cal[8];
    calibrate_touch(cal);
#else
    // The following is equivalent to the `_touch_instance` setting in `LGFX_ESP32_2432S028R_CYD.hpp`.
    // The `cal[8]` can be replaced with the result displayed on the serial monitor after calibration.
    const uint16_t cal[8] = {
      240,   // x_min
      3700,  // y_min
      240,   // x_min
      200,   // y_max
      3800,  // x_max
      3700,  // y_min
      3800,  // x_max
      200    // y_max
    };
#endif
    tft.setTouchCalibrate((uint16_t*)cal);
  } else {
    Serial.println("Touch device not found.");
  }
}

void setup() {
  Serial.begin(115200);
  while (millis() < 1000);

  tft_init();
}

void loop() {
  uint16_t x, y;
  if (tft.getTouch(&x, &y)) {
    Serial.println("x: " + String(x) + ", y: " + String(y));

    // Draw a white spot at the detected coordinates
    tft.fillCircle(x, y, 2, TFT_WHITE);
  }
  screendump();
}