/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --no-compress --font NotoSansJP-Regular.ttf --symbols 自らに勝つ事こそ、最も難しい勝利。 --range 32-127 --format lvgl -o noto_sans_jp_1bit_12.c
 ******************************************************************************/
/*
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
*/
#include "../ui.h"

#ifndef NOTO_SANS_JP_1BIT_12
#define NOTO_SANS_JP_1BIT_12 1
#endif

#if NOTO_SANS_JP_1BIT_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfc, 0x80,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x28, 0xa7, 0xca, 0x4b, 0xf4, 0x92, 0x50,

    /* U+0024 "$" */
    0x21, 0x1d, 0x18, 0x60, 0xc3, 0xc, 0x7c, 0x42,
    0x0,

    /* U+0025 "%" */
    0x61, 0x24, 0x89, 0x42, 0x56, 0x6a, 0x42, 0x91,
    0x24, 0x49, 0x21, 0x80,

    /* U+0026 "&" */
    0x38, 0x48, 0x48, 0x50, 0x62, 0x92, 0x9e, 0x8c,
    0x7a,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x49, 0x49, 0x24, 0x91, 0x20,

    /* U+0029 ")" */
    0x49, 0x12, 0x49, 0x25, 0x20,

    /* U+002A "*" */
    0x4f, 0x6a,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x10,

    /* U+002C "," */
    0xd8,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x10, 0x84, 0x42, 0x10, 0x88, 0x42, 0x21, 0x0,

    /* U+0030 "0" */
    0x76, 0xe3, 0x18, 0xc6, 0x3b, 0x70,

    /* U+0031 "1" */
    0x61, 0x8, 0x42, 0x10, 0x84, 0xf8,

    /* U+0032 "2" */
    0x74, 0x42, 0x11, 0x8, 0x88, 0xf8,

    /* U+0033 "3" */
    0x74, 0x42, 0x33, 0x4, 0x31, 0x70,

    /* U+0034 "4" */
    0x18, 0x62, 0x8a, 0x4b, 0x2f, 0xc2, 0x8,

    /* U+0035 "5" */
    0xfc, 0x21, 0xe1, 0x84, 0x33, 0xf0,

    /* U+0036 "6" */
    0x72, 0x21, 0x6c, 0xc6, 0x29, 0x70,

    /* U+0037 "7" */
    0xfc, 0x21, 0x4, 0x10, 0x82, 0x8, 0x20,

    /* U+0038 "8" */
    0x74, 0x63, 0x17, 0x4e, 0x31, 0x70,

    /* U+0039 "9" */
    0x74, 0xa3, 0x17, 0x84, 0x22, 0x70,

    /* U+003A ":" */
    0xc2,

    /* U+003B ";" */
    0xf0, 0xd, 0x80,

    /* U+003C "<" */
    0x1d, 0x8c, 0xc, 0xc,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0xe0, 0x60, 0xcc, 0xc0,

    /* U+003F "?" */
    0xe9, 0x11, 0x24, 0x40, 0x40,

    /* U+0040 "@" */
    0x1f, 0xc, 0x64, 0xd, 0x39, 0x8a, 0x64, 0x99,
    0x26, 0x4a, 0x9f, 0x90, 0x6, 0x0, 0x78,

    /* U+0041 "A" */
    0x10, 0x50, 0xa1, 0x42, 0x4f, 0x91, 0x21, 0x82,

    /* U+0042 "B" */
    0xfa, 0x18, 0x63, 0xfa, 0x18, 0x63, 0xf8,

    /* U+0043 "C" */
    0x39, 0x18, 0x20, 0x82, 0x8, 0x11, 0x38,

    /* U+0044 "D" */
    0xf2, 0x28, 0x61, 0x86, 0x18, 0x62, 0xf0,

    /* U+0045 "E" */
    0xfc, 0x21, 0xf, 0x42, 0x10, 0xf8,

    /* U+0046 "F" */
    0xfc, 0x21, 0xf, 0x42, 0x10, 0x80,

    /* U+0047 "G" */
    0x3c, 0x86, 0x4, 0x8, 0xf0, 0x60, 0xa1, 0x3c,

    /* U+0048 "H" */
    0x86, 0x18, 0x61, 0xfe, 0x18, 0x61, 0x84,

    /* U+0049 "I" */
    0xff, 0x80,

    /* U+004A "J" */
    0x8, 0x42, 0x10, 0x84, 0x31, 0x70,

    /* U+004B "K" */
    0x8e, 0x69, 0x28, 0xd3, 0x48, 0xa3, 0x84,

    /* U+004C "L" */
    0x84, 0x21, 0x8, 0x42, 0x10, 0xf8,

    /* U+004D "M" */
    0xc3, 0x8f, 0x1d, 0x5a, 0xb5, 0x6c, 0xc9, 0x82,

    /* U+004E "N" */
    0x87, 0x1c, 0x69, 0x96, 0x58, 0xe3, 0x84,

    /* U+004F "O" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xa2, 0x38,

    /* U+0050 "P" */
    0xfa, 0x18, 0x63, 0xfa, 0x8, 0x20, 0x80,

    /* U+0051 "Q" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xa2, 0x38,
    0x30, 0x38,

    /* U+0052 "R" */
    0xfa, 0x18, 0x63, 0xfa, 0x48, 0xa2, 0x84,

    /* U+0053 "S" */
    0x7a, 0x8, 0x30, 0x38, 0x30, 0x61, 0x78,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,

    /* U+0055 "U" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x73, 0x78,

    /* U+0056 "V" */
    0x83, 0x89, 0x12, 0x26, 0xc5, 0xa, 0x14, 0x10,

    /* U+0057 "W" */
    0xc4, 0x53, 0x14, 0xc5, 0x2b, 0x4a, 0x94, 0xa3,
    0x28, 0xc6, 0x31, 0x80,

    /* U+0058 "X" */
    0x44, 0x88, 0xa1, 0x41, 0x5, 0xa, 0x22, 0xc4,

    /* U+0059 "Y" */
    0x44, 0x88, 0xa1, 0x42, 0x82, 0x4, 0x8, 0x10,

    /* U+005A "Z" */
    0xfc, 0x30, 0x84, 0x30, 0x84, 0x30, 0xfc,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x4e,

    /* U+005C "\\" */
    0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x20,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x9e,

    /* U+005E "^" */
    0x23, 0x14, 0xa9, 0x44,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0xb4,

    /* U+0061 "a" */
    0x70, 0x42, 0xf8, 0xc5, 0xe0,

    /* U+0062 "b" */
    0x82, 0x8, 0x2e, 0xce, 0x18, 0x61, 0x8b, 0xe0,

    /* U+0063 "c" */
    0x7e, 0x21, 0x8, 0x65, 0xe0,

    /* U+0064 "d" */
    0x4, 0x10, 0x5f, 0x46, 0x18, 0x61, 0xc5, 0xf0,

    /* U+0065 "e" */
    0x39, 0x38, 0x7f, 0x81, 0x3, 0x80,

    /* U+0066 "f" */
    0x34, 0x4e, 0x44, 0x44, 0x44,

    /* U+0067 "g" */
    0x7e, 0x28, 0xa2, 0x72, 0x7, 0xe1, 0x85, 0xe0,

    /* U+0068 "h" */
    0x84, 0x21, 0x6c, 0xc6, 0x31, 0x8c, 0x40,

    /* U+0069 "i" */
    0x9f, 0xc0,

    /* U+006A "j" */
    0x20, 0x12, 0x49, 0x24, 0x9e,

    /* U+006B "k" */
    0x84, 0x21, 0x39, 0x53, 0x9a, 0x94, 0x40,

    /* U+006C "l" */
    0xaa, 0xaa, 0xb0,

    /* U+006D "m" */
    0xb3, 0x66, 0x62, 0x31, 0x18, 0x8c, 0x46, 0x22,

    /* U+006E "n" */
    0xb6, 0x63, 0x18, 0xc6, 0x20,

    /* U+006F "o" */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80,

    /* U+0070 "p" */
    0xbb, 0x38, 0x61, 0x86, 0x2f, 0xa0, 0x82, 0x0,

    /* U+0071 "q" */
    0x7d, 0x18, 0x61, 0x87, 0x17, 0xc1, 0x4, 0x10,

    /* U+0072 "r" */
    0xba, 0x49, 0x20,

    /* U+0073 "s" */
    0x68, 0x86, 0x19, 0xe0,

    /* U+0074 "t" */
    0x44, 0xf4, 0x44, 0x44, 0x70,

    /* U+0075 "u" */
    0x8c, 0x63, 0x18, 0xcd, 0xa0,

    /* U+0076 "v" */
    0x85, 0x14, 0x92, 0x28, 0xc3, 0x0,

    /* U+0077 "w" */
    0xcc, 0xa6, 0x53, 0x2a, 0xa5, 0x51, 0x98, 0xcc,

    /* U+0078 "x" */
    0x49, 0x23, 0xc, 0x31, 0x2c, 0xc0,

    /* U+0079 "y" */
    0x85, 0x14, 0x92, 0x28, 0xc1, 0x4, 0x21, 0x80,

    /* U+007A "z" */
    0xf8, 0x84, 0x44, 0x23, 0xe0,

    /* U+007B "{" */
    0x69, 0x24, 0xa2, 0x49, 0x26,

    /* U+007C "|" */
    0xff, 0xfc,

    /* U+007D "}" */
    0xc9, 0x24, 0x8a, 0x49, 0x2c,

    /* U+007E "~" */
    0x64, 0x70,

    /* U+3001 "、" */
    0x99, 0x80,

    /* U+3002 "。" */
    0x69, 0x96,

    /* U+3044 "い" */
    0x81, 0x40, 0xa0, 0x30, 0x18, 0xc, 0x45, 0x40,
    0xe0,

    /* U+3053 "こ" */
    0x7e, 0x0, 0x0, 0x0, 0x80, 0x80, 0xc0, 0x7f,

    /* U+3057 "し" */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x83, 0x86, 0x78,

    /* U+305D "そ" */
    0x3f, 0x2, 0x2, 0x7, 0xfe, 0x80, 0x80, 0x40,
    0x20, 0x18, 0x3, 0x80,

    /* U+3064 "つ" */
    0xf, 0x1c, 0x38, 0x4, 0x1, 0x0, 0x40, 0x20,
    0x38, 0x78,

    /* U+306B "に" */
    0x40, 0x47, 0xe0, 0x10, 0x8, 0x4, 0x3, 0x41,
    0xa0, 0x8f, 0x80,

    /* U+3082 "も" */
    0x10, 0x8, 0x24, 0x1f, 0x81, 0x1, 0xb, 0xf2,
    0x41, 0x20, 0x88, 0xc7, 0x80,

    /* U+3089 "ら" */
    0x30, 0xc, 0x80, 0x80, 0x9e, 0xe3, 0x81, 0x1,
    0x2, 0x3c,

    /* U+4E8B "事" */
    0x4, 0xf, 0xf8, 0xff, 0x12, 0x21, 0xf8, 0xff,
    0x81, 0x13, 0xff, 0x7f, 0xc0, 0x88, 0x30, 0x0,

    /* U+5229 "利" */
    0xc, 0x3e, 0x4, 0x44, 0x88, 0x9f, 0xd2, 0x62,
    0x4e, 0x4a, 0xa9, 0x90, 0x22, 0x4, 0x43, 0x80,

    /* U+52DD "勝" */
    0x75, 0x45, 0x54, 0x57, 0xe7, 0x28, 0x5f, 0xf5,
    0x44, 0x7d, 0x2d, 0xfe, 0xd2, 0x69, 0x24, 0xb4,
    0xc0,

    /* U+6700 "最" */
    0x3f, 0xc4, 0x8, 0xff, 0x1f, 0xe0, 0x0, 0xff,
    0xce, 0xf9, 0xca, 0x29, 0xdf, 0x38, 0x28, 0x80,

    /* U+81EA "自" */
    0x8, 0x2, 0xf, 0xff, 0x3, 0xc0, 0xff, 0xfc,
    0xf, 0x3, 0xff, 0xf0, 0x3f, 0xff, 0x3,

    /* U+96E3 "難" */
    0x52, 0x5f, 0x51, 0x4f, 0xfe, 0x4a, 0xc9, 0xf7,
    0xff, 0x21, 0x1f, 0xfc, 0x8a, 0x7e, 0x30, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 43, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 62, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 91, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 5, .adv_w = 107, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 107, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 21, .adv_w = 177, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 131, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 53, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 43, .adv_w = 65, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 48, .adv_w = 65, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 53, .adv_w = 90, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 55, .adv_w = 107, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 59, .adv_w = 53, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 60, .adv_w = 67, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 61, .adv_w = 53, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 75, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 70, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 107, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 107, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 53, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 53, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 136, .adv_w = 107, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 140, .adv_w = 107, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 143, .adv_w = 107, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 147, .adv_w = 91, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 182, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 167, .adv_w = 117, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 126, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 132, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 113, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 106, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 140, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 56, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 103, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 124, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 104, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 156, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 139, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 142, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 142, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 284, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 114, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 138, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 169, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 102, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 65, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 361, .adv_w = 75, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 369, .adv_w = 65, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 374, .adv_w = 107, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 378, .adv_w = 107, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 379, .adv_w = 116, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 380, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 98, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 106, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 62, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 417, .adv_w = 108, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 425, .adv_w = 117, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 53, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 53, .box_w = 3, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 439, .adv_w = 106, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 55, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 178, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 117, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 116, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 468, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 476, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 484, .adv_w = 74, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 72, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 117, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 154, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 515, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 100, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 529, .adv_w = 91, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 65, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 539, .adv_w = 52, .box_w = 1, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 541, .adv_w = 65, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 546, .adv_w = 107, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 548, .adv_w = 192, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 550, .adv_w = 192, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 552, .adv_w = 192, .box_w = 9, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 561, .adv_w = 192, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 192, .box_w = 8, .box_h = 11, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 580, .adv_w = 192, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 592, .adv_w = 192, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 602, .adv_w = 192, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 613, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 626, .adv_w = 192, .box_w = 8, .box_h = 10, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 636, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 652, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 668, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 685, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 701, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 716, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1}
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

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 1, 0, 0, 0, 0,
    1, 2, 0, 0, 0, 3, 4, 3,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 6, 6, 0, 0, 0,
    0, 0, 7, 8, 9, 10, 11, 12,
    13, 0, 0, 14, 15, 16, 0, 0,
    10, 17, 10, 18, 19, 20, 21, 22,
    23, 24, 25, 26, 2, 27, 0, 0,
    0, 0, 28, 29, 30, 0, 31, 32,
    33, 34, 0, 0, 35, 36, 34, 34,
    29, 29, 37, 38, 39, 40, 37, 41,
    42, 43, 44, 45, 2, 0, 0, 0,
    0, 0, 0, 46, 47, 0, 48, 49,
    50, 0, 0, 0, 0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 2, 0, 0, 0, 0,
    2, 0, 3, 4, 0, 5, 6, 7,
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 9, 10, 0, 0, 0,
    11, 0, 12, 0, 13, 0, 0, 0,
    13, 0, 0, 14, 0, 0, 0, 0,
    13, 0, 13, 0, 15, 16, 17, 18,
    19, 20, 21, 22, 0, 23, 3, 0,
    0, 0, 24, 0, 25, 25, 25, 26,
    27, 0, 28, 29, 0, 0, 30, 30,
    25, 30, 25, 30, 31, 32, 33, 34,
    35, 36, 37, 38, 0, 0, 3, 0,
    39, 40, 41, 42, 0, 43, 44, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, -25, 0, -25, 0,
    0, 0, 0, -12, 0, -21, -3, 0,
    0, 0, 0, -3, 0, 0, 0, 0,
    -7, 0, 0, 0, 0, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    17, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -21, 0, -30, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -22,
    -5, -14, -8, 0, -20, 0, 0, 0,
    -3, 0, 0, 0, 5, 0, 0, -10,
    0, -8, -5, 0, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, -4, -11, 0, -5, -3, -6,
    -15, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, -2, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -9, -3, -18, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    -7, 0, -3, 5, 5, 0, 0, 1,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -11,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -12, 0, -21, 0, 0, 0, 0,
    0, 0, -6, -2, -3, 0, 0, -12,
    -4, -3, 0, 0, -3, -2, -9, 4,
    0, -3, 0, 0, 0, 0, 4, -3,
    -2, -2, -1, -1, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -7,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, -3, -6, 0, -2, -1, -1,
    -3, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, -3, -3, -3,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, 0,
    0, 0, 0, 0, -7, -3, -6, -4,
    -3, -1, -1, -1, -2, -3, 0, 0,
    0, 0, -5, 0, 0, 0, 0, -6,
    -3, -3, -3, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -8,
    0, 0, 0, -4, 0, 0, 0, -3,
    0, -9, 0, -6, 0, -3, -2, -4,
    -5, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, -6,
    0, -3, 0, -7, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -16, 0, -16, -16, 0, 0, 0, -9,
    -3, -30, -5, 0, 0, 0, 0, -6,
    0, -7, 0, -8, -3, 0, -6, 0,
    0, -5, -5, -3, -4, -5, -4, -6,
    -4, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, 0, 0, 0,
    0, 0, 0, -1, 0, 0, 0, -5,
    0, -3, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, -6, 0, 0, 0, 0, 0,
    0, -9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, -9, 0, -7, 0, 0,
    0, 0, -2, -3, -5, 0, -2, -4,
    -3, -3, -3, 0, -4, 0, 0, 0,
    -2, 0, 0, 0, -3, 0, 0, -8,
    -4, -5, -4, -4, -5, -3, 0, 0,
    0, 0, 0, 0, 0, -19, 0, -33,
    0, -12, 0, 0, 0, 0, -7, 0,
    -6, 0, -5, -26, -7, -17, -12, 0,
    -17, 0, -18, 0, -3, -3, -1, 0,
    0, 0, 0, -5, -3, -8, -8, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -25, -8, -25, -17,
    0, 0, 0, -11, 0, -32, -3, -6,
    0, 0, 0, -6, -3, -18, 0, -10,
    -6, 0, -7, 0, 0, 0, -3, 0,
    0, 0, 0, -3, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -7, 0, 0, 0, 0, 0, -1,
    0, -4, -3, -3, 0, 1, 1, -1,
    -1, -3, 0, -1, -3, 0, -1, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, 2, 0, 0,
    0, 0, 0, 0, 0, -3, -3, -5,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -23, -16, -23, -20, -5, -5, 0, -9,
    -6, -28, -9, 0, 0, 0, 0, -5,
    -3, -12, 0, -16, -15, -4, -16, 0,
    0, -11, -13, -4, -11, -8, -8, -9,
    -8, -17, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, -4, -7,
    0, 0, 0, -4, 0, -11, -3, 0,
    0, -1, 0, -3, -3, 0, 0, -1,
    0, 0, -3, 0, 0, 0, -1, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -14, -5, -14, -11, 0, 0, 0, -3,
    -3, -16, -3, 0, -3, 2, 0, 0,
    0, -5, 0, -5, -4, 0, -5, 0,
    0, -5, -3, 0, -7, -2, -2, -4,
    -2, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -8, -3, -8, -7,
    0, 0, 0, 0, -2, -15, -2, 0,
    0, 0, 0, 0, 0, -2, 0, -4,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, -3, 0, -3,
    0, -6, 0, 0, 0, 0, 0, 0,
    -4, -1, -3, -5, -3, 0, 0, 0,
    0, 0, 0, -3, -2, -4, 0, 0,
    0, 0, 0, -4, -3, -4, -3, -3,
    -4, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -20, -15, -20, -15,
    -6, -6, -2, -3, -3, -22, -4, -3,
    -3, 0, 0, 0, 0, -6, 0, -15,
    -9, 0, -13, 0, 0, -9, -9, -7,
    -8, -3, -6, -8, -3, -11, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -8, 0, 0, 0, 0, 0, -2,
    -5, -8, -7, 0, -3, -2, -2, 0,
    -3, -4, 0, -4, -5, -5, -4, 0,
    0, 0, 0, -3, -6, -4, -4, -6,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -19,
    -7, -12, -7, 0, -16, 0, 0, 0,
    0, 0, 7, 0, 15, 0, 0, 0,
    0, -5, -3, 0, 2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -12,
    0, 0, 0, 0, 0, 0, -3, 0,
    0, 0, 0, -6, 0, -4, -1, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, -6, -3, 1, -3, 0,
    0, 0, -3, 0, 0, 0, 0, -13,
    0, -5, 0, -1, -10, 0, -6, -4,
    0, -1, 0, 0, 0, 0, -1, -4,
    0, -1, -1, -4, -1, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, 0, -3, 0, 0,
    -6, 0, 0, -3, -5, 0, -3, 0,
    0, 0, 0, -3, 0, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -8, 0, 2, 0, 0,
    0, 0, -2, 0, 0, -5, -5, -6,
    0, -4, -3, 0, -6, 0, -5, -4,
    0, -1, -3, 0, 0, 0, 0, -3,
    0, 1, 1, -2, 1, 0, 0, 0,
    0, 0, 0, 0, 2, 8, 10, 0,
    -11, -3, -11, -4, 0, 0, 5, 0,
    0, 0, 0, 9, 0, 14, 9, 7,
    12, 0, 13, -5, -3, 0, -4, 0,
    -3, 0, -1, 0, 0, 2, 0, -1,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 2, -8, 0, 0, 0, 10,
    0, 0, -8, 0, 0, 0, 0, -6,
    0, 0, 0, 0, -3, 0, 0, -4,
    -3, 0, 0, 0, 7, 0, 0, 0,
    0, -1, -1, 0, 3, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -8,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, -6, 0, -3, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, 2, -9, 2, 0,
    2, 2, -3, 0, 0, 0, 0, -8,
    0, 0, 0, 0, -3, 0, 0, -3,
    -4, 0, -3, 0, -3, 0, 0, -5,
    -3, 0, 0, -2, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, -3, 0, 0, -7, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -12, -6, -12, -8, 5, 5, 0, -3,
    0, -12, 0, 0, 0, 0, 0, 0,
    0, -3, 2, -6, -3, 0, -3, 0,
    0, 0, -1, 0, 0, 5, 4, 0,
    5, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -11, 0, 2, 0, 0,
    0, 0, -3, 0, 0, 0, 0, -6,
    0, -3, 0, 0, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, -6, 1, 2, 2, 2, -6, 0,
    0, 0, 0, -3, 0, 0, 0, 0,
    -1, 0, 0, -5, -3, 0, -3, 0,
    0, 0, -3, -5, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, -8, -2, -8, -5,
    0, 0, 0, -3, 0, -9, 0, -5,
    0, -2, 0, 0, -3, -3, 0, -5,
    -1, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    -9, 0, -9, -2, 0, 0, 0, -1,
    0, -7, 0, -6, 0, -2, 0, -3,
    -6, 0, 0, -3, -1, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, -5, 1, -3, -2, 0,
    0, 1, 0, 0, -3, 0, -1, -8,
    0, -4, 0, -3, -8, 0, 0, -3,
    -4, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -8, 0, -8, -4, 0, 0, 0, 0,
    0, -9, 0, -5, 0, -1, 0, -1,
    -2, 0, 0, -5, -1, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, -3,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, -7, 0, 0, -6,
    -3, 0, -2, 0, 0, 0, 0, 0,
    -3, -1, 0, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -12, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -8, -8, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -6, 0,
    0, -4, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, -4, 0, -4, -8
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 50,
    .right_class_cnt     = 44,
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
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 1,
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
const lv_font_t noto_sans_jp_1bit_12 = {
#else
lv_font_t noto_sans_jp_1bit_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
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



#endif /*#if NOTO_SANS_JP_1BIT_12*/

