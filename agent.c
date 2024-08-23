/*
 *              计算过程中的单位制：
 *                      1. 电流： μA
 *                      2. 电压： mV
 *                      3. 功率： μW
 *                      4. 能量： μJ
 *                      5. 时间： ms
 */

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <main.h>
#include <math.h>
#include <Modules/driver_include.h>

#define TIMER_ROUTINE               5000
#define BACKUP_VOLTAGE              2600
#define RECOVERY_VOLTAGE            3200

/************************************************TA0中所用**************************************************************************/
#pragma PERSISTENT(time_on)
uint32_t time_on = 0;                                       // 记录开机时间计算结果
uint16_t time_overflow_flag = 0;                        // 计时器的溢出标志，每一次重启都需要设置为0，在低速时钟里被记录。
uint32_t time_off = 0;                                      // 预测的断电时间
uint32_t var;                                           // 电压测量值

// regression data for 1000uF
//static const float w1 = -0.50083057;
//static const float w2 = -0.54463161;
//static const float bias = 10.094598802589179;

// 470uF
static const float w1 = -0.52611847;
static const float w2 = -0.55975162;
static const float bias = 9.053817974072206;



// Bakup & Recovery
extern  uint8_t system_in_running;              // 标志位为1表示当前系统正在运行，反之正处在休眠或者断电状态
extern  uint8_t recovery_done = 0;                  // 标志位为1表示当前的语句是从recovery恢复后跳转到backup()的位置，不要再次进入低功耗

extern unsigned int first_running;

// 发送缓冲区
unsigned int i = 0;
#define SHUT_LENGTH         9
#define TRANS_LENGTH        1
uint8_t trans_buffer[TRANS_LENGTH] = {0x42};
uint8_t shut_buffer[SHUT_LENGTH] = {0x41,0,0,0,0,0,0,0,0};

inline uint32_t regression(uint32_t,uint32_t);


/************************************************TA4中所用**************************************************************************/

#pragma PERSISTENT(first_breakpoint_flag)
uint8_t first_breakpoint_flag = 1;                 // 标志第一次进入断点

extern  uint8_t task_number;                             // 标识当前程序

#pragma PERSISTENT(phase_index)
uint8_t phase_index = 0xFF;                           // 用于标识当前断点对应阶段

uint32_t last_time_record = 0;                          // 用于计算时间差值
//#pragma PERSISTENT(energy_consumption)
uint32_t energy_consumption = 0;                        // 开机期间直到第一次进入breakpoint这段初始化消耗的能量（累加计算得到），初始值设为1



/**********************************************************************************************************************************/

// power table, 0-2代表各个大的阶段的典型功率，3代表任务之间切换的间隙的典型功率。
const uint32_t cycle_cost[FREQUENCY_NUMBER][TASK_NUMBER][PHASE_NUMBER] = {
  {
   {378,378,378,378},
   {367,382,366,366},
   {363,366,360,360}
  },//1MHz
  {
    {676,703,675,675},
    {626,636,612,612},
    {636,630,608,608}
  },//3.33MHz
  {
   {742,766,700,700},
   {679,686,668,668},
   {687,669,657,657}
  },//4MHz
  {
    {1090,1136,1000,878},
    {991,1005,976,976},
    {1008,1008,912,912}
  },//6.67MHz
  {
    {1242,1272,1200, 945},
    {1089,1101,1084,1084},
    {1118,1118,1010,1010}
  },//8MHz
  {
    {1020,1020,1020,1020},
    {1020,1020,1020,1020},
    {1020,1020,1020,1020}
  }//16MHz
};



