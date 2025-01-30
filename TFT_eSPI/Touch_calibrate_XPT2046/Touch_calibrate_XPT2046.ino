/*
  Sketch to generate the setup() calibration values,
  these are reported to the Serial Monitor.
*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

// https://github.com/espressif/arduino-esp32/blob/master/variants/jczn_2432s028r/pins_arduino.h
#define XPT2046_MOSI  CYD_TP_MOSI
#define XPT2046_MISO  CYD_TP_MISO
#define XPT2046_CLK   CYD_TP_CLK
#define XPT2046_CS    CYD_TP_CS
#define XPT2046_IRQ   CYD_TP_IRQ

#include "XPT2046_ScreenPoint.h"

SPIClass ts_spi = SPIClass(CYD_TP_SPI_BUS); // VSPI
XPT2046_ScreenPoint ts(XPT2046_CS, XPT2046_IRQ);

#define ROTATION  3   // Panel: CW --> Screen: CCW (0,2: portrait / 1,3: landscape)

#define CALIBRATED true // false: Execute calibrateTouch()

//------------------------------------------------------------------------------------------
void setup() {
  // Use serial port
  Serial.begin(115200);
  while (!Serial || millis() < 1000);

  // Initialise the TFT screen
  tft.init();
  tft.setRotation(ROTATION);

  // Initialise the touch screen
  ts_spi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  ts.begin(ts_spi);

  ts.init(tft.width(), tft.height());
  ts.setRotation(ROTATION);

#if   0
  // Run with default parameters without calibration.
  ;

#elif CALIBRATED
  // Set up calibrated data and run.
  // Please note that the calibration settings must be updated 
  // whenever the orientation is changed from the orientation 
  // used during calibration.
  const float calData[][4] = {
    {0.0657, 0.0880, -16.1129, -13.5261},
    {0.0883, 0.0660, -13.2114, -15.5541},
    {0.0662, 0.0882, -13.9073, -28.7110},
    {0.0894, 0.0674, -32.0140, -18.5705}
  };
  ts.setTouch(calData[ROTATION]);

#else
  // Calibrate the touch screen and retrieve the scaling factors.
  ts.calibrateTouch(&tft);
#endif

  // Clear the screen
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);

#ifdef _TFT_eSPIH_
  tft.setTextDatum(CC_DATUM);
  tft.drawString("Touch screen to test!", tft.width() / 2, tft.height() / 2, 2);
#else
  tft.setCursor(10, tft.height() / 2);
  tft.print("Touch screen to test!");
#endif
}

//------------------------------------------------------------------------------------------
void loop(void) {
  uint16_t x, y;
  if (ts.getTouch(&x, &y)) {
    // Draw a white spot at the detected coordinates
    tft.fillCircle(x, y, 2, TFT_WHITE);
  }
}