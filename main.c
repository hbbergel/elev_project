#include "elev.h"
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

    int floor = elev_get_floor_sensor_signal(); 
    int previous_floor = -1;



    while (1) {

       if(floor != -1) {

            fsm_floor_reached(floor);
        }
        else if(1) { /*overvåke om en knapp blir trykket*/
            /*fsm_buttons_pressed()*/
        }


        


        


    }

    return 0;
}
