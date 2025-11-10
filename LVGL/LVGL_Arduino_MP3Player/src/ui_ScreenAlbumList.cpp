//================================================================================
// MP3 Music Player for CYD - Album List Screen
// LVGL version: 9.2.2 and up
//================================================================================
#include "ui.h"
#include "../tree.hpp"

//--------------------------------------------------------------------------------
// Instance of the screen widget
//--------------------------------------------------------------------------------
lv_obj_t *ui_ScreenAlbumList;

// Components in list widget
#define INFO_LABEL_COLOR    { .blue = 0x88, .green = 0x88, .red = 0x88 }
#define CELL_COLOR_OUTLINE  { .blue = 0xe4, .green = 0xe0, .red = 0xe4 }
#define CELL_COLOR_NODE     lv_color_hex(0xf4f4f4)
#define CELL_COLOR_LEAF     lv_color_hex(0xffffff)
#define CELL_HEIGHT_SMALL   31  // For CUSTOM_FONT_SMALL
#define CELL_HEIGHT_MEDIUM  34  // For CUSTOM_FONT_MEDIUM
#define CELL_OFFSET_NODE    6   // Offset for node text
#define CELL_OFFSET_LEAF    10  // Offset for leaf text
#define CELL_PADDING_LEFT   6   // Padding left in pixels
#define CELL_PADDING_BORDER 8   // Padding top/bottom in pixels
#define CELL_MAX_VISIBLE    7   // Number of visible cells in the album list
#define CELL_SCROLL_POS     6   // Scroll Position to update list to add/remove cells
#define ALBUM_LIST_HEIGHT   220 // Height of the album list (CELL_HEIGHT_SMALL * CELL_MAX_VISIBLE + alpha)
#define FOLDING_DURATION    250 // Folding animation duration

#if   true
#define DROPDOWN_LIST_WIDTH 100
#define DROPDOWN_LIST_X     LV_PCT_X(42)    // Dropdown List
#define DROPDOWN_LIST_Y     LV_PCT_Y(2)+1   // Dropdown List
#define TITLE_LABEL_X       LV_PCT_X(5)     // Title Label
#define TITLE_LABEL_Y       LV_PCT_Y(5)     // Title Label
#define TOGGLE_BUTTON_X     LV_PCT_X(6)     // Button Matrix
#define TOGGLE_BUTTON_Y     LV_PCT_Y(14)    // Button Matrix
#define KEYPAD_BUTTON_X     LV_PCT_X(41)    // Button Matrix
#define KEYPAD_BUTTON_Y     LV_PCT_Y(14)    // Button Matrix
#else
#define DROPDOWN_LIST_WIDTH 90
#define DROPDOWN_LIST_X     LV_PCT_X(5)     // Dropdown List
#define DROPDOWN_LIST_Y     LV_PCT_Y(2)+1   // Dropdown List
#define TITLE_LABEL_X       LV_PCT_X(7)     // Title Label
#define TITLE_LABEL_Y       LV_PCT_Y(16)    // Title Label
#define TOGGLE_BUTTON_X     LV_PCT_X(44)    // Button Matrix
#define TOGGLE_BUTTON_Y     LV_PCT_Y(14)    // Button Matrix
#define KEYPAD_BUTTON_X     LV_PCT_X(44)    // Button Matrix
#define KEYPAD_BUTTON_Y     LV_PCT_Y(3)     // Button Matrix
#endif

#define ALBUM_LIST_X      LV_PCT_X(5)     // List Container
#define ALBUM_LIST_Y      LV_PCT_Y(24)    // List Container
#define BACK_TO_MAIN_X    LV_PCT_X(87)    // Back to Main
#define BACK_TO_MAIN_Y    LV_PCT_Y(4)     // Back to Main

typedef struct {
  int   top;        // node key at the top of the album list
  int   end;        // node key at the end of the album list
  int   count;      // number of the cells in the album list
  int   n_nodes;    // total number of the nodes in tree
  Node  *root;
} AlbumControl_t;

typedef struct {
  int   n_folded;   // number of folded   nodes in tree
  int   n_selected; // number of selected leafs in tree
  int   n_files;    // number of selected audio files
} AlbumInfo_t;

//--------------------------------------------------------------------------------
// Global variables and prototype
//--------------------------------------------------------------------------------
static lv_obj_t *album_list;
static lv_obj_t *album_info;
static AlbumControl_t album_control;
static bool update_scroll_running = false;

