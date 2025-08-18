//====================================================================
//
//====================================================================
#include "lvgl.h"
#include "list.h"

static int cell_count;

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
size_t get_cell_count(void) {
  return cell_count;
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
    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    const lv_image_dsc_t *img;
    if (data.type == TYPE_NODE) {
      img = (const lv_image_dsc_t*)(data.status ? &symbol_right : &symbol_down);
      rect_dsc.bg_color = CELL_COLOR_NODE;
    } else {
      img = (const lv_image_dsc_t*)(data.status ? &img_checked : &img_checkbox);
    }
    rect_dsc.bg_image_src = (const void *)img;

    lv_area_t sw_area;
    sw_area.x1 = 0;
    sw_area.x2 = img->header.w;
    sw_area.y1 = 0;
    sw_area.y2 = img->header.h;
    lv_area_t draw_task_area;
    lv_draw_task_get_area(draw_task, &draw_task_area);
    lv_area_align(&draw_task_area, &sw_area, LV_ALIGN_LEFT_MID, (data.depth + 1) * CELL_PADDING_SIZE, 0);
    lv_draw_rect(base_dsc->layer, &rect_dsc, &sw_area);
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
            data.status = !data.status;
            lv_obj_set_user_data(cell, data.user_data);
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
static void set_properties(lv_obj_t *cell, int key, int depth, int type) {
  lv_label_set_long_mode        (cell, LV_LABEL_LONG_CLIP); // LV_LABEL_LONG_DOT, LV_LABEL_LONG_SCROLL_CIRCULAR
  lv_obj_set_style_align        (cell, LV_ALIGN_LEFT_MID,  LV_PART_MAIN);
  lv_obj_set_style_text_font    (cell, &CUSTOM_FONT_SMALL, LV_PART_MAIN);
  lv_obj_set_style_height       (cell, CELL_HEIGHT_SMALL,  LV_PART_MAIN);
  lv_obj_set_style_pad_left     (cell, CELL_PADDING_SIZE * depth + (type ? CELL_OFFSET_LEAF : CELL_OFFSET_NODE), LV_PART_MAIN);
//lv_obj_set_style_pad_right    (cell, CELL_PADDING_SIZE,  LV_PART_MAIN);
  lv_obj_set_style_pad_top      (cell, CELL_PADDING_SIZE,  LV_PART_MAIN);
  lv_obj_set_style_pad_bottom   (cell, CELL_PADDING_SIZE,  LV_PART_MAIN);
  lv_obj_set_style_outline_color(cell, CELL_COLOR_OUTLINE, LV_PART_MAIN);
  lv_obj_set_style_outline_width(cell, 1, LV_PART_MAIN);
  lv_obj_set_style_bg_color     (cell, type ? CELL_COLOR_LEAF : CELL_COLOR_NODE, LV_PART_MAIN);

  CellData_t data = {
    .key    = (uint8_t)key,
    .depth  = (uint8_t)depth,
    .type   = (uint8_t)type,
    .status = false
  };

  lv_obj_set_user_data(cell, data.user_data);
  lv_obj_add_flag(cell, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_flag(cell, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);
  lv_obj_add_event_cb(cell, draw_image_cb, LV_EVENT_DRAW_TASK_ADDED, NULL);
  lv_obj_add_event_cb(cell, event_handler, LV_EVENT_CLICKED, NULL);
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
void add_list(File &dir, lv_obj_t *list, int max_depth, int depth) {
  ++depth;
  for (File entry = dir.openNextFile(); entry; entry = dir.openNextFile()) {
    if (cell_count >= MAX_CELLS) {
      entry.close();
      return;
    }

#ifdef USE_SDFAT
    char buf[BUF_SIZE];
    entry.getName(buf, sizeof(buf));
    const char *name = buf;
#else
    const char *name = entry.name();
#endif

    if (name[0] != '.' && name[0] != '@') {
      ++cell_count;
      // Serial.printf("count: %d\n", cell_count);

      if (entry.isDirectory() && depth < max_depth) {
        lv_obj_t *cell = lv_list_add_text(list, name);
        set_properties(cell, cell_count, depth, TYPE_NODE);
        add_list(entry, list, max_depth, depth);
      } else {
        lv_obj_t *cell = lv_list_add_text(list, name);
        set_properties(cell, cell_count, depth, TYPE_LEAF);
      }
    }

    entry.close();
  }
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
void add_list(Node *node, lv_obj_t *list, int depth) {
  ++depth;
  for (auto &n : node->children) {
    if (cell_count >= MAX_CELLS) {
      return;
    }

    ++cell_count;
    // Serial.printf("count: %d\n", cell_count);

    lv_obj_t *cell = lv_list_add_text(list, n->name.c_str());
    set_properties(cell, n->key, depth, n->children.size() ? TYPE_NODE : TYPE_LEAF);

    if (n->children.size()) {
      add_list(n, list, depth);
    }
  }
}