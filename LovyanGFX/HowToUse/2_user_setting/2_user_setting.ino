// Verify that auto-detection and manual configuration match
#define USE_AUTODETECT true

#if USE_AUTODETECT
// D-duino-32 XS, WT32-SC01, and PyBadge are not supported since the panel ID cannot be read.
#define LGFX_AUTODETECT
#include <LovyanGFX.h>
#else
#include <LovyanGFX.h>
#include "LGFX_CYD_2432S028R_ST7789.hpp"
#endif

// false: execute lcd.calibrateTouch()
#define CALIBRATED false

// Create instance
LGFX lcd;

void setup(void) {
  Serial.begin(115200);

  // Initializing the SPI bus and the panel
  lcd.init();

  lcd.setTextSize((std::max(lcd.width(), lcd.height()) + 255) >> 8);
  if (lcd.width() < lcd.height()) {
    lcd.setRotation(lcd.getRotation() ^ 1);
  }

  if (CALIBRATED) {
    uint16_t cal[8] = {
       248, // x_min
      3800, // y_min
       238, // x_min
       198, // y_max
      3856, // x_max
      3792, // y_min
      3841, // x_max
       192  // y_max
    };

    // https://github.com/lovyan03/LovyanGFX/blob/master/src/lgfx/v1/panel/Panel_Device.cpp#L367-L378
    lcd.setTouchCalibrate(cal);
  }

  // Calibrate touch when enabled (optional)
  else if (lcd.touch()) {
    // Draw guide text on the screen.
    lcd.setTextDatum(textdatum_t::middle_center);
    lcd.drawString("touch the arrow marker.", lcd.width() >> 1, lcd.height() >> 1);
    lcd.setTextDatum(textdatum_t::top_left);

    // You will need to calibrate by touching the four corners of the screen.
    uint16_t fg = TFT_WHITE;
    uint16_t bg = TFT_BLACK;
    if (lcd.isEPD()) {
      std::swap(fg, bg);
    }

    uint16_t cal[8];
    lcd.calibrateTouch(cal, fg, bg, std::max(lcd.width(), lcd.height()) >> 3);

    // https://github.com/lovyan03/LovyanGFX/discussions/539
    Serial.print("\nuint16_t cal[8] = { ");
    for (int i = 0; i < 8; i++) {
      Serial.printf("%d%s", cal[i], (i < 7 ? ", " : " };\n"));
    }
    Serial.print("lcd.setTouchCalibrate(cal);\n");
  }

  lcd.fillScreen(TFT_BLACK);
}

uint32_t count = ~0;
void loop(void) {
  lcd.startWrite();
  lcd.setRotation(++count & 7);
  lcd.setColorDepth((count & 8) ? 16 : 24);

  lcd.setTextColor(TFT_WHITE);
  lcd.drawNumber(lcd.getRotation(), 16, 0);

  lcd.setTextColor(0xFF0000U);
  lcd.drawString("R", 30, 16);
  lcd.setTextColor(0x00FF00U);
  lcd.drawString("G", 40, 16);
  lcd.setTextColor(0x0000FFU);
  lcd.drawString("B", 50, 16);

  lcd.drawRect(30, 30, lcd.width() - 60, lcd.height() - 60, count * 7);
  lcd.drawFastHLine(0, 0, 10);

  lcd.endWrite();

  int32_t x, y;
  lgfx::v1::touch_point_t tp;
  if (lcd.getTouch(&x, &y)) {
    lcd.getTouchRaw(&tp, 1);
    lcd.fillRect(x - 2, y - 2, 5, 5, count * 7);
    Serial.printf("x: %d (raw: %d), y: %d (raw: %d)\n", x, tp.x, y, tp.y);
  }
}