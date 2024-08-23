/*
 * File name: initialization.c
 * Description: 完成对于初始化函数的所有定义，初始化时钟、高速和低俗定时器，DMA以及两个按钮的中断。
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

    /* 完成左右LED和左按键的初始化 */

//    init_left_LED;
//    init_right_LED;
    init_left_button;
}

// 用于初始化DCO时钟的参数
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

    CS_initClockSignal(CS_MCLK,CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);       // 初始化主时钟MCLK，时钟源选择DCO，可能会变频至上述列表中的工作频率，无需分频
    CS_initClockSignal(CS_SMCLK,CS_MODOSC_SELECT, SMCLK_divider);           // 初始化子时钟SMCLK，时钟源选择MODCLK，其固定频率5MHZ，无需分频，ADC12也用该时钟源。
    CS_initClockSignal(CS_ACLK,CS_VLOCLK_SELECT, ACLK_divider);             // ACLK使用VLOCK，默认2分频，在定时器中再进行一次分频至1/5，总共1/10，低速计时器每计1，物理时间为1ms。
    CS_turnOffLFXT();
}

void timer_init()
{
    // 高速的计时器TimerA0，目前仅用于触发传感器来检测电源电压，连续模式
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

    TA0CCR0 = 500;  // 一个短暂的启动时延

    // 低速的定时器TimerA4，一般与主定时器频率不同，目前采用低速时钟来对程序进行检测，可以进行分频，设定为捕获模式来记录不同程序段的时间，在程序中通过手动控制中断源来触发该中断处理函数。
    // 在初始化函数中处理好P5.1和P5.7的端口输入输出，并且将断点函数直接生成为汇编语句作为断点直接插入函数中，在并且在中断服务函数中恢复信号以及处理COV溢出标志等，从而减少函数调用的压栈等操作。

    // 初始化主计时器，声明为连续模式，使用ACLK低速时钟，计时器的计数间隔可以设置为1ms
    Timer_A_initContinuousModeParam counter_low ={0};
    counter_low.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
    counter_low.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_5;
    counter_low.startTimer = false;
    counter_low.timerClear = TIMER_A_SKIP_CLEAR;
    counter_low.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;


    // 配置TA4CC1为捕获模式，其中捕获信息输入为P5.7，使用跳线在外面连接P5.1和P5.7。
    Timer_A_initCaptureModeParam param1 = {0};
    param1.captureMode = TIMER_A_CAPTUREMODE_RISING_EDGE;
    param1.captureInputSelect = TIMER_A_CAPTURE_INPUTSELECT_CCIxA;
    param1.captureInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    param1.captureOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;
    param1.captureRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    param1.synchronizeCaptureSource = TIMER_A_CAPTURE_ASYNCHRONOUS;



    // 配置TA4CC2为比较模式，用于在低速时钟下记录开机时间，实际上就是记录时钟的溢出标志
    Timer_A_initCompareModeParam param2 = {0};
    param2.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    param2.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
    param2.compareValue = 50000;
    param2.compareOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;


    // 取消对于TIMERA4的使能，在对其进行初始化和修改
    Timer_A_clearTimerInterrupt(TIMER_A4_BASE);

    // 分别初始化主计时器、捕获比较器1和2
    Timer_A_initContinuousMode(TIMER_A4_BASE, &counter_low);
    Timer_A_initCaptureMode(TIMER_A4_BASE, &param1);
    Timer_A_initCompareMode(TIMER_A4_BASE,&param2);

    // 分别使能计时器、捕获比较器1和2
    Timer_A_enableInterrupt(TIMER_A4_BASE);
    Timer_A_enableCaptureCompareInterrupt(TIMER_A4_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1);
    Timer_A_enableCaptureCompareInterrupt(TIMER_A4_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);

    // 计时器的触发选择在外部主函数进行
//    Timer_A_startCounter(TIMER_A0_BASE,TIMER_A_CONTINUOUS_MODE);
//    Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_CONTINUOUS_MODE);


    // 针对定时器捕获模式对于P5.7的单独配置
      P5SEL1 |= BIT7;
      P5SEL0 &= ~BIT7;
      P5DIR &= ~BIT7;
      P5REN |= BIT7;

//      // P5.7作为一个输入接口，承接另一个GPIO的输出，P5.1输出
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
