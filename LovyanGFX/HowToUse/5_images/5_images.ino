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

extern const uint8_t  rgb888[];
extern const uint8_t  bgr888[];
extern const uint16_t swap565[];
extern const uint16_t rgb565[];
extern const uint8_t  rgb332[];

static constexpr int image_width = 33;
static constexpr int image_height = 31;
//----------------------------------------------------------------------------

static LGFX lcd;

void setup(void) {
  lcd.init();
  lcd.startWrite();

  lcd.getPanel();
}

void loop(void) {

/*
There are several functions for drawing image data.

Method 1. Set the drawing range in advance, then specify the length of the image to draw
Method 2. Specify the coordinates, width and height to draw the image
*/

/*----------------------------------------------------------------------------
Method 1. Set the drawing range in advance, then specify the length of the image to draw

With this method, set the drawing range using setWindow/setAddrWindow(),
then specify the length of the image data using writePixels()/pushPixels() to draw.

  setWindow( x0, y0, x1, y1 );   // Specify the drawing range by the top left and bottom right coordinates.
  setAddrWindow( x, y, w, h );   // Specify the drawing range by the top left coordinate, width, and height.

The operation by setWindow() is not guaranteed if you specify coordinates outside the screen.
If setAddrWindow() is specified outside the drawing range, it will be automatically adjusted to fit within the range.
Please note that as a result of automatic adjustment, the actual width and height may be smaller than the specified values.

  writePixels   ( *data, len, swap );  // Draw an image. (Requires startWrite() beforehand and endWrite() afterward.)
  pushPixels    ( *data, len, swap );  // Draw an image. (startWrite() and endWrite() are not required.)

The function writePixels() is from AdafruitGFX, and pushPixels() is a function from TFT_eSPI.
The drawn content is the same, but the difference is whether startWrite()/endWrite() is executed automatically.

1st argument: Pointer to image data (color format will be converted according to the data type)
2nd argument: The number of pixels of the image data (note that this is not the number of bytes).
3rd argument: Byte order conversion flag (if omitted, the value previously set by the setSwapBytes() will be used.)

The color format is converted based on the data type of the 1st argument as follows:
  For uint8_t*,  convert as  8-bit color RGB332.
  For uint16_t*, convert as 16-bit color RGB565.
  For void*,     convert as 24-bit color RGB888.
  (Since there is no 3-byte primitive type, the void* type is converted as 24-bit color.)

Color format conversion is automatically performed according to the LCD color depth mode.
*/
  lcd.clear(TFT_DARKGREY);
  lcd.setColorDepth(16);  // Set the LCD to 16-bit color mode.
  lcd.setSwapBytes(true); // Enables byte order conversion.
  int len = image_width * image_height;

  // The image width and height are preset with setAddrWindow() and then drawn with writePixels.
  lcd.setAddrWindow(0, 0, image_width, image_height); // Set the drawing range.
  lcd.writePixels((uint16_t*)rgb565, len);            // Draw 16-bit RGB565 image data.

  // If the data and byte order conversion does not match, the colors will be corrupted.
  lcd.setAddrWindow(0, 40, image_width, image_height);
  // You can specify the byte order conversion flag as the 3rd argument.
  // Drawing an RGB565 image without byte order conversion will make colors corrupted.
  lcd.writePixels((uint16_t*)rgb565, len, false);

  // If the drawing range does not match the width or height of the image, the results will be corrupted.
  lcd.setAddrWindow(-1, 80, image_width, image_height); // The X coordinate -1 (off screen) cannot be set correctly.
  lcd.writePixels((uint16_t*)rgb565, len);              // The image is corrupted because the width does not match.

  // If the image format does not match, the rendering result will be corrupted.
  lcd.setAddrWindow(0, 120, image_width, image_height);
  // The RGB565 data is intentionally cast to uint8_t and converted to an 8-bit RGB332 color.
  lcd.writePixels((uint8_t*)rgb565, len);  // Inconsistent image formats and types will disrupt the rendering.

  // If the image format matches, the appropriate color type conversion is performed.
  lcd.setAddrWindow(0, 160, image_width, image_height);
  lcd.writePixels((uint8_t*)rgb332, len);  // Even RGB332 data can be correctly drawn on a 16-bit color LCD.


// Image data is transmitted to the LCD in 1-byte units, starting from the data in the lowest memory address.
// For this reason, if you simply prepare 16-bit RGB565 data as a uint16_t array, the byte order will be swapped.
// In this case, you can use setSwapBytes(true) beforehand or specify true as the 3rd argument to convert the byte order.
// If you create the image data with the byte order swapped in advance, no conversion will be necessary.
// It will be advantageous in terms of speed.

  lcd.setAddrWindow(40,  0, image_width, image_height);
  lcd.writePixels((uint16_t*)swap565, len, false); // For byte-swapped image, you can disable byte order conversion.

  lcd.setAddrWindow(40, 40, image_width, image_height);
  lcd.writePixels((uint16_t*)swap565, len, true);  // Enabling byte order conversion will cause corrupted colors.

  lcd.setAddrWindow(40, 80, image_width, image_height);
  lcd.writePixels((void*)rgb888, len, true);  // 24-bit RGB888 with blue on the lower side requires byte order conversion.

  lcd.setAddrWindow(40, 120, image_width, image_height);
  lcd.writePixels((void*)bgr888, len, false); // 24-bit BGR888 with red at the lower end do not require byte order conversion.

  lcd.setAddrWindow(40, 160, image_width, image_height);
  lcd.writePixels((void*)bgr888, len, true);  // Incorrect setting will result in corrupted colors (red and blue will be swapped).

  lcd.display();
  delay(4000);
  lcd.clear(TFT_DARKGREY);

/*----------------------------------------------------------------------------
Method 2. Specify the coordinates, width and height to draw the image

In this method, you use the pushImage() to specify the drawing range and image data.

  pushImage( x, y, w, h, *data);    // Draw an image at the specified coordinates.

Unlike method 1, drawing will not be corrupted even if you specify coordinates that extend beyond the screen.
(The parts that extend beyond the screen will not be drawn.)
Since there is no argument to specify byte order conversion, you must set it beforehand using setSwapBytes().
As with method 1, color conversion is performed according to the data type.
*/

  lcd.setSwapBytes(true); // Enables byte order conversion.

  // Draw image data by specifying the destination coordinates and the image width and height.
  lcd.pushImage(   0, 0, image_width, image_height, (uint16_t*)rgb565); // Draw 16-bit RGB565 image data.

  // If the data and byte order conversion specifications do not match, the colors will be corrupted.
  // Specifying byte order conversion on an image that has already been converted will be corrupted.
  lcd.pushImage(   0, 40, image_width, image_height, (uint16_t*)swap565); 

  // Even if the drawing range goes off screen, the results will not be corrupted.
  // The X coordinate -1 (off screen) will not be corrupted.
  lcd.pushImage(-1, 80, image_width, image_height, (uint16_t*)rgb565);

  // If the data and type do not match, the rendering results will be corrupted.
  // Converting RGB565 data to uint8_t as RGB332 will result in corrupted.
  lcd.pushImage(0, 120, image_width, image_height, (uint8_t*)rgb565);

  // If the data and type match, the appropriate format conversion will be performed.
  lcd.pushImage(0, 160, image_width, image_height, (uint8_t*)rgb332); // It can also draw correctly with RGB332 data.


  lcd.setSwapBytes(false);   // Disable byte order conversion.
  lcd.pushImage( 40,   0, image_width, image_height, (uint8_t* )rgb332);  // OK. RGB332 data is not affected by byte order conversion.
  lcd.pushImage( 40,  40, image_width, image_height, (uint16_t*)rgb565);  // NG. RGB565 data requires byte order conversion.
  lcd.pushImage( 40,  80, image_width, image_height, (void*    )rgb888);  // NG. RGB888 data requires byte order conversion.
  lcd.pushImage( 40, 120, image_width, image_height, (uint16_t*)swap565); // OK. Byte order converted RGB565 will not be corrupted.
  lcd.pushImage( 40, 160, image_width, image_height, (void*    )bgr888);  // OK. Byte order converted RGB888 will not be corrupted.

  lcd.setSwapBytes(true);   // Enable byte order conversion.
  lcd.pushImage( 80,   0, image_width, image_height, (uint8_t* )rgb332);  // OK. RGB332 data is not affected by byte order conversion.
  lcd.pushImage( 80,  40, image_width, image_height, (uint16_t*)rgb565);  // OK. RGB565 data will not be corrupted.
  lcd.pushImage( 80,  80, image_width, image_height, (void*    )rgb888);  // OK. RGB888 data will not be corrupted.
  lcd.pushImage( 80, 120, image_width, image_height, (uint16_t*)swap565); // NG. Byte order converted RGB565 will be corrupted.
  lcd.pushImage( 80, 160, image_width, image_height, (void*    )bgr888);  // NG. Byte order converted RGB888 will be corrupted.

// You can also use the types defined in the lgfx:: namespace as data types.
// When casting to these types, the setSwapBytes() setting is ignored.
  lcd.pushImage(120,   0, image_width, image_height, (lgfx:: rgb332_t*) rgb332); // OK  8bit data
  lcd.pushImage(120,  40, image_width, image_height, (lgfx:: rgb565_t*) rgb565); // OK 16bit data
  lcd.pushImage(120,  80, image_width, image_height, (lgfx:: rgb888_t*) rgb888); // OK 24bit data
  lcd.pushImage(120, 120, image_width, image_height, (lgfx::swap565_t*)swap565); // OK Byte order converted 16-bit data
  lcd.pushImage(120, 160, image_width, image_height, (lgfx:: bgr888_t*) bgr888); // OK Byte order converted 24-bit data

// The 6th argument can be used to specify a transparent color. Areas with it's color will not be drawn.
  lcd.pushImage(160,   0, image_width, image_height, (lgfx:: rgb332_t*) rgb332, 0);                   // Black as transparent
  lcd.pushImage(160,  40, image_width, image_height, (lgfx:: rgb565_t*) rgb565, (uint8_t)0xE0);       // Red   as transparent
  lcd.pushImage(160,  80, image_width, image_height, (lgfx:: rgb888_t*) rgb888, (uint16_t)0x07E0);    // Green as transparent
  lcd.pushImage(160, 120, image_width, image_height, (lgfx::swap565_t*)swap565, (uint32_t)0x0000FFU); // Blue  as transparent
  lcd.pushImage(160, 160, image_width, image_height, (lgfx:: bgr888_t*) bgr888, TFT_WHITE);           // White as transparent

  lcd.display();
  delay(4000);
  lcd.clear(TFT_DARKGREY);

// The pushImageRotateZoom() allows you to rotate, zoom, and draw an image.
  for (int angle = 0; angle <= 360; ++angle) {
    lcd.pushImageRotateZoom
      ( lcd.width()  >> 2  // Destination center coordinate X
      , lcd.height() >> 1  // Destination center coordinate Y
      , image_width  >> 1  // Center coordinate X of the image
      , image_height >> 1  // Center coordinate Y of the image
      , angle              // Rotation angle
      , 3.0                // Drawing scale in X direction (a negative value will be inverted)
      , 3.0                // Drawing scale in Y direction (a negative value will be inverted)
      , image_width        // Image data width
      , image_height       // Image data height
      , rgb332             // Image data pointer
      );

// Anti-aliasing is enabled using the pushImageRotateZoomWithAA().
    lcd.pushImageRotateZoomWithAA
      ( lcd.width()*3>> 2
      , lcd.height() >> 1
      , image_width  >> 1
      , image_height >> 1
      , angle
      , 3.0
      , 3.0
      , image_width
      , image_height
      , rgb332
      );

    if ((angle % 36) == 0) { lcd.display(); }
  }

  lcd.clear(TFT_DARKGREY);

// The pushImageAffine() allows you to draw an image using an affine transformation.
// The parameters of the affine transformation are specified as a float array.
  {
    float matrix[6] = // Actual size display
      { 1.0,  0.0,  (float)lcd.width()  / 2
      , 0.0,  1.0,  (float)lcd.height() / 2 };
    lcd.pushImageAffine(matrix, image_width, image_height, rgb332);
  }

  lcd.display();
  delay(1000);
  lcd.clear(TFT_DARKGREY);

  {
    float matrix[6] = // Double horizontal display
      { 2.0,  0.0,  (float)lcd.width()  / 2
      , 0.0,  1.0,  (float)lcd.height() / 2 };
    lcd.pushImageAffine(matrix, image_width, image_height, rgb332);
  }

  lcd.display();
  delay(1000);
  lcd.clear(TFT_DARKGREY);

  {
    float matrix[6] = // Double vertical display
      { 1.0,  0.0,  (float)lcd.width()  / 2
      , 0.0,  2.0,  (float)lcd.height() / 2 };
    lcd.pushImageAffine(matrix, image_width, image_height, rgb332);
  }

  lcd.display();
  delay(1000);
  lcd.clear(TFT_DARKGREY);

  {
    float matrix[6] = // Diagonal transformation
      { 1.0, -0.4,  (float)lcd.width()  / 2
      , 0.0,  1.0,  (float)lcd.height() / 2 };
    lcd.pushImageAffine(matrix, image_width, image_height, rgb332);
  }

  lcd.display();
  delay(1000);
  lcd.clear(TFT_DARKGREY);

  // Anti-aliasing is enabled using the pushImageAffineWithAA().
  {
    float matrix[6] =
      { 1.0,  0.0,  (float)lcd.width()  / 2
      , 0.0,  1.0,  (float)lcd.height() / 2 };
    for (int i = -300; i < 300; i++) {
      float f = (float)i / 100;
      matrix[1] = f;
      matrix[3] = f;
      lcd.pushImageAffineWithAA(matrix, image_width, image_height, rgb332);

      if ((i % 30) == 0) { lcd.display(); }
    }
  }
}


