#ifndef MENU_H
#define MENU_H

#include "button.h"

typedef enum {
    MENU_STATE_MAIN,
    MENU_STATE_TASK
} menu_state_t;

void menu_init();
void menu_update(button_t btn);
void menu_draw();

#endif
