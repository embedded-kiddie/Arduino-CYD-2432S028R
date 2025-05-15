#include <lvgl.h>

#include "actions.h"
#include "screens.h"
#include "ui.h"

extern int32_t counter;
extern int32_t selected_item_index;

void action_inc_counter(lv_event_t *e) {
    counter++;
}

void action_dec_counter(lv_event_t *e) {
    counter--;
}

void action_show_main_screen(lv_event_t *e) {
    loadScreen(SCREEN_ID_MAIN);
}

void action_select_item(lv_event_t * e) {
    lv_obj_t * obj = lv_event_get_target(e);
    selected_item_index = lv_dropdown_get_selected(obj);
}
