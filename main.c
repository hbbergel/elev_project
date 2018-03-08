#include "elev.h"
#include "io.h"
#include "fsm.h"
#include "timer.h"
#include "queue.h"
#include <stdio.h>




int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    

    if (!fsm_elev_init()) {
        printf("Unable to initialize elevator\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");




    while (1) {

    	int floor = elev_get_floor_sensor_signal(); 
    	int prev_floor;

      	if(floor != -1) {

            fsm_floor_reached(floor);
            prev_floor = floor;
        }

        		/// KUN EM. STOP MELLOM ETG
        if(floor == -1 && fsm_get_state() == IDLE) {
        	printf("her er det feil\n");
        	if(elev_get_button_signal(BUTTON_CALL_UP, 0) == 1) {
        	fsm_buttons_pressed(BUTTON_CALL_UP, 0, prev_floor);
	        }
	        else if(elev_get_button_signal(BUTTON_COMMAND, 0) == 1) {
	        	fsm_buttons_pressed(BUTTON_COMMAND, 0, prev_floor);
	        }
	        else if(elev_get_button_signal(BUTTON_CALL_UP, 1) == 1) {
	        	fsm_buttons_pressed(BUTTON_CALL_UP, 1, prev_floor);
	        }
	        else if(elev_get_button_signal(BUTTON_CALL_DOWN, 1) == 1) {
	        	fsm_buttons_pressed(BUTTON_CALL_DOWN, 1, prev_floor);
	        }
	        else if(elev_get_button_signal(BUTTON_COMMAND, 1) == 1) {
	        	fsm_buttons_pressed(BUTTON_COMMAND, 1, prev_floor);
	        }
	        else if(elev_get_button_signal(BUTTON_CALL_UP, 2) == 1) {
	        	fsm_buttons_pressed(BUTTON_CALL_UP, 2, prev_floor);
	        }
	        else if(elev_get_button_signal(BUTTON_CALL_DOWN, 2) == 1) {
	        	fsm_buttons_pressed(BUTTON_CALL_DOWN, 2, prev_floor);
	        }
	        else if(elev_get_button_signal(BUTTON_COMMAND, 2) == 1) {
	        	fsm_buttons_pressed(BUTTON_COMMAND, 2, prev_floor);
	        }
	        else if(elev_get_button_signal(BUTTON_CALL_DOWN, 3) == 1) {
	        	fsm_buttons_pressed(BUTTON_CALL_DOWN, 3, prev_floor);
	        }
	        else if(elev_get_button_signal(BUTTON_COMMAND, 3) == 1) {
	        	fsm_buttons_pressed(BUTTON_COMMAND, 3, prev_floor);
	        }
        }




        	// alle andre cases
        if(elev_get_button_signal(BUTTON_CALL_UP, 0) == 1) {
        	fsm_buttons_pressed(BUTTON_CALL_UP, 0, prev_floor);
        }
        else if(elev_get_button_signal(BUTTON_COMMAND, 0) == 1) {
        	fsm_buttons_pressed(BUTTON_COMMAND, 0, prev_floor);
        }
        else if(elev_get_button_signal(BUTTON_CALL_UP, 1) == 1) {
        	fsm_buttons_pressed(BUTTON_CALL_UP, 1, prev_floor);
        }
        else if(elev_get_button_signal(BUTTON_CALL_DOWN, 1) == 1) {
        	fsm_buttons_pressed(BUTTON_CALL_DOWN, 1, prev_floor);
        }
        else if(elev_get_button_signal(BUTTON_COMMAND, 1) == 1) {
        	fsm_buttons_pressed(BUTTON_COMMAND, 1, prev_floor);
        }
        else if(elev_get_button_signal(BUTTON_CALL_UP, 2) == 1) {
        	fsm_buttons_pressed(BUTTON_CALL_UP, 2, prev_floor);
        }
        else if(elev_get_button_signal(BUTTON_CALL_DOWN, 2) == 1) {
        	fsm_buttons_pressed(BUTTON_CALL_DOWN, 2, prev_floor);
        }
        else if(elev_get_button_signal(BUTTON_COMMAND, 2) == 1) {
        	fsm_buttons_pressed(BUTTON_COMMAND, 2, prev_floor);
        }
        else if(elev_get_button_signal(BUTTON_CALL_DOWN, 3) == 1) {
        	fsm_buttons_pressed(BUTTON_CALL_DOWN, 3, prev_floor);
        }
        else if(elev_get_button_signal(BUTTON_COMMAND, 3) == 1) {
        	fsm_buttons_pressed(BUTTON_COMMAND, 3, prev_floor);
        }


        if (timer_check_time() == 1) {
        	fsm_timeout();
        }

        if(elev_get_stop_signal() == 0 && fsm_get_state() == STOP) {
        	fsm_timeout();
        	elev_set_stop_lamp(0);
        }

        if (elev_get_stop_signal() == 1) {
        	fsm_stop_pressed();
        }

               


    }

    return 0;
}
