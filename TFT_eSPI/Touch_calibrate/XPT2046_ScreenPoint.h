/*----------------------------------------------------------------------
 * Touch screen calibration for XPT2046_Touchscreen
 *
 * This program is based on the following article:
 * https://bytesnbits.co.uk/arduino-touchscreen-calibration-coding/
 *----------------------------------------------------------------------*/
#ifndef _XPT2046_SCREENPOINT_H_
#define _XPT2046_SCREENPOINT_H_

#include <math.h>
#include <XPT2046_Touchscreen.h>

// Graphics library
#if   defined (_TFT_eSPIH_)
#define GFX_TYPE  TFT_eSPI
#elif defined (_ADAFRUIT_GFX_H)
#define GFX_TYPE  Adafruit_GFX
#elif defined (_ARDUINO_TFT_H_)
#define GFX_TYPE  Arduino_TFT
#error use TFT_eSPI, Adafruit_GFX or GFX_Library_for_Arduino
#endif

#define _BLACK  0x0000
#define _WHITE  0xFFFF
#define _RED    0xF800

// Defining the class that inherits from XPT2046_Touchscreen class
class XPT2046_ScreenPoint : public XPT2046_Touchscreen {
  // Inheriting constructor from the parent class
  using XPT2046_Touchscreen::XPT2046_Touchscreen;

private:
  bool calibrated = false;
  uint16_t width = 0, height = 0;
  float xCalM = 0.0, yCalM = 0.0;  // gradients
  float xCalC = 0.0, yCalC = 0.0;  // y axis crossing points

public:
  void init(uint16_t w, uint16_t h) {
    width  = w;
    height = h;
  }

  void calibrateTouch(GFX_TYPE *tft) {
    if (width == 0 || height == 0) {
      init(tft->width(), tft->height());
    }

    TS_Point p;
    int16_t x1, y1, x2, y2;

    tft->fillScreen(_BLACK);  
    while (touched()); // wait for no touch

    tft->drawFastHLine(10, 20, 20, _RED);
    tft->drawFastVLine(20, 10, 20, _RED);

    while (!touched());
    delay(50); // wait for touch being stable

    p = getPoint();
    x1 = p.x;
    y1 = p.y;
    tft->drawFastHLine(10, 20, 20, _BLACK);
    tft->drawFastVLine(20, 10, 20, _BLACK);

    delay(500);
    while (touched()); // wait for no touch

    tft->drawFastHLine(width - 30, height - 20, 20, _RED);
    tft->drawFastVLine(width - 20, height - 30, 20, _RED);

    while (!touched());
    delay(50); // wait for touch being stable

    p = getPoint();
    x2 = p.x;
    y2 = p.y;
    tft->drawFastHLine(width - 30, height - 20, 20, _BLACK);
    tft->drawFastVLine(width - 20, height - 30, 20, _BLACK);

    int16_t xDist = width - 40;
    int16_t yDist = height - 40;

    // translate in form pos = m x val + c
    xCalM = (float)xDist / (float)(x2 - x1);
    xCalC = 20.0 - ((float)x1 * xCalM);
    yCalM = (float)yDist / (float)(y2 - y1);
    yCalC = 20.0 - ((float)y1 * yCalM);

    Serial.print("\nfloat calData[4] = {");
    Serial.print(xCalM, 4); Serial.print(", ");
    Serial.print(yCalM, 4); Serial.print(", ");
    Serial.print(xCalC, 4); Serial.print(", ");
    Serial.print(yCalC, 4); Serial.print("};\n");
    Serial.print("sp.setTouch(calData);\n");

    calibrated = true;
  }

  void setTouch(float *data) {
    xCalM = data[0];
    yCalM = data[1];
    xCalC = data[2];
    yCalC = data[3];
    calibrated = true;
  }

  bool getTouch(uint16_t *x, uint16_t *y, uint16_t threshold = 600) {
    if (touched()) {
      TS_Point p = getPoint();

      //Serial.println("x: " + String(p.x) + ", y: " + String(p.y) + ", z: " + String(p.z));

      if (p.z >= threshold) {
        if (calibrated) {
          int16_t xCoord = round((p.x * xCalM) + xCalC);
          int16_t yCoord = round((p.y * yCalM) + yCalC);
    
          if (xCoord < 0) xCoord = 0; else
          if (xCoord >= width ) xCoord = width  - 1;
          if (yCoord < 0) yCoord = 0; else
          if (yCoord >= height) yCoord = height - 1;
    
          *x = xCoord;
          *y = yCoord;
        } else {
          // https://randomnerdtutorials.com/lvgl-cheap-yellow-display-esp32-2432s028r/
          *x = map(p.x, 200, 3700, 0, width  - 1);
          *y = map(p.y, 240, 3800, 0, height - 1);
        }
        return true;
      }
    }
    return false;
  }
};

#endif // _XPT2046_SCREENPOINT_H_
