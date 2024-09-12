/*
 * File name：UART.h
 * Date：2024-03-21
 * Description：用于初始化通信模块，目前只有UART模块，后续补充其他的方式
 */

#ifndef _EUSCI_H_
#define _EUSCI_H_


#include <msp430.h>
#include <Modules/driver_include.h>

// use EUSCI_init instead
void UART_init_lib(uint16_t number,uint16_t baud_model);

/*
 * Function name: EUSCI_init
 * Description: 初始化UART模块，
 * Input:   UART_mode - 用于选择UART的工作频率
 *          A0_flag - 为1时激活A0模块
 *          A1_flag - 为1时激活A1模块
 *          Baud_rate - 选取所需要的波特率
 */
void EUSCI_init(int UART_mode, int A0_flag, int A1_flag, int Baud_rate);

#endif
