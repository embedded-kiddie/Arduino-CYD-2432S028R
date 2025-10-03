/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/integration/framework/arduino.html  */

// IN lv_conf.h
//  DO NOT FORGET TO SET 'LV_USE_TFT_ESPI' TO 0
//  DO NOT FORGET TO SET 'LV_USE_ILI9341' and/or 'LV_USE_ST7789'
#include "lvgl.h"
#include "list.h"

/* Set to your screen resolution and rotation */
#define TFT_HOR_RES 240                     // Portrait orientation default width
#define TFT_VER_RES 320                     // Portrait orientation default height
#define TFT_ROTATION LV_DISPLAY_ROTATION_0  // LV_DISPLAY_ROTATION_{0|90|180|270}

/* LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes */
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
static uint8_t draw_buf[DRAW_BUF_SIZE];

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
#define DISPLAY_CYD_2USB true
#include "../src/LGFX_ESP32_2432S028R_CYD.hpp"
#endif  // USE_LGFX_AUTODETECT

static LGFX tft;

//----------------------------------------------------------------------
// Calibrate touch panel for LovyanGFX (optional)
//----------------------------------------------------------------------
static void calibrate_touch(uint16_t cal[8]) {
  // Draw guide text on the screen.
  tft.setTextDatum(textdatum_t::middle_center);
  tft.drawString("touch the arrow marker.", tft.width() >> 1, tft.height() >> 1);
  tft.setTextDatum(textdatum_t::top_left);

  // You will need to calibrate by touching the four corners of the screen.
  uint16_t fg = TFT_WHITE;
  uint16_t bg = TFT_BLACK;
  if (tft.isEPD()) {  // Electronic Paper Display
    std::swap(fg, bg);
  }

  tft.calibrateTouch(cal, fg, bg, std::max(tft.width(), tft.height()) >> 3);

  Serial.print("\nconst uint16_t cal[8] = { ");
  for (int i = 0; i < 8; i++) {
    Serial.printf("%d%s", cal[i], (i < 7 ? ", " : " };\n"));
  }
  Serial.print("tft.setTouchCalibrate(cal);\n");
}

static void tft_init(void) {
  tft.init();
  tft.initDMA();
  tft.setColorDepth(16);  // Set to 16-bit RGB565

  if (tft.touch()) {
    if (USE_LGFX_CALIBRATED) {
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
      tft.setTouchCalibrate((uint16_t *)cal);
    } else {
      uint16_t cal[8];
      calibrate_touch(cal);
      tft.setTouchCalibrate(cal);
    }
  } else {
    Serial.println("Touch device not found.");
  }
}

//----------------------------------------------------------------------
// Functions required by LVGL
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
  } else {
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

  /* handle rotation */
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

/* use Arduinos millis() as tick source */
static uint32_t my_tick(void) {
  return millis();
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  while (millis() < 1000);

  tft_init();
  lv_init();

  /* Set a tick source so that LVGL will know how much time elapsed. */
  lv_tick_set_cb(my_tick);

  /* register print function for debugging */
#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print);
#endif

  lv_display_t *disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
  lv_display_add_event_cb(disp, resolution_changed_event_cb, LV_EVENT_RESOLUTION_CHANGED, NULL);
  lv_display_set_rotation(disp, (lv_display_rotation_t)TFT_ROTATION);
  lv_display_set_flush_cb(disp, my_disp_flush);
  lv_display_set_buffers(disp, draw_buf, NULL, DRAW_BUF_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);

  /* Initialize the input device driver */
  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /* Touchpad should have POINTER type */
  lv_indev_set_read_cb(indev, my_touchpad_read);

  /*---------- Setup SD file system ----------*/
#ifdef USE_SDFAT
  SdFat SD;
#ifdef SD_SPI_BUS
  static DECLARE_SD_SPI_BUS;
  SD_SPI_BUS.begin(SCK, MISO, MOSI, SS);
#endif
#endif

#define ROOT_FOLDER "/MP3/"

  if (!SD.begin(SD_CONFIG)) {
    Serial.println("Can't initialize SD.");
    return;
  }

  File dir = SD.open(ROOT_FOLDER);
  if (!dir) {
    Serial.println("Can't open " ROOT_FOLDER ".");
    return;
  }

  /* Measure memory usage */
  lv_mem_monitor_t mon1;
  lv_mem_monitor(&mon1);
  uint32_t t = lv_tick_get();

  /*---------- Create a file list ----------*/
  lv_obj_t *list = lv_list_create(lv_screen_active());
  lv_obj_set_size(list, 180, 220);
  lv_obj_set_style_pad_left (list, 0, LV_PART_MAIN);
  lv_obj_set_style_pad_right(list, 0, LV_PART_MAIN);
  lv_obj_center(list);

#if   0
  /* SD カード直読み版 */
  add_list(dir, list, 2);   // 2: 2階層まで or 3: 3階層まで（"ROOT_FOLDER"を除く）
#else
  /* ファイルツリー構築版 */
  Node *root = new Node(ROOT_FOLDER);
  root->scan_dir(dir);      // 末端のディレクトリを選択対象とする
//root->scan_file(dir);     // 末端のファイルを選択対象とする

  add_list(root, list);

//root->print_tree();
//printf("Nodes: %d, Leafs: %d, Depth: %d\n", root->get_n_nodes(), root->get_n_leafs(), root->get_n_depth());
  delete root;
#endif

  /* Print memory usage */
  uint32_t elaps = lv_tick_elaps(t);
  lv_mem_monitor_t mon2;
  lv_mem_monitor(&mon2);

  size_t mem_used = mon1.free_size - mon2.free_size;
  lv_obj_t *label = lv_label_create(lv_screen_active());
  lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -10);
  lv_label_set_text_fmt(label, "Created %" LV_PRIu32 " items in %" LV_PRIu32 "ms\n"
                               "using %zu bytes of memory", get_cell_count(), elaps, mem_used);

  dir.close();
  Serial.println("Setup done");
}

void loop() {
  lv_timer_handler(); /* let the GUI do its work */
}