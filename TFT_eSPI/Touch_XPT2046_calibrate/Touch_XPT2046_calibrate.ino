/*----------------------------------------------------------------------
 * Generate the calibration values, reported to the Serial Monitor.
 *----------------------------------------------------------------------*/
#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

#if   0
#include <XPT2046_Bitbang.h>
#else
#include <XPT2046_Touchscreen.h>
#endif
#include "XPT2046_ScreenPoint.h"

#if defined (_XPT2046_Touchscreen_h_)
XPT2046_ScreenPoint sp(TOUCH_CS, TOUCH_IRQ);
#endif

#if defined (XPT2046_Bitbang_h)
XPT2046_ScreenPoint sp(TOUCH_MOSI, TOUCH_MISO, TOUCH_CLK, TOUCH_CS);
#endif

#define ROTATION    0 // Panel: CW --> Screen: CCW (0,2: portrait / 1,3: landscape)
#define CALIBRATED  false // false: Execute calibrateTouch()

/*----------------------------------------------------------------------
 * Setup LCD and touch panel
 *----------------------------------------------------------------------*/
void setup() {
  // Use serial port
  Serial.begin(115200);
  while (!Serial || millis() < 1000);

  // Initialise the TFT screen
  tft.init();
  tft.setRotation(ROTATION);

#if defined (_XPT2046_Touchscreen_h_)
  // assign the CYD touch panel to VSPI which is different from that of the display (HSPI).
  // https://github.com/espressif/arduino-esp32/blob/master/libraries/SPI/src/SPI.cpp#L333-L337
  #if 0
    SPI.begin(TOUCH_CLK, TOUCH_MISO, TOUCH_MOSI, TOUCH_CS); // 'SPI' is assigned to VSPI by default
    sp.begin(tft.width(), tft.height(), ROTATION);
  #else
    static SPIClass sp_spi = SPIClass(HSPI /*TOUCH_SPI_BUS*/); // both HSPI & VSPI will work
    sp_spi.begin(TOUCH_CLK, TOUCH_MISO, TOUCH_MOSI, TOUCH_CS);
    sp.begin(sp_spi, tft.width(), tft.height(), ROTATION);
  #endif
#endif

#if defined (XPT2046_Bitbang_h)
  sp.begin(tft.width(), tft.height(), ROTATION);
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
  printf(".cal = {");
  for (int i = 0; i < 4; ++i) {
    printf("%d, ", cal[i]);
  }
  printf("%d}\n", ROTATION);

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

/*----------------------------------------------------------------------
 * Follow the touched point 
 *----------------------------------------------------------------------*/
void loop(void) {
#if 1
  uint16_t x, y;
  if (sp.getTouch(&x, &y)) {
    Serial.println("x: " + String(x) + ", y: " + String(y));

    // Draw a white spot at the detected coordinates
    tft.fillCircle(x, y, 2, TFT_WHITE);
  }
#else
  if (sp.touched()) {
    uint16_t x, y;
    bool touched = sp.getTouch(&x, &y);
    Serial.printf("touched: %d, x: %d, y: %d\n", touched, x, y);
  }
#endif
}
