#include "main.h"
#include "input_processing.h"
#include "input_reading.h"
#include "output_display.h"

enum ButtonState { BUTTON_RELEASED , BUTTON_PRESSED , BUTTON_PRESSED_MORE_THAN_1_SECOND } ;
enum ButtonState buttonState[3] = {BUTTON_RELEASED,  BUTTON_RELEASED, BUTTON_RELEASED};
int time_duration = 0;
int mode = 0;
int Mode() {
	return mode;
}
void increase_mode(){
	if(mode > 3 ) mode = 1;
	else mode++;
}
void reset_mode(){ //reset time_duration after transform to a mode and reset timer each when we didn't complete time's run cycle at mode 1
	for(int i = 0; i < 3 ; i++){
		horizontal_arr[i] = arr2[i];
		vertical_arr[i] = arr2[i];
	}
	time_duration = 0;
}
void fsm_for_input_processing ( void ){
	for(int i = 0 ; i < N0_OF_BUTTONS; i++){
		switch ( buttonState[i] ){
			case BUTTON_RELEASED :
				if( is_button_pressed (i)){
					buttonState[i] = BUTTON_PRESSED ;
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, RESET);
					// INCREASE VALUE OF PORT A BY ONE UNIT
					if(i == 0){ //first button.
						increase_mode();
						if(mode > 1){
							reset_mode();
							display7SEG(time_duration%10, GPIOA, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14);
							display7SEG(time_duration/10, GPIOA, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7);
						}
					}
					else if(i == 1){ //second button.
						if(time_duration < 100)time_duration++;
						else time_duration = 0;
						display7SEG(time_duration%10, GPIOA, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14);
						display7SEG(time_duration/10, GPIOA, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7);
					}
					else if(i == 2){ //third button.
						if(mode > 1){
							arr2[mode - 2] = time_duration + 1;
						}
					}
				}
				break ;
			case BUTTON_PRESSED :
				if (! is_button_pressed (i)){
					buttonState[i] = BUTTON_RELEASED ;
					 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, SET);
				} else {
					if( is_button_pressed_1s (i) )
						buttonState[i] = BUTTON_PRESSED_MORE_THAN_1_SECOND ;
				}
				break ;
			case BUTTON_PRESSED_MORE_THAN_1_SECOND :
				if (! is_button_pressed (i)){
					buttonState[i] = BUTTON_RELEASED;
					 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, SET);
				}
				// todo
				break ;
			}
	}
	Mode();
}

