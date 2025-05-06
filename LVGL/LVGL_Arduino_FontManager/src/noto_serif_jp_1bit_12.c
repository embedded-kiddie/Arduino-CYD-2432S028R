/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --no-compress --font NotoSerifJP-Regular.ttf --symbols 自らに勝つ事こそ、最も難しい勝利。 --range 32-127 --format lvgl -o noto_serif_jp_1bit_12.c
 ******************************************************************************/
/*
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
*/
#include "../ui.h"

#ifndef NOTO_SERIF_JP_1BIT_12
#define NOTO_SERIF_JP_1BIT_12 1
#endif

#if NOTO_SERIF_JP_1BIT_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfe, 0xc0,

    /* U+0022 "\"" */
    0xb6, 0xd0,

    /* U+0023 "#" */
    0x24, 0x50, 0xa3, 0xf4, 0x89, 0x3f, 0x24, 0x48,
    0x80,

    /* U+0024 "$" */
    0x23, 0xab, 0x5a, 0x30, 0xc5, 0x2d, 0x5c, 0x42,
    0x0,

    /* U+0025 "%" */
    0x61, 0x24, 0x89, 0x22, 0x50, 0x99, 0x9a, 0x91,
    0x24, 0x49, 0x22, 0x40, 0x60,

    /* U+0026 "&" */
    0x30, 0x48, 0x48, 0x70, 0x23, 0x52, 0x8a, 0x8c,
    0x86, 0x7b,

    /* U+0027 "'" */
    0xf0,

    /* U+0028 "(" */
    0xd, 0x49, 0x24, 0x93, 0x24, 0x40,

    /* U+0029 ")" */
    0x11, 0x22, 0x49, 0x25, 0x28, 0x0,

    /* U+002A "*" */
    0x20, 0x8c, 0x88, 0x51, 0x20,

    /* U+002B "+" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x0,

    /* U+002C "," */
    0x56,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x11, 0x22, 0x22, 0x44, 0x48, 0x88, 0x80,

    /* U+0030 "0" */
    0x31, 0x28, 0x61, 0x86, 0x18, 0x61, 0x48, 0xc0,

    /* U+0031 "1" */
    0x23, 0x8, 0x42, 0x10, 0x84, 0x23, 0x80,

    /* U+0032 "2" */
    0x74, 0x42, 0x11, 0x8, 0x88, 0x87, 0xc0,

    /* U+0033 "3" */
    0x74, 0x42, 0x13, 0xc, 0x21, 0x8b, 0x80,

    /* U+0034 "4" */
    0x8, 0x62, 0x8a, 0x4a, 0x2f, 0xc2, 0x8, 0x20,

    /* U+0035 "5" */
    0x7d, 0x4, 0x10, 0x70, 0x30, 0x41, 0xc5, 0xe0,

    /* U+0036 "6" */
    0x9, 0x91, 0xb, 0x46, 0x31, 0x8b, 0x80,

    /* U+0037 "7" */
    0xf8, 0x44, 0x21, 0x10, 0x84, 0x42, 0x0,

    /* U+0038 "8" */
    0x74, 0x63, 0x17, 0x3a, 0x31, 0x8b, 0x80,

    /* U+0039 "9" */
    0x74, 0x63, 0x18, 0xb4, 0x42, 0x22, 0x0,

    /* U+003A ":" */
    0xc6,

    /* U+003B ";" */
    0x50, 0x15, 0x80,

    /* U+003C "<" */
    0x9, 0x91, 0x6, 0x8, 0x20,

    /* U+003D "=" */
    0xfe, 0x0, 0x7, 0xf0,

    /* U+003E ">" */
    0x83, 0x4, 0x13, 0x22, 0x0,

    /* U+003F "?" */
    0xc2, 0x11, 0x68, 0x80, 0x88,

    /* U+0040 "@" */
    0xf, 0xc, 0x24, 0x5, 0x39, 0x8a, 0x64, 0x99,
    0x26, 0x52, 0x89, 0x10, 0x6, 0x0, 0x70,

    /* U+0041 "A" */
    0x8, 0xc, 0x6, 0x4, 0x82, 0x41, 0x20, 0xf8,
    0x84, 0x42, 0x21, 0x80,

    /* U+0042 "B" */
    0x58, 0x89, 0x12, 0x27, 0x89, 0x90, 0xa1, 0x42,
    0xb8,

    /* U+0043 "C" */
    0x3e, 0x86, 0xc, 0x8, 0x10, 0x20, 0x41, 0x42,
    0x7c,

    /* U+0044 "D" */
    0x7c, 0x42, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41,
    0x42, 0x78,

    /* U+0045 "E" */
    0x7c, 0x89, 0x2, 0x4, 0x8f, 0x12, 0x20, 0x42,
    0xfc,

    /* U+0046 "F" */
    0x7d, 0x14, 0x10, 0x49, 0xe4, 0x90, 0x41, 0x0,

    /* U+0047 "G" */
    0x3e, 0x42, 0x82, 0x80, 0x80, 0x87, 0x82, 0x82,
    0x42, 0x3c,

    /* U+0048 "H" */
    0x42, 0x42, 0x42, 0x42, 0x42, 0x7e, 0x42, 0x42,
    0x42, 0x42,

    /* U+0049 "I" */
    0x49, 0x24, 0x92, 0x48,

    /* U+004A "J" */
    0x22, 0x22, 0x22, 0x22, 0x22, 0xc0,

    /* U+004B "K" */
    0x46, 0x44, 0x48, 0x50, 0x50, 0x68, 0x48, 0x44,
    0x44, 0x42,

    /* U+004C "L" */
    0x41, 0x4, 0x10, 0x41, 0x4, 0x11, 0x45, 0xf0,

    /* U+004D "M" */
    0x60, 0x98, 0x66, 0x19, 0xca, 0x52, 0x94, 0xa4,
    0xc9, 0x32, 0x4c, 0x92, 0x20,

    /* U+004E "N" */
    0x61, 0x30, 0x9c, 0x4a, 0x24, 0x92, 0x49, 0x14,
    0x8e, 0x43, 0x20, 0x80,

    /* U+004F "O" */
    0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x42, 0x3c,

    /* U+0050 "P" */
    0x79, 0x14, 0x51, 0x45, 0xe4, 0x10, 0x41, 0x0,

    /* U+0051 "Q" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x44,
    0x50, 0x40, 0x80, 0xc0,

    /* U+0052 "R" */
    0x58, 0x89, 0x12, 0x24, 0x4f, 0x12, 0x24, 0x45,
    0xcc,

    /* U+0053 "S" */
    0x7a, 0x18, 0x70, 0x60, 0x60, 0x61, 0x87, 0xe0,

    /* U+0054 "T" */
    0xff, 0x24, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20,

    /* U+0055 "U" */
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x66, 0x3c,

    /* U+0056 "V" */
    0x63, 0x42, 0x22, 0x22, 0x24, 0x14, 0x14, 0x18,
    0x8, 0x8,

    /* U+0057 "W" */
    0x62, 0x33, 0x11, 0x9, 0x48, 0x4a, 0x42, 0x54,
    0x14, 0xa0, 0x63, 0x3, 0x18, 0x18, 0x80, 0x84,
    0x0,

    /* U+0058 "X" */
    0x62, 0x24, 0x34, 0x18, 0x18, 0x8, 0x3c, 0x24,
    0x46, 0x42,

    /* U+0059 "Y" */
    0xc6, 0x88, 0xa1, 0x42, 0x82, 0x4, 0x8, 0x10,
    0x20,

    /* U+005A "Z" */
    0xfe, 0x20, 0x84, 0x10, 0x82, 0x10, 0x47, 0xf0,

    /* U+005B "[" */
    0xea, 0xaa, 0xaa, 0xc0,

    /* U+005C "\\" */
    0x88, 0x84, 0x44, 0x42, 0x22, 0x11, 0x0,

    /* U+005D "]" */
    0xd5, 0x55, 0x55, 0xc0,

    /* U+005E "^" */
    0x23, 0x15, 0x28, 0x80,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0x90,

    /* U+0061 "a" */
    0x72, 0x20, 0x9e, 0x8a, 0x2e, 0xc0,

    /* U+0062 "b" */
    0xc0, 0x81, 0x2, 0x5, 0xc8, 0xd0, 0xa1, 0x42,
    0x8f, 0xf0,

    /* U+0063 "c" */
    0x7c, 0x61, 0x8, 0x61, 0xe0,

    /* U+0064 "d" */
    0xc, 0x8, 0x10, 0x27, 0x59, 0xa1, 0x42, 0x85,
    0x9, 0xd8,

    /* U+0065 "e" */
    0x74, 0x63, 0xf8, 0x61, 0xe0,

    /* U+0066 "f" */
    0x3b, 0x10, 0x84, 0x21, 0x8, 0x42, 0x10,

    /* U+0067 "g" */
    0x7e, 0x28, 0xa2, 0x62, 0xf, 0xa1, 0x85, 0xe0,

    /* U+0068 "h" */
    0xc0, 0x81, 0x2, 0x5, 0x8c, 0x91, 0x22, 0x44,
    0x89, 0x10,

    /* U+0069 "i" */
    0x48, 0x24, 0x92, 0x48,

    /* U+006A "j" */
    0x24, 0x32, 0x49, 0x24, 0x9c,

    /* U+006B "k" */
    0xc0, 0x81, 0x2, 0x4, 0xca, 0x14, 0x38, 0x48,
    0x91, 0x10,

    /* U+006C "l" */
    0xc9, 0x24, 0x92, 0x49, 0x0,

    /* U+006D "m" */
    0xd9, 0x88, 0xc9, 0x11, 0x22, 0x24, 0x44, 0x88,
    0x91, 0x10,

    /* U+006E "n" */
    0xd8, 0x89, 0x12, 0x24, 0x48, 0x91, 0x0,

    /* U+006F "o" */
    0x7a, 0x18, 0x61, 0x86, 0x17, 0x80,

    /* U+0070 "p" */
    0xdc, 0x8d, 0xa, 0x14, 0x28, 0xdf, 0x20, 0x40,
    0x80,

    /* U+0071 "q" */
    0x7d, 0x8a, 0x14, 0x28, 0x50, 0x9d, 0x2, 0x4,
    0x8,

    /* U+0072 "r" */
    0xdb, 0x10, 0x84, 0x21, 0x0,

    /* U+0073 "s" */
    0x74, 0x70, 0xe0, 0xc7, 0xc0,

    /* U+0074 "t" */
    0x44, 0x64, 0x44, 0x44, 0x70,

    /* U+0075 "u" */
    0xcc, 0x89, 0x12, 0x24, 0x48, 0x8f, 0x80,

    /* U+0076 "v" */
    0x44, 0x91, 0x21, 0x43, 0x6, 0x4, 0x0,

    /* U+0077 "w" */
    0x44, 0x91, 0x24, 0xc8, 0xcc, 0x33, 0xc, 0xc2,
    0x20,

    /* U+0078 "x" */
    0x44, 0x50, 0xc0, 0x83, 0x89, 0x11, 0x0,

    /* U+0079 "y" */
    0x44, 0x91, 0x21, 0x43, 0x6, 0x4, 0x10, 0x21,
    0x80,

    /* U+007A "z" */
    0xfc, 0x84, 0x44, 0x23, 0xe0,

    /* U+007B "{" */
    0x69, 0x24, 0xa2, 0x49, 0x22,

    /* U+007C "|" */
    0xff, 0xfe,

    /* U+007D "}" */
    0xc9, 0x24, 0x8a, 0x49, 0x28,

    /* U+007E "~" */
    0x62, 0x60,

    /* U+3001 "、" */
    0x44, 0x80,

    /* U+3002 "。" */
    0x69, 0x96,

    /* U+3044 "い" */
    0x40, 0x10, 0x24, 0x5, 0x1, 0x40, 0x52, 0x3,
    0x0, 0x40,

    /* U+3053 "こ" */
    0x40, 0x3e, 0x8, 0x0, 0x0, 0x0, 0x80, 0x40,
    0x3f,

    /* U+3057 "し" */
    0xc0, 0x30, 0x10, 0x8, 0x4, 0x2, 0x1, 0x0,
    0x82, 0x42, 0x1e, 0x0,

    /* U+305D "そ" */
    0x6, 0x1e, 0x2, 0x2, 0x71, 0xc3, 0x80, 0x40,
    0x20, 0x8, 0x3, 0x0,

    /* U+3064 "つ" */
    0x7, 0x86, 0x2e, 0x4, 0x1, 0x0, 0x40, 0x20,
    0x38, 0x78,

    /* U+306B "に" */
    0x0, 0x11, 0xe4, 0x11, 0x0, 0x80, 0x28, 0xc,
    0x3, 0x20, 0xc7, 0xd0, 0x0,

    /* U+3082 "も" */
    0x10, 0x8, 0x90, 0x78, 0xd0, 0xa2, 0x79, 0x21,
    0x21, 0x23, 0x1e,

    /* U+3089 "ら" */
    0x20, 0x18, 0x38, 0x40, 0x40, 0x5e, 0xa1, 0xc1,
    0x1, 0x6, 0x3c,

    /* U+4E8B "事" */
    0x4, 0x1f, 0xfc, 0xfe, 0x12, 0x43, 0xf8, 0xff,
    0x1, 0x23, 0xff, 0x7f, 0x80, 0x90, 0x30, 0x0,

    /* U+5229 "利" */
    0x4, 0x7, 0x25, 0x44, 0x88, 0x9f, 0xf2, 0x62,
    0x4f, 0x4a, 0xa9, 0x51, 0x32, 0x24, 0x40, 0x88,
    0x30,

    /* U+52DD "勝" */
    0x71, 0x65, 0x54, 0x51, 0x27, 0x2c, 0x57, 0xf5,
    0x42, 0x77, 0xc5, 0x14, 0x51, 0x49, 0x24, 0x94,
    0xc0,

    /* U+6700 "最" */
    0x3f, 0x84, 0x10, 0xfe, 0x10, 0x4f, 0xfe, 0x77,
    0x8a, 0x11, 0xd4, 0x29, 0x9f, 0x38, 0x20, 0x80,

    /* U+81EA "自" */
    0x10, 0xfe, 0x82, 0x82, 0xfe, 0x82, 0x82, 0xfe,
    0x82, 0xfe, 0x82,

    /* U+96E3 "難" */
    0x29, 0x27, 0xea, 0xa, 0x7c, 0xfe, 0x85, 0x94,
    0x3c, 0xf9, 0xf5, 0x1f, 0xbc, 0x11, 0x41, 0x6f,
    0x90, 0x40
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 49, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 59, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 72, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 5, .adv_w = 110, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 106, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 23, .adv_w = 177, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 38, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 47, .adv_w = 70, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 53, .adv_w = 70, .box_w = 3, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 59, .adv_w = 92, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 64, .adv_w = 111, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 71, .adv_w = 63, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 72, .adv_w = 66, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 73, .adv_w = 63, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 68, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 81, .adv_w = 107, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 90, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 107, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 107, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 107, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 107, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 107, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 105, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 107, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 108, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 63, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 63, .box_w = 2, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 158, .adv_w = 111, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 163, .adv_w = 111, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 167, .adv_w = 111, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 172, .adv_w = 83, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 175, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 192, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 129, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 133, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 125, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 121, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 142, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 78, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 77, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 279, .adv_w = 140, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 187, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 153, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 147, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 147, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 352, .adv_w = 137, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 109, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 153, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 137, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 202, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 132, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 66, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 446, .adv_w = 68, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 453, .adv_w = 66, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 457, .adv_w = 111, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 461, .adv_w = 108, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 462, .adv_w = 84, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 463, .adv_w = 107, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 469, .adv_w = 122, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 479, .adv_w = 103, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 105, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 74, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 109, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 514, .adv_w = 127, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 524, .adv_w = 64, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 60, .box_w = 3, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 533, .adv_w = 117, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 64, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 187, .box_w = 11, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 558, .adv_w = 127, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 114, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 122, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 580, .adv_w = 117, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 589, .adv_w = 89, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 91, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 70, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 604, .adv_w = 125, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 105, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 161, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 627, .adv_w = 108, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 634, .adv_w = 106, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 643, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 72, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 653, .adv_w = 61, .box_w = 1, .box_h = 15, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 655, .adv_w = 72, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 660, .adv_w = 111, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 662, .adv_w = 192, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 664, .adv_w = 192, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 666, .adv_w = 192, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 676, .adv_w = 192, .box_w = 8, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 685, .adv_w = 192, .box_w = 9, .box_h = 10, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 697, .adv_w = 192, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 709, .adv_w = 192, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 719, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 732, .adv_w = 192, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 743, .adv_w = 192, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 754, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 770, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 787, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 804, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 820, .adv_w = 192, .box_w = 8, .box_h = 11, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 831, .adv_w = 192, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x1, 0x43, 0x52, 0x56, 0x5c, 0x63, 0x6a,
    0x81, 0x88, 0x1e8a, 0x2228, 0x22dc, 0x36ff, 0x51e9, 0x66e2
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 12289, .range_length = 26339, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 16, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t noto_serif_jp_1bit_12 = {
#else
lv_font_t noto_serif_jp_1bit_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if NOTO_SERIF_JP_1BIT_12*/

