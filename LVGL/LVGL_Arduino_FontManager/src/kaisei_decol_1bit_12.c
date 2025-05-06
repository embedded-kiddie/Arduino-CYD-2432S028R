/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --no-compress --font KaiseiDecol-Regular.ttf --symbols 自らに勝つ事こそ、最も難しい勝利。 --range 32-127 --format lvgl -o kaisei_decol_1bit_12.c
 ******************************************************************************/
/*
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
*/
#include "../ui.h"

#ifndef KAISEI_DECOL_1BIT_12
#define KAISEI_DECOL_1BIT_12 1
#endif

#if KAISEI_DECOL_1BIT_12

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
    0x24, 0x48, 0x93, 0xf2, 0x45, 0x3f, 0xa4, 0x48,
    0x90,

    /* U+0024 "$" */
    0x10, 0x79, 0x52, 0x97, 0x7, 0x7, 0x9, 0x93,
    0x25, 0xf0, 0x80,

    /* U+0025 "%" */
    0x60, 0x48, 0xa4, 0x92, 0x89, 0x80, 0x50, 0x52,
    0x49, 0x44, 0xa1, 0x80,

    /* U+0026 "&" */
    0x38, 0x24, 0x12, 0xa, 0x6, 0x75, 0x12, 0xc9,
    0x34, 0x8c, 0x3d, 0xc0,

    /* U+0027 "'" */
    0xf0,

    /* U+0028 "(" */
    0x29, 0x49, 0x24, 0x91, 0x10,

    /* U+0029 ")" */
    0x89, 0x12, 0x49, 0x29, 0x40,

    /* U+002A "*" */
    0x4d, 0x6f, 0x40,

    /* U+002B "+" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x0,

    /* U+002C "," */
    0xf0,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x11, 0x22, 0x24, 0x48, 0x88, 0x0,

    /* U+0030 "0" */
    0x39, 0x28, 0x61, 0x86, 0x18, 0x61, 0x89, 0xc0,

    /* U+0031 "1" */
    0xe, 0x22, 0x22, 0x22, 0x22,

    /* U+0032 "2" */
    0x74, 0x62, 0x11, 0x19, 0x10, 0x8f, 0xc0,

    /* U+0033 "3" */
    0x39, 0x14, 0x42, 0x38, 0x10, 0x41, 0xc5, 0xe0,

    /* U+0034 "4" */
    0x8, 0x30, 0x61, 0x44, 0x89, 0x22, 0x7e, 0x8,
    0x10,

    /* U+0035 "5" */
    0x7d, 0x4, 0x10, 0x59, 0x90, 0x41, 0x45, 0xe0,

    /* U+0036 "6" */
    0x8, 0xc4, 0x10, 0xb3, 0x38, 0x61, 0x85, 0xe0,

    /* U+0037 "7" */
    0xfe, 0x20, 0x84, 0x10, 0x41, 0x8, 0x20, 0x80,

    /* U+0038 "8" */
    0x7a, 0x18, 0x72, 0x32, 0x28, 0x61, 0x85, 0xe0,

    /* U+0039 "9" */
    0x7a, 0x18, 0x61, 0x85, 0xf0, 0x82, 0x11, 0x80,

    /* U+003A ":" */
    0xcc,

    /* U+003B ";" */
    0xcf,

    /* U+003C "<" */
    0x0, 0xc, 0x63, 0x8, 0xc, 0x6, 0x3,

    /* U+003D "=" */
    0xfe, 0x3, 0xf8,

    /* U+003E ">" */
    0x1, 0x80, 0xc0, 0x60, 0x21, 0x8c, 0x60,

    /* U+003F "?" */
    0x72, 0x72, 0x31, 0x10, 0x80, 0x31, 0x80,

    /* U+0040 "@" */
    0x1e, 0x30, 0x90, 0x31, 0xd9, 0x2c, 0xa6, 0x53,
    0x2a, 0x4a, 0x20, 0x8f, 0x80,

    /* U+0041 "A" */
    0x8, 0x4, 0x5, 0x2, 0x82, 0x41, 0x30, 0xf8,
    0x86, 0x43, 0x20, 0x80,

    /* U+0042 "B" */
    0x7c, 0x85, 0xa, 0x27, 0xc8, 0x50, 0xa1, 0x42,
    0xf8,

    /* U+0043 "C" */
    0x3c, 0x86, 0xc, 0x8, 0x10, 0x20, 0x41, 0x42,
    0x78,

    /* U+0044 "D" */
    0x7e, 0x20, 0x90, 0x28, 0x14, 0xa, 0x5, 0x2,
    0x82, 0x41, 0x3f, 0x0,

    /* U+0045 "E" */
    0xfe, 0x85, 0x2, 0x4, 0xf, 0x90, 0x20, 0x42,
    0xfc,

    /* U+0046 "F" */
    0xfd, 0x14, 0x10, 0x41, 0xf4, 0x10, 0x43, 0x80,

    /* U+0047 "G" */
    0x3e, 0x42, 0x80, 0x80, 0x80, 0x80, 0x87, 0x82,
    0x42, 0x3c,

    /* U+0048 "H" */
    0x41, 0x20, 0x90, 0x48, 0x24, 0x13, 0xf9, 0x4,
    0x82, 0x41, 0x20, 0x80,

    /* U+0049 "I" */
    0x49, 0x24, 0x92, 0x48,

    /* U+004A "J" */
    0x8, 0x20, 0x82, 0x8, 0x20, 0x82, 0x8, 0x24,
    0x9c,

    /* U+004B "K" */
    0x42, 0x44, 0x48, 0x50, 0x70, 0x50, 0x58, 0x4c,
    0x44, 0x46,

    /* U+004C "L" */
    0x40, 0x81, 0x2, 0x4, 0x8, 0x10, 0x21, 0x42,
    0xfc,

    /* U+004D "M" */
    0x60, 0x98, 0x65, 0x29, 0x4a, 0x52, 0x97, 0x24,
    0xc9, 0x32, 0x4c, 0x90, 0x20,

    /* U+004E "N" */
    0x61, 0x30, 0x94, 0x4b, 0x24, 0x92, 0x69, 0x1c,
    0x86, 0x43, 0x20, 0x80,

    /* U+004F "O" */
    0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x42, 0x3c,

    /* U+0050 "P" */
    0x7c, 0x85, 0xa, 0x14, 0x4f, 0x10, 0x20, 0x40,
    0x80,

    /* U+0051 "Q" */
    0x3c, 0x21, 0x30, 0x50, 0x28, 0x14, 0xa, 0x5,
    0x62, 0x4a, 0x16, 0x5, 0x0, 0x60,

    /* U+0052 "R" */
    0x7c, 0x42, 0x42, 0x42, 0x7c, 0x48, 0x4c, 0x44,
    0x46, 0x43,

    /* U+0053 "S" */
    0x7a, 0x28, 0x30, 0x70, 0x60, 0x61, 0x85, 0xe0,

    /* U+0054 "T" */
    0xfe, 0x91, 0x11, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10,

    /* U+0055 "U" */
    0x41, 0x20, 0x90, 0x48, 0x24, 0x12, 0x9, 0x4,
    0x82, 0x43, 0x1f, 0x0,

    /* U+0056 "V" */
    0x61, 0x30, 0x88, 0x84, 0x43, 0x20, 0xa0, 0x50,
    0x38, 0xc, 0x4, 0x0,

    /* U+0057 "W" */
    0x62, 0x26, 0x22, 0x66, 0x42, 0x64, 0x2b, 0x42,
    0x94, 0x29, 0x43, 0x9c, 0x10, 0x81, 0x8,

    /* U+0058 "X" */
    0x61, 0x11, 0x5, 0x3, 0x80, 0x80, 0x60, 0x50,
    0x4c, 0x22, 0x31, 0x80,

    /* U+0059 "Y" */
    0x61, 0x11, 0xc, 0x82, 0x81, 0x40, 0x40, 0x20,
    0x10, 0x8, 0x4, 0x0,

    /* U+005A "Z" */
    0xff, 0x18, 0x20, 0xc1, 0x4, 0x18, 0x21, 0xc3,
    0xfc,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x4e,

    /* U+005C "\\" */
    0x81, 0x4, 0x10, 0x20, 0x81, 0x4, 0x8, 0x20,
    0x80,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x9e,

    /* U+005E "^" */
    0x23, 0x25, 0x10,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0xe0,

    /* U+0061 "a" */
    0x71, 0x20, 0x9e, 0x8a, 0x2f, 0xc0,

    /* U+0062 "b" */
    0xc1, 0x4, 0x1e, 0x45, 0x14, 0x51, 0x49, 0xe0,

    /* U+0063 "c" */
    0x7c, 0x61, 0x8, 0x45, 0xc0,

    /* U+0064 "d" */
    0x18, 0x20, 0x9e, 0x8a, 0x28, 0xa2, 0x89, 0xf0,

    /* U+0065 "e" */
    0x72, 0x2f, 0xa0, 0x82, 0x27, 0x0,

    /* U+0066 "f" */
    0x74, 0x4f, 0x44, 0x44, 0x44,

    /* U+0067 "g" */
    0x1, 0xe8, 0xa2, 0x89, 0xc8, 0x3f, 0x87, 0xe0,

    /* U+0068 "h" */
    0xc0, 0x81, 0x2, 0xe6, 0x48, 0x91, 0x22, 0x44,
    0x88,

    /* U+0069 "i" */
    0x48, 0x64, 0x92, 0x48,

    /* U+006A "j" */
    0x11, 0x1, 0x11, 0x11, 0x11, 0x1e,

    /* U+006B "k" */
    0xc0, 0x81, 0x2, 0x25, 0x8a, 0x1c, 0x24, 0x48,
    0x88,

    /* U+006C "l" */
    0x49, 0x24, 0x92, 0x48,

    /* U+006D "m" */
    0xd9, 0xcc, 0xc9, 0x11, 0x22, 0x24, 0x44, 0x88,
    0x91, 0x10,

    /* U+006E "n" */
    0xdc, 0xc9, 0x12, 0x24, 0x48, 0x91, 0x0,

    /* U+006F "o" */
    0x7a, 0x18, 0x61, 0x86, 0x27, 0x80,

    /* U+0070 "p" */
    0xf9, 0x14, 0x51, 0x45, 0x16, 0x94, 0x40,

    /* U+0071 "q" */
    0x7d, 0xa, 0x14, 0x28, 0x50, 0x9f, 0x2, 0x4,

    /* U+0072 "r" */
    0xdb, 0x50, 0x84, 0x21, 0x0,

    /* U+0073 "s" */
    0x3a, 0x50, 0x60, 0x85, 0xc0,

    /* U+0074 "t" */
    0x44, 0xf4, 0x44, 0x44, 0x70,

    /* U+0075 "u" */
    0x44, 0x89, 0x12, 0x24, 0x48, 0x8f, 0x80,

    /* U+0076 "v" */
    0xc4, 0x88, 0x91, 0x42, 0x83, 0x4, 0x0,

    /* U+0077 "w" */
    0x44, 0x91, 0x24, 0xc8, 0xd2, 0x33, 0xc, 0xc3,
    0x30,

    /* U+0078 "x" */
    0x44, 0x50, 0xc0, 0x82, 0x89, 0x11, 0x0,

    /* U+0079 "y" */
    0x62, 0x24, 0x24, 0x14, 0x18, 0x18, 0x10, 0x10,
    0x60,

    /* U+007A "z" */
    0xf8, 0x8c, 0x44, 0x67, 0xe0,

    /* U+007B "{" */
    0x29, 0x25, 0x22, 0x49, 0x20,

    /* U+007C "|" */
    0xff, 0xf0,

    /* U+007D "}" */
    0x89, 0x24, 0x9a, 0x49, 0x40,

    /* U+007E "~" */
    0x70, 0x99, 0x6,

    /* U+3001 "、" */
    0x89, 0x0,

    /* U+3002 "。" */
    0x69, 0x96,

    /* U+3044 "い" */
    0x80, 0x86, 0x81, 0x81, 0x89, 0x90, 0x60,

    /* U+3053 "こ" */
    0x7e, 0x4, 0x0, 0x0, 0x0, 0x80, 0xc1, 0x3e,

    /* U+3057 "し" */
    0x81, 0x2, 0x4, 0x8, 0x10, 0x60, 0xc2, 0x78,

    /* U+305D "そ" */
    0x64, 0x8, 0x10, 0x2f, 0xd4, 0x8, 0x10, 0x10,
    0xe,

    /* U+3064 "つ" */
    0x1f, 0x30, 0xc0, 0x20, 0x10, 0x10, 0x10, 0x70,

    /* U+306B "に" */
    0x80, 0x47, 0xa0, 0x90, 0x8, 0x4, 0x46, 0x37,
    0x84,

    /* U+3082 "も" */
    0x10, 0x50, 0x10, 0x1a, 0xb1, 0x61, 0x21, 0x23,
    0x1e,

    /* U+3089 "ら" */
    0x41, 0xc0, 0x20, 0xbb, 0x10, 0x41, 0xb, 0xc0,

    /* U+4E8B "事" */
    0x8, 0x3f, 0xf7, 0xf1, 0x24, 0x3e, 0x3f, 0xc0,
    0x95, 0xfe, 0xff, 0x2, 0x3, 0x80,

    /* U+5229 "利" */
    0x1c, 0x4c, 0x51, 0x54, 0xe5, 0x39, 0x56, 0x55,
    0x54, 0x41, 0x10, 0x44, 0x30,

    /* U+52DD "勝" */
    0x75, 0x45, 0x12, 0x52, 0xc5, 0xff, 0x54, 0x45,
    0x94, 0x57, 0xf5, 0x14, 0x92, 0x4b, 0x48,

    /* U+6700 "最" */
    0x3f, 0x87, 0xd0, 0x4, 0xff, 0xf5, 0x80, 0xd7,
    0x9e, 0xa2, 0x4c, 0xf9, 0x81, 0xcc,

    /* U+81EA "自" */
    0x18, 0x10, 0xff, 0x81, 0x85, 0xfd, 0x85, 0xfd,
    0x81, 0x83, 0xfe,

    /* U+96E3 "難" */
    0x2d, 0x2, 0xb4, 0x75, 0x47, 0xde, 0x57, 0x43,
    0x9e, 0x7d, 0x4f, 0xde, 0x21, 0x42, 0x94, 0x47,
    0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 48, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 77, .box_w = 1, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 75, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 5, .adv_w = 150, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 25, .adv_w = 170, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 146, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 54, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 50, .adv_w = 86, .box_w = 3, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 55, .adv_w = 86, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 60, .adv_w = 86, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 63, .adv_w = 144, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 70, .adv_w = 67, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 71, .adv_w = 77, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 72, .adv_w = 67, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 96, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 79, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 113, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 113, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 113, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 75, .box_w = 1, .box_h = 6, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 75, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 158, .adv_w = 150, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 165, .adv_w = 144, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 168, .adv_w = 150, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 175, .adv_w = 108, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 173, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 195, .adv_w = 149, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 133, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 158, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 129, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 161, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 79, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 88, .box_w = 6, .box_h = 12, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 289, .adv_w = 139, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 129, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 182, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 150, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 157, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 157, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 366, .adv_w = 136, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 132, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 145, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 145, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 192, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 147, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 445, .adv_w = 133, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 86, .box_w = 3, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 471, .adv_w = 96, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 480, .adv_w = 86, .box_w = 3, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 485, .adv_w = 108, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 488, .adv_w = 96, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 489, .adv_w = 75, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 490, .adv_w = 104, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 104, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 105, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 75, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 106, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 536, .adv_w = 122, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 66, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 549, .adv_w = 73, .box_w = 4, .box_h = 12, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 555, .adv_w = 114, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 66, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 177, .box_w = 11, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 578, .adv_w = 121, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 119, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 591, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 598, .adv_w = 117, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 606, .adv_w = 85, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 86, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 71, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 121, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 110, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 164, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 644, .adv_w = 110, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 114, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 660, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 665, .adv_w = 86, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 670, .adv_w = 48, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 672, .adv_w = 86, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 677, .adv_w = 134, .box_w = 8, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 680, .adv_w = 192, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 682, .adv_w = 192, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 684, .adv_w = 192, .box_w = 8, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 691, .adv_w = 192, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 699, .adv_w = 192, .box_w = 7, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 192, .box_w = 8, .box_h = 9, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 716, .adv_w = 192, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 724, .adv_w = 192, .box_w = 9, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 733, .adv_w = 192, .box_w = 8, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 742, .adv_w = 192, .box_w = 6, .box_h = 10, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 750, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 764, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 777, .adv_w = 192, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 792, .adv_w = 192, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 806, .adv_w = 192, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 817, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1}
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
const lv_font_t kaisei_decol_1bit_12 = {
#else
lv_font_t kaisei_decol_1bit_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
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



#endif /*#if KAISEI_DECOL_1BIT_12*/

