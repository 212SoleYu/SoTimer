/*
 * File name: initialization.c
 * Description: ��ɶ��ڳ�ʼ�����������ж��壬��ʼ��ʱ�ӡ����ٺ͵��׶�ʱ����DMA�Լ�������ť���жϡ�
 */
#include <Modules/initialization.h>

void power_on_init()
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watch-dog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    // set 3 ports as output and low power
    P1DIR &= 0xFF;
    P2DIR |= 0xFF; P3DIR |= 0xFF;
    P1OUT = 0x00; P2OUT = 0x00; P3OUT = 0x00;


    // unused ports still be set
    P4DIR = 0xFF; P4OUT = 0x00;
    P5DIR = 0xFF; P5OUT = 0x00;
    P6DIR = 0xFF; P6OUT = 0x00;
    P7DIR = 0xFF; P7OUT = 0x00;
    P8DIR = 0xFF; P8OUT = 0x00;
    P9DIR = 0xFF; P9OUT = 0x00;
    PADIR = 0xFF; PAOUT = 0x00;
    PBDIR = 0xFF; PBOUT = 0x00;
    PCDIR = 0xFF; PCOUT = 0x00;
    PDDIR = 0xFF; PDOUT = 0x00;
    PEDIR = 0xFF; PEOUT = 0x00;

    /* �������LED���󰴼��ĳ�ʼ�� */

//    init_left_LED;
//    init_right_LED;
    init_left_button;
}

// ���ڳ�ʼ��DCOʱ�ӵĲ���
extern int CLK_SYS_params[6][2] =
{
      {CS_DCORSEL_0, CS_DCOFSEL_0},                  // 1MHz
      {CS_DCORSEL_0, CS_DCOFSEL_2},                  // 3.33
      {CS_DCORSEL_0, CS_DCOFSEL_3},                  // 4
      {CS_DCORSEL_0, CS_DCOFSEL_5},                  // 6.67
      {CS_DCORSEL_1, CS_DCOFSEL_3},                  // 8
      {CS_DCORSEL_1, CS_DCOFSEL_4},                  // 16

};




void clock_sys_init(int freq_mode, int SMCLK_divider, int ACLK_divider)
{
    // set working frequency by DCO
    CS_setDCOFreq(CLK_SYS_params[freq_mode][0], CLK_SYS_params[freq_mode][1]);

    CS_initClockSignal(CS_MCLK,CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);       // ��ʼ����ʱ��MCLK��ʱ��Դѡ��DCO�����ܻ��Ƶ�������б��еĹ���Ƶ�ʣ������Ƶ
    CS_initClockSignal(CS_SMCLK,CS_MODOSC_SELECT, SMCLK_divider);           // ��ʼ����ʱ��SMCLK��ʱ��Դѡ��MODCLK����̶�Ƶ��5MHZ�������Ƶ��ADC12Ҳ�ø�ʱ��Դ��
    CS_initClockSignal(CS_ACLK,CS_VLOCLK_SELECT, ACLK_divider);             // ACLKʹ��VLOCK��Ĭ��2��Ƶ���ڶ�ʱ�����ٽ���һ�η�Ƶ��1/5���ܹ�1/10�����ټ�ʱ��ÿ��1������ʱ��Ϊ1ms��
    CS_turnOffLFXT();
}

