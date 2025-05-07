//----------------------------------------------------------------------
// TrueType フォントビューワー 本体
//----------------------------------------------------------------------
#include <Arduino.h>
#include "ui.h"

#define N_BPP   3 // The number of patterns for "Bit Per Pixel"

typedef struct {
  const char      *name;            // フォントファミリーの名称
  const lv_font_t font[N_BPP];      // フォントデータ
  const char      *bin_data[N_BPP]; // ファイルシステム上のフォントデータ名
} FontType_t;

// https://fonts.google.com/?lang=ja_Jpan
FontType_t fonts[] = {
  { "Noto_Sans_1bit", { noto_sans_jp_1bit_12, noto_sans_jp_1bit_14, noto_sans_jp_1bit_16 }, { "noto_sans_jp_1bit_12", "noto_sans_jp_1bit_14", "noto_sans_jp_1bit_16" } },
  { "Noto_Sans_2bit", { noto_sans_jp_2bit_12, noto_sans_jp_2bit_14, noto_sans_jp_2bit_16 }, { "noto_sans_jp_2bit_12", "noto_sans_jp_2bit_14", "noto_sans_jp_2bit_16" } },
  { "Noto_Sans_4bit", { noto_sans_jp_4bit_12, noto_sans_jp_4bit_14, noto_sans_jp_4bit_16 }, { "noto_sans_jp_4bit_12", "noto_sans_jp_4bit_14", "noto_sans_jp_4bit_16" } },

  { "Noto_Serif_1bit", { noto_serif_jp_1bit_12, noto_serif_jp_1bit_14, noto_serif_jp_1bit_16 }, { "noto_serif_jp_1bit_12", "noto_serif_jp_1bit_14", "noto_serif_jp_1bit_16" } },
  { "Noto_Serif_2bit", { noto_serif_jp_2bit_12, noto_serif_jp_2bit_14, noto_serif_jp_2bit_16 }, { "noto_serif_jp_2bit_12", "noto_serif_jp_2bit_14", "noto_serif_jp_2bit_16" } },
  { "Noto_Serif_4bit", { noto_serif_jp_4bit_12, noto_serif_jp_4bit_14, noto_serif_jp_4bit_16 }, { "noto_serif_jp_4bit_12", "noto_serif_jp_4bit_14", "noto_serif_jp_4bit_16" } },

  { "Kaisei_Decol_1bit", { kaisei_decol_1bit_12, kaisei_decol_1bit_14, kaisei_decol_1bit_16 }, { "kaisei_decol_1bit_12", "kaisei_decol_1bit_14", "kaisei_decol_1bit_16" } },
  { "Kaisei_Decol_2bit", { kaisei_decol_2bit_12, kaisei_decol_2bit_14, kaisei_decol_2bit_16 }, { "kaisei_decol_2bit_12", "kaisei_decol_2bit_14", "kaisei_decol_2bit_16" } },
  { "Kaisei_Decol_4bit", { kaisei_decol_4bit_12, kaisei_decol_4bit_14, kaisei_decol_4bit_16 }, { "kaisei_decol_4bit_12", "kaisei_decol_4bit_14", "kaisei_decol_4bit_16" } },

  { "M_PLUS_Rounded_1c_1bit", { m_plus_rounded_1c_1bit_12, m_plus_rounded_1c_1bit_14, m_plus_rounded_1c_1bit_16 }, { "m_plus_rounded_1c_1bit_12", "m_plus_rounded_1c_1bit_14", "m_plus_rounded_1c_1bit_16" } },
  { "M_PLUS_Rounded_1c_2bit", { m_plus_rounded_1c_2bit_12, m_plus_rounded_1c_2bit_14, m_plus_rounded_1c_2bit_16 }, { "m_plus_rounded_1c_2bit_12", "m_plus_rounded_1c_2bit_14", "m_plus_rounded_1c_2bit_16" } },
  { "M_PLUS_Rounded_1c_4bit", { m_plus_rounded_1c_4bit_12, m_plus_rounded_1c_4bit_14, m_plus_rounded_1c_4bit_16 }, { "m_plus_rounded_1c_4bit_12", "m_plus_rounded_1c_4bit_14", "m_plus_rounded_1c_4bit_16" } },

  { "Hachi_Maru_Pop_1bit", { hachi_maru_pop_1bit_12, hachi_maru_pop_1bit_14, hachi_maru_pop_1bit_16 }, { "hachi_maru_pop_1bit_12", "hachi_maru_pop_1bit_14", "hachi_maru_pop_1bit_16" } },
  { "Hachi_Maru_Pop_2bit", { hachi_maru_pop_2bit_12, hachi_maru_pop_2bit_14, hachi_maru_pop_2bit_16 }, { "hachi_maru_pop_2bit_12", "hachi_maru_pop_2bit_14", "hachi_maru_pop_2bit_16" } },
  { "Hachi_Maru_Pop_4bit", { hachi_maru_pop_4bit_12, hachi_maru_pop_4bit_14, hachi_maru_pop_4bit_16 }, { "hachi_maru_pop_4bit_12", "hachi_maru_pop_4bit_14", "hachi_maru_pop_4bit_16" } },

  { "Mochiy_Pop_One_1bit", { mochiy_pop_one_1bit_12, mochiy_pop_one_1bit_14, mochiy_pop_one_1bit_16 }, { "mochiy_pop_one_1bit_12", "mochiy_pop_one_1bit_14", "mochiy_pop_one_1bit_16" } },
  { "Mochiy_Pop_One_2bit", { mochiy_pop_one_2bit_12, mochiy_pop_one_2bit_14, mochiy_pop_one_2bit_16 }, { "mochiy_pop_one_2bit_12", "mochiy_pop_one_2bit_14", "mochiy_pop_one_2bit_16" } },
  { "Mochiy_Pop_One_4bit", { mochiy_pop_one_4bit_12, mochiy_pop_one_4bit_14, mochiy_pop_one_4bit_16 }, { "mochiy_pop_one_4bit_12", "mochiy_pop_one_4bit_14", "mochiy_pop_one_4bit_16" } },
};

