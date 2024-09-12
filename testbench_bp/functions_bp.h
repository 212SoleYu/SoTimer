/*
 * File name: functions_bp.h
 * Date: 2024-03-11
 * Descriptioin: This file just declares the testbenches with breakpoints setted manually for other files to call.
 */

#ifndef _FUNCTIONS_BP_H
#define _FUNCTIONS_BP_H


/**********************************************************************************************************************/

/*
 * Function name: testbench_0
 * Description: 用于测试的程序0，包括ADC采样和一段乘法和冒泡排序算法
 * Input: None.
 * Output: None.
 * Return: None.
 */
void testbench_0();

/*
 * Function name: testbench_1
 * Description: 用于测试的程序1，调用了MSP430内置模块中的CRC和AES
 * Input: None.
 * Output: None.
 * Return: None.
 */
void testbench_1();

/*
 * Function name: testbench_2
 * Description: 用于测试的程序2，包含了通信、DMA与一段矩阵卷积操作
 */
void testbench_2();

/*
 * Function name: testbench_3
 * Description: 用于测试的程序3，包含DIJ算法
 */
void testbench_3();

/*
 * Function name: testbench_4
 * Description: 用于测试的程序4，包含了一个单块的SHA256哈希函数
 */
void testbench_4();

/*
 * Function name: testbench_5
 * Description: 用于测试的程序5，模拟了一次一层递归的strassen矩阵乘法，本质上是几组矩阵加法和乘法的组合
 */
void testbench_5();

/*
 * Function name: testbench_6
 * Description: 用于测试的程序6，包含了五种不同的bitcount的算法
 */
void testbench_6();

/**********************************************************************************************************************/

#endif
