#include <stdio.h>
#include <lvgl.h>

#include "vars.h"
#include "screens.h"
#include "ui.h"

int32_t counter = 0;
char counter_info[256];

int32_t selected_item_index = 0;
char selected_item_info[256];

const char *get_var_counter_info() {
    snprintf(counter_info, sizeof(counter_info), "Counter is %d", counter);
    return counter_info;
}

int32_t get_var_selected_item_index() {
    return selected_item_index;
}

void set_var_selected_item_index(int32_t value) {
    selected_item_index = value;
}

const char *get_var_selected_item_info() {
    snprintf(selected_item_info, sizeof(selected_item_info), "Selected index is %d", selected_item_index);
    return selected_item_info;
}
