/*
 * File name：UART.h
 * Date：2024-03-21
 * Description：用于初始化通信模块，目前只有UART模块，后续补充其他的方式
 */

#ifndef _EUSCI_H_
#define _EUSCI_H_


#include <msp430.h>
#include <Modules/driver_include.h>


/*
 * Function name: UART_init_lib
 * Description: 用于将EUSCI模块初始化为UART模块的函数，初始化两个模块A0和A1
 * Input:   number - 表示初始化模块的个数，1代表只有A0，2代表只有A1，3代表全部初始化
 *          baud_model - 表示预定的波特率选择，0代表9600而1代表115200
 * Output: None.
 * Return: None.
 */
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