void timer_init()
{
    // ���ٵļ�ʱ��TimerA0��Ŀǰ�����ڴ���������������Դ��ѹ������ģʽ
    Timer_A_initContinuousModeParam param = {0};
    param.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    param.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    param.timerClear = TIMER_A_SKIP_CLEAR;
    param.startTimer = false;

    Timer_A_clearTimerInterrupt(TIMER_A0_BASE);
    Timer_A_initContinuousMode(TIMER_A0_BASE, &param);
    Timer_A_enableInterrupt(TIMER_A0_BASE);
    Timer_A_enableCaptureCompareInterrupt(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_0);

    TA0CCR0 = 500;  // һ�����ݵ�����ʱ��

    // ���ٵĶ�ʱ��TimerA4��һ��������ʱ��Ƶ�ʲ�ͬ��Ŀǰ���õ���ʱ�����Գ�����м�⣬���Խ��з�Ƶ���趨Ϊ����ģʽ����¼��ͬ����ε�ʱ�䣬�ڳ�����ͨ���ֶ������ж�Դ���������жϴ�������
    // �ڳ�ʼ�������д����P5.1��P5.7�Ķ˿�������������ҽ��ϵ㺯��ֱ������Ϊ��������Ϊ�ϵ�ֱ�Ӳ��뺯���У��ڲ������жϷ������лָ��ź��Լ�����COV�����־�ȣ��Ӷ����ٺ������õ�ѹջ�Ȳ�����

    // ��ʼ������ʱ��������Ϊ����ģʽ��ʹ��ACLK����ʱ�ӣ���ʱ���ļ��������������Ϊ1ms
    Timer_A_initContinuousModeParam counter_low ={0};
    counter_low.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
    counter_low.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_5;
    counter_low.startTimer = false;
    counter_low.timerClear = TIMER_A_SKIP_CLEAR;
    counter_low.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;


    // ����TA4CC1Ϊ����ģʽ�����в�����Ϣ����ΪP5.7��ʹ����������������P5.1��P5.7��
    Timer_A_initCaptureModeParam param1 = {0};
    param1.captureMode = TIMER_A_CAPTUREMODE_RISING_EDGE;
    param1.captureInputSelect = TIMER_A_CAPTURE_INPUTSELECT_CCIxA;
    param1.captureInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    param1.captureOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;
    param1.captureRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    param1.synchronizeCaptureSource = TIMER_A_CAPTURE_ASYNCHRONOUS;



    // ����TA4CC2Ϊ�Ƚ�ģʽ�������ڵ���ʱ���¼�¼����ʱ�䣬ʵ���Ͼ��Ǽ�¼ʱ�ӵ������־
    Timer_A_initCompareModeParam param2 = {0};
    param2.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    param2.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
    param2.compareValue = 50000;
    param2.compareOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;


    // ȡ������TIMERA4��ʹ�ܣ��ڶ�����г�ʼ�����޸�
    Timer_A_clearTimerInterrupt(TIMER_A4_BASE);

    // �ֱ��ʼ������ʱ��������Ƚ���1��2
    Timer_A_initContinuousMode(TIMER_A4_BASE, &counter_low);
    Timer_A_initCaptureMode(TIMER_A4_BASE, &param1);
    Timer_A_initCompareMode(TIMER_A4_BASE,&param2);

    // �ֱ�ʹ�ܼ�ʱ��������Ƚ���1��2
    Timer_A_enableInterrupt(TIMER_A4_BASE);
    Timer_A_enableCaptureCompareInterrupt(TIMER_A4_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1);
    Timer_A_enableCaptureCompareInterrupt(TIMER_A4_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);

    // ��ʱ���Ĵ���ѡ�����ⲿ����������
//    Timer_A_startCounter(TIMER_A0_BASE,TIMER_A_CONTINUOUS_MODE);
//    Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_CONTINUOUS_MODE);


    // ��Զ�ʱ������ģʽ����P5.7�ĵ�������
      P5SEL1 |= BIT7;
      P5SEL0 &= ~BIT7;
      P5DIR &= ~BIT7;
      P5REN |= BIT7;

//      // P5.7��Ϊһ������ӿڣ��н���һ��GPIO�������P5.1���
//      P5DIR |= BIT1;


}

void button_init()
{
    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN5 + GPIO_PIN6);
    GPIO_clearInterrupt(GPIO_PORT_P5, GPIO_PIN5 + GPIO_PIN6);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN5 + GPIO_PIN6);
    GPIO_selectInterruptEdge(GPIO_PORT_P5, GPIO_PIN5 + GPIO_PIN6, GPIO_HIGH_TO_LOW_TRANSITION);
}


void DMA_init_lib()
{
    // set DMA0 to transmit data
    // DMA0 is selected to transfer all the data in stack, so we have the correspoding set
    DMA_initParam param = {0};
    param.channelSelect = DMA_CHANNEL_0;
    param.transferModeSelect = DMA_TRANSFER_BLOCK;                      // transfer a data block
    param.transferSize = 0;                                             // datasize should be set later
    param.triggerSourceSelect = DMA_TRIGGERSOURCE_0;                    // we set it manual in the BACKUP() or the RECOVERY()
    param.transferUnitSelect = DMA_SIZE_SRCBYTE_DSTBYTE;
    param.triggerTypeSelect = DMA_TRIGGER_RISINGEDGE;

    DMA_init(&param);

    // both address will be set in backup() and recovery()
    DMA_setSrcAddress(DMA_CHANNEL_0,0,DMA_DIRECTION_INCREMENT);
    DMA_setDstAddress(DMA_CHANNEL_0,0,DMA_DIRECTION_INCREMENT);

    DMA_clearInterrupt(DMA_CHANNEL_0);
//    DMA_enableInterrupt(DMA_CHANNEL_0);
    DMA_enableTransfers(DMA_CHANNEL_0);
}
