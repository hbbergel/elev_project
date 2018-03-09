#include "timer.h"
#include <time.h>

static int start_time = 0;

//Legger til start-tid til start_time.
void timer_start_timer() {

	start_time = time(NULL);
}

//Sjekker når current_time er 3 sekunder etter start_time.
int timer_check_time() {

	int current_time = time(NULL);

	if((current_time - start_time) == 3) {

		start_time = 0;
		return 1;
	}
	return 0;
}

int timer_get_start_time() {
	return start_time;
}

