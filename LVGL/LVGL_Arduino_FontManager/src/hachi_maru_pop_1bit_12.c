/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --no-compress --font HachiMaruPop-Regular.ttf --symbols 自らに勝つ事こそ、最も難しい勝利。 --range 32-127 --format lvgl -o hachi_maru_pop_1bit_12.c
 ******************************************************************************/
/*
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
*/
#include "../ui.h"

#ifndef HACHI_MARU_POP_1BIT_12
#define HACHI_MARU_POP_1BIT_12 1
#endif

#if HACHI_MARU_POP_1BIT_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x49, 0x24, 0x90, 0xf7, 0x80,

    /* U+0022 "\"" */
    0xf0,

    /* U+0023 "#" */
    0x0, 0x12, 0x22, 0xff, 0x24, 0x24, 0x44, 0xfe,
    0x48, 0x48, 0x48,

    /* U+0024 "$" */
    0x10, 0xfb, 0x4c, 0x89, 0xe, 0x7, 0x9, 0x13,
    0x2d, 0xf0, 0x80,

    /* U+0025 "%" */
    0x31, 0x4a, 0x4c, 0x4c, 0x38, 0x10, 0x26, 0x29,
    0x49, 0x86,

    /* U+0026 "&" */
    0x30, 0x48, 0x48, 0x48, 0x30, 0x50, 0x8a, 0x86,
    0x86, 0x79,

    /* U+0027 "'" */
    0xf0,

    /* U+0028 "(" */
    0x12, 0x44, 0x88, 0x88, 0x84, 0x63,

    /* U+0029 ")" */
    0x84, 0x22, 0x11, 0x11, 0x12, 0x48,

    /* U+002A "*" */
    0x25, 0x5c, 0x47, 0x54,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x0,

    /* U+002C "," */
    0xd0,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x24, 0x94, 0x92, 0x52, 0x0,

    /* U+0030 "0" */
    0x3e, 0x31, 0x90, 0x50, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x41, 0x31, 0x8f, 0x80,

    /* U+0031 "1" */
    0x35, 0x11, 0x11, 0x11, 0x11,

    /* U+0032 "2" */
    0x3c, 0x42, 0x81, 0x1, 0x1, 0x2, 0x4, 0x8,
    0x30, 0xff,

    /* U+0033 "3" */
    0x3c, 0xc2, 0x1, 0x1, 0x1, 0x2, 0xc, 0x3,
    0x1, 0x3, 0x3e,

    /* U+0034 "4" */
    0x10, 0x8, 0x8, 0x8, 0x44, 0x24, 0x12, 0x9,
    0x84, 0x7f, 0x82, 0x1, 0x0,

    /* U+0035 "5" */
    0xff, 0x2, 0x7, 0xc0, 0x40, 0x40, 0x81, 0x5,
    0xf0,

    /* U+0036 "6" */
    0x8, 0x30, 0x60, 0x7c, 0xc2, 0x81, 0x81, 0x81,
    0x81, 0x42, 0x3c,

    /* U+0037 "7" */
    0x0, 0xff, 0x81, 0x81, 0x82, 0x2, 0x2, 0x4,
    0x4, 0x4, 0x4, 0x0,

    /* U+0038 "8" */
    0x3c, 0x21, 0xa0, 0x50, 0x1c, 0x33, 0x60, 0xf1,
    0x84, 0x81, 0x61, 0x9f, 0x0,

    /* U+0039 "9" */
    0x3c, 0x31, 0x90, 0x50, 0x18, 0x4, 0x7, 0x4,
    0xc6, 0x3d, 0x1, 0x0, 0x80,

    /* U+003A ":" */
    0xf0, 0xf0,

    /* U+003B ";" */
    0xf0, 0x3c,

    /* U+003C "<" */
    0x0, 0x21, 0x8, 0xc1, 0x3, 0x2, 0x4,

    /* U+003D "=" */
    0xf8, 0x3e,

    /* U+003E ">" */
    0x1, 0x2, 0x6, 0x4, 0x21, 0x8, 0xc0,

    /* U+003F "?" */
    0x7c, 0xc2, 0x1, 0x1, 0x1, 0x6, 0x18, 0x10,
    0x38, 0x28, 0x38,

    /* U+0040 "@" */
    0x1f, 0x4, 0x19, 0x79, 0x48, 0x9a, 0x13, 0x42,
    0x68, 0x4d, 0xb, 0x52, 0xc5, 0x80, 0x7c, 0x0,

    /* U+0041 "A" */
    0x1c, 0x11, 0x10, 0x48, 0x28, 0xf, 0xfe, 0x3,
    0x1, 0x80, 0xc0, 0x40,

    /* U+0042 "B" */
    0xfc, 0x83, 0x81, 0x81, 0x82, 0x8e, 0x81, 0x81,
    0x83, 0xbc,

    /* U+0043 "C" */
    0x1e, 0x10, 0x90, 0x10, 0x8, 0x4, 0x2, 0x0,
    0x80, 0x61, 0xf, 0x0,

    /* U+0044 "D" */
    0xf8, 0x86, 0x82, 0x81, 0x81, 0x81, 0x81, 0x82,
    0x86, 0xf8,

    /* U+0045 "E" */
    0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80,
    0x80, 0x7f,

    /* U+0046 "F" */
    0xff, 0x80, 0x80, 0x80, 0x80, 0xfe, 0x80, 0x80,
    0x80, 0x0,

    /* U+0047 "G" */
    0x1e, 0x10, 0x90, 0x10, 0x8, 0x4, 0x2, 0x7f,
    0x4, 0x42, 0x31, 0xf, 0x80,

    /* U+0048 "H" */
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xf, 0xfe, 0x3,
    0x1, 0x80, 0xc0, 0x40,

    /* U+0049 "I" */
    0xf9, 0x8, 0x42, 0x10, 0x84, 0x27, 0xc0,

    /* U+004A "J" */
    0xff, 0x82, 0x1, 0x0, 0x40, 0x20, 0x10, 0x8,
    0x8, 0xc, 0x3c, 0x0,

    /* U+004B "K" */
    0x82, 0x84, 0x98, 0xa0, 0xc0, 0xc0, 0xe0, 0x90,
    0x8c, 0x83,

    /* U+004C "L" */
    0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x7f,

    /* U+004D "M" */
    0x73, 0x93, 0xe8, 0x46, 0x1, 0x80, 0x60, 0x18,
    0x6, 0x1, 0x80, 0x90, 0x20,

    /* U+004E "N" */
    0x81, 0x81, 0xc1, 0xa1, 0x91, 0x89, 0x85, 0x85,
    0x83, 0x81,

    /* U+004F "O" */
    0x3e, 0x31, 0xb0, 0x70, 0x18, 0xc, 0x6, 0x3,
    0x82, 0x63, 0x1f, 0x0,

    /* U+0050 "P" */
    0xfc, 0xc2, 0x81, 0x81, 0x81, 0x81, 0x82, 0xfc,
    0x80, 0x80,

    /* U+0051 "Q" */
    0x1e, 0x18, 0x64, 0xa, 0x1, 0x80, 0x60, 0x18,
    0x5, 0x9, 0x61, 0x8f, 0xe0,

    /* U+0052 "R" */
    0x7c, 0x82, 0x81, 0x81, 0x81, 0x81, 0x86, 0xf8,
    0x84, 0x82,

    /* U+0053 "S" */
    0x3e, 0x30, 0xf0, 0x10, 0x8, 0x6, 0x1, 0xfc,
    0x2, 0x1, 0xf, 0x0,

    /* U+0054 "T" */
    0xff, 0x84, 0x2, 0x1, 0x0, 0x80, 0x40, 0x20,
    0x10, 0x8, 0x4, 0x0,

    /* U+0055 "U" */
    0x41, 0x40, 0xa0, 0x30, 0x18, 0xc, 0x6, 0x2,
    0x83, 0x63, 0xf, 0x0,

    /* U+0056 "V" */
    0x80, 0x60, 0x14, 0x9, 0x2, 0x40, 0x88, 0x42,
    0x10, 0x48, 0xc, 0x0,

    /* U+0057 "W" */
    0x80, 0xa0, 0x18, 0x6, 0x1, 0x80, 0x60, 0x18,
    0x45, 0x32, 0x73, 0x80,

    /* U+0058 "X" */
    0x80, 0xa0, 0x88, 0x82, 0x80, 0x80, 0xa0, 0x50,
    0x44, 0x41, 0x40, 0x80,

    /* U+0059 "Y" */
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xa, 0x8, 0x88,
    0x10, 0x8, 0x4, 0x0,

    /* U+005A "Z" */
    0x7f, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x20, 0x3f, 0xc0,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x93, 0x80,

    /* U+005C "\\" */
    0x91, 0x24, 0x91, 0x24, 0x80,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x27, 0x80,

    /* U+005E "^" */
    0x2d,

    /* U+005F "_" */
    0xf0,

    /* U+0060 "`" */
    0x90,

    /* U+0061 "a" */
    0x3c, 0x42, 0x82, 0x82, 0x82, 0x82, 0x47, 0x3c,

    /* U+0062 "b" */
    0x82, 0x8, 0x3e, 0x8a, 0x18, 0x61, 0x8b, 0xc0,

    /* U+0063 "c" */
    0x3c, 0x86, 0x4, 0x8, 0x10, 0x10, 0x9e,

    /* U+0064 "d" */
    0x2, 0x4, 0xfa, 0x18, 0x30, 0x60, 0xc1, 0x42,
    0x7c,

    /* U+0065 "e" */
    0x3c, 0x42, 0x81, 0x81, 0xfe, 0x80, 0x60, 0x3c,

    /* U+0066 "f" */
    0x1c, 0x45, 0xa, 0x4, 0x8, 0x3f, 0x20, 0x40,
    0x40,

    /* U+0067 "g" */
    0x38, 0xc6, 0x82, 0x82, 0xc6, 0x7a, 0xe, 0x16,
    0xc,

    /* U+0068 "h" */
    0x81, 0x2, 0x5, 0xcc, 0x58, 0x60, 0xc1, 0x83,
    0x4,

    /* U+0069 "i" */
    0xf7, 0x84, 0x92,

    /* U+006A "j" */
    0x18, 0x92, 0x46, 0x0, 0x20, 0x82, 0x99, 0xc0,

    /* U+006B "k" */
    0x81, 0x2, 0x4, 0x29, 0x9c, 0x30, 0x70, 0x99,
    0xc,

    /* U+006C "l" */
    0x38, 0xd9, 0x12, 0x24, 0x48, 0x92, 0x18, 0xce,

    /* U+006D "m" */
    0xf7, 0x4a, 0x62, 0x31, 0x18, 0x8c, 0x6, 0x4,

    /* U+006E "n" */
    0x9d, 0x4f, 0xe, 0x18, 0x30, 0x61, 0x0,

    /* U+006F "o" */
    0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3c,

    /* U+0070 "p" */
    0xf9, 0xa, 0xc, 0x18, 0x30, 0x61, 0x7c, 0x80,

    /* U+0071 "q" */
    0x3c, 0x86, 0xc, 0x18, 0x30, 0x50, 0x9f, 0x2,

    /* U+0072 "r" */
    0x8f, 0x22, 0x82, 0x4, 0x8, 0x10, 0x0,

    /* U+0073 "s" */
    0x3c, 0x86, 0x4, 0x8, 0xc, 0x7, 0x2, 0x38,

    /* U+0074 "t" */
    0x0, 0x82, 0x3f, 0x41, 0x4, 0x10, 0x20, 0x70,

    /* U+0075 "u" */
    0x0, 0x82, 0x82, 0x82, 0x82, 0x86, 0x46, 0x79,

    /* U+0076 "v" */
    0x81, 0x81, 0x42, 0x42, 0x22, 0x24, 0x18,

    /* U+0077 "w" */
    0x80, 0xc0, 0x60, 0x31, 0x18, 0x8c, 0x45, 0x54,
    0xee,

    /* U+0078 "x" */
    0x82, 0x88, 0xa0, 0x82, 0x88, 0xa0, 0x80,

    /* U+0079 "y" */
    0x83, 0x5, 0x9, 0x12, 0x43, 0x82, 0x8, 0x60,

    /* U+007A "z" */
    0x7f, 0x2, 0x4, 0x8, 0x10, 0x20, 0x7f,

    /* U+007B "{" */
    0x34, 0x44, 0x4c, 0xc4, 0x44, 0x43,

    /* U+007C "|" */
    0x7f, 0xf0,

    /* U+007D "}" */
    0xc2, 0x22, 0x23, 0x32, 0x22, 0x2e,

    /* U+007E "~" */
    0xd3,

    /* U+3001 "、" */
    0x90,

    /* U+3002 "。" */
    0x69, 0x96,

    /* U+3044 "い" */
    0x40, 0x10, 0x28, 0x6, 0x1, 0x80, 0x60, 0x24,
    0x0,

    /* U+3053 "こ" */
    0x7c, 0x82, 0x1, 0x0, 0x0, 0x0, 0x0, 0x80,
    0xc3, 0x3c,

    /* U+3057 "し" */
    0x40, 0x20, 0x20, 0x10, 0x8, 0x4, 0x6, 0x3,
    0x81, 0x61, 0x1f, 0x0,

    /* U+305D "そ" */
    0xfe, 0x10, 0xc7, 0xf1, 0xc, 0x20, 0x40, 0x80,
    0x80, 0xf0,

    /* U+3064 "つ" */
    0xfc, 0x1, 0x80, 0x60, 0x10, 0x8, 0x4, 0xc,
    0x1c,

    /* U+306B "に" */
    0xf, 0x80, 0x20, 0x10, 0x8, 0x4, 0x0, 0x80,
    0x20, 0xf, 0x80,

    /* U+3082 "も" */
    0x10, 0xff, 0x20, 0x40, 0x40, 0xfe, 0x40, 0x40,
    0x20, 0x31, 0x1e,

    /* U+3089 "ら" */
    0x1e, 0x80, 0x80, 0x90, 0xe6, 0x3, 0x1, 0x1,
    0x1, 0x2, 0xc,

    /* U+4E8B "事" */
    0x4, 0xf, 0xf8, 0xff, 0x22, 0x24, 0x44, 0x7f,
    0x1f, 0xe0, 0x22, 0xff, 0xef, 0xf8, 0x10, 0x0,

    /* U+5229 "利" */
    0x7d, 0x22, 0x24, 0x44, 0xfe, 0x91, 0x12, 0x72,
    0x55, 0xa, 0x81, 0x10, 0x22, 0x4, 0x40, 0x80,

    /* U+52DD "勝" */
    0xe4, 0xd6, 0xaa, 0xff, 0x79, 0x4b, 0xff, 0x6a,
    0xbf, 0xed, 0x92, 0xb4, 0x56, 0x8a, 0xc2, 0x0,

    /* U+6700 "最" */
    0x3f, 0x4, 0x10, 0xfa, 0x1f, 0x8f, 0xfe, 0x90,
    0x1e, 0xf2, 0x42, 0x79, 0xdf, 0x38, 0x24, 0x0,

    /* U+81EA "自" */
    0x8, 0x1f, 0x30, 0x50, 0x1f, 0xfc, 0x6, 0x3,
    0xff, 0x80, 0xc0, 0x7f, 0xe0,

    /* U+96E3 "難" */
    0x4a, 0x3f, 0xa4, 0xab, 0xef, 0xa6, 0xbf, 0xf2,
    0x29, 0xef, 0xfe, 0x94, 0xa4, 0xbc
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 115, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 96, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 6, .adv_w = 96, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 18, .adv_w = 123, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 29, .adv_w = 142, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 39, .adv_w = 137, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 49, .adv_w = 96, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 50, .adv_w = 96, .box_w = 4, .box_h = 12, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 56, .adv_w = 96, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 62, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 66, .adv_w = 94, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 70, .adv_w = 96, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 71, .adv_w = 96, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 72, .adv_w = 96, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 73, .adv_w = 58, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 78, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 91, .adv_w = 78, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 96, .adv_w = 138, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 106, .adv_w = 136, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 117, .adv_w = 150, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 130, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 139, .adv_w = 145, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 150, .adv_w = 148, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 162, .adv_w = 157, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 175, .adv_w = 155, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 188, .adv_w = 96, .box_w = 2, .box_h = 6, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 190, .adv_w = 96, .box_w = 2, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 101, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 199, .adv_w = 83, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 201, .adv_w = 101, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 208, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 219, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 235, .adv_w = 171, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 247, .adv_w = 152, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 257, .adv_w = 152, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 269, .adv_w = 157, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 279, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 289, .adv_w = 156, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 299, .adv_w = 159, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 312, .adv_w = 169, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 324, .adv_w = 104, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 331, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 343, .adv_w = 146, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 353, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 363, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 376, .adv_w = 165, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 386, .adv_w = 165, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 398, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 408, .adv_w = 167, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 421, .adv_w = 155, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 431, .adv_w = 146, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 443, .adv_w = 166, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 455, .adv_w = 157, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 467, .adv_w = 162, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 479, .adv_w = 191, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 491, .adv_w = 143, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 503, .adv_w = 155, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 515, .adv_w = 157, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 527, .adv_w = 96, .box_w = 3, .box_h = 11, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 532, .adv_w = 58, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 537, .adv_w = 96, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 542, .adv_w = 75, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 543, .adv_w = 96, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 96, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 545, .adv_w = 142, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 553, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 561, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 568, .adv_w = 130, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 577, .adv_w = 135, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 585, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 594, .adv_w = 129, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 603, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 612, .adv_w = 70, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 615, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 623, .adv_w = 122, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 632, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 640, .adv_w = 165, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 648, .adv_w = 147, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 655, .adv_w = 138, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 663, .adv_w = 136, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 671, .adv_w = 140, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 679, .adv_w = 132, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 686, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 694, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 702, .adv_w = 138, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 710, .adv_w = 132, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 717, .adv_w = 173, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 726, .adv_w = 119, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 733, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 741, .adv_w = 133, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 748, .adv_w = 96, .box_w = 4, .box_h = 12, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 754, .adv_w = 96, .box_w = 1, .box_h = 12, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 756, .adv_w = 96, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 762, .adv_w = 84, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 763, .adv_w = 192, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 764, .adv_w = 192, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 766, .adv_w = 192, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 775, .adv_w = 192, .box_w = 8, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 785, .adv_w = 192, .box_w = 9, .box_h = 10, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 797, .adv_w = 192, .box_w = 7, .box_h = 11, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 807, .adv_w = 192, .box_w = 9, .box_h = 8, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 816, .adv_w = 192, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 827, .adv_w = 192, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 838, .adv_w = 192, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 849, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 865, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 881, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 897, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 913, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 926, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2}
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
const lv_font_t hachi_maru_pop_1bit_12 = {
#else
lv_font_t hachi_maru_pop_1bit_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if HACHI_MARU_POP_1BIT_12*/

