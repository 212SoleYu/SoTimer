/*
 * File name: initialization.h
 * Date: 2024-03-21
 * Description: 对于系统的基本初始化函数的声明，主要包括时钟和定时器，通讯模块和传感器模块会单独进行初始化。
 */


#ifndef _INITIALIZATION_H
#define _INITIALIZATION_H

#include <Modules/driver_include.h>


/*
 * Function name: power_on_init()
 * Description: 初始化通用端口、按键以及关闭低功耗限制和看门狗限制
 */
void power_on_init();

/*
 * Function name: clock_sys_init()
 * Description: 初始化时钟，包括设定工作频率、SMCLK、MCLK和外设低速时钟ACLK
 */
void clock_sys_init(int freq_mode, int SMCLK_divider, int ACLK_divider);

/*
 * Function name:timer_init()
 * Description: 初始化两个计时器TimerA0和TimerA1,前者用于传感器采样，后者用于测量阶段的计时或者后续计时，二者皆设定为为连续模式
 */
void timer_init();

/*
 * Function name：button_init()
 * Description：初始化两个按键，设置为上拉电阻并使能
 */
void button_init();

/*
 * Function name：DMA_init_lib()
 * Description：用于初始化DMA相关，起始地址和结束地址在需要触发传输的位置确定。
 */
void DMA_init_lib();

#endif
