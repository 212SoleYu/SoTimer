/*
 * File name: header.h
 * Date: 2024-03-11
 * Description: This file is to declare all the STRUCT, const variable and array used in all testbenches.
 */

#ifndef HEADER_H
#define HEADER_H
#include<stdint.h>
#include<Modules/driver_include.h>

/*******************************testbench_1********************************************************/

#define BUF_LENGTH          256

extern uint16_t Volt[BUF_LENGTH];

/********************************testbench_2*******************************************************/

#define CRC_LENGTH          (512)
#define CRC_INIT            (0xFFFF)

extern const uint16_t CRC_Input[CRC_LENGTH];

uint16_t CRC_Result;                    // Holds results obtained through the CRC16 module
uint16_t SW_Results;                    // Holds results obtained through SW

unsigned int CCITT_Update(unsigned int init, unsigned int input);

/*******************************testbench_3********************************************************/

#define INPUT_LENGTH        (16)
#define INPUT_SIZE          (256)

#define POOL_LENGTH         (INPUT_LENGTH - KERNEL_LENGTH + 1)
#define KERNEL_LENGTH       (3)

#define POOL_KERNEL_LENGTH  (2)

#define OUTPUT_LENGTH       (POOL_LENGTH / POOL_KERNEL_LENGTH)

extern const uint8_t origin_matrix[INPUT_LENGTH][INPUT_LENGTH];

extern uint8_t input_matrix[INPUT_LENGTH][INPUT_LENGTH];
extern uint8_t pool_matrix[POOL_LENGTH][POOL_LENGTH];

extern uint8_t output_matrix[OUTPUT_LENGTH][OUTPUT_LENGTH];

extern const uint8_t kernel_matrix[KERNEL_LENGTH][KERNEL_LENGTH];

/********************************BREAKPOINT********************************************************/


#define set_breakpoint                    P5OUT |= BIT1

extern uint8_t phase_index;

#define phase_update                      phase_index++


/**************************************************************************************************/



/**************************************************************************************************/

#endif
