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

    
    //int previous_floor = -1;


    while (1) {

    	int floor = elev_get_floor_sensor_signal(); 

      	if(floor != -1) {

            fsm_floor_reached(floor);
        }

        if(elev_get_button_signal(BUTTON_CALL_UP, 0) == 1) {
        	fsm_buttons_pressed(BUTTON_CALL_UP, 0);
        }
        else if(elev_get_button_signal(BUTTON_COMMAND, 0) == 1) {
        	fsm_buttons_pressed(BUTTON_COMMAND, 0);
        }
        else if(elev_get_button_signal(BUTTON_CALL_UP, 1) == 1) {
        	fsm_buttons_pressed(BUTTON_CALL_UP, 1);
        }
        else if(elev_get_button_signal(BUTTON_CALL_DOWN, 1) == 1) {
        	fsm_buttons_pressed(BUTTON_CALL_DOWN, 1);
        }
        else if(elev_get_button_signal(BUTTON_COMMAND, 1) == 1) {
        	fsm_buttons_pressed(BUTTON_COMMAND, 1);
        }
        else if(elev_get_button_signal(BUTTON_CALL_UP, 2) == 1){
        	fsm_buttons_pressed(BUTTON_CALL_UP, 2);
        }
        else if(elev_get_button_signal(BUTTON_CALL_DOWN, 2) == 1) {
        	fsm_buttons_pressed(BUTTON_CALL_DOWN, 2);
        }
        else if(elev_get_button_signal(BUTTON_COMMAND, 2) == 1) {
        	fsm_buttons_pressed(BUTTON_COMMAND, 2);
        }
        else if(elev_get_button_signal(BUTTON_CALL_DOWN, 3) == 1) {
        	fsm_buttons_pressed(BUTTON_CALL_DOWN, 3);
        }
        else if(elev_get_button_signal(BUTTON_COMMAND, 3) == 1) {
        	fsm_buttons_pressed(BUTTON_COMMAND, 3);
        }

        if (timer_check_time() == 1){
        	fsm_timeout();
        }

        if (elev_get_stop_signal() == 1){
        	fsm_stop_pressed();
        }

                
        if ((elev_get_stop_signal() != 1) && fsm_get_state() == STOP){
        	fsm_timeout();
        }

        


    }

    return 0;
}
