//================================================================================
// MP3 Music Player for CYD - Album List Screen
// LVGL version: 9.x
//================================================================================
#include "ui.h"
#include "../tree.hpp"

//--------------------------------------------------------------------------------
// Instance of the screen widget
//--------------------------------------------------------------------------------
lv_obj_t *ui_ScreenAlbumList;

// Components in list widget
#define CELL_COLOR_NODE     lv_color_hex(0xf4f4f4)
#define CELL_COLOR_LEAF     lv_color_hex(0xffffff)
#define CELL_COLOR_OUTLINE  { .blue = 0xe4, .green = 0xe0, .red = 0xe4 }  // lv_color_hex(0xe4e0e4)
#define CELL_HEIGHT_SMALL   31  // for CUSTOM_FONT_SMALL
#define CELL_HEIGHT_MEDIUM  34  // for CUSTOM_FONT_MEDIUM
#define CELL_OFFSET_NODE    6   // offset for node text
#define CELL_OFFSET_LEAF    10  // offset for leaf text
#define CELL_PADDING_LEFT   6   // padding left in pixels
#define CELL_PADDING_BORDER 8   // padding top/bottom in pixels
#define CELL_MAX_VISIBLE    7   // number of cells visible in the list
#define ALBUM_LIST_HEIGHT   220 // height of the album list (CELL_HEIGHT_SMALL * CELL_MAX_VISIBLE + alpha)
#define FOLDING_DURATION    250 // folding animation duration

// Settings for controlling cells in the list
#define NODE_OPEN   false
#define NODE_CLOSE  true

typedef struct {
  int   top;      // node key at the top of the list
  int   end;      // node key at the end of the list
  int   count;    // number of the cells in the list
  int   n_nodes;  // total number of the nodes in tree
  Node  *root;
} ListControl_t;

//--------------------------------------------------------------------------------
// Global variables and prototype
//--------------------------------------------------------------------------------
static lv_obj_t *album_list;
static ListControl_t list_control;
static bool update_scroll_running = false;

static void event_handler(lv_event_t *e);
static void draw_image_cb(lv_event_t *e);

