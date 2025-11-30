//================================================================================
// MP3 Music Player for CYD
// LVGL version: 9.2.2 and up
// IN lv_conf.h
//  DO NOT FORGET TO SET 'LV_USE_TFT_ESPI' TO 0
//  DO NOT FORGET TO SET 'LV_USE_ILI9341' and/or 'LV_USE_ST7789'
//================================================================================
#include <lvgl.h>
#include "src/ui.h"
#include "peripherals.h"

#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH in lv_conf.h should be 16bit"
#endif

/* Set to your screen resolution and rotation */
#define TFT_HOR_RES   SCREEN_WIDTH  // Portrait orientation default width  (defined in ui.h)
#define TFT_VER_RES   SCREEN_HEIGHT // Portrait orientation default height (defined in ui.h)
#define TFT_ROTATION  LV_DISPLAY_ROTATION_0 // LV_DISPLAY_ROTATION_{0|90|180|270}

/* LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes */
#define DRAW_BUF_SIZE   (TFT_HOR_RES * TFT_VER_RES / DRAW_BUF_N_DIVS * (LV_COLOR_DEPTH / 8))
#define DRAW_BUF_N_DIVS 15  // 2 (75KB) - 10 (15KB) - 15 (10KB)
#define DRAW_BUF_N_BUFS 1   // 1 or 2

#define USE_HEAP_MALLOC false
#if USE_HEAP_MALLOC
static uint8_t* draw_buf;
#else
static uint8_t draw_buf[DRAW_BUF_SIZE];
#endif

//----------------------------------------------------------------------
// LovyanGFX configuration
//----------------------------------------------------------------------
#define USE_LGFX_AUTODETECT true
#define USE_LGFX_CALIBRATED true

#if USE_LGFX_AUTODETECT
#define LGFX_AUTODETECT
#include <LovyanGFX.h>
#else
// false: Panel driver: ILI9341 (micro-USB x 1 type)
// true : Panel driver: ST7789  (micro-USB x 1 + USB-C x 1 type)
#define DISPLAY_CYD_2USB false
#include "LGFX_ESP32_2432S028R_CYD.hpp"
#endif // USE_LGFX_AUTODETECT

static LGFX tft;

//----------------------------------------------------------------------
// Signle or Sequentcial screenshot
//----------------------------------------------------------------------
#define SCREENSHORT false
#if SCREENSHORT
#define USE_SDFAT
#include "../src/sdcard.hpp"
#endif

#define SAVE_SEQUENCIAL_BMP false
#if SAVE_SEQUENCIAL_BMP
#include "../src/sdcard.hpp"
static uint32_t _skip = 0;
static uint32_t _prev = 0;
static uint32_t N = 0;
static char fname[16];
#endif

#ifndef _SDCARD_HPP_
#include "ESP32.hpp"
#endif

//----------------------------------------------------------------------
// Calibrate touch panel for LovyanGFX (optional)
//----------------------------------------------------------------------
static void calibrate_touch(uint16_t cal[8]) {
  tft.clear(TFT_BLACK);                   // Clear screen with background color
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set foreground color, background color
  tft.setFont(&fonts::Font2);             // https://lang-ship.com/blog/files/LovyanGFX/font/

  // Draw guide text on the screen.
  tft.setTextDatum(textdatum_t::middle_center);
  tft.drawString  ("Touch the arrow tips in order", tft.width() >> 1, tft.height() >> 1);
  tft.setTextDatum(textdatum_t::top_left);

  uint16_t fg = TFT_WHITE;
  uint16_t bg = TFT_BLACK;

  // Electronic Paper Display
  if (tft.isEPD()) {
    std::swap(fg, bg);
  }

  // You will need to calibrate by touching the four corners of the screen.
  tft.calibrateTouch(cal, fg, bg, std::max(tft.width(), tft.height()) >> 3);

  Serial.print("\nconst uint16_t cal[8] = { ");
  for (int i = 0; i < 8; i++) {
    Serial.printf("%d%s", cal[i], (i < 7 ? ", " : " };\n"));
  }
}

static void tft_init(void) {
  tft.init();
  tft.initDMA();
  tft.setColorDepth(16);  // Set to 16-bit RGB565

  if (tft.touch()) {
    if (USE_LGFX_CALIBRATED) {
      // The following is equivalent to the `_touch_instance` setting in `LGFX_ESP32_2432S028R_CYD.hpp`.
      // The `cal[8]` can be replaced with the result displayed on the serial monitor after calibration.
      const uint16_t cal[8] = {
        240,   // x_min
        3700,  // y_min
        240,   // x_min
        200,   // y_max
        3800,  // x_max
        3700,  // y_min
        3800,  // x_max
        200    // y_max
      };
      tft.setTouchCalibrate((uint16_t*)cal);
    } else {
      uint16_t cal[8];
      calibrate_touch(cal);
      tft.setTouchCalibrate((uint16_t*)cal);
    }
  } else {
    Serial.println("Touch device not found.");
  }
}

//----------------------------------------------------------------------
// Display sleep/wakeup
//----------------------------------------------------------------------
static bool is_awake = true;

