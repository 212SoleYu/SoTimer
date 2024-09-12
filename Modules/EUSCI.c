#include <msp430.h>
#include <lib/driverlib_MSP430FR5xx_6xx/eusci_a_uart.h>
#include <Modules/EUSCI.h>


#define CLK_PRESCALAR_USED          8
#define FIRST_MODE_REG_USED         0
#define SECOND_MODE_REG_USED        214
#define OVER_SAMP_USED              0

// different WORKING GREQUENCY for same baud rate 115200 or baud rate 9600

EUSCI_A_UART_initParam UARTlist[6][2] =
{
    {
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,
            6,                                            // UCBRx
            8,                                            // UCBRFx
            0x20,                                         // UCBRSx
            EUSCI_A_UART_NO_PARITY,
            EUSCI_A_UART_LSB_FIRST,
            EUSCI_A_UART_ONE_STOP_BIT,
            EUSCI_A_UART_MODE,
            1                                             // UCOS16 bit
        },
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,
            8,                                            // UCBRx
            0,                                            // UCBRFx
            0xD6,                                         // UCBRSx
            EUSCI_A_UART_NO_PARITY,
            EUSCI_A_UART_LSB_FIRST,
            EUSCI_A_UART_ONE_STOP_BIT,
            EUSCI_A_UART_MODE,
            0                                             // UCOS16 bit
        }
    },// 1MHz

    {
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,
            8,                                            // UCBRx
            0,                                            // UCBRFx
            0xD6,                                         // UCBRSx
            EUSCI_A_UART_NO_PARITY,
            EUSCI_A_UART_LSB_FIRST,
            EUSCI_A_UART_ONE_STOP_BIT,
            EUSCI_A_UART_MODE,
            0                                             // UCOS16 bit
        },
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,
            8,                                            // UCBRx
            0,                                            // UCBRFx
            0xD6,                                         // UCBRSx
            EUSCI_A_UART_NO_PARITY,
            EUSCI_A_UART_LSB_FIRST,
            EUSCI_A_UART_ONE_STOP_BIT,
            EUSCI_A_UART_MODE,
            0                                             // UCOS16 bit
        }
    },// 3.33MHz
    {
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,
            26,                                            // UCBRx
            0,                                            // UCBRFx
            0xB6,                                         // UCBRSx
            EUSCI_A_UART_NO_PARITY,
            EUSCI_A_UART_LSB_FIRST,
            EUSCI_A_UART_ONE_STOP_BIT,
            EUSCI_A_UART_MODE,
            1                                             // UCOS16 bit
        },
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,
            2,                                            // UCBRx
            2,                                            // UCBRFx
            0xBB,                                         // UCBRSx
            EUSCI_A_UART_NO_PARITY,
            EUSCI_A_UART_LSB_FIRST,
            EUSCI_A_UART_ONE_STOP_BIT,
            EUSCI_A_UART_MODE,
            1                                             // UCOS16 bit
        }
    },// 4MHz
    {
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,
            52,                                            // UCBRx
            1,                                            // UCBRFx
            0x49,                                         // UCBRSx
            EUSCI_A_UART_NO_PARITY,
            EUSCI_A_UART_LSB_FIRST,
            EUSCI_A_UART_ONE_STOP_BIT,
            EUSCI_A_UART_MODE,
            1                                             // UCOS16 bit
        },
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,
            4,                                            // UCBRx
            5,                                            // UCBRFx
            0x55,                                         // UCBRSx
            EUSCI_A_UART_NO_PARITY,
            EUSCI_A_UART_LSB_FIRST,
            EUSCI_A_UART_ONE_STOP_BIT,
            EUSCI_A_UART_MODE,
            1                                             // UCOS16 bit
        }
    },// 8MHz
    {
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,
            104,                                            // UCBRx
            2,                                            // UCBRFx
            0xD6,                                         // UCBRSx
            EUSCI_A_UART_NO_PARITY,
            EUSCI_A_UART_LSB_FIRST,
            EUSCI_A_UART_ONE_STOP_BIT,
            EUSCI_A_UART_MODE,
            1                                             // UCOS16 bit
        },
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,
            8,                                            // UCBRx
            10,                                            // UCBRFx
            0xF7,                                         // UCBRSx
            EUSCI_A_UART_NO_PARITY,
            EUSCI_A_UART_LSB_FIRST,
            EUSCI_A_UART_ONE_STOP_BIT,
            EUSCI_A_UART_MODE,
            1                                             // UCOS16 bit
        }
    },// 16MHz
    {
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,
            8,                                            // UCBRx
            0,                                            // UCBRFx
            0xD6,                                         // UCBRSx
            EUSCI_A_UART_NO_PARITY,
            EUSCI_A_UART_LSB_FIRST,
            EUSCI_A_UART_ONE_STOP_BIT,
            EUSCI_A_UART_MODE,
            0                                             // UCOS16 bit
        },
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,
            8,                                            // UCBRx
            0,                                            // UCBRFx
            0xD6,                                         // UCBRSx
            EUSCI_A_UART_NO_PARITY,
            EUSCI_A_UART_LSB_FIRST,
            EUSCI_A_UART_ONE_STOP_BIT,
            EUSCI_A_UART_MODE,
            0                                             // UCOS16 bit
        }
    }// 20MHz

};

void EUSCI_init(int UART_mode, int A0_flag, int A1_flag, int Baud_rate)
{
    // A0, P2.0 and P2.1
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN0, GPIO_SECONDARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN1, GPIO_SECONDARY_MODULE_FUNCTION);
    // A1, P2.5 and P2.6
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5, GPIO_SECONDARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN6, GPIO_SECONDARY_MODULE_FUNCTION);

    // changing configuration of UART Buad rate
//    EUSCI_A_UART_initParam param = {0};
//    param = UARTlist[UART_mode][Baud_rate];

    // constant configuration
    EUSCI_A_UART_initParam param = {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,
        2,                                            // UCBRx
        11,                                            // UCBRFx
        0x92,                                         // UCBRSx
        EUSCI_A_UART_NO_PARITY,
        EUSCI_A_UART_LSB_FIRST,
        EUSCI_A_UART_ONE_STOP_BIT,
        EUSCI_A_UART_MODE,
        1                                             // UCOS16 bit
    };  // 5MHz in 115200 baud rate. use MODOSC for SMCLK instead of DCO. Fixed UART configuration.

    if(A0_flag == 1)
    {
        if (STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A0_BASE, &param)) {
            while (1){}
        }
        EUSCI_A_UART_enable(EUSCI_A0_BASE);             // Enable eZ-FET UART.
        EUSCI_A_UART_clearInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
    }

    if(A1_flag == 1)
    {
        if (STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A1_BASE, &param)) {
            while (1){}
        }
        EUSCI_A_UART_enable(EUSCI_A1_BASE);
        EUSCI_A_UART_clearInterrupt(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
    }

}
