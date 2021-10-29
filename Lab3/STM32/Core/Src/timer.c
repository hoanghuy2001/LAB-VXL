#include "main.h"
#include "timer.h"
#include "output_display.h"
#include "input_reading.h"
int count = 0;
int mode_button;
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim ){
		count--;
		button_reading();
		mode_button = Mode();
		if(count <= 0){
			if(mode_button == 1){
				mode_1();
				count = count_1s;
			}
			if(mode_button == 2){
				mode_2();
				count = count_500ms;
			}
			if(mode_button == 3){
				mode_3();
				count = count_500ms;
			}
			if(mode_button == 4){
				mode_4();
				count = count_500ms;
			}
		}
}

