/*
 * File name: functions_bp.h
 * Date: 2024-03-11
 * Descriptioin: This file just declares the testbenches with breakpoints setted manually for other files to call.
 */

#ifndef _FUNCTIONS_BP_H
#define _FUNCTIONS_BP_H


/**********************************************************************************************************************/

/*
 * Function name: testbench_1
 * Description: 用于测试的程序1，包括ADC采样和一段乘法和冒泡排序算法
 * Input: None.
 * Output: None.
 * Return: None.
 */
void testbench_1();

/*
 * Function name: testbench_2
 * Description: 用于测试的程序2，调用了MSP430内置模块中的CRC和AES
 * Input: None.
 * Output: None.
 * Return: None.
 */
void testbench_2();

/*
 * Function name: testbench_3
 * Description: 用于测试的程序3，包含了通信、DMA与一段矩阵卷积操作
 */
void testbench_3();







/**********************************************************************************************************************/

#endif
