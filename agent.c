/*
 *              ��������еĵ�λ�ƣ�
 *                      1. ������ ��A
 *                      2. ��ѹ�� mV
 *                      3. ���ʣ� ��W
 *                      4. ������ ��J
 *                      5. ʱ�䣺 ms
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

/************************************************TA0������**************************************************************************/
#pragma PERSISTENT(time_on)
uint32_t time_on = 0;                                       // ��¼����ʱ�������
uint16_t time_overflow_flag = 0;                        // ��ʱ���������־��ÿһ����������Ҫ����Ϊ0���ڵ���ʱ���ﱻ��¼��
uint32_t time_off = 0;                                      // Ԥ��Ķϵ�ʱ��
uint32_t var;                                           // ��ѹ����ֵ

// regression data for 1000uF
//static const float w1 = -0.50083057;
//static const float w2 = -0.54463161;
//static const float bias = 10.094598802589179;

// 470uF
static const float w1 = -0.52611847;
static const float w2 = -0.55975162;
static const float bias = 9.053817974072206;



// Bakup & Recovery
extern  uint8_t system_in_running;              // ��־λΪ1��ʾ��ǰϵͳ�������У���֮���������߻��߶ϵ�״̬
extern  uint8_t recovery_done = 0;                  // ��־λΪ1��ʾ��ǰ������Ǵ�recovery�ָ�����ת��backup()��λ�ã���Ҫ�ٴν���͹���

extern unsigned int first_running;

// ���ͻ�����
unsigned int i = 0;
#define SHUT_LENGTH         9
#define TRANS_LENGTH        1
uint8_t trans_buffer[TRANS_LENGTH] = {0x42};
uint8_t shut_buffer[SHUT_LENGTH] = {0x41,0,0,0,0,0,0,0,0};

inline uint32_t regression(uint32_t,uint32_t);


/************************************************TA4������**************************************************************************/

#pragma PERSISTENT(first_breakpoint_flag)
uint8_t first_breakpoint_flag = 1;                 // ��־��һ�ν���ϵ�

extern  uint8_t task_number;                             // ��ʶ��ǰ����

#pragma PERSISTENT(phase_index)
uint8_t phase_index = 0xFF;                           // ���ڱ�ʶ��ǰ�ϵ��Ӧ�׶�

uint32_t last_time_record = 0;                          // ���ڼ���ʱ���ֵ
//#pragma PERSISTENT(energy_consumption)
uint32_t energy_consumption = 0;                        // �����ڼ�ֱ����һ�ν���breakpoint��γ�ʼ�����ĵ��������ۼӼ���õ�������ʼֵ��Ϊ1



/**********************************************************************************************************************************/

// power table, 0-2���������Ľ׶εĵ��͹��ʣ�3��������֮���л��ļ�϶�ĵ��͹��ʡ�
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



// ���ĵ��жϺ���
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Agent_ISR(void)
{
    if(first_running == 1)
    {
        __bic_SR_register_on_exit(LPM0_bits);
        return ;
    }

    uint16_t volt1;


    // �ȴ�ADC��ֹ��ͻ
    while(ADC12CTL1_L & BIT0){}

    ADC12CTL0 |= ADC12SC;
     while (!(ADC12IFGR0 & BIT0)) {/* WAIT */}
    HWREG16(TIMER_A0_BASE + OFS_TAxCTL) &= ~TAIFG;
    volt1 = ADC12MEM0;

    var = (uint16_t)((((uint32_t)(volt1))*225)>>8);              // ��ѹת��Ϊ��mVΪ��λ�Ĺ�ֵ������ѹ�²ο���ѹΪ1.2V��


    TA0CCR0 += TIMER_ROUTINE;


    if ((var < BACKUP_VOLTAGE) && (system_in_running == 1))
    {
        if (energy_consumption == 0)
        {
            EUSCI_A_UART_transmitData(EUSCI_A1_BASE, 0x43);
            return ;
        }
        // ʱ����msΪ��λ
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

        // Ȼ��ִ�б���
        system_in_running = 0;                                  // ��λ���Ȼ�󱸷ݡ�����
        time_overflow_flag = 0;TA4R = 0;
        backup();
        __no_operation();   // �ָ�������Ŷ�,��Ҫ��ӱ�־Ϊ��ȷ���ǻָ�������
        if(recovery_done == 0)
        {
            __bis_SR_register(GIE | LPM0_bits);
        }
        else if (recovery_done == 1)
        {
            // ��ʾ��recovery�лָ�����ת��־λ��Ҫ�ٴν���lpm
            recovery_done = 0;
            // ͬʱ��Ҫ����¼��һ���źţ���ʾ��ǰ�ػ�ʱ���Ѿ�����

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
        // ��ѹ������ֵ�����Իָ�, ����Ҫ���ö�Ӧ��־λ�Ĵ���
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
            P5OUT &= ~BIT1;         // �ָ������ź�Ϊ�͵�ƽ
            // 1. ���㵱ǰ�ϵ�����һ�ϵ�����ʱ��
            // 2. ͨ��phase_index�������в鿴��Ӧ�׶εĹ���ֵ
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
            // ��ʱ������ж�
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
        // ��Χ���ˣ���Ҫ��������
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

