
#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "ctrlTask.h"
#include "main.h"


#define TIMER_INTERUPT 10 // 10 miliseconds
#define Timer_Task1 	500
#define Timer_Task2 	1000
#define Timer_Task3 	1500
#define Timer_Task4 	2000
#define Timer_Task5 	2500
int timer0_counter;
int timer0_flag;
int timer1_counter;
int timer1_flag;
void TimerInit(void);
void setTimer0 (unsigned int duration);
void setTimer1 (unsigned int duration);
void timer_run ();
#endif /* INC_TIMER_H_ */
