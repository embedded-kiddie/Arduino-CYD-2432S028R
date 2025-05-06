#ifndef _UI_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

LV_FONT_DECLARE(noto_sans_jp_1bit_12);
LV_FONT_DECLARE(noto_sans_jp_1bit_14);
LV_FONT_DECLARE(noto_sans_jp_1bit_16);
LV_FONT_DECLARE(noto_sans_jp_2bit_12);
LV_FONT_DECLARE(noto_sans_jp_2bit_14);
LV_FONT_DECLARE(noto_sans_jp_2bit_16);
LV_FONT_DECLARE(noto_sans_jp_4bit_12);
LV_FONT_DECLARE(noto_sans_jp_4bit_14);
LV_FONT_DECLARE(noto_sans_jp_4bit_16);

LV_FONT_DECLARE(noto_serif_jp_1bit_12);
LV_FONT_DECLARE(noto_serif_jp_1bit_14);
LV_FONT_DECLARE(noto_serif_jp_1bit_16);
LV_FONT_DECLARE(noto_serif_jp_2bit_12);
LV_FONT_DECLARE(noto_serif_jp_2bit_14);
LV_FONT_DECLARE(noto_serif_jp_2bit_16);
LV_FONT_DECLARE(noto_serif_jp_4bit_12);
LV_FONT_DECLARE(noto_serif_jp_4bit_14);
LV_FONT_DECLARE(noto_serif_jp_4bit_16);

LV_FONT_DECLARE(kaisei_decol_1bit_12);
LV_FONT_DECLARE(kaisei_decol_1bit_14);
LV_FONT_DECLARE(kaisei_decol_1bit_16);
LV_FONT_DECLARE(kaisei_decol_2bit_12);
LV_FONT_DECLARE(kaisei_decol_2bit_14);
LV_FONT_DECLARE(kaisei_decol_2bit_16);
LV_FONT_DECLARE(kaisei_decol_4bit_12);
LV_FONT_DECLARE(kaisei_decol_4bit_14);
LV_FONT_DECLARE(kaisei_decol_4bit_16);

LV_FONT_DECLARE(m_plus_rounded_1c_1bit_12);
LV_FONT_DECLARE(m_plus_rounded_1c_1bit_14);
LV_FONT_DECLARE(m_plus_rounded_1c_1bit_16);
LV_FONT_DECLARE(m_plus_rounded_1c_2bit_12);
LV_FONT_DECLARE(m_plus_rounded_1c_2bit_14);
LV_FONT_DECLARE(m_plus_rounded_1c_2bit_16);
LV_FONT_DECLARE(m_plus_rounded_1c_4bit_12);
LV_FONT_DECLARE(m_plus_rounded_1c_4bit_14);
LV_FONT_DECLARE(m_plus_rounded_1c_4bit_16);

LV_FONT_DECLARE(hachi_maru_pop_1bit_12);
LV_FONT_DECLARE(hachi_maru_pop_1bit_14);
LV_FONT_DECLARE(hachi_maru_pop_1bit_16);
LV_FONT_DECLARE(hachi_maru_pop_2bit_12);
LV_FONT_DECLARE(hachi_maru_pop_2bit_14);
LV_FONT_DECLARE(hachi_maru_pop_2bit_16);
LV_FONT_DECLARE(hachi_maru_pop_4bit_12);
LV_FONT_DECLARE(hachi_maru_pop_4bit_14);
LV_FONT_DECLARE(hachi_maru_pop_4bit_16);

LV_FONT_DECLARE(mochiy_pop_one_1bit_12);
LV_FONT_DECLARE(mochiy_pop_one_1bit_14);
LV_FONT_DECLARE(mochiy_pop_one_1bit_16);
LV_FONT_DECLARE(mochiy_pop_one_2bit_12);
LV_FONT_DECLARE(mochiy_pop_one_2bit_14);
LV_FONT_DECLARE(mochiy_pop_one_2bit_16);
LV_FONT_DECLARE(mochiy_pop_one_4bit_12);
LV_FONT_DECLARE(mochiy_pop_one_4bit_14);
LV_FONT_DECLARE(mochiy_pop_one_4bit_16);

int ui_init(void);
const char* ui_loop(void);

// 有効にする場合は、事前にフォントデータを Flash 上にアップロードしておくこと
#define USE_LITTLEFS  0
bool fs_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif // _UI_H_