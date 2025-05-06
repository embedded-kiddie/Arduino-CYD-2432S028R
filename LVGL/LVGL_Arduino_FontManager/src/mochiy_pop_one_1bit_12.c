/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --no-compress --font MochiyPopOne-Regular.ttf --symbols 自らに勝つ事こそ、最も難しい勝利。 --range 32-127 --format lvgl -o mochiy_pop_one_1bit_12.c
 ******************************************************************************/
/*
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
*/
#include "../ui.h"

#ifndef MOCHIY_POP_ONE_1BIT_12
#define MOCHIY_POP_ONE_1BIT_12 1
#endif

#if MOCHIY_POP_ONE_1BIT_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0x3c,

    /* U+0022 "\"" */
    0xff, 0xf0,

    /* U+0023 "#" */
    0x19, 0x8c, 0xcf, 0xff, 0xff, 0x33, 0xc, 0xcf,
    0xff, 0xff, 0x63, 0x19, 0xc6, 0x60,

    /* U+0024 "$" */
    0x18, 0x7e, 0xfe, 0xda, 0xf8, 0x7e, 0x1f, 0xdb,
    0xff, 0x7e, 0x18,

    /* U+0025 "%" */
    0x70, 0x9f, 0x3b, 0x66, 0x7d, 0x87, 0x60, 0x1b,
    0x87, 0xf8, 0xdb, 0x33, 0x6c, 0x7c, 0x7, 0x0,

    /* U+0026 "&" */
    0x1e, 0x1f, 0xc6, 0x31, 0x9c, 0x3e, 0xe, 0x67,
    0xdb, 0x3c, 0xc7, 0xbf, 0xf7, 0xcc,

    /* U+0027 "'" */
    0xfc,

    /* U+0028 "(" */
    0x27, 0x6e, 0xcc, 0xcc, 0xce, 0x66,

    /* U+0029 ")" */
    0x66, 0x63, 0x33, 0x33, 0x37, 0x6e,

    /* U+002A "*" */
    0x33, 0xf3, 0x1e, 0x34,

    /* U+002B "+" */
    0xc, 0x3, 0x0, 0xc0, 0x30, 0xff, 0xff, 0xf0,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0,

    /* U+002C "," */
    0xfc,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xfc,

    /* U+002F "/" */
    0x18, 0x84, 0x62, 0x10, 0x8c, 0x42, 0x11, 0x80,
    0x0,

    /* U+0030 "0" */
    0x3c, 0x7e, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x66, 0x7e, 0x3c,

    /* U+0031 "1" */
    0x37, 0xf7, 0x33, 0x33, 0x33, 0x30,

    /* U+0032 "2" */
    0x3c, 0xff, 0x9a, 0x30, 0x61, 0x87, 0x1c, 0x71,
    0xff, 0xf8, 0x0,

    /* U+0033 "3" */
    0x7d, 0xfc, 0x18, 0x73, 0xc7, 0x83, 0x83, 0x87,
    0xf9, 0xe0,

    /* U+0034 "4" */
    0x1e, 0xf, 0xd, 0x8e, 0xc6, 0x63, 0x31, 0xfe,
    0xff, 0x6, 0x3, 0x1, 0x80,

    /* U+0035 "5" */
    0x7f, 0x7f, 0x60, 0x60, 0x7e, 0x7f, 0x3, 0x43,
    0x63, 0x7e, 0x3c,

    /* U+0036 "6" */
    0xc, 0x1e, 0x38, 0x70, 0x7e, 0x7f, 0xe3, 0x43,
    0x63, 0x7e, 0x3c,

    /* U+0037 "7" */
    0xfe, 0xff, 0xc6, 0xc6, 0x66, 0xc, 0xc, 0x18,
    0x18, 0x38, 0x30,

    /* U+0038 "8" */
    0x7c, 0xfe, 0xc7, 0xcf, 0x7c, 0x38, 0x7e, 0xc6,
    0xc6, 0xfe, 0x7c,

    /* U+0039 "9" */
    0x3f, 0x3f, 0xb8, 0xd8, 0xcc, 0xe7, 0xf1, 0xf0,
    0x18, 0xc, 0x6, 0x3, 0x0,

    /* U+003A ":" */
    0xfc, 0x3, 0xf0,

    /* U+003B ";" */
    0xfc, 0x0, 0xfc,

    /* U+003C "<" */
    0xc, 0x18, 0x71, 0xc7, 0xc, 0xc, 0xc, 0xc,
    0x18,

    /* U+003D "=" */
    0xff, 0xff, 0xf0, 0x0, 0x0, 0xff, 0xff, 0xf0,

    /* U+003E ">" */
    0x60, 0xc1, 0xc1, 0xc1, 0xc3, 0x8e, 0x18, 0x70,
    0xc0,

    /* U+003F "?" */
    0x3f, 0x3f, 0xfc, 0xf, 0x3, 0xc1, 0xc1, 0xe0,
    0xe0, 0x30, 0xc, 0x3, 0x0, 0xc0,

    /* U+0040 "@" */
    0xf, 0x87, 0xf9, 0xff, 0xbc, 0xbf, 0xb7, 0xe6,
    0xfd, 0xbf, 0xfe, 0x79, 0x8f, 0xe0, 0x7c, 0x0,

    /* U+0041 "A" */
    0xe, 0x7, 0xc1, 0xb0, 0xce, 0x31, 0x8f, 0xe7,
    0xf9, 0x83, 0x60, 0xf8, 0x30,

    /* U+0042 "B" */
    0x3f, 0x3f, 0xd8, 0x6c, 0x37, 0xf3, 0xf9, 0x8e,
    0xc3, 0x61, 0xbf, 0xdf, 0x80,

    /* U+0043 "C" */
    0x1e, 0x3f, 0x98, 0xf8, 0x2c, 0x6, 0x3, 0x5,
    0x83, 0x63, 0xbf, 0x87, 0x80,

    /* U+0044 "D" */
    0xfc, 0x7f, 0x99, 0xcc, 0x36, 0x1b, 0xd, 0x86,
    0xc3, 0x63, 0x3f, 0x9f, 0x80,

    /* U+0045 "E" */
    0xff, 0x7f, 0xb0, 0x18, 0xf, 0xf7, 0xfb, 0x1,
    0x80, 0xc1, 0xff, 0xdf, 0xc0,

    /* U+0046 "F" */
    0xff, 0xff, 0xb0, 0x18, 0xf, 0xf7, 0xfb, 0x1,
    0x80, 0xc0, 0x60, 0x30, 0x0,

    /* U+0047 "G" */
    0x1f, 0xf, 0xe6, 0x1b, 0x80, 0xc0, 0x31, 0xfc,
    0x7f, 0x6, 0x63, 0x9f, 0xe3, 0xd8,

    /* U+0048 "H" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3f, 0xff, 0xff, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x60,

    /* U+0049 "I" */
    0xff, 0xff, 0xfc,

    /* U+004A "J" */
    0x6, 0xc, 0x18, 0x30, 0x60, 0xd1, 0xe3, 0xee,
    0xf8, 0xf0,

    /* U+004B "K" */
    0xc1, 0x63, 0xb3, 0xdf, 0x8f, 0x7, 0x3, 0xe1,
    0xb8, 0xcf, 0x63, 0xf0, 0x40,

    /* U+004C "L" */
    0xc0, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3, 0x1,
    0x80, 0xc1, 0x7f, 0xdf, 0xc0,

    /* U+004D "M" */
    0x71, 0xce, 0x7b, 0xef, 0xfd, 0xbd, 0xb7, 0xbe,
    0xf7, 0x9e, 0x73, 0xce, 0x79, 0xcf, 0x39, 0x80,

    /* U+004E "N" */
    0xc1, 0xf0, 0xf8, 0x7e, 0x3f, 0x9e, 0xcf, 0x77,
    0x9b, 0xc7, 0xe3, 0xf0, 0xc0,

    /* U+004F "O" */
    0x1e, 0x1f, 0xe6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x83, 0x71, 0x8f, 0xe1, 0xe0,

    /* U+0050 "P" */
    0x7e, 0x7f, 0xb8, 0x6c, 0x36, 0x3b, 0xf9, 0xf8,
    0xc0, 0x60, 0x30, 0x18, 0x0,

    /* U+0051 "Q" */
    0x1e, 0x1f, 0xe6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xef, 0x1f, 0x63, 0x9f, 0xf1, 0xe8,

    /* U+0052 "R" */
    0x7f, 0x3f, 0xee, 0x19, 0x86, 0x63, 0x9f, 0xc7,
    0x81, 0xf0, 0x6f, 0x18, 0xf6, 0x18,

    /* U+0053 "S" */
    0x3e, 0x3f, 0xd8, 0x4e, 0x7, 0xc0, 0xf8, 0x1e,
    0x83, 0x61, 0xbf, 0x87, 0x80,

    /* U+0054 "T" */
    0xff, 0xff, 0xf0, 0xc0, 0x30, 0xc, 0x3, 0x0,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xe6, 0x7e, 0x3c,

    /* U+0056 "V" */
    0xe0, 0xd8, 0x36, 0x1d, 0x86, 0x71, 0x8c, 0xe3,
    0x30, 0xec, 0x1e, 0x7, 0x80, 0xc0,

    /* U+0057 "W" */
    0xce, 0xf9, 0xdb, 0x3b, 0x67, 0x6c, 0xed, 0xdd,
    0x9f, 0xb3, 0xfc, 0x7b, 0x8f, 0x70, 0xcc, 0x0,

    /* U+0058 "X" */
    0xc1, 0xb8, 0xf7, 0x78, 0xfc, 0x1e, 0x7, 0x3,
    0xe1, 0xdc, 0xe3, 0xb0, 0x78, 0x8,

    /* U+0059 "Y" */
    0x0, 0xb0, 0x76, 0x19, 0xce, 0x33, 0x7, 0x80,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0,

    /* U+005A "Z" */
    0xff, 0xff, 0xe0, 0xe0, 0xe0, 0x70, 0x70, 0x70,
    0x70, 0x70, 0x7f, 0xff, 0xe0,

    /* U+005B "[" */
    0xff, 0x6d, 0xb6, 0xdf, 0x80,

    /* U+005C "\\" */
    0x8c, 0x44, 0x46, 0x22, 0x23, 0x11, 0x0,

    /* U+005D "]" */
    0xfd, 0xb6, 0xdb, 0x6f, 0xf0,

    /* U+005E "^" */
    0x10, 0x71, 0xf7, 0x74, 0x40,

    /* U+005F "_" */
    0xff, 0xff,

    /* U+0060 "`" */
    0x5c, 0x80,

    /* U+0061 "a" */
    0x3e, 0x7e, 0xe6, 0xc6, 0xc6, 0xce, 0x7f, 0x7b,

    /* U+0062 "b" */
    0xc1, 0x83, 0x7, 0xcf, 0xd8, 0xf1, 0xe3, 0xc7,
    0xfb, 0xe0,

    /* U+0063 "c" */
    0x3c, 0xff, 0x96, 0xc, 0x1c, 0xdf, 0x9e,

    /* U+0064 "d" */
    0x6, 0xc, 0x19, 0xf7, 0xfc, 0xf1, 0xe3, 0xc6,
    0xfc, 0xf8,

    /* U+0065 "e" */
    0x3c, 0xff, 0x1f, 0xff, 0xd8, 0xdf, 0x9e,

    /* U+0066 "f" */
    0x1e, 0x7c, 0xc7, 0xef, 0xc6, 0xc, 0x18, 0x30,
    0x60, 0xc0,

    /* U+0067 "g" */
    0x3e, 0xff, 0x1e, 0x3c, 0x7f, 0xdf, 0xa3, 0xfe,
    0xf8,

    /* U+0068 "h" */
    0xc1, 0x83, 0x7, 0xef, 0xfc, 0xf1, 0xe3, 0xc7,
    0x8f, 0x18,

    /* U+0069 "i" */
    0xf3, 0xff, 0xfc,

    /* U+006A "j" */
    0xc, 0x30, 0x3, 0xc, 0x30, 0xf3, 0xcd, 0xf3,
    0x80,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0x2d, 0xff, 0xbc, 0x70, 0xf9,
    0xbf, 0x38,

    /* U+006C "l" */
    0xcc, 0xcc, 0xcc, 0xcc, 0xcf, 0x70,

    /* U+006D "m" */
    0xfb, 0xbf, 0xfc, 0xef, 0x33, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33,

    /* U+006E "n" */
    0xdd, 0xff, 0x9e, 0x3c, 0x78, 0xf1, 0xe3,

    /* U+006F "o" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c,

    /* U+0070 "p" */
    0xfc, 0xfe, 0xe7, 0xc3, 0xc3, 0xe7, 0xfe, 0xfc,
    0xc0, 0xc0, 0x0,

    /* U+0071 "q" */
    0x3e, 0xff, 0x9e, 0x3c, 0x78, 0xdf, 0x9f, 0x6,
    0xc, 0x18,

    /* U+0072 "r" */
    0xff, 0xf9, 0x8c, 0x63, 0x18,

    /* U+0073 "s" */
    0x7d, 0xff, 0x17, 0xc3, 0xf8, 0xff, 0xbe,

    /* U+0074 "t" */
    0x18, 0x70, 0xc7, 0xff, 0xe6, 0xc, 0x18, 0x34,
    0x78, 0x70,

    /* U+0075 "u" */
    0xcd, 0x9b, 0x36, 0x6c, 0xdb, 0xbf, 0xbb,

    /* U+0076 "v" */
    0xe3, 0x63, 0x67, 0x66, 0x76, 0x3c, 0x3c, 0x18,

    /* U+0077 "w" */
    0xcc, 0xf3, 0x3c, 0xdb, 0x76, 0x5d, 0x9f, 0x67,
    0x70, 0xdc,

    /* U+0078 "x" */
    0x43, 0x7b, 0x8f, 0x83, 0x83, 0xe3, 0xb9, 0x8e,
    0x82,

    /* U+0079 "y" */
    0x43, 0xe3, 0x67, 0x36, 0x3c, 0x1c, 0x18, 0x38,
    0x70, 0x60,

    /* U+007A "z" */
    0xfe, 0xfe, 0x8e, 0x1c, 0x38, 0x70, 0xff, 0xff,

    /* U+007B "{" */
    0x37, 0x66, 0x66, 0xee, 0x66, 0x73,

    /* U+007C "|" */
    0xff, 0xff, 0xff,

    /* U+007D "}" */
    0xce, 0x66, 0x66, 0x77, 0x66, 0xec,

    /* U+007E "~" */
    0x38, 0xf, 0x89, 0x9b, 0xf3, 0xe0, 0x38,

    /* U+3001 "、" */
    0xce, 0x72,

    /* U+3002 "。" */
    0x76, 0xf7, 0xb7, 0x0,

    /* U+3044 "い" */
    0xc1, 0x18, 0x7b, 0x3, 0xe0, 0x36, 0x0, 0xc0,
    0x1d, 0x81, 0xf0, 0x1c, 0x0,

    /* U+3053 "こ" */
    0x7f, 0x1f, 0xe0, 0x10, 0x0, 0x0, 0x10, 0xe,
    0xb, 0xfe, 0x3f, 0x0,

    /* U+3057 "し" */
    0x20, 0x30, 0x18, 0xc, 0xc, 0x6, 0x3, 0x5,
    0x83, 0xe3, 0xbf, 0x8f, 0x0,

    /* U+305D "そ" */
    0x0, 0x18, 0x77, 0x30, 0x38, 0x1d, 0xdf, 0xff,
    0xe0, 0x70, 0x18, 0x3, 0xe0,

    /* U+3064 "つ" */
    0xf, 0x8f, 0xf9, 0xc3, 0xa0, 0x30, 0x6, 0x1,
    0xc0, 0x30, 0x1c, 0x7, 0x0, 0x40,

    /* U+306B "に" */
    0x0, 0x19, 0xec, 0xfb, 0x30, 0xc0, 0x30, 0xc,
    0x3, 0x30, 0xcf, 0xf0, 0xf0,

    /* U+3082 "も" */
    0x18, 0x3, 0x3, 0xfc, 0x58, 0x3, 0x10, 0x7e,
    0x3f, 0x11, 0x83, 0x18, 0xc3, 0xf0, 0x3c, 0x0,

    /* U+3089 "ら" */
    0x18, 0x7, 0xc0, 0xf1, 0x80, 0x60, 0x37, 0xef,
    0xf, 0x3, 0x1, 0xc1, 0xe0, 0x70,

    /* U+4E8B "事" */
    0xff, 0xe0, 0xc0, 0xff, 0x1f, 0xe3, 0xfc, 0x7f,
    0xbf, 0xff, 0xff, 0x3f, 0xc0, 0xd8, 0x30, 0x0,

    /* U+5229 "利" */
    0x3c, 0x7e, 0x6c, 0xcd, 0xff, 0xbf, 0xf6, 0x66,
    0xdf, 0xdf, 0xfb, 0xb0, 0x66, 0x3c, 0xc7, 0x0,

    /* U+52DD "勝" */
    0x7f, 0xe2, 0xff, 0x97, 0xfc, 0xf6, 0x87, 0xff,
    0x2f, 0x19, 0xfe, 0xeb, 0xfe, 0x5b, 0x62, 0xdb,
    0x3d, 0xb8,

    /* U+6700 "最" */
    0x7f, 0xcc, 0x19, 0xff, 0x3f, 0xef, 0xfe, 0xf7,
    0x9e, 0xf3, 0xde, 0x69, 0x9f, 0xfc, 0x29, 0x0,

    /* U+81EA "自" */
    0x10, 0xc, 0x3f, 0xf8, 0x3f, 0xfe, 0xf, 0x7,
    0xff, 0xc1, 0xff, 0xf0, 0x60,

    /* U+96E3 "難" */
    0x69, 0x7f, 0xf9, 0xaf, 0xff, 0xff, 0xed, 0xff,
    0xff, 0xb7, 0xff, 0xfe, 0xdf, 0xfd, 0x28, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 44, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 74, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 4, .adv_w = 97, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 187, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 20, .adv_w = 135, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 31, .adv_w = 181, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 47, .adv_w = 165, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 61, .adv_w = 63, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 62, .adv_w = 85, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 68, .adv_w = 82, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 74, .adv_w = 90, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 78, .adv_w = 179, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 92, .adv_w = 52, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 93, .adv_w = 90, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 94, .adv_w = 56, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 95, .adv_w = 75, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 104, .adv_w = 147, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 115, .adv_w = 128, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 121, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 132, .adv_w = 146, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 142, .adv_w = 144, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 155, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 166, .adv_w = 136, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 177, .adv_w = 144, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 188, .adv_w = 144, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 199, .adv_w = 147, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 212, .adv_w = 56, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 56, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 218, .adv_w = 117, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 174, .box_w = 10, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 235, .adv_w = 113, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 178, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 258, .adv_w = 197, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 274, .adv_w = 167, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 160, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 300, .adv_w = 171, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 313, .adv_w = 153, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 326, .adv_w = 161, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 339, .adv_w = 161, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 352, .adv_w = 176, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 366, .adv_w = 168, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 379, .adv_w = 56, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 382, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 392, .adv_w = 163, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 405, .adv_w = 159, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 418, .adv_w = 188, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 434, .adv_w = 176, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 447, .adv_w = 176, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 461, .adv_w = 158, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 474, .adv_w = 175, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 488, .adv_w = 167, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 502, .adv_w = 151, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 515, .adv_w = 170, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 529, .adv_w = 159, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 540, .adv_w = 170, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 554, .adv_w = 188, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 570, .adv_w = 180, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 584, .adv_w = 178, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 598, .adv_w = 165, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 611, .adv_w = 81, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 616, .adv_w = 75, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 623, .adv_w = 80, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 628, .adv_w = 119, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 633, .adv_w = 126, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 635, .adv_w = 115, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 11},
    {.bitmap_index = 637, .adv_w = 140, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 645, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 655, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 662, .adv_w = 127, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 672, .adv_w = 132, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 679, .adv_w = 108, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 689, .adv_w = 119, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 698, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 708, .adv_w = 51, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 711, .adv_w = 111, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 720, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 730, .adv_w = 89, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 736, .adv_w = 176, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 746, .adv_w = 130, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 753, .adv_w = 133, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 761, .adv_w = 135, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 772, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 782, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 787, .adv_w = 127, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 794, .adv_w = 113, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 804, .adv_w = 132, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 811, .adv_w = 137, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 819, .adv_w = 175, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 829, .adv_w = 145, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 838, .adv_w = 140, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 848, .adv_w = 137, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 856, .adv_w = 68, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 862, .adv_w = 65, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 865, .adv_w = 68, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 871, .adv_w = 180, .box_w = 11, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 878, .adv_w = 192, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 880, .adv_w = 192, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 884, .adv_w = 192, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 897, .adv_w = 192, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 909, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 922, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 935, .adv_w = 192, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 949, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 962, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 978, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 992, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1008, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1024, .adv_w = 192, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1042, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1058, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1071, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1}
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
const lv_font_t mochiy_pop_one_1bit_12 = {
#else
lv_font_t mochiy_pop_one_1bit_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if MOCHIY_POP_ONE_1BIT_12*/

