/*
  Sketch to generate the setup() calibration values,
  these are reported to the Serial Monitor.
*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

// https://github.com/espressif/arduino-esp32/blob/master/variansp/jczn_2432s028r/pins_arduino.h
#define XPT2046_MOSI  CYD_TP_MOSI
#define XPT2046_MISO  CYD_TP_MISO
#define XPT2046_CLK   CYD_TP_CLK
#define XPT2046_CS    CYD_TP_CS
#define XPT2046_IRQ   CYD_TP_IRQ
#define XPT2046_SPI   CYD_TP_SPI_BUS // VSPI

#include "XPT2046_ScreenPoint.h"

SPIClass sp_spi = SPIClass(XPT2046_SPI); 
XPT2046_ScreenPoint sp(XPT2046_CS, XPT2046_IRQ);

#define ROTATION  3 // Panel: CW --> Screen: CCW (0,2: portrait / 1,3: landscape)

#define CALIBRATED  false // false: Execute calibrateTouch()

//------------------------------------------------------------------------------------------
void setup() {
  // Use serial port
  Serial.begin(115200);
  while (!Serial || millis() < 1000);

  // Initialise the TFT screen
  tft.init();
  tft.setRotation(ROTATION);

  // Initialise the touch screen
  sp_spi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  sp.begin(sp_spi, tft.width(), tft.height(), ROTATION);

#if   0
  // Run with default parameters without calibration.
  ;

#elif CALIBRATED
  // Set up calibrated data and run.
  // Please note that the calibration settings must be updated 
  // whenever the orientation is changed from the orientation 
  // used during calibration.
  const uint16_t cal[][5] = {
    {590, 380, 3570, 3550, 0},
    {380, 510, 3560, 3560, 1},
    {520, 520, 3490, 3680, 2},
    {560, 590, 3720, 3580, 3}
  };

  sp.setTouch(cal[ROTATION]);

#else
  // Calibrate the touch screen and retrieve the scaling factors.
  uint16_t cal[5];
  sp.calibrateTouch(cal, &tft, TFT_WHITE, TFT_BLACK);

  printf("\n// XPT2046\n");
  printf(".cal = { ");
  for (int i = 0; i < 5; ++i) {
    printf("%d", cal[i]);
    printf(i < 4 ? ", " : ", 0, },\n");
  }

  sp.setTouch(static_cast<const uint16_t*>(cal));
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
  if (sp.getTouch(&x, &y)) {
    Serial.println("x: " + String(x) + ", y: " + String(y));

    // Draw a white spot at the detected coordinates
    tft.fillCircle(x, y, 2, TFT_WHITE);
  }
}