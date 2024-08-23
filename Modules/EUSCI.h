/*
 * File name��UART.h
 * Date��2024-03-21
 * Description�����ڳ�ʼ��ͨ��ģ�飬Ŀǰֻ��UARTģ�飬�������������ķ�ʽ
 */

#ifndef _EUSCI_H_
#define _EUSCI_H_


#include <msp430.h>
#include <Modules/driver_include.h>


/*
 * Function name: UART_init_lib
 * Description: ���ڽ�EUSCIģ���ʼ��ΪUARTģ��ĺ�������ʼ������ģ��A0��A1
 * Input:   number - ��ʾ��ʼ��ģ��ĸ�����1����ֻ��A0��2����ֻ��A1��3����ȫ����ʼ��
 *          baud_model - ��ʾԤ���Ĳ�����ѡ��0����9600��1����115200
 * Output: None.
 * Return: None.
 */
void UART_init_lib(uint16_t number,uint16_t baud_model);

/*
 * Function name: EUSCI_init
 * Description: ��ʼ��UARTģ�飬
 * Input:   UART_mode - ����ѡ��UART�Ĺ���Ƶ��
 *          A0_flag - Ϊ1ʱ����A0ģ��
 *          A1_flag - Ϊ1ʱ����A1ģ��
 *          Baud_rate - ѡȡ����Ҫ�Ĳ�����
 */
void EUSCI_init(int UART_mode, int A0_flag, int A1_flag, int Baud_rate);

#endif
