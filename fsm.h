#ifndef __INCLUDE_FSM_H__
#define __INCLUDE_FSM_H__
#include "elev.h"
#include "queue.h"
#include "timer.h"
#include <stdio.h>

typedef enum elev_state{IDLE, RUNNING, STOP, DOOR_OPEN, NONE} elev_state;


void fsm_buttons_pressed(elev_button_type_t button, int floor);

void fsm_floor_reached(int floor);

void fsm_stop_pressed();

void fsm_timeout();

int fsm_elev_init();

elev_state fsm_get_state();

#endif