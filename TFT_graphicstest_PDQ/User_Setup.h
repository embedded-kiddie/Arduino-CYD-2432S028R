//                            USER DEFINED SETTINGS
//   Set driver type, fonts to be loaded, pins used and SPI control method etc
//
//   See the User_Setup_Select.h file if you wish to be able to define multiple
//   setups and then easily select which setup file is used by the compiler.
//
//   If this file is edited correctly then all the library example sketches should
//   run without the need to make any more changes for a particular hardware setup!
//   Note that some sketches are designed for a particular TFT pixel width/height

// User defined information reported by "Read_User_Setup" test & diagnostics example
#define USER_SETUP_INFO "User_Setup"

// Define to disable all #warnings in library (can be put in User_Setup_Select.h)
//#define DISABLE_ALL_LIBRARY_WARNINGS

#define CYD_2432S028R_1USB  0 // Panel driver: ILI9341 (micro-USB x 1 type)
#define CYD_2432S028R_2USB  1 // Panel driver: ST7789  (micro-USB x 1 + USB-C x 1 type)
#define CROWPANEL_HMI_2432  2 // CrowPanel HMI 2.4"/2.8" (LCD & touch share the SPI bus)

#define CYD_DISPLAY_TYPE    CROWPANEL_HMI_2432

//===================================================================================
// https://github.com/Elecrow-RD/CrowPanel-ESP32-Display-Course-File
// https://www.elecrow.com/wiki/esp32-display-282727-intelligent-touch-screen-wi-fi26ble-240320-hmi-display.html
//===================================================================================

// ##################################################################################
//
// Section 1. Call up the right driver file and any options for it
//
// ##################################################################################

// Only define one driver, the other ones must be commented out
#if   (CYD_DISPLAY_TYPE == CYD_2432S028R_2USB)
#define ST7789_DRIVER
#elif (CYD_DISPLAY_TYPE == CYD_2432S028R_1USB)
#define ILI9341_2_DRIVER
#else // CROWPANEL_HMI_2432
#define ILI9341_DRIVER
#endif

#define TFT_WIDTH  240
#define TFT_HEIGHT 320

// ##################################################################################
//
// Section 2. Define the pins that are used to interface with the display here
//
// ##################################################################################

// If a backlight control signal is available then define the TFT_BL pin in Section 2
// below. The backlight will be turned ON when tft.begin() is called, but the library
// needs to know if the LEDs are ON with the pin HIGH or LOW. If the LEDs are to be
// driven with a PWM signal or turned OFF/ON then this must be handled by the user
// sketch. e.g. with digitalWrite(TFT_BL, LOW);

#if     (CYD_DISPLAY_TYPE != CROWPANEL_HMI_2432)

// ESP32-2432S028R CYD
// https://github.com/espressif/arduino-esp32/blob/master/variants/jczn_2432s028r/pins_arduino.h
#ifndef CYD_TFT_DC
#define CYD_TFT_DC      2
#define CYD_TFT_MISO    12
#define CYD_TFT_MOSI    13
#define CYD_TFT_SCK     14
#define CYD_TFT_CS      15
#define CYD_TFT_RST     -1
#define CYD_TFT_BL      21
#define CYD_TP_MOSI     32
#define CYD_TP_MISO     39
#define CYD_TP_CLK      25
#define CYD_TP_CS       33
#define CYD_TP_IRQ      36
#define CYD_SD_SS       5
#define CYD_SD_MOSI     23
#define CYD_SD_MISO     19
#define CYD_SD_SCK      18
#define CYD_TFT_SPI_BUS HSPI
#define CYD_SD_SPI_BUS  VSPI
#endif

#else

// CrowPanel ESP32 HMI 2.8-inch
// https://github.com/Elecrow-RD/CrowPanel-ESP32-Display-Course-File
// https://www.elecrow.com/wiki/esp32-display-282727-intelligent-touch-screen-wi-fi26ble-240320-hmi-display.html
#define CYD_TFT_DC      2
#define CYD_TFT_MISO    12
#define CYD_TFT_MOSI    13
#define CYD_TFT_SCK     14
#define CYD_TFT_CS      15
#define CYD_TFT_RST     -1
#define CYD_TFT_BL      27
#define CYD_TP_MISO     CYD_TFT_MISO
#define CYD_TP_MOSI     CYD_TFT_MOSI
#define CYD_TP_CLK      CYD_TFT_SCK
#define CYD_TP_CS       33
#define CYD_TP_IRQ      38
#define CYD_SD_SS       5
#define CYD_SD_MOSI     23
#define CYD_SD_MISO     19
#define CYD_SD_SCK      18
#define CYD_TFT_SPI_BUS HSPI
#define CYD_SD_SPI_BUS  VSPI

#endif

#define TFT_BL   CYD_TFT_BL
#define TFT_BACKLIGHT_ON HIGH  // Level to turn ON back-light (HIGH or LOW)

// For ESP32 Dev board (only tested with GC9A01 display)
// The hardware SPI can be mapped to any pins
#define TFT_MISO CYD_TFT_MISO
#define TFT_MOSI CYD_TFT_MOSI
#define TFT_SCLK CYD_TFT_SCK
#define TFT_CS   CYD_TFT_CS
#define TFT_DC   CYD_TFT_DC
#define TFT_RST  CYD_TFT_RST

#define TOUCH_CS CYD_TP_CS

// ##################################################################################
//
// Section 3. Define the fonts that are to be used here
//
// ##################################################################################

// Comment out the #defines below with // to stop that font being loaded
// The ESP8366 and ESP32 have plenty of memory so commenting out fonts is not
// normally necessary. If all fonts are loaded the extra FLASH space required is
// about 17Kbytes. To save FLASH space only enable the fonts you need!

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
//#define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

// Comment out the #define below to stop the SPIFFS filing system and smooth font code being loaded
// this will save ~20kbytes of FLASH
#define SMOOTH_FONT

// ##################################################################################
//
// Section 4. Other options
//
// ##################################################################################

// Define the SPI clock frequency, this affects the graphics rendering speed. Too
// fast and the TFT driver will not keep up and display corruption appears.
// With an ILI9341 display 40MHz works OK, 80MHz sometimes fails
// With a ST7735 display more than 27MHz may not work (spurious pixels and lines)
// With an ILI9163 display 27 MHz works OK.
#if   (CYD_DISPLAY_TYPE == CYD_2432S028R_2USB)
#define SPI_FREQUENCY       80000000
#define SPI_READ_FREQUENCY  20000000
#elif (CYD_DISPLAY_TYPE == CYD_2432S028R_1USB)
#define SPI_FREQUENCY       40000000
#define SPI_READ_FREQUENCY  20000000
#else // CROWPANEL_HMI_2432
#define SPI_FREQUENCY       40000000
//#define SPI_FREQUENCY       15999999  // Original

// Optional reduced SPI frequency for reading TFT
#define SPI_READ_FREQUENCY  20000000  // 20MHz, 10MHz, 8MHz, 4MHz, 2MHz, 1MHz, 400KHz ... readRectRGB() does not work
#endif

// The XPT2046 requires a lower SPI clock rate of 2.5MHz so we define that here:
#define SPI_TOUCH_FREQUENCY  600000   // Original
//#define SPI_TOUCH_FREQUENCY  2500000  // Testing Required

// The ESP32 has 2 free SPI ports i.e. VSPI and HSPI, the VSPI is the default.
// If the VSPI port is in use and pins are not accessible (e.g. TTGO T-Beam)
// then uncomment the following line:
#define USE_HSPI_PORT   // Avoid conflict with SD card on VSPI
