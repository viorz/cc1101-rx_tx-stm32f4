#ifndef __APP_CC_H__
#define __APP_CC_H__

#include "main.h"
#include "gpio.h"
#include "CC1101.h"
#include "usart.h"

#define BLUE_LED_L() HAL_GPIO_WritePin(Led_blue_GPIO_Port,Led_blue_Pin,GPIO_PIN_RESET)
#define BLUE_LED_H() HAL_GPIO_WritePin(Led_blue_GPIO_Port,Led_blue_Pin,GPIO_PIN_SET)


void start_init(void);
void run_App(void);

#endif
