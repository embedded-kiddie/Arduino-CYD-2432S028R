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
  Node *node = (Node*)lv_obj_get_user_data(cell);

  while (cell = lv_obj_get_sibling(cell, -1)) {
    Node *n = (Node*)lv_obj_get_user_data(cell);
    if (n->meta.depth < node->meta.depth) {
      return cell;
    }
  }

  return NULL; // never reached
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
static NodeMeta_t *get_node_meta(lv_obj_t *cell) {
  Node *node = (Node*)lv_obj_get_user_data(cell);
  return &node->meta;
}

//--------------------------------------------------------------------
// https://docs.lvgl.io/master/details/widgets/table.html
//--------------------------------------------------------------------
static void draw_image_cb(lv_event_t *e) {
  // If the cells are drawn...
  lv_draw_task_t *draw_task = lv_event_get_draw_task(e);
  lv_draw_task_type_t type  = lv_draw_task_get_type(draw_task);

  if (type == LV_DRAW_TASK_TYPE_FILL) {
    lv_obj_t *cell = lv_event_get_target_obj(e);
    NodeMeta_t *meta = get_node_meta(cell);
    if (meta->depth > 1 && meta->hidden) {
      return;
    }

    // Draw icon image
    const lv_image_dsc_t *img;
    if (meta->type == TYPE_NODE) {
      img = (const lv_image_dsc_t*)(meta->checked ? &img_symbol_right : &img_symbol_down);
    } else {
      img = (const lv_image_dsc_t*)(meta->checked ? &img_checked : &img_checkbox);
    }

    lv_area_t area;
    area.x1 = 0;
    area.x2 = img->header.w - 1;
    area.y1 = 0;
    area.y2 = img->header.h - 1;
    lv_area_t draw_task_area;
    lv_draw_task_get_area(draw_task, &draw_task_area);
    lv_area_align(&draw_task_area, &area, LV_ALIGN_LEFT_MID, meta->depth * CELL_PADDING_LEFT, 0);

    lv_draw_dsc_base_t *base_dsc = (lv_draw_dsc_base_t *)lv_draw_task_get_draw_dsc(draw_task);

#if 1
    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.bg_image_src = (const void *)img;
    rect_dsc.bg_color = meta->type == TYPE_NODE ? CELL_COLOR_NODE : CELL_COLOR_LEAF;
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

  if (code == LV_EVENT_CLICKED) {
    lv_obj_t *cell = lv_event_get_target_obj(e);
    NodeMeta_t *meta = get_node_meta(cell);

    if (meta->type == TYPE_NODE) {
      uint8_t depth = meta->depth;
      bool checked  = meta->checked = !meta->checked;
      lv_obj_send_event(cell, LV_EVENT_STYLE_CHANGED, NULL);

      lv_anim_t a;
      lv_anim_init(&a);
      lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_height);
      lv_anim_set_duration(&a, FOLDING_DURATION);

      if (checked) {
        lv_anim_set_values(&a, CELL_HEIGHT_SMALL, 0);
      } else {
        lv_anim_set_values(&a, 0, CELL_HEIGHT_SMALL);
      }

      // folding with animation
      while (cell = lv_obj_get_sibling(cell, 1)) {
        meta = get_node_meta(cell);
        if (meta->depth <= depth) {
          break;
        }

        // child inherits the state of parent
        lv_obj_t *obj = get_parent(cell);
        NodeMeta_t *m = get_node_meta(obj);

        // child follows the state of parent
        bool hidden = checked | m->checked;
        if (meta->hidden == hidden) {
          continue;
        } else {
          meta->hidden = hidden;
        }

        lv_obj_send_event(cell, LV_EVENT_STYLE_CHANGED, NULL);
        lv_anim_set_var(&a, cell);
        lv_anim_start(&a);
      }
    }

    // change the state of checkbox
    else {
      meta->checked = !meta->checked;
      lv_obj_send_event(cell, LV_EVENT_STYLE_CHANGED, NULL);
    }
  }
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
static void set_styles(lv_obj_t *cell, Node *node) {
  static constexpr lv_style_const_prop_t style_prop_common[] = {
    LV_STYLE_CONST_ALIGN(LV_ALIGN_LEFT_MID),
    LV_STYLE_CONST_TEXT_FONT(&CUSTOM_FONT_SMALL),
//  LV_STYLE_CONST_HEIGHT(CELL_HEIGHT_SMALL),
    LV_STYLE_CONST_PAD_TOP(CELL_PADDING_BORDER),
    LV_STYLE_CONST_PAD_BOTTOM(CELL_PADDING_BORDER),
    LV_STYLE_CONST_OUTLINE_COLOR(CELL_COLOR_OUTLINE),
    LV_STYLE_CONST_OUTLINE_WIDTH(1),
    LV_STYLE_CONST_PROPS_END
  };
  static LV_STYLE_CONST_INIT(style_common, (void*)style_prop_common);
  lv_obj_add_style(cell, &style_common, (uint32_t)LV_PART_MAIN);

  NodeMeta_t *meta = &node->meta;
  lv_obj_set_style_height   (cell, (meta->depth > 1 && meta->hidden ? 0 : CELL_HEIGHT_SMALL), LV_PART_MAIN);
  lv_obj_set_style_bg_color (cell, (meta->type == TYPE_NODE ? CELL_COLOR_NODE : CELL_COLOR_LEAF), LV_PART_MAIN);
  lv_obj_set_style_pad_left (cell, (meta->depth * CELL_PADDING_LEFT + (meta->type == TYPE_NODE ? CELL_OFFSET_NODE: CELL_OFFSET_LEAF)), LV_PART_MAIN);
  lv_label_set_long_mode    (cell, LV_LABEL_LONG_CLIP); // LV_LABEL_LONG_DOT, LV_LABEL_LONG_SCROLL_CIRCULAR

  lv_obj_set_user_data(cell, (void*)node);
  lv_obj_add_flag(cell, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_flag(cell, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);
  lv_obj_add_event_cb(cell, draw_image_cb, LV_EVENT_DRAW_TASK_ADDED, NULL);
  lv_obj_add_event_cb(cell, event_handler, LV_EVENT_CLICKED, NULL);
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
void add_node_to_list(Node *node, lv_obj_t *list) {
  for (auto &n : node->children) {
    if (cell_count++ >= MAX_CELLS) {
      // printf("count: %d\n", cell_count);
      return;
    }

    lv_obj_t * cell = lv_list_add_text(list, n->name.c_str());
    set_styles(cell, n);

    if (n->children.size()) {
      add_node_to_list(n, list);
    }
  }
}