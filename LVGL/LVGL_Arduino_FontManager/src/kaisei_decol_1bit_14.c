/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --font KaiseiDecol-Regular.ttf --symbols 自らに勝つ事こそ、最も難しい勝利。 --range 32-127 --format lvgl -o kaisei_decol_1bit_14.c
 ******************************************************************************/
/*
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
*/
#include "../ui.h"

#ifndef KAISEI_DECOL_1BIT_14
#define KAISEI_DECOL_1BIT_14 1
#endif

#if KAISEI_DECOL_1BIT_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xe8, 0x3c,

    /* U+0022 "\"" */
    0xaa, 0xaa, 0x80,

    /* U+0023 "#" */
    0x12, 0x9, 0x4, 0x8f, 0xf2, 0x21, 0x23, 0xfc,
    0x48, 0x24, 0x22, 0x11, 0x0,

    /* U+0024 "$" */
    0x11, 0xe9, 0x65, 0xd1, 0xc3, 0x87, 0x16, 0x59,
    0x5e, 0x10,

    /* U+0025 "%" */
    0x70, 0x51, 0x12, 0x24, 0x45, 0x9, 0x40, 0xc9,
    0x2, 0xd0, 0x91, 0x22, 0x28, 0x45, 0x7, 0x0,

    /* U+0026 "&" */
    0x1c, 0x9, 0x2, 0x40, 0xa1, 0x33, 0x94, 0x49,
    0x92, 0x24, 0x85, 0x30, 0x87, 0xdc,

    /* U+0027 "'" */
    0xf8,

    /* U+0028 "(" */
    0x12, 0x44, 0x88, 0x88, 0x88, 0x84, 0x42, 0x10,

    /* U+0029 ")" */
    0x84, 0x22, 0x11, 0x11, 0x11, 0x12, 0x24, 0x80,

    /* U+002A "*" */
    0x2d, 0x2d, 0x20,

    /* U+002B "+" */
    0x8, 0x4, 0x2, 0x1, 0xf, 0xf8, 0x40, 0x20,
    0x10, 0x8, 0x0,

    /* U+002C "," */
    0xf4,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x8, 0x44, 0x21, 0x10, 0x88, 0x42, 0x21, 0x8,
    0x0,

    /* U+0030 "0" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x84,
    0x88, 0xe0,

    /* U+0031 "1" */
    0x65, 0x8, 0x42, 0x10, 0x84, 0x21, 0x1c,

    /* U+0032 "2" */
    0x7b, 0x18, 0x41, 0xc, 0x21, 0x18, 0x82, 0x1f,
    0xc0,

    /* U+0033 "3" */
    0x3c, 0x85, 0x8, 0x10, 0x43, 0x80, 0x81, 0x2,
    0x89, 0xe0,

    /* U+0034 "4" */
    0x8, 0x30, 0xa1, 0x44, 0x89, 0x22, 0x7f, 0x8,
    0x10, 0x20,

    /* U+0035 "5" */
    0x7e, 0x81, 0x2, 0x5, 0xcc, 0x50, 0x81, 0x3,
    0x89, 0xe0,

    /* U+0036 "6" */
    0x4, 0x30, 0x82, 0xb, 0x98, 0xa0, 0xc1, 0x83,
    0x8, 0xe0,

    /* U+0037 "7" */
    0xff, 0x8, 0x20, 0x40, 0x82, 0x4, 0x18, 0x30,
    0x60, 0x80,

    /* U+0038 "8" */
    0x38, 0x89, 0x12, 0x23, 0x89, 0xa1, 0xc1, 0x83,
    0x9, 0xe0,

    /* U+0039 "9" */
    0x39, 0x8a, 0xc, 0x18, 0x28, 0xce, 0x82, 0x8,
    0x21, 0x80,

    /* U+003A ":" */
    0xf0, 0x3c,

    /* U+003B ";" */
    0xf0, 0x3d, 0x0,

    /* U+003C "<" */
    0x1, 0x2, 0xc, 0x30, 0xc0, 0x60, 0x10, 0x6,
    0x1,

    /* U+003D "=" */
    0xff, 0x0, 0xff,

    /* U+003E ">" */
    0x80, 0x40, 0x30, 0xc, 0x3, 0x6, 0x18, 0x20,
    0xc0,

    /* U+003F "?" */
    0x7a, 0x18, 0x41, 0x18, 0xc2, 0x8, 0x0, 0xc3,
    0x0,

    /* U+0040 "@" */
    0xf, 0x86, 0x9, 0x0, 0xa7, 0x99, 0x13, 0x22,
    0x64, 0x8c, 0x92, 0x8d, 0x88, 0x0, 0x82, 0xf,
    0x80,

    /* U+0041 "A" */
    0xc, 0x1, 0xc0, 0x58, 0x9, 0x1, 0x30, 0x46,
    0x7, 0xc1, 0xc, 0x41, 0x88, 0x11, 0x3, 0x0,

    /* U+0042 "B" */
    0xfc, 0x42, 0x42, 0x42, 0x44, 0x7c, 0x43, 0x41,
    0x41, 0x41, 0x7e,

    /* U+0043 "C" */
    0x1e, 0x30, 0x90, 0x50, 0x8, 0x4, 0x2, 0x1,
    0x0, 0x40, 0xa0, 0x8f, 0x80,

    /* U+0044 "D" */
    0xfe, 0x10, 0x24, 0x9, 0x1, 0x40, 0x50, 0x14,
    0x5, 0x1, 0x40, 0x90, 0x47, 0xe0,

    /* U+0045 "E" */
    0xfe, 0x42, 0x40, 0x40, 0x40, 0x7c, 0x40, 0x40,
    0x41, 0x41, 0x7f,

    /* U+0046 "F" */
    0x7f, 0x21, 0x20, 0x20, 0x20, 0x3e, 0x20, 0x20,
    0x20, 0x20, 0x70,

    /* U+0047 "G" */
    0x1f, 0x98, 0x64, 0xa, 0x0, 0x80, 0x20, 0x8,
    0x3e, 0x2, 0x40, 0x98, 0x21, 0xf0,

    /* U+0048 "H" */
    0x40, 0x90, 0x24, 0x9, 0x2, 0x40, 0x9f, 0xe4,
    0x9, 0x2, 0x40, 0x90, 0x24, 0x8,

    /* U+0049 "I" */
    0x49, 0x24, 0x92, 0x49, 0x0,

    /* U+004A "J" */
    0x1c, 0x10, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8,
    0x10, 0x20, 0x4d, 0x1e, 0x0,

    /* U+004B "K" */
    0x43, 0x22, 0x12, 0xa, 0x5, 0x3, 0x81, 0x60,
    0x98, 0x44, 0x23, 0x10, 0xc0,

    /* U+004C "L" */
    0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x41, 0x41, 0x7f,

    /* U+004D "M" */
    0x60, 0x23, 0x83, 0x14, 0x28, 0xb1, 0x45, 0x8a,
    0x24, 0x91, 0x34, 0x88, 0xc4, 0x46, 0x22, 0x31,
    0x10, 0xc,

    /* U+004E "N" */
    0x60, 0x9c, 0x25, 0x9, 0x62, 0x4c, 0x91, 0x24,
    0x69, 0xe, 0x41, 0x90, 0x64, 0x8,

    /* U+004F "O" */
    0x1e, 0x18, 0x64, 0xa, 0x1, 0x80, 0x60, 0x18,
    0x6, 0x1, 0x40, 0x90, 0x23, 0xf0,

    /* U+0050 "P" */
    0x7e, 0x41, 0x41, 0x41, 0x42, 0x7c, 0x40, 0x40,
    0x40, 0x40, 0x40,

    /* U+0051 "Q" */
    0x1e, 0xc, 0x31, 0x2, 0x40, 0x28, 0x5, 0x0,
    0xa0, 0x14, 0xc2, 0x64, 0x88, 0xd0, 0xcc, 0x7,
    0x80, 0x1c,

    /* U+0052 "R" */
    0x7c, 0x21, 0x10, 0x88, 0x44, 0x43, 0xc1, 0x20,
    0x98, 0x44, 0x23, 0x10, 0xc0,

    /* U+0053 "S" */
    0x79, 0xa, 0x16, 0x6, 0x3, 0x1, 0x1, 0x83,
    0x5, 0xf0,

    /* U+0054 "T" */
    0xff, 0xa2, 0x10, 0x84, 0x20, 0x8, 0x2, 0x0,
    0x80, 0x20, 0x8, 0x2, 0x0, 0x80,

    /* U+0055 "U" */
    0x60, 0x90, 0x24, 0x9, 0x2, 0x40, 0x90, 0x24,
    0x9, 0x2, 0x40, 0x90, 0x43, 0xe0,

    /* U+0056 "V" */
    0x60, 0xc8, 0x22, 0x8, 0xc4, 0x11, 0x4, 0x41,
    0xa0, 0x28, 0xa, 0x3, 0x0, 0x40,

    /* U+0057 "W" */
    0x61, 0x19, 0x84, 0x42, 0x31, 0x8, 0xe4, 0x25,
    0x90, 0xd2, 0x43, 0x4a, 0x5, 0x38, 0x18, 0x60,
    0x61, 0x81, 0x86, 0x0,

    /* U+0058 "X" */
    0x60, 0x86, 0x20, 0x64, 0x5, 0x0, 0xc0, 0x8,
    0x1, 0x80, 0xd8, 0x11, 0x4, 0x31, 0x83, 0x0,

    /* U+0059 "Y" */
    0xc1, 0x10, 0x88, 0x82, 0x81, 0x40, 0x40, 0x20,
    0x10, 0x8, 0x4, 0x2, 0x0,

    /* U+005A "Z" */
    0xff, 0x86, 0x4, 0xc, 0x18, 0x10, 0x30, 0x60,
    0x41, 0xc1, 0xff,

    /* U+005B "[" */
    0xf8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0xf0,

    /* U+005C "\\" */
    0x84, 0x20, 0x84, 0x10, 0x82, 0x10, 0x82, 0x10,

    /* U+005D "]" */
    0xf1, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xf0,

    /* U+005E "^" */
    0x31, 0x44, 0xa1,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0xc3,

    /* U+0061 "a" */
    0x38, 0x88, 0x10, 0xe6, 0x50, 0xa1, 0x3f,

    /* U+0062 "b" */
    0xc0, 0x81, 0x2, 0xe6, 0x48, 0x50, 0xa1, 0x42,
    0x89, 0xe0,

    /* U+0063 "c" */
    0x38, 0x8a, 0x4, 0x8, 0x10, 0x11, 0x1c,

    /* U+0064 "d" */
    0xc, 0x8, 0x11, 0xe4, 0x50, 0xa1, 0x42, 0x85,
    0x9, 0xf8,

    /* U+0065 "e" */
    0x3b, 0x1f, 0xe0, 0x82, 0xc, 0x5e,

    /* U+0066 "f" */
    0x3a, 0x51, 0xe4, 0x21, 0x8, 0x42, 0x10,

    /* U+0067 "g" */
    0x3c, 0x89, 0x12, 0x24, 0x86, 0x10, 0x3e, 0x85,
    0x9, 0xe0,

    /* U+0068 "h" */
    0xc0, 0x40, 0x40, 0x5c, 0x62, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x42,

    /* U+0069 "i" */
    0x48, 0x64, 0x92, 0x49, 0x0,

    /* U+006A "j" */
    0x33, 0x3, 0x11, 0x11, 0x11, 0x11, 0x9e,

    /* U+006B "k" */
    0xc0, 0x40, 0x40, 0x44, 0x48, 0x50, 0x70, 0x58,
    0x48, 0x44, 0x46,

    /* U+006C "l" */
    0xc9, 0x24, 0x92, 0x49, 0x0,

    /* U+006D "m" */
    0xd9, 0x8c, 0xc9, 0x11, 0x22, 0x24, 0x44, 0x88,
    0x91, 0x12, 0x22,

    /* U+006E "n" */
    0xdc, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x61, 0x3c,

    /* U+0070 "p" */
    0xdc, 0xc9, 0xa, 0x14, 0x28, 0x51, 0x34, 0x50,
    0x81, 0x0,

    /* U+0071 "q" */
    0x3e, 0x42, 0x82, 0x82, 0x82, 0x82, 0x42, 0x2e,
    0x12, 0x2, 0x2,

    /* U+0072 "r" */
    0xdb, 0x10, 0x84, 0x21, 0x8,

    /* U+0073 "s" */
    0x7c, 0x60, 0xc3, 0x6, 0x3e,

    /* U+0074 "t" */
    0x4, 0x4f, 0x44, 0x44, 0x44, 0x70,

    /* U+0075 "u" */
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3f,

    /* U+0076 "v" */
    0xc2, 0x62, 0x22, 0x24, 0x34, 0x14, 0x18, 0x18,

    /* U+0077 "w" */
    0x42, 0x24, 0x62, 0x66, 0x42, 0xa4, 0x29, 0x42,
    0x98, 0x39, 0x81, 0x18,

    /* U+0078 "x" */
    0x62, 0x24, 0x18, 0x18, 0x18, 0x2c, 0x24, 0x46,

    /* U+0079 "y" */
    0xe1, 0x10, 0x8c, 0x82, 0x41, 0x40, 0xe0, 0x20,
    0x10, 0x10, 0x28, 0x18, 0x0,

    /* U+007A "z" */
    0xfe, 0x21, 0x8c, 0x21, 0x8c, 0x7f,

    /* U+007B "{" */
    0x9, 0x24, 0x94, 0x49, 0x24, 0x80,

    /* U+007C "|" */
    0xff, 0xf8,

    /* U+007D "}" */
    0x9, 0x24, 0x91, 0x49, 0x25, 0x0,

    /* U+007E "~" */
    0x70, 0x46, 0x0, 0xe0,

    /* U+3001 "、" */
    0xc8, 0x80,

    /* U+3002 "。" */
    0x69, 0x96,

    /* U+3044 "い" */
    0x80, 0x20, 0x68, 0xa, 0x1, 0x80, 0x62, 0x1c,
    0x81, 0xc0,

    /* U+3053 "こ" */
    0x7e, 0x6, 0x4, 0x0, 0x0, 0x0, 0x0, 0x80,
    0x41, 0x3e,

    /* U+3057 "し" */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x81,
    0x86, 0x78,

    /* U+305D "そ" */
    0x2, 0x33, 0x7, 0x2, 0x2, 0xfe, 0xb0, 0x30,
    0x30, 0x10, 0x8, 0x3, 0xc0,

    /* U+3064 "つ" */
    0xf, 0x9c, 0x78, 0xc, 0x3, 0x0, 0xc0, 0x60,
    0x30, 0x70,

    /* U+306B "に" */
    0x87, 0xa0, 0x28, 0x2, 0x0, 0x80, 0x21, 0x8,
    0x46, 0xe, 0xe0, 0x0,

    /* U+3082 "も" */
    0x4, 0x36, 0x2, 0x1, 0x40, 0xaf, 0xa4, 0x42,
    0x21, 0x19, 0x7, 0x80,

    /* U+3089 "ら" */
    0x60, 0x70, 0x4, 0xb, 0xd8, 0x40, 0x81, 0x4,
    0x1b, 0xc0,

    /* U+4E8B "事" */
    0x2, 0x0, 0x10, 0xdf, 0xf8, 0x7f, 0x82, 0x24,
    0x1f, 0xe0, 0x8, 0x7, 0xf9, 0xff, 0xf8, 0x12,
    0x1f, 0xf0, 0x4, 0x0, 0xe0, 0x0,

    /* U+5229 "利" */
    0x0, 0x0, 0x78, 0x5e, 0x12, 0x10, 0x97, 0xf4,
    0x8c, 0x24, 0x79, 0x25, 0x49, 0x29, 0x4a, 0x40,
    0x42, 0x2, 0x10, 0x10, 0x83, 0x80,

    /* U+52DD "勝" */
    0x74, 0xb2, 0x9d, 0x14, 0x44, 0xe3, 0xc5, 0x34,
    0xab, 0xfd, 0x4e, 0x8a, 0xff, 0x59, 0x22, 0x89,
    0x24, 0x89, 0x69, 0x80,

    /* U+6700 "最" */
    0x1f, 0xe0, 0xfd, 0x4, 0x8, 0x1f, 0x9f, 0xff,
    0x93, 0x0, 0xfb, 0xc7, 0xd4, 0x26, 0x61, 0xf2,
    0x19, 0xa8, 0xe, 0x30,

    /* U+81EA "自" */
    0x10, 0x18, 0x30, 0xff, 0x81, 0x85, 0xfd, 0x81,
    0x85, 0xfd, 0x81, 0x81, 0xfe,

    /* U+96E3 "難" */
    0x2c, 0x1, 0x46, 0x9f, 0xec, 0x51, 0x57, 0xdf,
    0xaa, 0xd4, 0xe3, 0xe2, 0x94, 0x38, 0xab, 0xf7,
    0x8a, 0x28, 0x51, 0x54, 0x6f, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 90, .box_w = 2, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 87, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 7, .adv_w = 175, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 157, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 30, .adv_w = 198, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 170, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 63, .box_w = 1, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 61, .adv_w = 101, .box_w = 4, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 69, .adv_w = 101, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 77, .adv_w = 101, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 80, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 91, .adv_w = 78, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 92, .adv_w = 90, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 93, .adv_w = 78, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 112, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 103, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 132, .box_w = 5, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 132, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 87, .box_w = 2, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 87, .box_w = 2, .box_h = 9, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 204, .adv_w = 175, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 213, .adv_w = 168, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 216, .adv_w = 175, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 225, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 202, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 251, .adv_w = 173, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 155, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 162, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 184, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 151, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 137, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 175, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 187, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 93, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 102, .box_w = 7, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 373, .adv_w = 162, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 212, .box_w = 13, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 175, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 429, .adv_w = 184, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 140, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 184, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 472, .adv_w = 158, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 155, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 169, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 169, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 224, .box_w = 14, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 171, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 155, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 586, .adv_w = 144, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 597, .adv_w = 101, .box_w = 4, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 605, .adv_w = 112, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 613, .adv_w = 101, .box_w = 4, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 621, .adv_w = 125, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 624, .adv_w = 112, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 625, .adv_w = 87, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 626, .adv_w = 122, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 633, .adv_w = 137, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 660, .adv_w = 122, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 87, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 673, .adv_w = 124, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 683, .adv_w = 142, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 694, .adv_w = 77, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 699, .adv_w = 85, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 706, .adv_w = 133, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 78, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 722, .adv_w = 206, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 733, .adv_w = 142, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 741, .adv_w = 139, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 748, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 758, .adv_w = 136, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 769, .adv_w = 99, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 774, .adv_w = 100, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 779, .adv_w = 83, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 785, .adv_w = 141, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 793, .adv_w = 129, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 801, .adv_w = 191, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 813, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 821, .adv_w = 133, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 834, .adv_w = 108, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 101, .box_w = 3, .box_h = 14, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 846, .adv_w = 56, .box_w = 1, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 848, .adv_w = 101, .box_w = 3, .box_h = 14, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 854, .adv_w = 157, .box_w = 9, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 858, .adv_w = 224, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 860, .adv_w = 224, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 862, .adv_w = 224, .box_w = 10, .box_h = 8, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 872, .adv_w = 224, .box_w = 8, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 882, .adv_w = 224, .box_w = 8, .box_h = 10, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 892, .adv_w = 224, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 905, .adv_w = 224, .box_w = 10, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 915, .adv_w = 224, .box_w = 10, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 927, .adv_w = 224, .box_w = 9, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 939, .adv_w = 224, .box_w = 7, .box_h = 11, .ofs_x = 4, .ofs_y = -1},
    {.bitmap_index = 949, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 971, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 993, .adv_w = 224, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1013, .adv_w = 224, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1033, .adv_w = 224, .box_w = 8, .box_h = 13, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 1046, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = -1}
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
const lv_font_t kaisei_decol_1bit_14 = {
#else
lv_font_t kaisei_decol_1bit_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
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



#endif /*#if KAISEI_DECOL_1BIT_14*/

