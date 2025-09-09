//====================================================================
//
//====================================================================
#include <lvgl.h>
#include "list.h"

static int cell_count;

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
size_t get_cell_count(void) {
  return cell_count;
}

void reset_cell_count(void) {
  cell_count = 0;
}

 //--------------------------------------------------------------------
//
//--------------------------------------------------------------------
static lv_obj_t *get_parent(lv_obj_t *cell) {
  CellData_t data;
  data.user_data = lv_obj_get_user_data(cell);

  while (cell = lv_obj_get_sibling(cell, -1)) {
    CellData_t d;
    d.user_data = lv_obj_get_user_data(cell);
    if (d.depth < data.depth) {
      return cell;
    }
  }

  return NULL;
}

//--------------------------------------------------------------------
// https://docs.lvgl.io/master/details/widgets/table.html
//--------------------------------------------------------------------
static void draw_image_cb(lv_event_t *e) {
  lv_draw_task_t *draw_task = lv_event_get_draw_task(e);
  lv_draw_dsc_base_t *base_dsc = (lv_draw_dsc_base_t *)lv_draw_task_get_draw_dsc(draw_task);

  // If the cells are drawn...
  lv_draw_task_type_t type = lv_draw_task_get_type(draw_task);
  // Serial.printf("task type: %d\n", type);

  if (type == LV_DRAW_TASK_TYPE_FILL) {
    CellData_t data;
    lv_obj_t *cell = lv_event_get_target_obj(e);
    data.user_data = lv_obj_get_user_data(cell);

    // Do not draw if parent cell is folded
    lv_obj_t *obj = cell;
    while (obj = get_parent(obj)) {
      CellData_t d;
      d.user_data = lv_obj_get_user_data(obj);
      if (d.type == TYPE_NODE && d.status) {
        return;
      }
    }

    // Draw icon image
    const lv_image_dsc_t *img;
    if (data.type == TYPE_NODE) {
      img = (const lv_image_dsc_t*)(data.status ? &img_symbol_right : &img_symbol_down);
    } else {
      img = (const lv_image_dsc_t*)(data.status ? &img_checked : &img_checkbox);
    }

    lv_area_t area;
    area.x1 = 0;
    area.x2 = img->header.w - 1;
    area.y1 = 0;
    area.y2 = img->header.h - 1;
    lv_area_t draw_task_area;
    lv_draw_task_get_area(draw_task, &draw_task_area);
    lv_area_align(&draw_task_area, &area, LV_ALIGN_LEFT_MID, (data.depth + 1) * CELL_PADDING_LEFT, 0);

#if 1
    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.bg_image_src = (const void *)img;
    rect_dsc.bg_color = data.type ? CELL_COLOR_LEAF : CELL_COLOR_NODE;
    lv_draw_rect(base_dsc->layer, &rect_dsc, &area);
#else
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    img_dsc.src = (const void *)img;
    img_dsc.recolor = lv_color_black();
    lv_draw_image(base_dsc->layer, &img_dsc, &area);
#endif
  }
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *cell = lv_event_get_target_obj(e);  // lv_event_stop_bubbling(e)
  lv_obj_t *list = lv_obj_get_parent(cell);

  if (code == LV_EVENT_CLICKED) {
    CellData_t data;
    data.user_data = lv_obj_get_user_data(cell);

    if (data.type == TYPE_NODE) {
      uint8_t depth = data.depth + 1;
      bool folding = !data.status;
      bool parent = data.status = folding;
      lv_obj_set_user_data(cell, data.user_data);
      lv_obj_send_event(cell, LV_EVENT_STYLE_CHANGED, NULL);

      lv_anim_t a;
      lv_anim_init(&a);
      lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_height);
      lv_anim_set_duration(&a, FOLDING_DURATION);

      if (folding) {
        lv_anim_set_values(&a, CELL_HEIGHT_SMALL, 0);
      } else {
        lv_anim_set_values(&a, 0, CELL_HEIGHT_SMALL);
      }

      // folding with animation
      while (cell = lv_obj_get_sibling(cell, 1)) {
        data.user_data = lv_obj_get_user_data(cell);
        if (data.depth < depth) {
          break;
        }

        if (data.type == TYPE_NODE) {
          parent = data.status = !data.status;
          lv_obj_set_user_data(cell, data.user_data);
          lv_obj_send_event(cell, LV_EVENT_STYLE_CHANGED, NULL);
        } else {
          if (parent != folding) {
            continue;
          } else {
            lv_obj_send_event(cell, LV_EVENT_STYLE_CHANGED, NULL);
          }
        }

        lv_anim_set_var(&a, cell);
        lv_anim_start(&a);
      }
    }

    // selected
    else {
      data.status = !data.status;
      lv_obj_set_user_data(cell, data.user_data);
      lv_obj_send_event(cell, LV_EVENT_STYLE_CHANGED, NULL);
    }
  }
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
static void set_styles(lv_obj_t *cell, Node *node, int depth, int type) {
  static constexpr lv_style_const_prop_t style_prop_common[] = {
    LV_STYLE_CONST_ALIGN(LV_ALIGN_LEFT_MID),
    LV_STYLE_CONST_TEXT_FONT(&CUSTOM_FONT_SMALL),
    LV_STYLE_CONST_HEIGHT(CELL_HEIGHT_SMALL),
    LV_STYLE_CONST_PAD_TOP(CELL_PADDING_BORDER),
    LV_STYLE_CONST_PAD_BOTTOM(CELL_PADDING_BORDER),
    LV_STYLE_CONST_OUTLINE_COLOR(CELL_COLOR_OUTLINE),
    LV_STYLE_CONST_OUTLINE_WIDTH(1),
    LV_STYLE_CONST_PROPS_END
  };
  static LV_STYLE_CONST_INIT(style_common, (void*)style_prop_common);
  lv_obj_add_style(cell, &style_common, (uint32_t)LV_PART_MAIN);
  lv_obj_set_style_bg_color(cell, type ? CELL_COLOR_LEAF : CELL_COLOR_NODE, LV_PART_MAIN);
  lv_obj_set_style_pad_left(cell, CELL_PADDING_LEFT * depth + (type ? CELL_OFFSET_LEAF : CELL_OFFSET_NODE), LV_PART_MAIN);
  lv_label_set_long_mode(cell, LV_LABEL_LONG_CLIP); // LV_LABEL_LONG_DOT, LV_LABEL_LONG_SCROLL_CIRCULAR

#if ESP_ARDUINO_VERSION_MAJOR >= 3
  CellData_t data = {
    .key    = (uint8_t)node->key,
    .depth  = (uint8_t)depth,
    .type   = (uint8_t)type,
    .status = type == TYPE_NODE ? false : (bool)node->selected
  };
#else
  CellData_t data;
  data.key    = (uint8_t)node->key;
  data.depth  = (uint8_t)depth;
  data.type   = (uint8_t)type;
  data.status = type == TYPE_NODE ? false : (bool)node->selected;
#endif

  lv_obj_set_user_data(cell, data.user_data);
  lv_obj_add_flag(cell, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_flag(cell, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);
  lv_obj_add_event_cb(cell, draw_image_cb, LV_EVENT_DRAW_TASK_ADDED, NULL);
  lv_obj_add_event_cb(cell, event_handler, LV_EVENT_CLICKED, NULL);
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
void add_list(Node *node, lv_obj_t *list, int depth) {
  ++depth;
  for (auto &n : node->children) {
    if (cell_count >= MAX_CELLS) {
      // printf("count: %d\n", cell_count);
      return;
    }

    ++cell_count;
    // printf("count: %d\n", cell_count);

    lv_obj_t * cell = lv_list_add_text(list, n->name.c_str());
    set_styles(cell, n, depth, n->children.size() ? TYPE_NODE : TYPE_LEAF);

    if (n->children.size()) {
      add_list(n, list, depth);
    }
  }
}

/*--------------------------------------------------------------------------------
 * Create a subtree from selected node in playlist
 *--------------------------------------------------------------------------------*/
void make_subtree(Node *root_node, lv_obj_t *list) {
  uint32_t n = lv_obj_get_child_count(list);
  for(uint32_t i = 0; i < n; i++) {
    lv_obj_t * child = lv_obj_get_child(list, i);
    CellData_t data;
    data.user_data = lv_obj_get_user_data(child);
    if (data.type == TYPE_LEAF) {
      Serial.println(lv_label_get_text(child));
    }
  }
}