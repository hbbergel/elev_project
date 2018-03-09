#include "elev.h"
#include "io.h"
#include "fsm.h"
#include "timer.h"
#include "queue.h"
#include <stdio.h>

//Vi har valgt å implementere ved hjelp av FSM. Vi har 4 states vi bruker: IDLE(heisen er ledig), RUNNING(heisen betjener en bestilling),
//STOP(stopp-knappen har blitt trykket inn) og DOOR-OPEN(døren er åpen). NONE brukes bare helt i starten. Vi tenker det kan oppstå
//5 ulike hendelser: fsm_buttons_pressed, fsm_floor_reached, fsm_stop_pressed, fsm_timeout og fsm_elev_init. Disse hendelsene
//kan forandre states og få heisen til å gjøre riktige oppgaver avhengig av state, posisjon, retning på heis osv..
//Ved kompilering kan det oppstå noen "warnings", men vi har spurt utallige studasser om det og alle sier at vi skal ignorere disse for
//ingen kan se at det er noen feil som skal gi de warningene i koden. 



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




        	// Hvis en knapp blir trykket inn.
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

        //Hopper inn hvis det har gått tre sekunder etter timer ble satt.
        if (timer_check_time() == 1) {
        	fsm_timeout();
        }
        
        //Stopp-knappen er sluppet og heisen gjøres klar til bruk igjen.
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
