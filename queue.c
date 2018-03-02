#include "queue.h"
#include <stdio.h>

static int queue[3][4] = {{0}};

void queue_add_to_queue(elev_button_type_t button, int floor) {

	queue[button][floor] = 1;

}


void queue_remove_from_queue(elev_button_type_t button, int floor) {

	queue[button][floor] = 0;

}


void queue_remove_all_orders() {

	for(int button = 0; button < 3; button++) {
		for(int floor = 0; floor < 4; floor++) {
			queue[button][floor] = 0;
		} 
	}
}


int queue_is_order(elev_button_type_t button, int floor) {

	if(queue[button][floor] == 1) {
		return 1;
	}

	return 0;
}

int queue_elev_stop(int floor, int dir){

	if (queue_is_order(BUTTON_CALL_UP, floor) && dir == 1){
		return 1;
	} 
	else if (queue_is_order(BUTTON_CALL_DOWN, floor) && dir == -1){
		return 1;
	}
	else if (queue_is_order(BUTTON_COMMAND, floor)){
		return 1;
	}

	return 0;
}


int queue_is_empty(){

	for(int button = 0; button < 3; button++) {
		for(int floor = 0; floor < 4; floor++) {
			if(queue[button][floor] == 1) {
				return 0;
			}
		} 
	}
	return 1;
}	

void queue_print () {

	for(int button = 0; button < 3; button++) {
		for(int floor = 0; floor < 4; floor++) {
			printf("%d", queue[button][floor]);
		}
		printf("\n");
	}
}