/*
 * File name: handwritten_cpu.c
 * Date: 2024-03-12
 * Description: 用于运行的例程1.
 */

#include<testbench_bp/header.h>


// 划分任务时要注意BUF_LENGTH长度： 256
void testbench_1()
{

    set_breakpoint;
    __no_operation();
    phase_update;
    // phase 1
    unsigned int i,j;
    uint16_t volt = 0x7f;
    for(i =0;i<BUF_LENGTH;i++)
    {
//        ADC12CTL0 |= ADC12SC;                        // Start conversion-software trigger
//        while (!(ADC12IFGR0 & BIT0)) {/* WAIT */}
//        volt = ADC12MEM0;
        Volt[i] = volt;

        // 256长度采样的一半中断一次
        if((i&0xFF) == 0x7F)
            set_breakpoint;
    }

    set_breakpoint;                             // 剩余的一半结束后打个断点

    __no_operation();
    // phase 2
    phase_update;                               // 进入第二阶段

    for(i = 0; i<BUF_LENGTH-1;i++)
    {
        Volt[i] = Volt[i] * Volt[i+1];
        if((i&0xFF) == 0x7F)                    // 256采样的一半结束后打个断点
             set_breakpoint;
    }

    // 剩余部分打个断点
    set_breakpoint;
    __no_operation();
    phase_update;
    // phase 3
    for(i = 0; i<BUF_LENGTH;i++)
    {
        for(j = 0;j<BUF_LENGTH-i-1;j++)
        {
            if(Volt[j]>Volt[j+1])
            {
                volt = Volt[j];
                Volt[j] = Volt[j+1];
                Volt[j+1] = volt;
            }
        }
        set_breakpoint;
    }
    set_breakpoint;
    __no_operation();
    phase_update;
}

