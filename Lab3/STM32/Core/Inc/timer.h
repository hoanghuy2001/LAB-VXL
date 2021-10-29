#ifndef INC_TIMER_H_
#define INC_TIMER_H_
#include "main.h"
#define TIMER_INTERUPT 		10 	// 10miliseconds

#define TIMER_1s  			1000 //1000miliseconds = 1seconds
static int count_1s = TIMER_1s / TIMER_INTERUPT;

#define TIMER_50ms  		50 //50miliseconds
static int count_50ms = TIMER_50ms / TIMER_INTERUPT;

#define TIMER_blinking  		500 //500miliseconds = 0.5seconds
static int count_500ms = TIMER_blinking / TIMER_INTERUPT;
#endif /* INC_TIMER_H_ */
