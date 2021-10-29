
#ifndef INC_OUTPUT_DISPLAY_H_
#define INC_OUTPUT_DISPLAY_H_

int vertical_arr[3];
int horizontal_arr[3];
int arr2[3];
void display7SEG(int num,GPIO_TypeDef* GPIO1, uint16_t GPIO_PIN0,
				 uint16_t GPIO_PIN1, uint16_t GPIO_PIN2, uint16_t GPIO_PIN3,
				 uint16_t GPIO_PIN4, uint16_t GPIO_PIN5, uint16_t GPIO_PIN6);
void traffic_light(uint16_t GPIO_Pin1,uint16_t GPIO_Pin2,uint16_t GPIO_Pin3,int count, int arr[]);
void traffic_light_4(int count_vled,int count_hled);
void mode_1();
void mode_2();
void mode_3();
void mode_4();
void default_setting(void);
#endif /* INC_OUTPUT_DISPLAY_H_ */