static void event_handler(lv_event_t *e);
static void draw_image_cb(lv_event_t *e);

//--------------------------------------------------------------------------------
// Setup cell styles and properties
//--------------------------------------------------------------------------------
static void set_properties(lv_obj_t *cell, Node *node) {
  static constexpr lv_style_const_prop_t style_prop_cell[] = {
    LV_STYLE_CONST_ALIGN(LV_ALIGN_LEFT_MID),
    LV_STYLE_CONST_TEXT_FONT(&CUSTOM_FONT_SMALL),
    LV_STYLE_CONST_PAD_TOP(CELL_PADDING_BORDER),
    LV_STYLE_CONST_PAD_BOTTOM(CELL_PADDING_BORDER),
    LV_STYLE_CONST_OUTLINE_COLOR(CELL_COLOR_OUTLINE),
    LV_STYLE_CONST_OUTLINE_WIDTH(1),
    LV_STYLE_CONST_PROPS_END
  };
  static LV_STYLE_CONST_INIT(style_cell, (void*)(style_prop_cell));
  lv_obj_add_style(cell, &style_cell, (uint32_t)LV_PART_MAIN);

  NodeMeta_t *meta = &node->meta;
  lv_obj_set_style_height   (cell, (meta->depth > 1 && meta->hidden ? 0 : CELL_HEIGHT_SMALL), LV_PART_MAIN);
  lv_obj_set_style_bg_color (cell, (meta->type == TYPE_NODE ? CELL_COLOR_NODE : CELL_COLOR_LEAF), LV_PART_MAIN);
  lv_obj_set_style_pad_left (cell, (meta->depth * CELL_PADDING_LEFT + (meta->type == TYPE_NODE ? CELL_OFFSET_NODE: CELL_OFFSET_LEAF)), LV_PART_MAIN);
  lv_label_set_long_mode    (cell, LV_LABEL_LONG_CLIP); // LV_LABEL_LONG_DOT, LV_LABEL_LONG_SCROLL_CIRCULAR
  lv_obj_add_flag           (cell, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_flag           (cell, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);
  lv_obj_add_event_cb       (cell, draw_image_cb, LV_EVENT_DRAW_TASK_ADDED, NULL);
  lv_obj_add_event_cb       (cell, event_handler, LV_EVENT_CLICKED, NULL);
  lv_obj_set_user_data      (cell, reinterpret_cast<void*>(node));
}

//--------------------------------------------------------------------------------
// Count / Update open cells, selected nodes and selected audio files
//--------------------------------------------------------------------------------
static void count_checked(Node *node, AlbumInfo_t *info) {
  if (node->meta.type == TYPE_NODE) {
    // Is the node open?
    if (node->meta.checked == NODE_FOLDED) {
      info->n_folded++;
    }
    for (auto &n : node->children) {
      count_checked(n, info);
    }
  }
  // Is the leaf selected?
  else if (node->meta.checked == LEAF_SELECTED) {
    info->n_selected++;
    info->n_files += node->n_files;
  }
}

static void get_album_info(AlbumInfo_t *info) {
  *info = {0,};
  for (auto &n : album_control.root->children) {
    count_checked(n, info);
  }
}

static void update_info(lv_obj_t *label) {
  AlbumInfo_t info;
  get_album_info(&info);
  lv_label_set_text_fmt(label, "Selected albums: %d, files: %d", info.n_selected, info.n_files);
}

//--------------------------------------------------------------------------------
// Sets the state of all cells in the album list
//--------------------------------------------------------------------------------
static void set_state_all(int type, int state) {
  const int n = album_control.n_nodes;
  for (int i = 0; i < n; i++) {
    Node *node = album_control.root->find_preorder(i);
    DBG_ASSERT(node);
    if (type == TYPE_NODE) {
      node->meta.hidden = (state == NODE_FOLDED ? NODE_HIDDEN : NODE_REVEALED);
      if (node->meta.type == TYPE_NODE) {
        node->meta.checked = state;
      }
    } else if (node->meta.type == TYPE_LEAF) {
      node->meta.checked = state;
    }
  }
}

//--------------------------------------------------------------------------------
// Get the node pointer from the cell's userdata
//--------------------------------------------------------------------------------
static inline Node *get_node(lv_obj_t *cell) {
  return (Node*)lv_obj_get_user_data(cell);
}

//--------------------------------------------------------------------------------
// Update cells' position in the list
//--------------------------------------------------------------------------------
static inline void update_list(lv_obj_t *list) {
  lv_obj_update_layout(list);
  album_control.top = get_node(lv_obj_get_child(list,  0))->key;
  album_control.end = get_node(lv_obj_get_child(list, -1))->key;
  album_control.count = lv_obj_get_child_count(list);
}

//--------------------------------------------------------------------------------
// Append / Delete the specified node to the list
//--------------------------------------------------------------------------------
static inline lv_obj_t *append_cell(lv_obj_t *list, Node *node) {
  DBG_EXEC(printf("count:%3d added   %3d \"%s\"\n", album_control.count, node->key, node->name.c_str()));

  lv_obj_t * cell = lv_list_add_text(list, node->name.c_str());
  set_properties(cell, node);
  return cell;
}

static inline void delete_cell(lv_obj_t *list, lv_obj_t *cell) {
  DBG_EXEC({
    Node *node = get_node(cell);
    printf("count:%3d deleted %3d \"%s\"\n", album_control.count, node->key, node->name.c_str());
  });

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
static void adjust_bottom(lv_obj_t *list) {
  DBG_EXEC(printf("bottom: %d --> ", lv_obj_get_scroll_bottom(list)));

  // If the bottom position is negative, reposition it to a positive
  if (lv_obj_get_scroll_bottom(list) <= 0) {
    lv_obj_scroll_to_y(list, CELL_HEIGHT_SMALL, LV_ANIM_OFF); // 1. Move to positive position
    lv_obj_scroll_to_y(list, 0, LV_ANIM_OFF);                 // 2. Snap to the bottom position
  }

  // Update cells' position in the list
  update_list(list);

  DBG_EXEC(printf("%d\n", lv_obj_get_scroll_bottom(list)));
}

//--------------------------------------------------------------------------------
// Get the open node after/before the specified key
//--------------------------------------------------------------------------------
static Node *find_after(int key) {
  while (++key < album_control.n_nodes) {
    Node *node = album_control.root->find_preorder(key);
    DBG_ASSERT(node);
    if (node->meta.depth == 1 || node->meta.hidden == false) {
      return node;
    }
  }
  return NULL;
}

static Node *find_before(int key) {
  while (--key >= 0) {
    Node *node = album_control.root->find_preorder(key);
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
  lv_draw_dsc_base_t *base_dsc = (lv_draw_dsc_base_t *)lv_draw_task_get_draw_dsc(draw_task);

  if (base_dsc->part == LV_PART_MAIN && type == LV_DRAW_TASK_TYPE_FILL) {
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
    area.x1 = 0; area.x2 = img->header.w - 1;
    area.y1 = 0; area.y2 = img->header.h - 1;

    lv_area_t draw_task_area;
    lv_draw_task_get_area(draw_task, &draw_task_area);
    lv_area_align(&draw_task_area, &area, LV_ALIGN_LEFT_MID, meta->depth * CELL_PADDING_LEFT, 0);

#if 0
    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.bg_image_src = (const void *)img;
    rect_dsc.bg_color = (meta->type == TYPE_NODE ? CELL_COLOR_NODE : CELL_COLOR_LEAF);
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
static void scroll_to_view(void* obj) {
  lv_obj_scroll_to_view((lv_obj_t *)obj, LV_ANIM_OFF);
}

static void update_open_cb(lv_anim_t* a) {
  // Scroll to make it visible
  lv_obj_scroll_to_view((lv_obj_t*)a->var, LV_ANIM_ON);

  // Delete the last cell if it is not newly added
  lv_obj_t *list = (lv_obj_t*)lv_anim_get_user_data(a);
  lv_obj_t *cell = lv_obj_get_child(list, -1);

  if (a->var != cell) {
    delete_cell(list, cell);
  } else {
    // Ensure to make the last cell visible
    lv_async_call(scroll_to_view, a->var);
  }

  // Not required at the end of animation ?
  update_list(list);
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

  for (int key = node->key + 1; key < album_control.n_nodes; key++) {
    node = album_control.root->find_preorder(key);
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
    bool hidden = (stack.back()->meta.checked == NODE_UNFOLDED ? false : true);
    node->meta.hidden = hidden;

    if (hidden == false && ++index <= CELL_MAX_VISIBLE + 1) {
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
  for (int key = node->key + 1; key < album_control.n_nodes; key++) {
    node = album_control.root->find_preorder(key);
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
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_CLICKED);

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
    lv_anim_set_user_data(&a, reinterpret_cast<void*>(list));

    uint32_t index = lv_obj_get_index(cell);

    if (checked == NODE_UNFOLDED) {
      lv_anim_set_values(&a, 0, CELL_HEIGHT_SMALL);
      lv_anim_set_completed_cb(&a, update_open_cb);
      update_open(list, node, index, &a);
    }

    else /* checked == NODE_FOLDED */ {
      lv_anim_set_values(&a, CELL_HEIGHT_SMALL, 0);
      lv_anim_set_completed_cb(&a, update_close_cb);
      update_close(list, node, index, &a);
    }
  }

  else /* meta->type == TYPE_LEAF */ {
    // Update the checkbox state and appearance
    meta->checked = !meta->checked;
    update_info(album_info);
    lv_obj_send_event(cell, LV_EVENT_STYLE_CHANGED, NULL);
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
  while (album_control.end < album_control.n_nodes - 1 && (pos = lv_obj_get_scroll_bottom(list)) < CELL_SCROLL_POS) {
    if (node = find_after(album_control.end)) {
      append_cell(list, node);
      update_list(list);
      DBG_EXEC(printf("added   end at pos:%4d --> top:%3d, end:%3d, count: %d\n", pos, album_control.top, album_control.end, album_control.count));
    } else {
      break;
    }
  }

  // Scroll UP: Add new cells to TOP while the bottom position of the scroll range is smaller than the cell height
  while (album_control.top > 0 && (pos = lv_obj_get_scroll_top(list)) < CELL_SCROLL_POS) {
    if (node = find_before(album_control.top)) {
      int32_t bottom_before = lv_obj_get_scroll_bottom(list);
      lv_obj_t *new_item = append_cell(list, node);
      lv_obj_move_to_index(new_item, 0);
      update_list(list);
      int32_t bottom_after = lv_obj_get_scroll_bottom(list);
      lv_obj_scroll_by(list, 0, bottom_before - bottom_after, LV_ANIM_OFF);
      DBG_EXEC(printf("added   top at pos:%4d --> top:%3d, end:%3d, count: %d\n", pos, album_control.top, album_control.end, album_control.count));
    } else {
      break;
    }
  }

  // Scroll UP: Delete the END cells outside the scrolling range
  while (album_control.count > CELL_MAX_VISIBLE + 1 && (pos = lv_obj_get_scroll_bottom(list)) > CELL_HEIGHT_SMALL) {
    if (node = find_before(album_control.end)) {
      lv_obj_t *child = lv_obj_get_child(list, -1);
      delete_cell(list, child);
      update_list(list);
      DBG_EXEC(printf("deleted end at pos:%4d --> top:%3d, end:%3d, count: %d\n", pos, album_control.top, album_control.end, album_control.count));
    } else {
      break;
    }
  }

  // Scroll DOWN: Delete the TOP cells outside the scrolling range
  while (album_control.count > CELL_MAX_VISIBLE + 1 && (pos = lv_obj_get_scroll_top(list)) > CELL_HEIGHT_SMALL) {
    if (node = find_after(album_control.top)) {
      int32_t bottom_before = lv_obj_get_scroll_bottom(list);
      lv_obj_t *child = lv_obj_get_child(list, 0);
      delete_cell(list, child);
      update_list(list);
      int32_t bottom_after = lv_obj_get_scroll_bottom(list);
      lv_obj_scroll_by(list, 0, bottom_before - bottom_after, LV_ANIM_OFF);
      DBG_EXEC(printf("deleted top at pos:%4d --> top:%3d, end:%3d, count: %d\n", pos, album_control.top, album_control.end, album_control.count));
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
// Append a first cell to the album list
//--------------------------------------------------------------------------------
static void album_init(int key = 0) {
  update_scroll_running = true;   // Disable 'update_scroll()' once
  lv_obj_clean  (album_list);
  update_scroll_running = false;  // Enable 'update_scroll()' again

  if (album_control.root) {
    append_cell   (album_list, album_control.root->find_preorder(album_control.top = key));
    update_list   (album_list);
    update_scroll (album_list);
    update_info   (album_info);
  }
}

//--------------------------------------------------------------------------------
// Callback for dropdown list
//--------------------------------------------------------------------------------
static void dropdown_cb(lv_event_t *e) {
  DBG_ASSERT(lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED);

  lv_obj_t * obj = lv_event_get_target_obj(e);
  ui_option.selectPlaylist = lv_dropdown_get_selected(obj);
}

//--------------------------------------------------------------------------------
// Callback for button matrix
// https://docs.lvgl.io/master/details/widgets/buttonmatrix.html#custom-buttons
//--------------------------------------------------------------------------------
static void button_draw_cb(lv_event_t *e) {
  lv_draw_task_t *draw_task = lv_event_get_draw_task(e);
  lv_draw_task_type_t type  = lv_draw_task_get_type(draw_task);
  lv_draw_dsc_base_t *base_dsc = (lv_draw_dsc_base_t *)lv_draw_task_get_draw_dsc(draw_task);

  // When the button matrix draws the buttons...
  if(base_dsc->part == LV_PART_ITEMS) {
    lv_obj_t *obj = lv_event_get_target_obj(e);
    bool pressed  = lv_obj_has_state(obj, LV_STATE_PRESSED);
    int selected  = lv_buttonmatrix_get_selected_button(obj);

    if (type == LV_DRAW_TASK_TYPE_LABEL) {
      lv_draw_label_dsc_t *label_dsc = lv_draw_task_get_label_dsc(draw_task);
      if (label_dsc) {
        label_dsc->ofs_x = label_dsc->ofs_y = (base_dsc->id1 == selected && pressed == true) ? 1 : 0;
      }
    }

    else if (type == LV_DRAW_TASK_TYPE_FILL) {
      lv_draw_fill_dsc_t *fill_dsc = lv_draw_task_get_fill_dsc(draw_task);
      if (fill_dsc) {
        fill_dsc->opa = (base_dsc->id1 == selected && pressed == true) ? 128 : 0;
      }
    }
  }
}

static void toggle_click_cb(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  DBG_ASSERT(event_code == LV_EVENT_VALUE_CHANGED);

  AlbumInfo_t info;
  get_album_info(&info);

  lv_obj_t *obj = lv_event_get_target_obj(e);
  uint32_t id = lv_buttonmatrix_get_selected_button(obj);
  switch (id) {
    case 0:
      set_state_all(TYPE_NODE, info.n_folded == 0 ? NODE_FOLDED : NODE_UNFOLDED);
      break;
    case 1:
      set_state_all(TYPE_LEAF, info.n_selected == 0 ? LEAF_SELECTED : LEAF_UNSELECTED);
      break;
    case LV_BUTTONMATRIX_BUTTON_NONE:
    default:
      DBG_ASSERT(false);
      break;
  }

  album_init(/*album_control.top*/);
}

static void keypad_click_cb(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  DBG_ASSERT(event_code == LV_EVENT_VALUE_CHANGED);

  lv_obj_t *obj = lv_event_get_target_obj(e);
  uint32_t id = lv_buttonmatrix_get_selected_button(obj);
  switch (id) {
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case LV_BUTTONMATRIX_BUTTON_NONE:
    default:
      DBG_ASSERT(false);
      break;
  }
}

//--------------------------------------------------------------------------------
// Set the pointer to the widget to NULL when its object is deleted
//--------------------------------------------------------------------------------
static void delete_cb(lv_event_t *e) {
  lv_obj_t **obj = (lv_obj_t **)lv_event_get_user_data(e);
  static constexpr lv_obj_t ** const adrs[] = {
    &ui_ScreenAlbumList,
    &album_list,
    &album_info,
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
    lv_obj_add_event_cb       (ui_ScreenAlbumList, delete_cb, LV_EVENT_DELETE, reinterpret_cast<void*>(&ui_ScreenAlbumList));

    lv_obj_t *obj;

#if SHOW_ARROW_BUTTON || true
    //////////////////// Back to Main ////////////////////
    static constexpr lv_style_const_prop_t style_prop_common[] = {
      LV_STYLE_CONST_WIDTH(27),
      LV_STYLE_CONST_HEIGHT(27),
      LV_STYLE_CONST_X(BACK_TO_MAIN_X),
      LV_STYLE_CONST_Y(BACK_TO_MAIN_Y),
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
    static LV_STYLE_CONST_INIT(style_common,  (void*)(style_prop_common ));
    static LV_STYLE_CONST_INIT(style_default, (void*)(style_prop_default));
    static LV_STYLE_CONST_INIT(style_pressed, (void*)(style_prop_pressed));
    static LV_STYLE_CONST_INIT(style_checked, (void*)(style_prop_checked));

    obj = lv_checkbox_create(ui_ScreenAlbumList);
    lv_checkbox_set_text_static(obj, "");
    lv_obj_add_style    (obj, &style_common,  (uint32_t)LV_PART_MAIN      | (uint32_t)LV_STATE_DEFAULT);
    lv_obj_add_style    (obj, &style_default, (uint32_t)LV_PART_INDICATOR | (uint32_t)LV_STATE_DEFAULT);
    lv_obj_add_style    (obj, &style_pressed, (uint32_t)LV_PART_INDICATOR | (uint32_t)LV_STATE_PRESSED);
    lv_obj_add_style    (obj, &style_checked, (uint32_t)LV_PART_INDICATOR | (uint32_t)LV_STATE_CHECKED);
    lv_obj_add_event_cb (obj, ui_event_ScreenAlbumList, LV_EVENT_CLICKED, NULL);
#endif

    ///////////////////// Title Label /////////////////////
    obj = lv_label_create(ui_ScreenAlbumList);
    lv_obj_set_pos(obj, TITLE_LABEL_X, TITLE_LABEL_Y);
    lv_label_set_text_static(obj, "Album List");

    //////////////////// Dropdown List ////////////////////
    static constexpr lv_style_const_prop_t style_prop_dropdown[] = {
      LV_STYLE_CONST_X(DROPDOWN_LIST_X),
      LV_STYLE_CONST_Y(DROPDOWN_LIST_Y),
      LV_STYLE_CONST_WIDTH(DROPDOWN_LIST_WIDTH),
      LV_STYLE_CONST_HEIGHT(LV_SIZE_CONTENT),
      LV_STYLE_CONST_TEXT_FONT(&CUSTOM_FONT_SMALL),
      LV_STYLE_CONST_PROPS_END
    };
    static LV_STYLE_CONST_INIT(style_dropdown, (void*)(style_prop_dropdown));

    obj = lv_dropdown_create(ui_ScreenAlbumList);
    lv_obj_add_style        (obj, &style_dropdown, 0);
    lv_obj_add_event_cb     (obj, dropdown_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_dropdown_set_options (obj, "All");
    lv_dropdown_set_selected(obj, ui_option.selectPlaylist);

    //////////////////// Button Matrix ////////////////////
    static constexpr lv_style_const_prop_t style_prop_button_main[] = {
      LV_STYLE_CONST_HEIGHT(30),
      LV_STYLE_CONST_BG_OPA(0),
      LV_STYLE_CONST_BORDER_WIDTH(0),
      LV_STYLE_CONST_PAD_TOP(0),
      LV_STYLE_CONST_PAD_LEFT(0),
      LV_STYLE_CONST_PAD_RIGHT(0),
      LV_STYLE_CONST_PAD_BOTTOM(0),
      LV_STYLE_CONST_PROPS_END
    };
    static constexpr lv_style_const_prop_t style_prop_button_item[] = {
      LV_STYLE_CONST_RADIUS(LV_RADIUS_CIRCLE),
      LV_STYLE_CONST_BORDER_WIDTH(0),
      LV_STYLE_CONST_SHADOW_WIDTH(0),
      LV_STYLE_CONST_PROPS_END
    };
    static constexpr lv_style_const_prop_t style_prop_toggle_main[] = {
      LV_STYLE_CONST_X(TOGGLE_BUTTON_X),
      LV_STYLE_CONST_Y(TOGGLE_BUTTON_Y),
      LV_STYLE_CONST_WIDTH(68), // 34 * 2
      LV_STYLE_CONST_PROPS_END
    };
    static constexpr lv_style_const_prop_t style_prop_keypad_main[] = {
      LV_STYLE_CONST_X(KEYPAD_BUTTON_X),
      LV_STYLE_CONST_Y(KEYPAD_BUTTON_Y),
      LV_STYLE_CONST_WIDTH(102), // 34 * 3
      LV_STYLE_CONST_PROPS_END
    };
    static LV_STYLE_CONST_INIT(style_button_main, (void*)(style_prop_button_main));
    static LV_STYLE_CONST_INIT(style_button_item, (void*)(style_prop_button_item));
    static LV_STYLE_CONST_INIT(style_toggle_main, (void*)(style_prop_toggle_main));
    static LV_STYLE_CONST_INIT(style_keypad_main, (void*)(style_prop_keypad_main));
    static constexpr lv_buttonmatrix_ctrl_t button_ctrl = (lv_buttonmatrix_ctrl_t)(
      (uint32_t)LV_BUTTONMATRIX_CTRL_CLICK_TRIG |
      (uint32_t)LV_BUTTONMATRIX_CTRL_NO_REPEAT
    );
    static constexpr const char* toggle_map[] = { LV_SYMBOL_DIRECTORY, LV_SYMBOL_OK, NULL };
    static constexpr const char* keypad_map[] = { LV_SYMBOL_PLUS, LV_SYMBOL_KEYBOARD, LV_SYMBOL_MINUS, NULL };

    obj = lv_buttonmatrix_create(ui_ScreenAlbumList);
    lv_buttonmatrix_set_map             (obj, toggle_map );
    lv_buttonmatrix_set_button_ctrl_all (obj, button_ctrl);
    lv_obj_add_style                    (obj, &style_toggle_main, LV_PART_MAIN );
    lv_obj_add_style                    (obj, &style_button_main, LV_PART_MAIN );
    lv_obj_add_style                    (obj, &style_button_item, LV_PART_ITEMS);
    lv_obj_add_event_cb                 (obj, button_draw_cb,  LV_EVENT_DRAW_TASK_ADDED, NULL);
    lv_obj_add_event_cb                 (obj, toggle_click_cb, LV_EVENT_VALUE_CHANGED,   NULL);
    lv_obj_add_flag                     (obj, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);

    obj = lv_buttonmatrix_create(ui_ScreenAlbumList);
    lv_buttonmatrix_set_map             (obj, keypad_map);
    lv_buttonmatrix_set_button_ctrl_all (obj, button_ctrl);
    lv_obj_add_style                    (obj, &style_keypad_main, LV_PART_MAIN );
    lv_obj_add_style                    (obj, &style_button_main, LV_PART_MAIN );
    lv_obj_add_style                    (obj, &style_button_item, LV_PART_ITEMS);
    lv_obj_add_event_cb                 (obj, button_draw_cb,  LV_EVENT_DRAW_TASK_ADDED, NULL);
    lv_obj_add_event_cb                 (obj, keypad_click_cb, LV_EVENT_VALUE_CHANGED,   NULL);
    lv_obj_add_flag                     (obj, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);
  }

  //////////////////// List Container ////////////////////
  if (album_list == NULL) {
    static constexpr lv_style_const_prop_t style_prop_album[] = {
      LV_STYLE_CONST_X(ALBUM_LIST_X),
      LV_STYLE_CONST_Y(ALBUM_LIST_Y),
      LV_STYLE_CONST_WIDTH(SCREEN_WIDTH - LV_PCT_X(10)),
      LV_STYLE_CONST_HEIGHT(ALBUM_LIST_HEIGHT),
      LV_STYLE_CONST_PROPS_END
    };
    static LV_STYLE_CONST_INIT(style_album, (void*)(style_prop_album));

    album_list = lv_list_create(ui_ScreenAlbumList);
    lv_obj_add_style          (album_list, &style_album, 0);
//  lv_obj_set_scrollbar_mode (album_list, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_event_cb       (album_list, scroll_cb, LV_EVENT_SCROLL, NULL);
    lv_obj_add_event_cb       (album_list, delete_cb, LV_EVENT_DELETE, reinterpret_cast<void*>(&album_list));
  }

  /////////////////// Infomation Label ///////////////////
  if (album_info == NULL) {
    static constexpr lv_style_const_prop_t style_prop_info[] = {
      LV_STYLE_CONST_Y(LV_PCT_Y(-2)+1),
      LV_STYLE_CONST_ALIGN(LV_ALIGN_BOTTOM_MID),
//    LV_STYLE_CONST_TEXT_COLOR(LV_PALETTE_GREY),
      LV_STYLE_CONST_TEXT_FONT(&CUSTOM_FONT_SMALL),
      LV_STYLE_CONST_PROPS_END
    };
    static LV_STYLE_CONST_INIT(style_info, (void*)(style_prop_info));

    album_info = lv_label_create(ui_ScreenAlbumList);
    lv_obj_add_style            (album_info, &style_info, LV_PART_MAIN);
    lv_label_set_text_static    (album_info, "No album");
    lv_obj_set_style_text_color (album_info, INFO_LABEL_COLOR, LV_PART_MAIN);
    lv_obj_add_event_cb         (album_info, delete_cb, LV_EVENT_DELETE, reinterpret_cast<void*>(&album_info));
  }
}

void ui_ScreenAlbumList_screen_deinit(void) {
  if (ui_ScreenAlbumList) {
    // Re-traverse node tree before making a new playlist
    if (album_control.root) {
      album_control.root->traverse_node();
    }

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
    album_control.root = reinterpret_cast<Node*>(root);
    album_control.n_nodes = album_control.root->traverse_preorder();
    album_init();
  } else {
    memset((void*)&album_control, 0, sizeof(album_control));
  }
}

#if   false
//--------------------------------------------------------------------------------
// Debug functions (static)
//--------------------------------------------------------------------------------
static size_t count_exposed(Node *node) {
  size_t count = 0;
  for (auto &n : node->children) {
    ++count; // count self

    // when node is open and has children...
    size_t size = n->children.size();
    if (size && n->meta.checked == NODE_UNFOLDED) {
      if (n->children[0]->children.size()) {
        count += count_exposed(n);
      } else {
        count += size;
      }
    }
  }

  return count;
}

// Dump the contents of a list
typedef struct {
  const lv_obj_class_t *m_class;
  const char *m_name;
} ClassName_t;

static const char *check_class(lv_obj_t *obj) {
  // https://docs.lvgl.io/master/details/widgets/index.html
  static const ClassName_t list[] = {
    { &lv_bar_class,      "lv_bar"      },
    { &lv_label_class,    "lv_label"    },
    { &lv_button_class,   "lv_button"   },
    { &lv_checkbox_class, "lv_checkbox" },
    { &lv_image_class,    "lv_image"    },
    { &lv_list_class,     "lv_list"     },
    { &lv_obj_class,      "lv_obj"      },
  };

  for (int i = 0; i < sizeof(list) / sizeof(list[0]); i++) {
    if (lv_obj_has_class(obj, list[i].m_class)) {
      return list[i].m_name;
    }
  }

  return "unknown";
}

static void dump_album(lv_obj_t *obj, int depth) {
  for (int i = 0; i < depth; i++) { printf("  "); }

  Node *node = get_node(obj);
  if (node) {
    NodeMeta_t *meta = &node->meta;
    printf("key: %3d, type: %d, depth: %d, hidden: %d, checked: %d --> ",
      node->key, meta->type, meta->depth, meta->hidden, meta->checked
    );
  }

  const char *c = check_class(obj);
  if (strcmp(c, "lv_label"   ) == 0) { printf("%s \"%s\"\n", c, lv_label_get_text(obj));    } else
  if (strcmp(c, "lv_checkbox") == 0) { printf("%s \"%s\"\n", c, lv_checkbox_get_text(obj)); } else
  if (strcmp(c, "lv_dropdown") == 0) { printf("%s \"%s\"\n", c, lv_dropdown_get_text(obj)); } else
  if (strcmp(c, "lv_dropdown") == 0) { printf("%s \"%s\"\n", c, lv_dropdown_get_text(obj)); } else
  printf("%s\n", c);

  lv_obj_t *cell;
  for (int i = 0; cell = lv_obj_get_child(obj, i); i++) {
    dump_album(cell, depth + 1);
  }
}

//--------------------------------------------------------------------------------
// Debug functions (global)
//--------------------------------------------------------------------------------
size_t count_exposed_nodes(void) {
  return count_exposed(album_control.root); // number of exposed nodes in tree
}

size_t count_album_list(void) {
  return lv_obj_get_child_count(album_list); // number of cells in album list
}

void show_album_list(void) {
#if   true
  Node *top = album_control.root->find_preorder(album_control.top);
  Node *end = album_control.root->find_preorder(album_control.end);
  printf("top:%3d (pos: %d) \"%s\", end:%3d (pos: %d) \"%s\", count: %d/%d\n",
    album_control.top, lv_obj_get_scroll_top   (album_list), top->name.c_str(),
    album_control.end, lv_obj_get_scroll_bottom(album_list), end->name.c_str(),
    album_control.count, lv_obj_get_child_count(album_list)
  );
#else
  AlbumInfo_t info;
  get_album_info(&info);
  printf("n_nodes: %d, n_leafs: %d, n_folded: %d, n_selected: %d, n_files: %d\n",
    album_control.n_nodes, album_control.root->get_n_leafs(), info.n_folded, info.n_selected, info.n_files
  );
#endif
}

void dump_album_list(void) {
  dump_album(album_list, 0); // dump all cells in album list
}

void dump_preorder(void) {
  album_control.root->dump_preorder(true); // dump all nodes in tree by preorder
}
#endif // Debug functions