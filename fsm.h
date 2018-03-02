#ifndef __INCLUDE_FSM_H__
#define __INCLUDE_FSM_H__
#include "elev.h"

void fsm_buttons_pressed(elev_button_type_t button, int floor);

void fsm_floor_reached(int floor);

void fsm_stop_pressed();

void fsm_timeout();

int fsm_elev_init();

#endif