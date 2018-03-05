#include "queue.h"
#include "elev.h"
#include <stdio.h>

static int queue[4][3] = {{0}};


void queue_add_to_queue(elev_button_type_t button, int floor) {

	queue[floor][button] = 1;
	queue_print ();

}


void queue_remove_from_queue(elev_button_type_t button, int floor) {

	queue[floor][button] = 0;

}


void queue_remove_all_orders() {

	for(int floor = 0; floor < 4; floor++) {
		for(int button = 0; button < 3; button++) {
			queue[floor][button] = 0;
		}
	}
}


int queue_is_order(elev_button_type_t button, int floor) {

	if(queue[floor][button] == 1) {
		return 1;
	}

	return 0;
}

int queue_elev_stop(int floor, int dir){

	if ((queue_is_order(BUTTON_CALL_UP, floor) == 1) && dir == 1){
		return 1;
	} 
	else if ((queue_is_order(BUTTON_CALL_DOWN, floor) == 1) && dir == -1){
		return 1;
	}
	else if (queue_is_order(BUTTON_COMMAND, floor) == 1){
		return 1;
	}

	return 0;
}


int queue_is_empty(){

	for(int floor = 0; floor < 4; floor++) {
		for(int button = 0; button < 3; button++) {
			if(queue[floor][button] == 1) {
				return 0;
			}
		}
	}
	return 1;
}	

void queue_print (){

	for(int floor = 0; floor < 4; floor++) {
		for(int button = 0; button < 3; button++) {
			printf("%d", queue[floor][button]);
		}
		printf("\n");
	}
}



