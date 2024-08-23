#include <msp430.h> 
#include <Modules/driver_include.h>
#include <main.h>
#include <stdint.h>

#pragma PERSISTENT(system_in_running)
extern  uint8_t system_in_running = 0;

extern  uint8_t recovery_done;

#pragma PERSISTENT(first_running)
unsigned int first_running = 1;

#pragma PERSISTENT(current_working_freq)
extern unsigned int current_working_freq = WORK_FREQUENCY_4;



int main(void)
{

    /* General Initialization */
	power_on_init();

	clock_sys_init(current_working_freq, CS_CLOCK_DIVIDER_1, CS_CLOCK_DIVIDER_2);       // ����2��3Ĭ��Ϊ1��Ƶ��2��Ƶ������ı䣬��ʱ��MCLKƵ����ÿ��������Ҫ����FRAM�еı���Ƶ�ʽ��С�
    EUSCI_init(current_working_freq,1,1,1);                                             // ����2��3Ĭ��Ϊ1����ʶEUSCIA0��A1������������4Ĭ��Ϊ1����ʾ����״̬Ϊ115200�����ʡ�
	timer_init();                                                                       // ����ʱ��ѡ��SMCLK������ʱ��ѡ��ACLK

	DMA_init_lib();
	ref_init(REF_1_2V);
	adc_init();
	aes_init();


	if(first_running == 0)
	{
	    /* Start 2 timer, both are running all the time */
	    Timer_A_startCounter(TIMER_A0_BASE,TIMER_A_CONTINUOUS_MODE);    // used to control ADC Sample for VCC
	    Timer_A_startCounter(TIMER_A4_BASE,TIMER_A_CONTINUOUS_MODE);    // used to calculate time_on
	    __no_operation();
	    __bis_SR_register(GIE);
	    __bis_SR_register(LPM0);
	    __no_operation();
	}



	system_in_running = 0;



	if(first_running == 1)
	{
	    turn_on_right_LED;
        /* wait for button press*/
        while(!check_left_button){}
        turn_off_right_LED;

        Timer_A_startCounter(TIMER_A0_BASE,TIMER_A_CONTINUOUS_MODE);    // used to control ADC Sample for VCC
        Timer_A_startCounter(TIMER_A4_BASE,TIMER_A_CONTINUOUS_MODE);    // used to calculate time_on
        __no_operation();
        __bis_SR_register(GIE);

        system_in_running = 1;

	    first_running = 0;
	    testbench_breakpoint();
	}


	__no_operation();



  	/* keep routine */
    while(1){
        __delay_cycles(500000);
    }

  	return 0;
}
