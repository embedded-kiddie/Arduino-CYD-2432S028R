/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --font NotoSansJP-Regular.ttf --symbols 自らに勝つ事こそ、最も難しい勝利。 --range 32-127 --format lvgl -o noto_sans_jp_1bit_14.c
 ******************************************************************************/
/*
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
*/
#include "../ui.h"

#ifndef NOTO_SANS_JP_1BIT_14
#define NOTO_SANS_JP_1BIT_14 1
#endif

#if NOTO_SANS_JP_1BIT_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xaa, 0xa8, 0x3c,

    /* U+0022 "\"" */
    0x99, 0x99,

    /* U+0023 "#" */
    0x49, 0x24, 0xbf, 0x49, 0x24, 0xbf, 0x52, 0x49,
    0x0,

    /* U+0024 "$" */
    0x23, 0xa3, 0x8, 0x60, 0xc3, 0x8, 0x63, 0xe2,
    0x10,

    /* U+0025 "%" */
    0x70, 0x8d, 0x90, 0x89, 0x8, 0xa0, 0x8a, 0xed,
    0xdb, 0x75, 0x10, 0x91, 0x9, 0x10, 0x9b, 0x10,
    0xe0,

    /* U+0026 "&" */
    0x38, 0x22, 0x11, 0x9, 0x87, 0x83, 0x7, 0x45,
    0x12, 0x86, 0x63, 0x9e, 0x60,

    /* U+0027 "'" */
    0xf0,

    /* U+0028 "(" */
    0x29, 0x29, 0x24, 0x92, 0x24, 0x88,

    /* U+0029 ")" */
    0x89, 0x22, 0x49, 0x24, 0xa4, 0xa0,

    /* U+002A "*" */
    0x25, 0x1c, 0xe1, 0x0,

    /* U+002B "+" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x0,

    /* U+002C "," */
    0xf6, 0x0,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x8, 0x42, 0x21, 0x8, 0x84, 0x22, 0x10, 0x84,
    0x40,

    /* U+0030 "0" */
    0x31, 0x28, 0x61, 0x86, 0x18, 0x61, 0x85, 0x23,
    0x0,

    /* U+0031 "1" */
    0x63, 0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x8f,
    0xc0,

    /* U+0032 "2" */
    0x7b, 0x30, 0x41, 0x4, 0x20, 0x84, 0x21, 0x8f,
    0xc0,

    /* U+0033 "3" */
    0x78, 0x98, 0x10, 0x20, 0xc7, 0x1, 0x1, 0x3,
    0x8d, 0xf0,

    /* U+0034 "4" */
    0xc, 0x18, 0x50, 0xa2, 0x4c, 0x91, 0x7f, 0x4,
    0x8, 0x10,

    /* U+0035 "5" */
    0x7c, 0x81, 0x2, 0x7, 0xc8, 0xc0, 0x81, 0x3,
    0x89, 0xe0,

    /* U+0036 "6" */
    0x39, 0xc, 0x20, 0xbb, 0x38, 0x61, 0x85, 0x33,
    0x80,

    /* U+0037 "7" */
    0xfc, 0x20, 0x84, 0x10, 0x42, 0x8, 0x20, 0x82,
    0x0,

    /* U+0038 "8" */
    0x39, 0x14, 0x51, 0x28, 0xe4, 0xe1, 0x87, 0x37,
    0x80,

    /* U+0039 "9" */
    0x73, 0x28, 0x61, 0x87, 0x37, 0x41, 0x8, 0x27,
    0x0,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0xf0, 0xf, 0x60,

    /* U+003C "<" */
    0x2, 0x1c, 0xc6, 0x6, 0x3, 0x81, 0x80,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x1, 0xc0, 0xe0, 0x31, 0xcc, 0x20, 0x0,

    /* U+003F "?" */
    0x79, 0x10, 0x41, 0x8, 0x43, 0xc, 0x0, 0xc3,
    0x0,

    /* U+0040 "@" */
    0xf, 0x81, 0x6, 0x20, 0x24, 0x1, 0xc7, 0x18,
    0x91, 0x91, 0x19, 0x11, 0x93, 0x28, 0xdc, 0x40,
    0x2, 0x0, 0x1f, 0x0,

    /* U+0041 "A" */
    0x8, 0xa, 0x5, 0x2, 0x83, 0x61, 0x10, 0x88,
    0xfe, 0x41, 0x20, 0xb0, 0x60,

    /* U+0042 "B" */
    0xf9, 0x1a, 0x14, 0x28, 0xdf, 0x21, 0xc1, 0x83,
    0xf, 0xf0,

    /* U+0043 "C" */
    0x3c, 0xc5, 0x4, 0x8, 0x10, 0x20, 0x40, 0x40,
    0xc4, 0xf0,

    /* U+0044 "D" */
    0xf9, 0x1a, 0x14, 0x18, 0x30, 0x60, 0xc1, 0x85,
    0x1b, 0xe0,

    /* U+0045 "E" */
    0xfe, 0x8, 0x20, 0x83, 0xe8, 0x20, 0x82, 0xf,
    0xc0,

    /* U+0046 "F" */
    0xfe, 0x8, 0x20, 0x83, 0xe8, 0x20, 0x82, 0x8,
    0x0,

    /* U+0047 "G" */
    0x1e, 0x61, 0x40, 0x80, 0x80, 0x87, 0x81, 0x81,
    0x41, 0x61, 0x1e,

    /* U+0048 "H" */
    0x83, 0x6, 0xc, 0x18, 0x3f, 0xe0, 0xc1, 0x83,
    0x6, 0x8,

    /* U+0049 "I" */
    0xff, 0xe0,

    /* U+004A "J" */
    0x8, 0x42, 0x10, 0x84, 0x21, 0xc, 0x5c,

    /* U+004B "K" */
    0x85, 0x1a, 0x64, 0x8b, 0x1e, 0x36, 0x44, 0x8d,
    0xa, 0x8,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x82, 0xf,
    0xc0,

    /* U+004D "M" */
    0xc3, 0xc3, 0xc3, 0xa3, 0xa5, 0xa5, 0x95, 0x99,
    0x99, 0x99, 0x81,

    /* U+004E "N" */
    0x83, 0x87, 0x8d, 0x1b, 0x32, 0x66, 0xc5, 0x8f,
    0xe, 0x8,

    /* U+004F "O" */
    0x3e, 0x31, 0x90, 0x50, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x41, 0x31, 0x8f, 0x80,

    /* U+0050 "P" */
    0xf9, 0xe, 0xc, 0x18, 0x30, 0xbe, 0x40, 0x81,
    0x2, 0x0,

    /* U+0051 "Q" */
    0x3e, 0x31, 0x90, 0x50, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x41, 0x31, 0x8f, 0x81, 0x80, 0x78,

    /* U+0052 "R" */
    0xfd, 0xe, 0xc, 0x18, 0x7f, 0xa6, 0x44, 0x85,
    0xe, 0x8,

    /* U+0053 "S" */
    0x7a, 0x18, 0x20, 0x60, 0xe0, 0xc1, 0x6, 0x37,
    0x80,

    /* U+0054 "T" */
    0xff, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10,

    /* U+0055 "U" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+0056 "V" */
    0xc1, 0xc3, 0x42, 0x42, 0x66, 0x24, 0x24, 0x24,
    0x1c, 0x18, 0x18,

    /* U+0057 "W" */
    0xc6, 0x14, 0x63, 0x46, 0x24, 0x72, 0x65, 0x26,
    0x92, 0x29, 0x62, 0x9c, 0x28, 0xc3, 0xc, 0x30,
    0xc0,

    /* U+0058 "X" */
    0x42, 0x66, 0x24, 0x34, 0x18, 0x18, 0x18, 0x24,
    0x24, 0x42, 0xc3,

    /* U+0059 "Y" */
    0xc2, 0x89, 0x11, 0x42, 0x85, 0x4, 0x8, 0x10,
    0x20, 0x40,

    /* U+005A "Z" */
    0xfe, 0xc, 0x30, 0x41, 0x82, 0x8, 0x10, 0x41,
    0x83, 0xf8,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x49, 0xc0,

    /* U+005C "\\" */
    0x82, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10,
    0x84,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x93, 0xc0,

    /* U+005E "^" */
    0x30, 0xc5, 0x12, 0x4a, 0x10,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0x19, 0x90,

    /* U+0061 "a" */
    0x78, 0x10, 0x4f, 0xc6, 0x18, 0xdd,

    /* U+0062 "b" */
    0x82, 0x8, 0x2e, 0xce, 0x18, 0x61, 0x86, 0x2f,
    0x0,

    /* U+0063 "c" */
    0x39, 0x8, 0x20, 0x82, 0x4, 0xe,

    /* U+0064 "d" */
    0x2, 0x4, 0x9, 0xf4, 0x70, 0x60, 0xc1, 0x82,
    0x8c, 0xe8,

    /* U+0065 "e" */
    0x39, 0x38, 0x7f, 0x82, 0x4, 0xe,

    /* U+0066 "f" */
    0x34, 0x4f, 0x44, 0x44, 0x44, 0x40,

    /* U+0067 "g" */
    0x7f, 0xa, 0x16, 0x67, 0x90, 0x20, 0x3e, 0x83,
    0xd, 0xf0,

    /* U+0068 "h" */
    0x82, 0x8, 0x2e, 0xc6, 0x18, 0x61, 0x86, 0x18,
    0x40,

    /* U+0069 "i" */
    0x9f, 0xe0,

    /* U+006A "j" */
    0x20, 0x12, 0x49, 0x24, 0x93, 0x80,

    /* U+006B "k" */
    0x82, 0x8, 0x22, 0x9a, 0xca, 0x34, 0x9a, 0x28,
    0xc0,

    /* U+006C "l" */
    0xaa, 0xaa, 0xac,

    /* U+006D "m" */
    0xb9, 0xd8, 0xc6, 0x10, 0xc2, 0x18, 0x43, 0x8,
    0x61, 0xc, 0x21,

    /* U+006E "n" */
    0xbb, 0x18, 0x61, 0x86, 0x18, 0x61,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+0070 "p" */
    0xbb, 0x38, 0x61, 0x86, 0x18, 0xbc, 0x82, 0x8,
    0x0,

    /* U+0071 "q" */
    0x3e, 0x8e, 0xc, 0x18, 0x30, 0x51, 0x9d, 0x2,
    0x4, 0x8,

    /* U+0072 "r" */
    0xbc, 0x88, 0x88, 0x88,

    /* U+0073 "s" */
    0x74, 0x20, 0xc1, 0x86, 0x3e,

    /* U+0074 "t" */
    0x44, 0xf4, 0x44, 0x44, 0x43,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0xdd,

    /* U+0076 "v" */
    0xc2, 0x8d, 0x13, 0x22, 0xc5, 0xe, 0xc,

    /* U+0077 "w" */
    0x44, 0x68, 0xc9, 0x29, 0x35, 0x22, 0xa4, 0x53,
    0xc, 0x61, 0x8c,

    /* U+0078 "x" */
    0x44, 0xd8, 0xa0, 0xc3, 0x85, 0x13, 0x62,

    /* U+0079 "y" */
    0xc2, 0x8d, 0x11, 0x22, 0xc5, 0x6, 0xc, 0x10,
    0x61, 0x80,

    /* U+007A "z" */
    0x7c, 0x21, 0x84, 0x31, 0x84, 0x3f,

    /* U+007B "{" */
    0x69, 0x24, 0x94, 0x49, 0x24, 0xc0,

    /* U+007C "|" */
    0xff, 0xff,

    /* U+007D "}" */
    0xc9, 0x24, 0x91, 0x49, 0x25, 0x80,

    /* U+007E "~" */
    0xe4, 0x70,

    /* U+3001 "、" */
    0x84, 0x20,

    /* U+3002 "。" */
    0x74, 0x63, 0x17, 0x0,

    /* U+3044 "い" */
    0x80, 0x10, 0x12, 0x2, 0x40, 0x28, 0x5, 0x0,
    0xa0, 0x1a, 0x41, 0x48, 0x6, 0x0,

    /* U+3053 "こ" */
    0x7f, 0x0, 0x0, 0x0, 0x0, 0x4, 0x2, 0x1,
    0x0, 0xc0, 0x3f, 0xc0,

    /* U+3057 "し" */
    0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1,
    0x0, 0x80, 0xc0, 0xf0, 0xcf, 0x80,

    /* U+305D "そ" */
    0x1f, 0xc0, 0x20, 0x8, 0x6, 0x1, 0xfe, 0xcc,
    0x2, 0x0, 0x40, 0x8, 0x1, 0x80, 0xe, 0x0,

    /* U+3064 "つ" */
    0xf, 0x8e, 0xa, 0x0, 0x80, 0x10, 0x2, 0x0,
    0x40, 0x10, 0xc, 0x1e, 0x0,

    /* U+306B "に" */
    0x40, 0x18, 0xfa, 0x0, 0x40, 0x8, 0x1, 0x0,
    0x2a, 0x6, 0x40, 0xc8, 0x18, 0xfd, 0x0, 0x0,

    /* U+3082 "も" */
    0x18, 0x2, 0x3, 0xf8, 0x8, 0x1, 0x1, 0x21,
    0xbf, 0x98, 0x81, 0x10, 0x22, 0x4, 0x61, 0x7,
    0xc0,

    /* U+3089 "ら" */
    0x20, 0x1f, 0x0, 0x18, 0x8, 0x4, 0xfb, 0x87,
    0x81, 0x80, 0x80, 0xc1, 0xc7, 0x80,

    /* U+4E8B "事" */
    0x2, 0x3, 0xff, 0xc0, 0x80, 0x7f, 0xc2, 0x22,
    0xf, 0xe0, 0xff, 0x80, 0x44, 0xff, 0xf8, 0x11,
    0x1f, 0xf8, 0x4, 0x40, 0xe0, 0x0,

    /* U+5229 "利" */
    0x4, 0x17, 0x81, 0x90, 0x91, 0x9, 0xfe, 0x91,
    0x9, 0x38, 0x93, 0xc9, 0x50, 0x99, 0x1, 0x90,
    0x11, 0x1, 0x10, 0x70,

    /* U+52DD "勝" */
    0x0, 0x3, 0xa9, 0x14, 0xc8, 0xaf, 0xf7, 0x14,
    0x2b, 0xfd, 0x4c, 0xce, 0xa3, 0xd7, 0xee, 0x89,
    0x34, 0x49, 0x24, 0x4b, 0x4e, 0x0,

    /* U+6700 "最" */
    0x3f, 0xe1, 0x1, 0xf, 0xf8, 0x7f, 0xc0, 0x0,
    0x7f, 0xfc, 0x90, 0x7, 0x9e, 0x3c, 0xb1, 0x23,
    0x3f, 0x3c, 0xa, 0x30,

    /* U+81EA "自" */
    0x4, 0x1, 0x83, 0xff, 0xe0, 0x3c, 0x7, 0xff,
    0xf0, 0x1e, 0x3, 0xff, 0xf8, 0xf, 0x1, 0xff,
    0xfc, 0x6,

    /* U+96E3 "難" */
    0x48, 0x97, 0xed, 0x12, 0x48, 0x3, 0xff, 0xf2,
    0x53, 0x93, 0xf7, 0xe4, 0x24, 0xfd, 0x21, 0xf,
    0xff, 0x48, 0xd3, 0xfc, 0x50, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 50, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 72, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 106, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 124, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 24, .adv_w = 206, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 152, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 62, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 55, .adv_w = 76, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 61, .adv_w = 76, .box_w = 3, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 67, .adv_w = 105, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 71, .adv_w = 124, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 78, .adv_w = 62, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 80, .adv_w = 78, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 81, .adv_w = 62, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 88, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 91, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 124, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 124, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 124, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 62, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 62, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 189, .adv_w = 124, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 196, .adv_w = 124, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 199, .adv_w = 124, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 206, .adv_w = 106, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 212, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 235, .adv_w = 136, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 147, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 143, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 132, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 163, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 317, .adv_w = 66, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 120, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 145, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 122, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 182, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 162, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 166, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 142, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 166, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 404, .adv_w = 142, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 162, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 129, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 197, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 128, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 119, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 76, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 509, .adv_w = 88, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 518, .adv_w = 76, .box_w = 3, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 524, .adv_w = 124, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 529, .adv_w = 125, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 530, .adv_w = 136, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 532, .adv_w = 126, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 138, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 114, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 553, .adv_w = 139, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 563, .adv_w = 124, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 73, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 575, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 585, .adv_w = 136, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 62, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 62, .box_w = 3, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 602, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 64, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 614, .adv_w = 207, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 625, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 136, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 139, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 647, .adv_w = 139, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 657, .adv_w = 87, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 661, .adv_w = 105, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 84, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 671, .adv_w = 136, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 180, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 695, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 702, .adv_w = 117, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 712, .adv_w = 106, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 718, .adv_w = 76, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 724, .adv_w = 60, .box_w = 1, .box_h = 16, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 726, .adv_w = 76, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 732, .adv_w = 124, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 734, .adv_w = 224, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 736, .adv_w = 224, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 740, .adv_w = 224, .box_w = 11, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 754, .adv_w = 224, .box_w = 9, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 766, .adv_w = 224, .box_w = 9, .box_h = 12, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 780, .adv_w = 224, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 796, .adv_w = 224, .box_w = 11, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 809, .adv_w = 224, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 825, .adv_w = 224, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 842, .adv_w = 224, .box_w = 9, .box_h = 12, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 856, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 878, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 898, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 920, .adv_w = 224, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 940, .adv_w = 224, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 958, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -1}
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
    0, 0, 0, 0, -29, 0, -29, 0,
    0, 0, 0, -14, 0, -24, -3, 0,
    0, 0, 0, -3, 0, 0, 0, 0,
    -8, 0, 0, 0, 0, 0, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    19, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -24, 0, -35, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -25,
    -6, -17, -9, 0, -24, 0, 0, 0,
    -4, 0, 0, 0, 6, 0, 0, -12,
    0, -9, -6, 0, -6, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, -5, -12, 0, -5, -3, -7,
    -17, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -7, 0, -2, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -11, -3, -21, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    -9, 0, -3, 6, 6, 0, 0, 2,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -13,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -14, 0, -24, 0, 0, 0, 0,
    0, 0, -7, -2, -3, 0, 0, -14,
    -4, -4, 0, 0, -4, -2, -11, 5,
    0, -3, 0, 0, 0, 0, 5, -4,
    -2, -2, -2, -2, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -8,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, -4, -6, 0, -2, -2, -2,
    -4, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, -4, -3, -3,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -7, 0, 0,
    0, 0, 0, 0, -8, -3, -6, -5,
    -4, -2, -2, -2, -2, -3, 0, 0,
    0, 0, -6, 0, 0, 0, 0, -7,
    -3, -4, -3, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -9,
    0, 0, 0, -5, 0, 0, 0, -3,
    0, -11, 0, -6, 0, -3, -2, -5,
    -6, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, -6,
    0, -3, 0, -8, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -19, 0, -19, -18, 0, 0, 0, -10,
    -3, -35, -6, 0, 0, 0, 0, -6,
    0, -8, 0, -9, -4, 0, -6, 0,
    0, -6, -6, -3, -4, -6, -5, -7,
    -5, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -7, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, -6,
    0, -4, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, -6, 0, 0, 0, 0, 0,
    0, -11, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, -11, 0, -8, 0, 0,
    0, 0, -2, -3, -6, 0, -3, -5,
    -4, -4, -3, 0, -5, 0, 0, 0,
    -2, 0, 0, 0, -3, 0, 0, -9,
    -4, -6, -5, -5, -6, -4, 0, 0,
    0, 0, 0, 0, 0, -22, 0, -39,
    0, -14, 0, 0, 0, 0, -9, 0,
    -7, 0, -6, -31, -8, -20, -15, 0,
    -19, 0, -21, 0, -4, -4, -2, 0,
    0, 0, 0, -6, -3, -10, -9, 0,
    -10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -29, -9, -29, -20,
    0, 0, 0, -13, 0, -37, -3, -7,
    0, 0, 0, -6, -3, -21, 0, -11,
    -7, 0, -8, 0, 0, 0, -3, 0,
    0, 0, 0, -4, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -8, 0, 0, 0, 0, 0, -2,
    0, -5, -4, -4, 0, 1, 1, -2,
    -1, -3, 0, -2, -3, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, 0, 3, 0, 0,
    0, 0, 0, 0, 0, -4, -4, -6,
    0, 0, 0, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -27, -19, -27, -23, -6, -6, 0, -11,
    -6, -32, -11, 0, 0, 0, 0, -6,
    -4, -14, 0, -19, -17, -5, -19, 0,
    0, -12, -15, -5, -12, -9, -9, -11,
    -9, -19, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, -5, -9,
    0, 0, 0, -5, 0, -12, -3, 0,
    0, -2, 0, -3, -4, 0, 0, -2,
    0, 0, -3, 0, 0, 0, -2, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -17, -5, -17, -13, 0, 0, 0, -4,
    -3, -19, -3, 0, -3, 2, 0, 0,
    0, -5, 0, -6, -4, 0, -6, 0,
    0, -6, -4, 0, -8, -3, -3, -4,
    -3, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -9, -3, -9, -8,
    0, 0, 0, 0, -2, -17, -2, 0,
    0, 0, 0, 0, 0, -2, 0, -5,
    0, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, -3, 0, -3,
    0, -7, 0, 0, 0, 0, 0, 0,
    -5, -1, -4, -6, -3, 0, 0, 0,
    0, 0, 0, -3, -2, -5, 0, 0,
    0, 0, 0, -5, -3, -5, -4, -3,
    -5, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -23, -17, -23, -17,
    -7, -7, -2, -4, -4, -26, -4, -4,
    -3, 0, 0, 0, 0, -7, 0, -17,
    -11, 0, -16, 0, 0, -11, -11, -8,
    -9, -4, -6, -9, -4, -12, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -9, 0, 0, 0, 0, 0, -2,
    -6, -9, -8, 0, -3, -2, -2, 0,
    -4, -5, 0, -5, -6, -6, -4, 0,
    0, 0, 0, -4, -6, -5, -5, -6,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -22,
    -8, -14, -8, 0, -19, 0, 0, 0,
    0, 0, 8, 0, 18, 0, 0, 0,
    0, -6, -3, 0, 3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -14,
    0, 0, 0, 0, 0, 0, -4, 0,
    0, 0, 0, -6, 0, -5, -2, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -8, 0, -7, -3, 1, -3, 0,
    0, 0, -4, 0, 0, 0, 0, -15,
    0, -5, 0, -2, -12, 0, -7, -4,
    0, -1, 0, 0, 0, 0, -1, -5,
    0, -2, -2, -5, -2, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, -4, 0, 0,
    -6, 0, 0, -3, -6, 0, -3, 0,
    0, 0, 0, -3, 0, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -9, 0, 2, 0, 0,
    0, 0, -2, 0, 0, -6, -6, -6,
    0, -5, -3, 0, -7, 0, -6, -4,
    0, -1, -3, 0, 0, 0, 0, -3,
    0, 1, 1, -2, 1, 0, 0, 0,
    0, 0, 0, 0, 3, 9, 12, 0,
    -13, -4, -13, -4, 0, 0, 6, 0,
    0, 0, 0, 11, 0, 16, 11, 8,
    14, 0, 15, -6, -3, 0, -4, 0,
    -3, 0, -2, 0, 0, 3, 0, -2,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 3, -9, 0, 0, 0, 11,
    0, 0, -10, 0, 0, 0, 0, -7,
    0, 0, 0, 0, -4, 0, 0, -4,
    -4, 0, 0, 0, 9, 0, 0, 0,
    0, -2, -2, 0, 3, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -9,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, -6, 0, -3, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 3, -11, 3, 0,
    3, 3, -4, 0, 0, 0, 0, -9,
    0, 0, 0, 0, -3, 0, 0, -3,
    -5, 0, -3, 0, -3, 0, 0, -6,
    -4, 0, 0, -2, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -7, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, -4, 0, 0, -8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -14, -6, -14, -9, 6, 6, 0, -4,
    0, -14, 0, 0, 0, 0, 0, 0,
    0, -3, 3, -6, -3, 0, -3, 0,
    0, 0, -2, 0, 0, 6, 4, 0,
    6, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -13, 0, 2, 0, 0,
    0, 0, -3, 0, 0, 0, 0, -6,
    0, -3, 0, 0, -6, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, -7, 1, 2, 3, 3, -7, 0,
    0, 0, 0, -4, 0, 0, 0, 0,
    -2, 0, 0, -6, -4, 0, -3, 0,
    0, 0, -3, -6, 0, 0, 0, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, -9, -2, -9, -6,
    0, 0, 0, -3, 0, -11, 0, -6,
    0, -3, 0, 0, -4, -3, 0, -6,
    -2, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    -10, 0, -10, -2, 0, 0, 0, -2,
    0, -8, 0, -6, 0, -3, 0, -4,
    -6, 0, 0, -3, -2, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, -6, 1, -4, -2, 0,
    0, 1, 0, 0, -3, 0, -2, -9,
    0, -4, 0, -3, -9, 0, 0, -3,
    -5, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -9, 0, -9, -4, 0, 0, 0, 0,
    0, -11, 0, -6, 0, -2, 0, -2,
    -2, 0, 0, -6, -2, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, -4,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -7,
    0, 0, 0, 0, -8, 0, 0, -6,
    -3, 0, -2, 0, 0, 0, 0, 0,
    -3, -2, 0, 0, -2, 0, 0, 0,
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
    0, 0, 0, -13, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -9, -9, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -7, 0,
    0, -4, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -7, 0, -4, 0, -4, -9
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
const lv_font_t noto_sans_jp_1bit_14 = {
#else
lv_font_t noto_sans_jp_1bit_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if NOTO_SANS_JP_1BIT_14*/

