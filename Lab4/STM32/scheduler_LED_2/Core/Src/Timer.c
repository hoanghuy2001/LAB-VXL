#include "Timer.h"
#include "main.h"
int timer0_counter = 0;
int timer0_flag = 0;
int timer1_counter = 0;
int timer1_flag = 0;
//setTimer0 begin processing
void TimerInit(void) {
	setTimer0(10);
	setTimer1(10);
}

void setTimer0 (unsigned int duration) {
	timer0_counter = duration / TIMER_INTERUPT ;
	timer0_flag = 0;
}
void setTimer1 (unsigned int duration) {
	timer1_counter = duration / TIMER_INTERUPT ;
	timer1_flag = 0;
}
void timer_run () {
	if( timer0_counter > 0) {
		timer0_counter --;
		if(timer0_counter == 0) {
			timer0_flag = 1;
		}
	}
	if( timer1_counter > 0) {
			timer1_counter --;
			if(timer1_counter == 0) {
				timer1_flag = 1;
			}
		}

}
void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim ){
	SCH_Update();
	timer_run();
}
