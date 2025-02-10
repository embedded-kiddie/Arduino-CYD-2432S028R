/*
  Sketch to generate the setup() calibration values,
  these are reported to the Serial Monitor.
*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "XPT2046_ScreenPoint.h"

#define ROTATION  3 // Panel: CW --> Screen: CCW (0,2: portrait / 1,3: landscape)
#define CALIBRATED  false // false: Execute calibrateTouch()

TFT_eSPI tft = TFT_eSPI();
XPT2046_ScreenPoint sp(TOUCH_CS, TOUCH_IRQ);

//------------------------------------------------------------------------------------------
void setup() {
  // Use serial port
  Serial.begin(115200);
  while (!Serial || millis() < 1000);

  // Initialise the TFT screen
  tft.init();
  tft.setRotation(ROTATION);

#if 0
  // The pinout of the CYD touch panel is different from that of the display.
  SPI.begin(TOUCH_CLK, TOUCH_MISO, TOUCH_MOSI, TOUCH_CS);
  sp.begin(tft.width(), tft.height(), ROTATION);
#else
  // Assign the CYD touch panel on a different SPI bus from that of the display.
  static SPIClass spi = SPIClass(TOUCH_SPI_BUS);
  spi.begin(TOUCH_CLK, TOUCH_MISO, TOUCH_MOSI, TOUCH_CS);
  sp.begin(spi, tft.width(), tft.height(), ROTATION);
#endif

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
