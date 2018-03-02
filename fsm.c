#include "elev.h"
#include "fsm.h"
#include "queue.h"
#include "timer.h"
#include <stdio.h>



typedef enum elev_state{IDLE, RUNNING, STOP, DOOR_OPEN, NONE} elev_state;

static elev_state state = NONE;

static int dir;

//hvor skal denne stå, får bare feilmelding når det kompileres
/*static int current_floor = elev_get_floor_sensor_signal();*/



void fsm_buttons_pressed(elev_button_type_t button, int floor) {

	switch(state){

		case IDLE:
			queue_add_to_queue(button, floor);
			elev_set_button_lamp(button, floor, 1);
			if(current_floor < floor) {
				elev_set_motor_direction(DIRN_UP);
				state = RUNNING;
			}
			else if(current_floor > floor) {
				elev_set_motor_direction(DIRN_DOWN);
				state = RUNNING;
			}
			break;

		case RUNNING:
			elev_set_button_lamp(button, floor, 1);
			queue_add_to_queue(button, floor);
			break;

		case STOP:
			printf("Stop-button is pressed!");

		case DOOR_OPEN:
			elev_set_button_lamp(button, floor, 1);
			queue_add_to_queue(button, floor);
	}


}


void fsm_floor_reached() {

	switch(state){

		case IDLE:
			printf("Something went wrong fsm_floor_reached!\n");
			break;


//skal jeg stoppe, slette fra kø her, fjerne lys?
		case RUNNING:
			elev_set_floor_indicator(current_floor);
			if (queue_elev_stop(current_floor, dir) == 1){
				elev_set_motor_direction(DIRN_STOP);
				timer_start_timer();
				elev_set_door_open_lamp(1);
				state = DOOR_OPEN;
			}
			break;

//stop knappen
		case STOP:
			elev_set_floor_indicator(current_floor);
			elev_set_door_open_lamp(1);
			break;
		
		case DOOR_OPEN:
			printf("Something wrong fsm_floor_reached case door_open\n");
			break;
	}

} 


void fsm_stop_pressed() {


	state = IDLE;

}


void fsm_timeout() {


}


int fsm_elev_init() {

	printf("Initialize elevator\n");

	if (elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(DIRN_UP);

	}

	state = IDLE;

	return 1;
}