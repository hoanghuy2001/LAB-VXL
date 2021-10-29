#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

//the buffer that the final result is stored after
# define N0_OF_BUTTONS 3

# define DURATION_FOR_AUTO_INCREASING 100
# define BUTTON_IS_PRESSED 		GPIO_PIN_RESET
# define BUTTON_IS_RELEASED 	GPIO_PIN_SET

void preprocessing(void);
void button_reading ( void );
int getButton (int index);
unsigned char is_button_pressed ( unsigned char index );
unsigned char is_button_pressed_1s ( unsigned char index );
#endif /* INC_INPUT_READING_H_ */
