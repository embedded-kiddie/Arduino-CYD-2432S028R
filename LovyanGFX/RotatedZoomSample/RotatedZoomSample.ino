// Verify that auto-detection and manual configuration match
#define USE_AUTODETECT false

#if USE_AUTODETECT
// D-duino-32 XS, WT32-SC01, and PyBadge are not supported since the panel ID cannot be read.
#define LGFX_AUTODETECT
#include <LovyanGFX.h>
#else
#include <LovyanGFX.h>
// false: (micro-USB x 1 type)
// true : (micro-USB x 1 + USB-C x 1 type)
#define DISPLAY_CYD_2USB  false
#include "LGFX_CYD_2432S028R.hpp"
#endif // USE_AUTODETECT

static LGFX lcd;
static LGFX_Sprite sprite1(&lcd);
static LGFX_Sprite sprite2(&lcd);
static LGFX_Sprite* sprites[2] = {&sprite1, &sprite2};
static int32_t width = 280;
static size_t count = 0;

void setup(void)
{
  lcd.init();
  lcd.setPivot(lcd.width()>>1, lcd.height()>>1);
  width = std::min(width, (std::max(lcd.width(), lcd.height())+10)) | 1;
  for (int i = 0; i < 2; ++i) {
    sprites[i]->setColorDepth(8);
    sprites[i]->createSprite(width, width);
    sprites[i]->createPalette();
  }
}

void loop(void)
{
  ++count;
  bool flip = count & 1;
  for (int i = 0; i < 256; ++i) {
    sprites[flip]->setPaletteColor(i, ((i-count-1) & 0x7F)<<1, ((i-count-1) & 0xFF), ((i-count-1) & 0x3F)<<2);
  }
  sprites[!flip]->clearClipRect();
  sprites[!flip]->setColor(count);
  sprites[!flip]->fillRect(0,0,width,3);
  sprites[!flip]->fillRect(0,0,3,width);
  sprites[!flip]->fillRect(width-3,0,3,width);
  sprites[!flip]->fillRect(0,width-3,width,3);
  sprites[!flip]->setClipRect(3,3,width-6,width-6);
  sprites[!flip]->pushRotateZoom(sprites[flip], width>>1, (width>>1)+10, ((float)count)*.5, 0.9, 0.95);
  sprites[flip]->pushSprite((lcd.width() - width) >> 1, (lcd.height() - width) >> 1);
}