/*
 * File name: initialization.h
 * Date: 2024-03-21
 * Description: ����ϵͳ�Ļ�����ʼ����������������Ҫ����ʱ�ӺͶ�ʱ����ͨѶģ��ʹ�����ģ��ᵥ�����г�ʼ����
 */


#ifndef _INITIALIZATION_H
#define _INITIALIZATION_H

#include <Modules/driver_include.h>


/*
 * Function name: power_on_init()
 * Description: ��ʼ��ͨ�ö˿ڡ������Լ��رյ͹������ƺͿ��Ź�����
 */
void power_on_init();

/*
 * Function name: clock_sys_init()
 * Description: ��ʼ��ʱ�ӣ������趨����Ƶ�ʡ�SMCLK��MCLK���������ʱ��ACLK
 */
void clock_sys_init(int freq_mode, int SMCLK_divider, int ACLK_divider);

/*
 * Function name:timer_init()
 * Description: ��ʼ��������ʱ��TimerA0��TimerA1,ǰ�����ڴ������������������ڲ����׶εļ�ʱ���ߺ�����ʱ�����߽��趨ΪΪ����ģʽ
 */
void timer_init();

/*
 * Function name��button_init()
 * Description����ʼ����������������Ϊ�������貢ʹ��
 */
void button_init();

/*
 * Function name��DMA_init_lib()
 * Description�����ڳ�ʼ��DMA��أ���ʼ��ַ�ͽ�����ַ����Ҫ���������λ��ȷ����
 */
void DMA_init_lib();

#endif
