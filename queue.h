#ifndef __INCLUDE_FSM_H__
#define __INCLUDE_FSM_H__
#include "elev.h"
#include <stdio.h>



void queue_add_to_queue(elev_button_type_t button, int floor);

void queue_remove_from_queue(elev_button_type_t button, int floor);

void queue_remove_all_orders();

int queue_is_order(elev_button_type_t button, int floor);

int queue_elev_stop(int floor, int dir);

int queue_is_empty();

void queue_print();







#endif