// 核心的中断函数
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Agent_ISR(void)
{
    if(first_running == 1)
    {
        __bic_SR_register_on_exit(LPM0_bits);
        return ;
    }

    uint16_t volt1;


    // 等待ADC防止冲突
    while(ADC12CTL1_L & BIT0){}

    ADC12CTL0 |= ADC12SC;
     while (!(ADC12IFGR0 & BIT0)) {/* WAIT */}
    HWREG16(TIMER_A0_BASE + OFS_TAxCTL) &= ~TAIFG;
    volt1 = ADC12MEM0;

    var = (uint16_t)((((uint32_t)(volt1))*225)>>8);              // 电压转换为以mV为单位的估值。三分压下参考电压为1.2V。


    TA0CCR0 += TIMER_ROUTINE;


    if ((var < BACKUP_VOLTAGE) && (system_in_running == 1))
    {
        if (energy_consumption == 0)
        {
            EUSCI_A_UART_transmitData(EUSCI_A1_BASE, 0x43);
            return ;
        }
        // 时间以ms为单位
        time_on = ((uint32_t)(time_overflow_flag) << 16) + (uint32_t)TA4R;

//        time_off = regression(energy_consumption,time_on);
        time_off = energy_consumption;

//        time_on = energy_consumption;
        char* ptr = (char*)(&time_off);
        for(i = 0;i<4;i++)
            shut_buffer[i+1] = *(ptr+i);

        ptr = (char*)(&time_on);
        for(i = 0;i<4;i++)
            shut_buffer[i+5] = *(ptr+i);

        for(i = 0;i<SHUT_LENGTH;i++)
        {
            while(!(UCA1IFG&UCTXIFG));
            UCA1TXBUF = shut_buffer[i];
        }

        __no_operation();

        // 然后执行备份
        system_in_running = 0;                                  // 置位标记然后备份、休眠
        time_overflow_flag = 0;TA4R = 0;
        backup();
        __no_operation();   // 恢复到这里才对,需要添加标志为来确定是恢复到那里
        if(recovery_done == 0)
        {
            __bis_SR_register(GIE | LPM0_bits);
        }
        else if (recovery_done == 1)
        {
            // 表示从recovery中恢复，反转标志位不要再次进入lpm
            recovery_done = 0;
            // 同时需要给记录机一个信号，表示当前关机时间已经结束

            for(i = 0;i<TRANS_LENGTH;i++)
            {
                while(!(UCA1IFG&UCTXIFG));
                UCA1TXBUF = trans_buffer[i];
            }
            energy_consumption = 0;
            __no_operation();
        }
    }


    if ((var > RECOVERY_VOLTAGE) && (system_in_running == 0))
    {
        // 电压高于阈值，可以恢复, 但是要做好对应标志位的处理
        last_time_record = 0;
        energy_consumption = 0;
        system_in_running = 1;
        recovery_done = 1;
        recovery();
    }
}


#pragma vector=TIMER0_A1_VECTOR
__interrupt void timer_over_handle()
{
    switch(__even_in_range(TA0IV,14))
    {
    case 14: break;
    default:break;
    }
    __no_operation();
}
unsigned int counter = 0;
#pragma vector=TIMER4_A1_VECTOR
__interrupt void ACLK_timer_handle()
{
    uint32_t time_now;
    uint32_t period;
    switch(__even_in_range(TA4IV,14))
    {
    case 02:
        {
            P5OUT &= ~BIT1;         // 恢复输入信号为低电平
            // 1. 计算当前断点与上一断点间隔的时间
            // 2. 通过phase_index在数组中查看对应阶段的功率值
            time_now = TA4CCR1;

            if(first_breakpoint_flag == 0)
            {
                time_now = time_now + ((uint32_t)time_overflow_flag << 16);
                period = (time_now - last_time_record);
                last_time_record = time_now;
            }
            else if(first_breakpoint_flag == 1)
            {
                first_breakpoint_flag = 0;
                time_now = time_now + ((uint32_t)time_overflow_flag << 16);
                period = time_now;
                last_time_record = time_now;
                energy_consumption += ((var*220)>>10) * period >> 10;
                break;
            }
            if(phase_index>=4) phase_index = 0;
            energy_consumption += (((cycle_cost[current_working_freq][task_number][phase_index]*var)>>10) * period) >> 10;

//            phase_index++;

            break;
        }

    case 14:
        {
            // 计时器溢出中断
            time_overflow_flag++;
//            printf("%d\n",counter++);
            break;
        }
    default:break;
    }
    __no_operation();
}

inline uint32_t regression(uint32_t E,uint32_t T)
{
    if (E>4000 || T>4000)
    {
        return 10000;
    }
//    float a = (float)E;float b = (float)T;
    float a = log_result[E];
    float b = log_result[T];
    float c = w1*a+w2*b + bias;
    uint32_t res;
//    uint32_t res = (uint32_t)expf(c);

    if (c < 0.0  || c > log_result[DATA_RANGE-1])
    {
        // 范围超了，需要单独处理
        return 10000;
    }

    unsigned int left = 0;
    unsigned int right = DATA_RANGE-1;
    unsigned int mid;

    while(left <= right)
    {
        mid = (left + right) >> 1;
        if (log_result[mid] < c)
        {
            left = mid +1;
        }
        else if(log_result[mid] > c)
        {
            right = mid -1;
        }
    }
    if (mid > 0 && (c - log_result[mid-1])<(log_result[mid]-c))
    {
        res = mid-1;
    }
    else
        res = mid;





    return res;
}

#pragma vector = DMA_VECTOR
__interrupt void DMA_Finish_ISR()
{
    switch(__even_in_range(DMAIV,14))
    {
    case 14:break;
    default:break;
    }
}

#pragma vector = AES256_VECTOR
__interrupt void AES_ISR()
{
    return;
}

#pragma vector = EUSCI_A1_VECTOR
__interrupt void EUSCIA1_ISR()
{
    switch(__even_in_range(UCA1IV,14))
   {
        default:break;
   }
    return ;
}

#pragma vector = EUSCI_A0_VECTOR
__interrupt void EUSCIA0_ISR()
{
    switch(__even_in_range(UCA0IV,14))
   {
        default:break;
   }
    return ;
}

