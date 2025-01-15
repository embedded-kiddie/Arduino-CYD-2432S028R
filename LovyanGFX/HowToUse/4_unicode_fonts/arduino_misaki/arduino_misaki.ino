
// This example needs misakifont to run.
//
// URL : https://github.com/Tamakichi/Arduino-misakiUTF16
//

// Include the font data of Arduino-misakiUTF16.
#include "misakiUTF16FontData.h"

#define LGFX_AUTODETECT
#include <LovyanGFX.h>

static LGFX lcd;

// Use the lgfx::BDFfont class to set it up to use Arduino-misakiUTF16.
static constexpr lgfx::BDFfont misaki_font = {
  fdata,                // Font bitmap data
  ftable,               // Unicode font table
  sizeof(ftable) >> 1,  // Font table size
  8,                    // Font width
  4,                    // Font width (half width)
  7,                    // Font height
  6,                    // Baseline height
  8                     // Vertical cursor movement when starting a new line
};


void setup() {
  lcd.init();

  // By specifying the created misaki_font as an argument to setFont(),
  // you can use it in print(), drawString(), etc.
  lcd.setFont(&misaki_font);

  lcd.setTextWrap(true, true);
}

void loop() {
  lcd.setTextColor(0x808080U | random(0xFFFFFF), 0x7F7F7FU & random(0x10000));

  lcd.print("美さきフォントは8x8のコンパクトなフォントです。");
  lcd.print("Arduino-misakiUTF16は、教育漢字1,006字(小学校で習う漢字）＋ひらがな・カタカナ・記号・半角等の1,710字にしぼって収録されています。");
  lcd.print("Hello");
  lcd.print("ＨＥＬＬＯ");
  lcd.print("こんにちは");
  delay(1000);
}