static void update_display_state(UI_State_t state) {
  switch (state) {
    case UI_STATE_AWAKE:
      tft.wakeup();
      RGB_LED_ON();
      ui_redisplay();
      is_awake = true;
      break;
    case UI_STATE_BLOFF:
    default: // may be UI_STATE_SLEEP
      tft.sleep();
      RGB_LED_OFF();
      is_awake = false;
      break;
  }
}

//----------------------------------------------------------------------
// LVGL required functions
//----------------------------------------------------------------------
#if LV_USE_LOG != 0
static void my_print(lv_log_level_t level, const char *buf) {
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}
#endif

/* LVGL calls it when a rendered image needs to copied to the display */
static void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
  uint32_t w = lv_area_get_width(area);
  uint32_t h = lv_area_get_height(area);

  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushPixelsDMA((lgfx::rgb565_t *)px_map, w * h);  // { startWrite(); writePixelsDMA(data, len); endWrite(); }

  /* Call it to tell LVGL you are ready */
  lv_display_flush_ready(disp);
}

/* Read the touchpad */
static void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data) {
  uint16_t x, y;
  bool touched = tft.getTouch(&x, &y);

  if (!touched) {
    data->state = LV_INDEV_STATE_RELEASED;
  }

  else if (!is_awake) {
    update_display_state(UI_STATE_AWAKE);
    delay(200); // Prevent unintended events from firing
    data->state = LV_INDEV_STATE_RELEASED;
  }

  else {
    data->state = LV_INDEV_STATE_PRESSED;

    switch (tft.getRotation()) {
      case LV_DISPLAY_ROTATION_0:
        data->point.x = x;
        data->point.y = y;
        break;
      case LV_DISPLAY_ROTATION_90:
        data->point.x = y;
        data->point.y = TFT_VER_RES - x;
        break;
      case LV_DISPLAY_ROTATION_180:
        data->point.x = TFT_HOR_RES - x;
        data->point.y = TFT_VER_RES - y;
        break;
      case LV_DISPLAY_ROTATION_270:
        data->point.x = TFT_HOR_RES - y;
        data->point.y = x;
        break;
    }

//  Serial.printf("x: %d (%d), y: %d (%d)\n", data->point.x, x, data->point.y, y);
  }
}

static void resolution_changed_event_cb(lv_event_t *e) {
  lv_display_t *disp = (lv_display_t *)lv_event_get_target(e);
  lv_display_rotation_t rot = lv_display_get_rotation(disp);

  /* Handle rotation */
  switch (rot) {
    case LV_DISPLAY_ROTATION_0:
      tft.setRotation(0); /* Portrait orientation */
      break;
    case LV_DISPLAY_ROTATION_90:
      tft.setRotation(1); /* Landscape orientation */
      break;
    case LV_DISPLAY_ROTATION_180:
      tft.setRotation(2); /* Portrait orientation, flipped */
      break;
    case LV_DISPLAY_ROTATION_270:
      tft.setRotation(3); /* Landscape orientation, flipped */
      break;
  }
}

/* Use Arduino millis() as tick source */
static uint32_t my_tick(void) {
#if SAVE_SEQUENCIAL_BMP
  return millis() - _skip;
#else
  return millis();
#endif
}

void setup() {
//DBG_EXEC({
    Serial.begin(115200);
    while (millis() < 500);
//});

  tft_init();
  lv_init();

  /* Set a tick source so that LVGL will know how much time elapsed. */
  lv_tick_set_cb(my_tick);

  /* Register print function for debugging */
#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print);
#endif

  lv_display_t *disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
  lv_display_add_event_cb(disp, resolution_changed_event_cb, LV_EVENT_RESOLUTION_CHANGED, NULL);
  lv_display_set_rotation(disp, (lv_display_rotation_t)TFT_ROTATION);
  lv_display_set_flush_cb(disp, my_disp_flush);

#if USE_HEAP_MALLOC
  draw_buf = (uint8_t*)heap_caps_malloc(DRAW_BUF_SIZE, MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
#endif
  lv_display_set_buffers(disp, draw_buf, NULL, DRAW_BUF_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);

  /* Initialize the input device driver */
  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /* Touchpad should have POINTER type */
  lv_indev_set_read_cb(indev, my_touchpad_read);

  ui_init();
}

void loop() {
  lv_timer_handler(); /* Let the GUI do its work */

  UI_State_t state = ui_loop();
  if (state == UI_STATE_SLEEP || (state == UI_STATE_BLOFF && is_awake == true)) {
    update_display_state(state);
  }

#if SAVE_SEQUENCIAL_BMP
  uint32_t t = millis();
  if (t - _skip < 45 * 1000 && t - _prev >= 66) {
    sprintf(fname, "/%05d.bmp", N++);
    SaveBMP24(SD, fname, tft);
    _skip += (_prev = millis()) - t;
  }
#else
  if (Serial.available()) {
  #if SCREENSHORT
    Serial.readStringUntil('\n');
    static int No;
    char fname[16];
    sprintf(fname, "/demo%02d.bmp", ++No);
    SaveBMP24(SD, fname, tft);
  #else
    String in = Serial.readStringUntil('\n');
    switch (in[0]) {
      case '0':
        if (show_ui_control) {
          show_ui_control();
        }
        break;
      case '1':
        if (dump_play_list) {
          dump_play_list();
        }
        break;
      case '2':
        PrintESP32System();
        break;
      default:
        PrintESP32Memory();
        break;
    }
  #endif
  }
#endif
}