//--------------------------------------------------------------------------------
// Setup cell styles and properties
//--------------------------------------------------------------------------------
static void set_properties(lv_obj_t *cell, Node *node) {
  static constexpr lv_style_const_prop_t style_prop_common[] = {
    LV_STYLE_CONST_ALIGN(LV_ALIGN_LEFT_MID),
    LV_STYLE_CONST_TEXT_FONT(&CUSTOM_FONT_SMALL),
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
  lv_obj_add_flag           (cell, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_flag           (cell, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);
  lv_obj_add_event_cb       (cell, draw_image_cb, LV_EVENT_DRAW_TASK_ADDED, NULL);
  lv_obj_add_event_cb       (cell, event_handler, LV_EVENT_CLICKED, NULL);
  lv_obj_set_user_data      (cell, (void*)node);
}

//--------------------------------------------------------------------------------
// Get the node pointer from the cell's userdata
//--------------------------------------------------------------------------------
inline static Node *get_node(lv_obj_t *cell) {
  return (Node*)lv_obj_get_user_data(cell);
}

//--------------------------------------------------------------------------------
// Update cells' position in the list
//--------------------------------------------------------------------------------
inline static void update_list(lv_obj_t *list) {
  lv_obj_update_layout(list);
  list_control.top = get_node(lv_obj_get_child(list,  0))->key;
  list_control.end = get_node(lv_obj_get_child(list, -1))->key;
  list_control.count = lv_obj_get_child_count(list);
}

//--------------------------------------------------------------------------------
// Append / Delete the specified node to the list
//--------------------------------------------------------------------------------
inline static lv_obj_t *append_cell(lv_obj_t *list, Node *node) {
//printf("count:%3d added   %3d \"%s\"\n", list_control.count, node->key, node->name.c_str());
  lv_obj_t * cell = lv_list_add_text(list, node->name.c_str());
  set_properties(cell, node);
  return cell;
}

inline static void delete_cell(lv_obj_t *list, lv_obj_t *cell) {
//Node *node = get_node(cell);
//printf("count:%3d deleted %3d \"%s\"\n", list_control.count, node->key, node->name.c_str());
  lv_obj_delete(cell);
}

static void delete_cell_async(void *cell) {
  lv_obj_t *list = lv_obj_get_parent((lv_obj_t *)cell);
  delete_cell(list, (lv_obj_t *)cell);
  update_list(list);
}

//--------------------------------------------------------------------------------
// A function to reduce the impact of a bug related to LVGL lv_list animation
// Note: This bug occurs if a blank space is created at the bottom of the list 
// after deleting a cell.
//--------------------------------------------------------------------------------
inline static void adjust_bottom(lv_obj_t *list) {
//printf("bottom: %d --> ", lv_obj_get_scroll_bottom(list));

  // If the bottom position is negative, reposition it to a positive
  if (lv_obj_get_scroll_bottom(list) <= 0) {
    lv_obj_scroll_to_y(list, CELL_HEIGHT_SMALL, LV_ANIM_OFF); // 1. Move to positive position
    lv_obj_scroll_to_y(list, 0, LV_ANIM_OFF);                 // 2. Snap to the bottom position
  }

  // Update cells' position in the list
  update_list(list);

//printf("%d\n", lv_obj_get_scroll_bottom(list));
}

//--------------------------------------------------------------------------------
// Get the open node after/before the specified key
//--------------------------------------------------------------------------------
static Node *find_after(int key) {
  while (++key < list_control.n_nodes) {
    Node *node = list_control.root->find_preorder(key);
    if (node && (node->meta.depth == 1 || node->meta.hidden == false)) {
      return node;
    }
  }
  return NULL;
}

static Node *find_before(int key) {
  while (--key >= 0) {
    Node *node = list_control.root->find_preorder(key);
    if (node && (node->meta.depth == 1 || node->meta.hidden == false)) {
      return node;
    }
  }
  return NULL;
}

//--------------------------------------------------------------------------------
// Draw a graphic icon for the cell
// Reference: https://docs.lvgl.io/master/details/widgets/table.html
//--------------------------------------------------------------------------------
static void draw_image_cb(lv_event_t *e) {
  lv_draw_task_t *draw_task = lv_event_get_draw_task(e);
  lv_draw_task_type_t type  = lv_draw_task_get_type(draw_task);

  if (type == LV_DRAW_TASK_TYPE_FILL) {
    lv_obj_t *cell = lv_event_get_target_obj(e);
    NodeMeta_t *meta = &(get_node(cell)->meta);
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

//--------------------------------------------------------------------------------
// Callbacks when a cell is opened or closed
//--------------------------------------------------------------------------------
static void update_open_cb(lv_anim_t* a) {
  lv_obj_t *list = (lv_obj_t*)lv_anim_get_user_data(a);

  // Scroll to make it visible
  lv_obj_scroll_to_view((lv_obj_t *)a->var, LV_ANIM_ON);

  // Delete the last cell
  delete_cell(list, lv_obj_get_child(list, -1));
  update_list(list); // Not required at the end of animation ?
}

static void update_close_cb(lv_anim_t* a) {
  lv_obj_t *list = (lv_obj_t*)lv_anim_get_user_data(a);

  // Avoid LVGL bug (?)
  adjust_bottom(list);
  lv_async_call(delete_cell_async, a->var);
}

//--------------------------------------------------------------------------------
// Processing when opening and closing the cell
//--------------------------------------------------------------------------------
static void update_open(lv_obj_t *list, Node *node, uint32_t index, lv_anim_t *a) {
  Node *prev = node;
  std::vector <Node*> stack = {node};

  uint32_t depth = node->meta.depth;
  uint32_t d = depth + 1;

  for (int key = node->key + 1; key < list_control.n_nodes; key++) {
    node = list_control.root->find_preorder(key);
    if (node->meta.depth <= depth) {
      break;
    }

    // Update the stack depending on the depth
    if (node->meta.depth > d) {
      d = node->meta.depth;
      stack.push_back(prev);
    } else if (node->meta.depth < d) {
      d = node->meta.depth;
      stack.pop_back();
    }

    // Child's "hidden" follows parent's "checked"
    bool hidden = (stack.back()->meta.checked == NODE_OPEN ? false : true);
    node->meta.hidden = hidden;

    if (hidden == false && ++index < CELL_MAX_VISIBLE + 1) {
      // 1. Add a new cell and re-index
      lv_obj_t *cell = append_cell(list, node);
      lv_obj_move_to_index(cell, index);
      update_list(list);

      // 2. Set the animation to delete the last cell
      lv_anim_set_var(a, cell);
      lv_anim_start(a);
    }

    // Update previous node
    prev = node;
  }
}

static void update_close(lv_obj_t *list, Node *node, uint32_t index, lv_anim_t *a) {
  uint32_t depth = node->meta.depth;

  // Hide all the children
  for (int key = node->key + 1; key < list_control.n_nodes; key++) {
    node = list_control.root->find_preorder(key);
    if (node->meta.depth <= depth) {
      break;
    }
    node->meta.hidden = true;
  }

  // Get the last node key in the list
  uint32_t last_key = get_node(lv_obj_get_child(list, -1))->key;

  lv_obj_t *cell;
  while (cell = lv_obj_get_child(list, ++index)) {
    node = get_node(cell);
    if (node->meta.depth <= depth) {
      break;
    }

    // 1. Apply animation to the cell and start playing
    lv_anim_set_var(a, cell);
    lv_anim_start(a);

    // 2. Add the same number of new cells to the end of the list
    if (node = find_after(last_key)) {
      last_key = node->key;
      append_cell(list, node);
      update_list(list);
    }
  }
}

//--------------------------------------------------------------------------------
// Event handler for when a cell is clicked
//--------------------------------------------------------------------------------
static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_CLICKED) {
    lv_obj_t *cell = lv_event_get_target_obj(e);
    lv_obj_t *list = lv_obj_get_parent(cell);

    Node *node = get_node(cell);
    NodeMeta_t *meta = &node->meta;

    if (meta->type == TYPE_NODE) {
      // Update the node status and appearance
      bool checked  = meta->checked = !meta->checked;
      lv_obj_send_event(cell, LV_EVENT_STYLE_CHANGED, NULL);

      // Setup an animation template
      lv_anim_t a;
      lv_anim_init(&a);
      lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_height);
      lv_anim_set_duration(&a, FOLDING_DURATION);
      lv_anim_set_user_data(&a, list);

      uint32_t index = lv_obj_get_index(cell);

      if (checked == NODE_OPEN) {
        lv_anim_set_values(&a, 0, CELL_HEIGHT_SMALL);
        lv_anim_set_completed_cb(&a, update_open_cb);
        update_open(list, node, index, &a);
      }

      else /* checked == NODE_CLOSED */ {
        lv_anim_set_values(&a, CELL_HEIGHT_SMALL, 0);
        lv_anim_set_completed_cb(&a, update_close_cb);
        update_close(list, node, index, &a);
      }
    }

    else /* meta->type == TYPE_LEAF */ {
      // Update the checkbox state and appearance
      meta->checked = !meta->checked;
      lv_obj_send_event(cell, LV_EVENT_STYLE_CHANGED, NULL);
    }
  }
}

//--------------------------------------------------------------------------------
// Adjust the number of cells in the list according to the scroll
// https://docs.lvgl.io/master/details/common-widget-features/scrolling.html
// https://github.com/lvgl/lvgl/blob/master/examples/scroll/lv_example_scroll_7.c
//--------------------------------------------------------------------------------
static void update_scroll(lv_obj_t *list) {
  // Do not re-enter this function when `lv_obj_scroll_by` triggers this callback again.
  if (update_scroll_running) return;
  update_scroll_running = true;

  Node *node;
  int32_t pos;

  // Scroll DOWN: Add new cells to END while the bottom position of the scroll range is smaller than the cell height
  while (list_control.end < list_control.n_nodes - 1 && (pos = lv_obj_get_scroll_bottom(list)) < CELL_OFFSET_NODE) {
    if (node = find_after(list_control.end)) {
      append_cell(list, node);
      update_list(list);
      // printf("added end --> pos: %d, top:%3d, end:%3d, count: %d\n", pos, list_control.top, list_control.end, list_control.count);
    } else {
      break;
    }
  }

  // Scroll UP: Add new cells to TOP while the bottom position of the scroll range is smaller than the cell height
  while (list_control.top > 0 && (pos = lv_obj_get_scroll_top(list)) < CELL_OFFSET_NODE) {
    if (node = find_before(list_control.top)) {
      int32_t bottom_before = lv_obj_get_scroll_bottom(list);
      lv_obj_t *new_item = append_cell(list, node);
      lv_obj_move_to_index(new_item, 0);
      update_list(list);
      int32_t bottom_after = lv_obj_get_scroll_bottom(list);
      lv_obj_scroll_by(list, 0, bottom_before - bottom_after, LV_ANIM_OFF);
      // printf("added top --> pos: %d, top:%3d, end:%3d, count: %d\n", pos, list_control.top, list_control.end, list_control.count);
    } else {
      break;
    }
  }

  // Scroll UP: Delete the END cells outside the scrolling range
  while (list_control.count > CELL_MAX_VISIBLE + 1 && (pos = lv_obj_get_scroll_bottom(list)) > CELL_HEIGHT_SMALL) {
    if (node = find_before(list_control.end)) {
      lv_obj_t *child = lv_obj_get_child(list, -1);
      delete_cell(list, child);
      update_list(list);
      // printf("deleted end --> pos: %d, top:%3d, end:%3d, count: %d\n", pos, list_control.top, list_control.end, list_control.count);
    } else {
      break;
    }
  }

  // Scroll DOWN: Delete the TOP cells outside the scrolling range
  while (list_control.count > CELL_MAX_VISIBLE + 1 && (pos = lv_obj_get_scroll_top(list)) > CELL_HEIGHT_SMALL) {
    if (node = find_after(list_control.top)) {
      int32_t bottom_before = lv_obj_get_scroll_bottom(list);
      lv_obj_t *child = lv_obj_get_child(list, 0);
      delete_cell(list, child);
      update_list(list);
      int32_t bottom_after = lv_obj_get_scroll_bottom(list);
      lv_obj_scroll_by(list, 0, bottom_before - bottom_after, LV_ANIM_OFF);
      // printf("deleted top --> pos: %d, top:%3d, end:%3d, count: %d\n", pos, list_control.top, list_control.end, list_control.count);
    } else {
      break;
    }
  }

  update_scroll_running = false;
}

static void scroll_cb(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  DBG_ASSERT(event_code == LV_EVENT_SCROLL);
  DBG_ASSERT(album_list == lv_event_get_target_obj(e));
  update_scroll(album_list);
}

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
static void playlist_cb(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED);

  lv_obj_t * obj = lv_event_get_target_obj(e);
  ui_option.selectPlaylist = lv_dropdown_get_selected(obj);
}

