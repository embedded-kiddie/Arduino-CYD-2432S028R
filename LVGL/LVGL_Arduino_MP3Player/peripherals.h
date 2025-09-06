//====================================================================
//
//====================================================================
#ifndef _PERIPHERALS_H
#define _PERIPHERALS_H

// https://github.com/espressif/arduino-esp32/blob/master/variants/jczn_2432s028r/pins_arduino.h
#ifndef CYD_LED_RGB_OFF

#define CYD_LED_RED   4
#define CYD_LED_GREEN 16
#define CYD_LED_BLUE  17

#define CYD_LED_RED_OFF()   (digitalWrite(CYD_LED_RED,   1))
#define CYD_LED_RED_ON()    (digitalWrite(CYD_LED_RED,   0))
#define CYD_LED_GREEN_OFF() (digitalWrite(CYD_LED_GREEN, 1))
#define CYD_LED_GREEN_ON()  (digitalWrite(CYD_LED_GREEN, 0))
#define CYD_LED_BLUE_OFF()  (digitalWrite(CYD_LED_BLUE,  1))
#define CYD_LED_BLUE_ON()   (digitalWrite(CYD_LED_BLUE,  0))
#define CYD_LED_RGB_OFF() \
  CYD_LED_RED_OFF();      \
  CYD_LED_GREEN_OFF();    \
  CYD_LED_BLUE_OFF()
#define CYD_LED_RGB_ON()  \
  CYD_LED_RED_ON();       \
  CYD_LED_GREEN_ON();     \
  CYD_LED_BLUE_ON()
#define CYD_LED_WHITE_OFF() CYD_LED_RGB_OFF()
#define CYD_LED_WHITE_ON()  CYD_LED_RGB_ON()

#endif // CYD_LED_RGB_OFF

#define RGB_LED_OFF() {           \
  pinMode(CYD_LED_RED,   OUTPUT); \
  pinMode(CYD_LED_GREEN, OUTPUT); \
  pinMode(CYD_LED_BLUE,  OUTPUT); \
  CYD_LED_RGB_OFF();              \
}

//#include "esp_bt.h"       // esp_bt_controller_disable(), esp_bt_controller_deinit()
//#include "esp_bt_main.h"  // esp_bluedroid_disable(), esp_bluedroid_deinit()
//#include "esp_wifi.h"     // esp_wifi_stop()

#define shutdown_peripherals() {  \
/*esp_bluedroid_disable();        \
  esp_bluedroid_deinit();         \
  esp_bt_controller_disable();    \
  esp_bt_controller_deinit();     \
  esp_wifi_stop();*/              \
  RGB_LED_OFF();                  \
}

#endif // _PERIPHERALS_H