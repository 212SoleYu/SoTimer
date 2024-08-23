#ifndef _LED_BUTTON_H
#define _LED_BUTTON_H

#include <Modules/driver_include.h>

// LED
#define init_left_LED                P1DIR |= BIT0
#define turn_on_left_LED             P1OUT |= BIT0
#define turn_off_left_LED            P1OUT &= ~(BIT0)
#define switch_left_LED              P1OUT ^= BIT0

#define init_right_LED               P1DIR |= BIT1
#define turn_on_right_LED            P1OUT |= BIT1
#define turn_off_right_LED            P1OUT &= ~(BIT1)
#define switch_right_LED              P1OUT ^= BIT1

// Button

#define init_left_button                GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN6)
#define disable_left_button             GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN6); \
                                        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN6)
#define check_left_button               (GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN6) == GPIO_INPUT_PIN_LOW)

#endif
