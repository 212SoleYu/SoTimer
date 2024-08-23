#include<Modules/ADC.h>


void ref_init(unsigned int mode)
{
    if(mode == 1)
        Ref_A_setReferenceVoltage(REF_A_BASE, REF_A_VREF1_2V);
    else if (mode == 2)
        Ref_A_setReferenceVoltage(REF_A_BASE, REF_A_VREF2_0V);
    else if (mode == 3)
        Ref_A_setReferenceVoltage(REF_A_BASE, REF_A_VREF2_5V);
}


void adc_init()
{


    GPIO_setAsPeripheralModuleFunctionOutputPin(ADC_CHANNEL_INPUT_PORT, ADC_CHANNEL_INPUT_PIN,ADC_CHANNEL_INPUT_FUNCTION);

    ADC12_B_initParam initParam = {0};
    initParam.clockSourceDivider = ADC12_B_CLOCKDIVIDER_1;
    initParam.clockSourcePredivider = ADC12_B_CLOCKPREDIVIDER__1;
    initParam.clockSourceSelect = ADC12_B_CLOCKSOURCE_ADC12OSC;
    initParam.internalChannelMap = ADC12_B_NOINTCH;
//     initParam.sampleHoldSignalSourceSelect = ADC12_B_SAMPLEHOLDSOURCE_1;     // TA0 CCR1 output
    initParam.sampleHoldSignalSourceSelect = ADC12_B_SAMPLEHOLDSOURCE_SC;       // Manual.

    ADC12_B_init(ADC12_B_BASE, &initParam);
    ADC12_B_setupSamplingTimer(ADC12_B_BASE,
                               ADC12_B_CYCLEHOLD_32_CYCLES,
                               ADC12_B_CYCLEHOLD_32_CYCLES,
                               ADC12_B_MULTIPLESAMPLESDISABLE
                               );



    ADC12_B_configureMemoryParam configureMemoryParam = {0};
    configureMemoryParam.memoryBufferControlIndex = ADC12_B_MEMORY_0;
    configureMemoryParam.refVoltageSourceSelect = ADC12_B_VREFPOS_INTBUF_VREFNEG_VSS;
    configureMemoryParam.endOfSequence = ADC12_B_ENDOFSEQUENCE;
    configureMemoryParam.windowComparatorSelect = ADC12_B_WINDOW_COMPARATOR_DISABLE;
    configureMemoryParam.differentialModeSelect = ADC12_B_DIFFERENTIAL_MODE_DISABLE;
    configureMemoryParam.inputSourceSelect = ADC_INPUT_SOURCE;

    ADC12_B_configureMemory(ADC12_B_BASE, &configureMemoryParam);

    // Disable ADC, set ADC12ON to 1, and then enable ADC.
    ADC12CTL0 &= ~ADC12ENC;
    ADC12CTL0 |= ADC12ON;
    ADC12CTL0 |= ADC12ENC;
    ADC12IFGR0 &= ~BIT0;

}





