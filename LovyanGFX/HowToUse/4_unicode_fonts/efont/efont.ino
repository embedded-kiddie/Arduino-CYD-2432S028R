// This example needs efont to run.
//
// URL : https://github.com/tanakamasayuki/efont
//

// Include a header corresponding to the character set used.
//#include <efontEnableAll.h>
//#include <efontEnableAscii.h>
//#include <efontEnableCJK.h>
//#include <efontEnableCn.h>
#include <efontEnableJa.h>
//#include <efontEnableJaMini.h>
//#include <efontEnableKr.h>
//#include <efontEnableTw.h>

// Include the font data of efont.
#include <efontFontData.h>

// Need to include efont before LovyanGFX.
#define LGFX_AUTODETECT
#include <LovyanGFX.h>

static LGFX lcd;

void setup() {
  lcd.init();

  // If you specify the argument efont to the setFont(),
  // you can use the efont with print(), drawString(), etc.
  lcd.setFont(&fonts::efont);

  lcd.setTextWrap(true, true);
}

void loop() {
  lcd.setTextColor(random(0x10000), random(0x10000));
  lcd.setTextSize(random(1, 3), random(1, 3));

  lcd.print("Hello");
  lcd.print("こんにちは");
  lcd.print("你好");
  lcd.print("안녕하세요");
  lcd.print("Доброе утро");
  lcd.print("Päivää");
  lcd.print("Здравствуйте");
  delay(1000);
}
