//====================================================================
//
//====================================================================
#ifndef _LIST_H_
#define _LIST_H_

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include "tree.hpp"

// Custom font
#define CUSTOM_FONT_SMALL   noto_sans_jp_4bit_jis1_12
#define CUSTOM_FONT_MEDIUM  noto_sans_jp_4bit_jis1_14
LV_FONT_DECLARE(CUSTOM_FONT_SMALL);
LV_FONT_DECLARE(CUSTOM_FONT_MEDIUM);

// List Components
#define CELL_COLOR_NODE     lv_color_hex(0xf4f4f4)
#define CELL_COLOR_LEAF     lv_color_hex(0xffffff)
#define CELL_COLOR_OUTLINE  { .blue = 0xe4, .green = 0xe0, .red = 0xe4 }  // lv_color_hex(0xe4e0e4)
#define CELL_HEIGHT_SMALL   31  // for CUSTOM_FONT_SMALL
#define CELL_HEIGHT_MEDIUM  34  // for CUSTOM_FONT_MEDIUM
#define CELL_OFFSET_NODE    6   // offset for node text
#define CELL_OFFSET_LEAF    10  // offset for leaf text
#define CELL_PADDING_LEFT   6   // padding left in pixels
#define CELL_PADDING_BORDER 8   // padding top/bottom in pixels
#define FOLDING_DURATION    250 // folding animation duration

// Icon images
LV_IMAGE_DECLARE(img_checkbox);         // assets/icons/img_checkbox.png
LV_IMAGE_DECLARE(img_checked);          // assets/icons/img_checked.png
LV_IMAGE_DECLARE(img_symbol_down);      // assets/icons/img_symbol_down.png
LV_IMAGE_DECLARE(img_symbol_right);     // assets/icons/img_symbol_right.png

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
#define MAX_CELLS   100 // LV_MEM_SIZE = (64 * 1024U)

size_t get_cell_count(void);
void reset_cell_count(void);
void add_node_to_list(Node *node, lv_obj_t *list);

#endif  // _LIST_H_