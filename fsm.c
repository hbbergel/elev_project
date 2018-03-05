#include "elev.h"
#include "fsm.h"
#include "timer.h"
#include "queue.h"
#include <stdio.h>




static elev_state state = NONE;

static int dir;



void fsm_buttons_pressed(elev_button_type_t button, int floor) {

	int current_floor = elev_get_floor_sensor_signal();

	switch(state){

		case IDLE:
			queue_add_to_queue(button, floor);
			elev_set_button_lamp(button, floor, 1);
			if(current_floor < floor) {
				elev_set_motor_direction(DIRN_UP);
				dir = 1;
				state = RUNNING;
			}
			else if(current_floor > floor) {
				elev_set_motor_direction(DIRN_DOWN);
				dir = -1;
				state = RUNNING;
			}
			break;

		case RUNNING:
			elev_set_button_lamp(button, floor, 1);
			queue_add_to_queue(button, floor);
			break;

		case STOP:
			printf("Stop-button is pressed!");
			break;

		case DOOR_OPEN:
			elev_set_button_lamp(button, floor, 1);
			queue_add_to_queue(button, floor);
			break;
	}


}


void fsm_floor_reached(int floor) {

	switch(state){

		case IDLE:
	
			break;


//skal jeg stoppe, slette fra kø her, fjerne lys?
		case RUNNING:
			elev_set_floor_indicator(floor);
			if (queue_elev_stop(floor, dir) == 1){
				elev_set_motor_direction(DIRN_STOP);
				timer_start_timer();
				elev_set_door_open_lamp(1);
				state = DOOR_OPEN;
			}
			break;

//stop knappen
		case STOP:
			elev_set_floor_indicator(floor);
			elev_set_door_open_lamp(1);
			break;
		
		case DOOR_OPEN:
			printf("Something wrong fsm_floor_reached case door_open\n");
			break;
	}

} 


void fsm_stop_pressed() {

	switch(state){
		case IDLE:
			elev_set_stop_lamp(1);
			queue_remove_all_orders();
			state = STOP;
			break;

		case RUNNING:
			elev_set_stop_lamp(1);
			elev_set_motor_direction(0);
			queue_remove_all_orders();
			state = STOP;
			break;

		case STOP:
			printf("Error, already in STOP. fsm_stop_pressed()\n");
			break;

		case DOOR_OPEN:
			elev_set_stop_lamp(1);
			queue_remove_all_orders();
			state = STOP;
			break;
	}

}


void fsm_timeout() {
	int current_floor = elev_get_floor_sensor_signal();

	switch(state){
		case IDLE:
			printf("Error. IDLE, fsm_timeout()\n");
			break;

		case RUNNING:
			printf("Error. RUNNING, fsm_timeout()\n");
			break;

		case STOP:
			printf("Stop state.\n");
			break;

		case DOOR_OPEN:
			elev_set_door_open_lamp(0);
			if (queue_is_empty() == 1){
				state = IDLE;
			}
			else if((queue_is_empty() == 0) && (dir == 1) && current_floor != 3){
				elev_set_motor_direction(DIRN_UP);
				state = RUNNING;
				dir = 1;
			}
			else if((queue_is_empty() == 0) && (dir == -1) && current_floor != 0){
				elev_set_motor_direction(DIRN_DOWN);
				state = RUNNING;
				dir = -1;
			}
			break;
	}
}


int fsm_elev_init() {

	printf("Initialize elevator\n");


	while (elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(DIRN_UP);
		dir = 1;

	}

	elev_set_motor_direction(DIRN_STOP);

	state = IDLE;

	return 1;
}

elev_state fsm_get_state() {
	return state;
}