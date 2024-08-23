/*
 * File name：ADC.h
 * Description： 用于声明与ADC有关的函数的宏定义
 * Date：2024-03-21
 */

#ifndef _ADC_H
#define _ADC_H

#include<Modules/driver_include.h>


#define ADC_INPUT_SOURCE                ADC12_B_INPUT_A2                    // P1.2 A2, P1SEL1.x = 1, P1SEL0.x = 1
#define ADC_CHANNEL_INPUT_PORT          GPIO_PORT_P1
#define ADC_CHANNEL_INPUT_PIN           GPIO_PIN2
#define ADC_CHANNEL_INPUT_FUNCTION      GPIO_TERNARY_MODULE_FUNCTION

#define REF_1_2V                        1
#define REF_2_0V                        2
#define REF_2_5V                        3


void ref_init(unsigned int mode);

void adc_init();

#endif

