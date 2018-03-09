#include "elev.h"
#include "fsm.h"
#include "timer.h"
#include "queue.h"
#include <stdio.h>


static elev_state state = NONE;

//Variabel som holder styr på sist retning heisen kjørte i.
static int dir;


//Når er knapp blir trykket inn blir denne funksjonen kjørt. Avhengig av state blir det lagt til i kø, lagt til i kø og sette heis i bevegelse eller ignorering av knappetrykk.
void fsm_buttons_pressed(elev_button_type_t button, int floor, int prev_floor) {

	int current_floor = elev_get_floor_sensor_signal();

	switch(state){

		case IDLE:
			queue_add_to_queue(button, floor);
			if(current_floor == floor) {
				elev_set_door_open_lamp(1);
				timer_start_timer();
			}
			else if(current_floor < floor && current_floor != -1) {
				elev_set_motor_direction(DIRN_UP);
				dir = 1;
				state = RUNNING;
			}
			else if(current_floor > floor && current_floor != -1) {
				elev_set_motor_direction(DIRN_DOWN);
				dir = -1;
				state = RUNNING;
			}
			else if(current_floor == -1){
				
				if((floor < prev_floor) || (floor == prev_floor && dir == 1)){
					elev_set_motor_direction(DIRN_DOWN);
					dir = -1;
					state = RUNNING;
				}
				else if((floor > prev_floor) ||(floor == prev_floor && dir == -1)){
					elev_set_motor_direction(DIRN_UP);
					dir = 1;
					state = RUNNING;
				}
			}	
		break;

		case RUNNING:
			queue_add_to_queue(button, floor);
			break;

		case STOP:
			printf("Stop-button is pressed!");
			break;

		case DOOR_OPEN:
			queue_add_to_queue(button, floor);
			break;
	}


}

//Hver gang heisen passerer en etasje blir denne funksjonen kjørt. Tar beslutning om heisen skal stoppe og betjene en bestilling eller fortsette.
void fsm_floor_reached(int floor) {

	switch(state){

		case IDLE:
			
			queue_remove_from_queue(floor, dir);
	
			break;



		case RUNNING:
			
			elev_set_floor_indicator(floor);
			if (queue_elev_stop(floor, dir) == 1){
				elev_set_motor_direction(DIRN_STOP);
				timer_start_timer();
				elev_set_door_open_lamp(1);
				queue_remove_from_queue(floor,dir);
				state = DOOR_OPEN;
			}
			break;


		case STOP:

			elev_set_floor_indicator(floor);
			elev_set_door_open_lamp(1);
			break;
		
		case DOOR_OPEN:
			
						
			break;
	}

} 

//Hvis stopp-knappen blir trykket inn hopper koden inn her og tar hensyn til krav for stopp-knappen.
void fsm_stop_pressed() {

	switch(state){
		case IDLE:
			elev_set_stop_lamp(1);
			queue_remove_all_orders();
			elev_set_door_open_lamp(1);
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

//Etter tre sekunder har gått er det her evt. dør lukkes og heisen gjøres klar til å betjene neste bestilling.
void fsm_timeout() {
	int current_floor = elev_get_floor_sensor_signal();

	switch(state){
		case IDLE:
			elev_set_door_open_lamp(0);
			break;

		case RUNNING:
			printf("Error. RUNNING, fsm_timeout()\n");
			break;

		case STOP:
			state = IDLE;
			if(timer_get_start_time() == 0) {
				timer_start_timer();
				
			}
			break;

		case DOOR_OPEN:
			elev_set_door_open_lamp(0);
						
			if (queue_is_empty() == 1){
				state = IDLE;
			}

            else if((queue_is_empty() == 0) && queue_which_direction(dir, current_floor) == 1){
				elev_set_motor_direction(DIRN_UP);
				state = RUNNING;
				dir = 1;
			}
			else if((queue_is_empty() == 0) && queue_which_direction(dir, current_floor) == -1){
				elev_set_motor_direction(DIRN_DOWN);
				state = RUNNING;
				dir = -1;
			}

			
			break;
	}
}

//Initialiserer heisen.
int fsm_elev_init() {

	printf("Initialize elevator\n");


	while (elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(DIRN_UP);
		dir = 1;

	}

	elev_set_motor_direction(DIRN_STOP);
	elev_set_floor_indicator(elev_get_floor_sensor_signal());

	state = IDLE;

	return 1;
}

//Returnerer staten heisen er i.
elev_state fsm_get_state() {
	return state;
}