//----------------------------------------------------------------------------
#define R 0x00,0x00,0xFF,
#define G 0x00,0xFF,0x00,
#define B 0xFF,0x00,0x00,
#define C 0xFF,0xFF,0x00,
#define M 0xFF,0x00,0xFF,
#define Y 0x00,0xFF,0xFF,
#define W 0xFF,0xFF,0xFF,
#define _ 0x00,0x00,0x00,
constexpr uint8_t rgb888[] = {
#include "image.h"
};
#undef R
#undef G
#undef B
#undef C
#undef M
#undef Y
#undef W
#undef _
//----------------------------------------------------------------------------
#define R 0xFF,0x00,0x00,
#define G 0x00,0xFF,0x00,
#define B 0x00,0x00,0xFF,
#define C 0x00,0xFF,0xFF,
#define M 0xFF,0x00,0xFF,
#define Y 0xFF,0xFF,0x00,
#define W 0xFF,0xFF,0xFF,
#define _ 0x00,0x00,0x00,
constexpr uint8_t bgr888[] = {
#include "image.h"
};
#undef R
#undef G
#undef B
#undef C
#undef M
#undef Y
#undef W
#undef _
//----------------------------------------------------------------------------
#define R 0x00F8,
#define G 0xE007,
#define B 0x1F00,
#define C 0xFF07,
#define M 0x1FF8,
#define Y 0xE0FF,
#define W 0xFFFF,
#define _ 0x0000,
constexpr uint16_t swap565[] = {
#include "image.h"
};
#undef R
#undef G
#undef B
#undef C
#undef M
#undef Y
#undef W
#undef _
//----------------------------------------------------------------------------
#define R 0xF800,
#define G 0x07E0,
#define B 0x001F,
#define C 0x07FF,
#define M 0xF81F,
#define Y 0xFFE0,
#define W 0xFFFF,
#define _ 0x0000,
constexpr uint16_t rgb565[] = {
#include "image.h"
};
#undef R
#undef G
#undef B
#undef C
#undef M
#undef Y
#undef W
#undef _
//----------------------------------------------------------------------------
#define R 0xE0,
#define G 0x1C,
#define B 0x03,
#define C 0x1F,
#define M 0xE3,
#define Y 0xFC,
#define W 0xFF,
#define _ 0x00,
constexpr uint8_t rgb332[] = {
#include "image.h"
};
#undef R
#undef G
#undef B
#undef C
#undef M
#undef Y
#undef W
#undef _