const char *sample = \
  "自らに勝つ事こそ、最も難しい勝利。\n"
  "01234567890"
  "#$%&@*?<>^[]()\n"
  "abcdefghijklm"
  "nopqrstuvwxyz\n"
  "ABCDEFGHIJKLM"
  "NOPQRSTUVWXYZ";

#define N_FONTS (sizeof(fonts) / sizeof(fonts[0]))

static int fontNo;
static lv_obj_t *label[N_BPP];

#if USE_LITTLEFS
//----------------------------------------------------------------------
// ファイルシステム上のフォントデータを扱う関数
//----------------------------------------------------------------------
static lv_font_t *create_font(int n, int bpp) {
  // lv_conf.h で以下を設定しておくこと
  // #define LV_USE_FS_ARDUINO_ESP_LITTLEFS 1
  // #define LV_FS_ARDUINO_ESP_LITTLEFS_LETTER 'L'
  char path[64];
  sprintf(path, "%c:/%s.bin", LV_FS_ARDUINO_ESP_LITTLEFS_LETTER, fonts[n].bin_data[bpp]);

  lv_font_t *font = lv_binfont_create(path);
  if(font == NULL) {
    Serial.printf("failed to create font %s\n", path);
  }

  return font;
}

static void delete_font(lv_font_t *font) {
  if (font) {
    lv_binfont_destroy(font);
  }
}
#endif // USE_LITTLEFS

//----------------------------------------------------------------------
// フォントスタイルを各ラベルに反映する
//----------------------------------------------------------------------
static void apply_font_style(int n) {
#if USE_LITTLEFS

  // 表示中はフォントデータをキープする必要がある
  static lv_font_t *font[N_BPP] = { NULL, };

  for (int i = 0; i < N_BPP; i++) {
    // 反映前のフォントを削除
    delete_font(font[i]);

    // 新たにフォントデータを作成し、ラベルに反映
    if (font[i] = create_font(n, i)) {
      lv_obj_set_style_text_font(label[i], font[i], (int32_t)LV_PART_MAIN /* 0 */ | (int32_t)LV_STATE_DEFAULT /* 0 */);
    }
  }

#else

  const lv_font_t *font = fonts[n].font;

  for (int i = 0; i < N_BPP; i++) {
    lv_obj_set_style_text_font(label[i], &font[i], (int32_t)LV_PART_MAIN /* 0 */ | (int32_t)LV_STATE_DEFAULT /* 0 */);
  }

#endif // USE_LITTLEFS
}

//----------------------------------------------------------------------
// LVGL からのイベント通知を扱う関数
//----------------------------------------------------------------------
static void event_screen_callback(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_GESTURE) {
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());

    // 上にスワイプ：次のフォント
    if (dir == LV_DIR_TOP) {
      fontNo = (fontNo + 1) % N_FONTS;
      apply_font_style(fontNo);
    }

    // 下にスワイプ：前のフォント
    else if (dir == LV_DIR_BOTTOM) {
      fontNo = (fontNo - 1 + N_FONTS) % N_FONTS;
      apply_font_style(fontNo);
    }
  }
}

//----------------------------------------------------------------------
// フォントサンプル表示用のラベルを初期化する
//----------------------------------------------------------------------
int ui_init(void) {
  const int32_t ypos[N_BPP] = { lv_pct(-35)+1, lv_pct(-5), lv_pct(30), };

  // サンプル表示用のラベルを生成
  for (int i = 0; i < N_BPP; i++) {
    label[i] = lv_label_create(lv_screen_active());
    lv_obj_align(label[i], LV_ALIGN_CENTER, 0, ypos[i]);
    lv_obj_set_style_text_align(label[i], LV_TEXT_ALIGN_CENTER, (int32_t)LV_PART_MAIN /* 0 */ | (int32_t)LV_STATE_DEFAULT /* 0 */);
    lv_label_set_text(label[i], sample);
  }

  // 最初のフォントを反映
  apply_font_style(fontNo);

  // LVGL からのイベントハンドラを設定
  lv_obj_add_event_cb(lv_screen_active(), event_screen_callback, LV_EVENT_ALL, NULL);

  return N_FONTS;
}

const char* ui_loop(void) {
  return fonts[fontNo].name;
}