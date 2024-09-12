#ifndef INITPARAM_H
#define INITPARAM_H
/*
 * List all the params to init the modules, which can be changed.
 */

#include <Modules/driver_include.h>

// clock system params
#define WORK_FREQUENCY_1                    0
#define WORK_FREQUENCY_3_33                 1
#define WORK_FREQUENCY_4                    2
#define WORK_FREQUENCY_6_67                 3
#define WORK_FREQUENCY_8                    4
#define WORK_FREQUENCY_16                   5


extern int CLK_SYS_params[6][2];


// UART params
extern EUSCI_A_UART_initParam UARTlist[6][2];

#endif
