#include "main.h"
#include "input_reading.h"
#include "output_display.h"

GPIO_PinState buttonBuffer [ N0_OF_BUTTONS ];
// we define two buffers for
GPIO_PinState debounceButtonBuffer1 [ N0_OF_BUTTONS ];
GPIO_PinState debounceButtonBuffer2 [ N0_OF_BUTTONS ];

uint16_t pinBuffer[N0_OF_BUTTONS];

// we define a flag for a button pressed more than 1 second
static uint8_t flagForButtonPress1s [ N0_OF_BUTTONS ];
// we define counter for automatically increasing the value
// after the button is pressed more than 1 second .
static uint16_t counterForButtonPress1s [ N0_OF_BUTTONS ];
void preprocessing(void){
	pinBuffer[0] = GPIO_PIN_13;
	pinBuffer[1] = GPIO_PIN_14;
	pinBuffer[2] = GPIO_PIN_15;
	default_setting();
	for(int i = 0 ; i < N0_OF_BUTTONS ; i++){
		debounceButtonBuffer1[i] = BUTTON_IS_RELEASED;
		debounceButtonBuffer2[i]= BUTTON_IS_RELEASED;
		buttonBuffer[i]= BUTTON_IS_RELEASED;
	}
}
int getButton(int index){
	return index;
}
void button_reading ( void ){
	for(int i = 0; i < N0_OF_BUTTONS; i++){
			debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
			debounceButtonBuffer1 [i] = HAL_GPIO_ReadPin (GPIOB, pinBuffer[i]);
			if(debounceButtonBuffer1 [i] == debounceButtonBuffer2 [i]){
				buttonBuffer [i] = debounceButtonBuffer1 [i];
			}
			if( buttonBuffer [i] == BUTTON_IS_PRESSED){
				if( counterForButtonPress1s [i] < DURATION_FOR_AUTO_INCREASING ){
					counterForButtonPress1s [i]++;
				}
				else {
					flagForButtonPress1s [i] = 1;
				}
			}
			else {
				counterForButtonPress1s [i] = 0;
				flagForButtonPress1s [i] = 0;
			}
		}
}
unsigned char is_button_pressed ( uint8_t index ){
	if( index >= N0_OF_BUTTONS ) return 0;
	return ( buttonBuffer [ index ] == BUTTON_IS_PRESSED );
}
unsigned char is_button_pressed_1s ( unsigned char index ){
	if( index >= N0_OF_BUTTONS ) return 0xff;
	return ( flagForButtonPress1s [ index ] == 1);
}
