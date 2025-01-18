/*
  Sketch to generate the setup() calibration values,
  these are reported to the Serial Monitor.
*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

// https://github.com/espressif/arduino-esp32/blob/master/variants/jczn_2432s028r/pins_arduino.h
#define XPT2046_IRQ   CYD_TP_IRQ
#define XPT2046_MOSI  CYD_TP_MOSI
#define XPT2046_MISO  CYD_TP_MISO
#define XPT2046_CLK   CYD_TP_CLK
#define XPT2046_CS    CYD_TP_CS

#include "XPT2046_ScreenPoint.h"

SPIClass vspi = SPIClass(VSPI);
XPT2046_ScreenPoint ts(XPT2046_CS, XPT2046_IRQ);

#define ROTATION  1 // landscape

//------------------------------------------------------------------------------------------
void setup() {
  // Use serial port
  Serial.begin(115200);
  while (!Serial || millis() < 1000);

  // Initialise the TFT screen
  tft.init();
  tft.setRotation(ROTATION);

  // Initialise the touch screen
  vspi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  ts.begin(vspi);
  ts.setRotation(ROTATION);

#if   0
  // Run with default parameters without calibration
  ts.init(tft.width(), tft.height());
#elif 0
  // Calibrate the touch screen and retrieve the scaling factors
  ts.calibrateTouch(&tft);
#else
  // Set up calibrated data and run
  float calData[4] = {0.0879, 0.0665, -14.3844, -18.8833};
  ts.setTouch(calData);
  ts.init(tft.width(), tft.height());
#endif

  // Clear the screen
  tft.fillScreen(TFT_BLACK);
  tft.drawCentreString("Touch screen to test!", tft.width() / 2, tft.height() / 2, 2);
}

//------------------------------------------------------------------------------------------
void loop(void) {
  uint16_t x, y;
  if (ts.getTouch(&x, &y)) {
    // Draw a white spot at the detected coordinates
    tft.fillCircle(x, y, 2, TFT_WHITE);
  }
}