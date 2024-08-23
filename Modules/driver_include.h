#ifndef _DRIVER_LIB_INCLUDE_H
#define _DRIVER_LIB_INCLUDE_H

#include <msp430.h>

#if defined(__MSP430FR5969__) || defined(__MSP430FR5994__)
    #include<lib/driverlib_MSP430FR5xx_6xx/driverlib.h>
    #include<Modules/LED_button.h>
    #include<Modules/initialization.h>
    #include<Modules/EUSCI.h>
    #include<Modules/ADC.h>
    #include<Modules/nv.h>
    #include<Modules/backup_and_recovery.h>
    #include<Modules/redirection.h>
    #include<Modules/aes.h>
    #include<Modules/initparam.h>
#endif

#endif