//--------------------------------------------------------------------------------
// Set the pointer to the widget to NULL when its object is deleted
//--------------------------------------------------------------------------------
static void delete_cb(lv_event_t *e) {
  lv_obj_t **obj = (lv_obj_t **)lv_event_get_user_data(e);
  static constexpr lv_obj_t ** const adrs[] = {
    &ui_ScreenAlbumList,
    &album_list,
  };

  for (int i = 0; i < sizeof(adrs) / sizeof(adrs[0]); i++) {
    if (obj == adrs[i]) {
      *obj = NULL;
      DBG_EXEC(printf("deleted: %d\n", i));
      return;
    }
  }
  DBG_EXEC(printf("deleted: 0x%x\n", obj));
}

//--------------------------------------------------------------------------------
// Initialize / Deinitialize widgets
//--------------------------------------------------------------------------------
void ui_ScreenAlbumList_screen_init(void) {
  if (ui_ScreenAlbumList == NULL) {
    ui_ScreenAlbumList = lv_obj_create(NULL);
    lv_obj_set_style_bg_color (ui_ScreenAlbumList, UI_COLOR_BACKGROUND, 0);
    lv_obj_add_event_cb       (ui_ScreenAlbumList, ui_event_ScreenAlbumList, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb       (ui_ScreenAlbumList, ui_event_ScreenAlbumList, LV_EVENT_SCREEN_LOADED, NULL);
    lv_obj_add_event_cb       (ui_ScreenAlbumList, ui_event_ScreenAlbumList, LV_EVENT_SCREEN_UNLOADED, NULL);
    lv_obj_add_event_cb       (ui_ScreenAlbumList, delete_cb, LV_EVENT_DELETE, (void*)&ui_ScreenAlbumList);

#if SHOW_ARROW_BUTTON
    //////////////////// Arrow Icon ////////////////////
    {
      static constexpr lv_style_const_prop_t style_prop_common[] = {
        LV_STYLE_CONST_WIDTH(27),
        LV_STYLE_CONST_HEIGHT(27),
        LV_STYLE_CONST_X(LV_PCT_X(42)),
        LV_STYLE_CONST_Y(LV_PCT_Y(-44)),
        LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
        LV_STYLE_CONST_PROPS_END
      };
      static constexpr lv_style_const_prop_t style_prop_default[] = {
        LV_STYLE_CONST_BG_IMAGE_SRC(&img_menu_right),
        LV_STYLE_CONST_BG_COLOR(UI_COLOR_BACKGROUND),
        LV_STYLE_CONST_RADIUS(LV_RADIUS_CIRCLE),
        LV_STYLE_CONST_BORDER_WIDTH(0),
        LV_STYLE_CONST_PAD_TOP(8),
        LV_STYLE_CONST_PAD_RIGHT(0),
        LV_STYLE_CONST_PAD_BOTTOM(0),
        LV_STYLE_CONST_PAD_LEFT(8),
        LV_STYLE_CONST_PROPS_END
      };
      static constexpr lv_style_const_prop_t style_prop_pressed[] = {
        LV_STYLE_CONST_PAD_TOP(10),
        LV_STYLE_CONST_PAD_LEFT(10),
        LV_STYLE_CONST_PROPS_END
      };
      static constexpr lv_style_const_prop_t style_prop_checked[] = {
        LV_STYLE_CONST_BG_IMAGE_SRC(&img_menu_right),
        LV_STYLE_CONST_BG_COLOR(UI_COLOR_BACKGROUND),
        LV_STYLE_CONST_PROPS_END
      };
      static LV_STYLE_CONST_INIT(style_common,  (void*)style_prop_common );
      static LV_STYLE_CONST_INIT(style_default, (void*)style_prop_default);
      static LV_STYLE_CONST_INIT(style_pressed, (void*)style_prop_pressed);
      static LV_STYLE_CONST_INIT(style_checked, (void*)style_prop_checked);

      lv_obj_t *obj = lv_checkbox_create(ui_ScreenAlbumList);
      lv_checkbox_set_text_static(obj, "");
      lv_obj_add_style    (obj, &style_common,  (uint32_t)LV_PART_MAIN      | (uint32_t)LV_STATE_DEFAULT);
      lv_obj_add_style    (obj, &style_default, (uint32_t)LV_PART_INDICATOR | (uint32_t)LV_STATE_DEFAULT);
      lv_obj_add_style    (obj, &style_pressed, (uint32_t)LV_PART_INDICATOR | (uint32_t)LV_STATE_PRESSED);
      lv_obj_add_style    (obj, &style_checked, (uint32_t)LV_PART_INDICATOR | (uint32_t)LV_STATE_CHECKED);
      lv_obj_add_event_cb (obj, ui_event_ScreenAlbumList, LV_EVENT_CLICKED, NULL);
    }
#endif

    //////////////////// Title Label ////////////////////
    lv_obj_t *obj = lv_label_create(ui_ScreenAlbumList);
    lv_obj_set_pos(obj, LV_PCT_X(5), LV_PCT_Y(4));
    lv_label_set_text_static(obj, "Album list");

    //////////////////// Dropdown List ////////////////////
    obj = lv_dropdown_create(ui_ScreenAlbumList);
    lv_obj_set_pos          (obj, LV_PCT_X(5), LV_PCT_Y(11));
    lv_obj_set_size         (obj, OPTIONS_WIDTH, LV_SIZE_CONTENT);
    lv_obj_add_event_cb     (obj, playlist_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_dropdown_set_options (obj, "All");
    lv_dropdown_set_selected(obj, ui_option.selectPlaylist);

    //////////////////// List Container ////////////////////
    static constexpr lv_style_const_prop_t style_prop_album[] = {
      LV_STYLE_CONST_X(LV_PCT_X(5)),
      LV_STYLE_CONST_Y(LV_PCT_Y(26)),
      LV_STYLE_CONST_WIDTH(SCREEN_WIDTH - LV_PCT_X(10)),
      LV_STYLE_CONST_HEIGHT(ALBUM_LIST_HEIGHT),
      LV_STYLE_CONST_PROPS_END
    };
    static LV_STYLE_CONST_INIT(style_album, (void*)style_prop_album);

    album_list = lv_list_create(ui_ScreenAlbumList);
    lv_obj_add_style          (album_list, &style_album, 0);
//  lv_obj_set_scrollbar_mode (album_list, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_event_cb       (album_list, scroll_cb, LV_EVENT_SCROLL, NULL);
    lv_obj_add_event_cb       (album_list, delete_cb, LV_EVENT_DELETE, (void*)&album_list);
  }
}

void ui_ScreenAlbumList_screen_deinit(void) {
  if (ui_ScreenAlbumList) {
    // Re-traverse node tree before making a new playlist
    list_control.root->traverse_node();

    // Delete all the instances at delete_cb()
    lv_obj_delete_async(ui_ScreenAlbumList);
  }
}

//--------------------------------------------------------------------------------
// Create selectable playlist
//--------------------------------------------------------------------------------
void ui_ScreenAlbumList_create_list(void *root) {
  if (root) {
    // Re-traverse node tree by preorder
    list_control.root = static_cast<Node*>(root);
    list_control.n_nodes = list_control.root->traverse_preorder();

    list_control.top = list_control.end = 0;
    append_cell(album_list, list_control.root->find_preorder(0));
    update_scroll(album_list);
  }
}