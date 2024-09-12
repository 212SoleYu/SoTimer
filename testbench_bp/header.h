/*
 * File name: header.h
 * Date: 2024-03-11
 * Description: This file is to declare all the STRUCT, const variable and array used in all testbenches.
 */

#ifndef HEADER_H
#define HEADER_H
#include<stdint.h>
#include<Modules/driver_include.h>

/*******************************testbench_0********************************************************/

#define BUF_LENGTH          256

extern uint16_t Volt[BUF_LENGTH];

/********************************testbench_1*******************************************************/

#define CRC_LENGTH          (512)
#define CRC_INIT            (0xFFFF)

extern const uint16_t CRC_Input[CRC_LENGTH];

uint16_t CRC_Result;                    // Holds results obtained through the CRC16 module
uint16_t SW_Results;                    // Holds results obtained through SW

unsigned int CCITT_Update(unsigned int init, unsigned int input);

/*******************************testbench_2********************************************************/

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


/*******************************testbench_3********************************************************/
#define DIJ_NODE_NUMBER         25
extern const uint8_t adj_Matrix[DIJ_NODE_NUMBER][DIJ_NODE_NUMBER];
extern uint16_t dist_result[DIJ_NODE_NUMBER];
#define MAX_DIS                 0xFF

/*******************************testbench_4********************************************************/

#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define SHR(x, n) ((x) >> (n))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SIG0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
#define SIG1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))
#define SIG2(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define SIG3(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))

extern const uint32_t K[64];
extern const uint32_t H[8];
extern const char text[];
#define TEXT_LENGTH     13

//#pragma PERSISTENT(w)
//uint32_t w[64] = {0};



extern uint32_t sha_result[8];

/*******************************testbench_5********************************************************/
#define MATRIX_SIZE             16
#define MATRIX_HALF             (MATRIX_SIZE / 2)
extern const uint8_t A_MATRIX[MATRIX_SIZE][MATRIX_SIZE];
extern const uint8_t B_MATRIX[MATRIX_SIZE][MATRIX_SIZE];
extern uint8_t C_MATRIX[MATRIX_SIZE][MATRIX_SIZE];

/*******************************testbench_6********************************************************/
extern const uint8_t bit_table[256];

#define BIT_INPUT_LENGTH    256
extern const uint32_t bit_input[BIT_INPUT_LENGTH];

extern uint8_t bit_result[BIT_INPUT_LENGTH];

/********************************BREAKPOINT********************************************************/


#define set_breakpoint                    P5OUT |= BIT1

extern uint8_t phase_index;

#define phase_update                      phase_index++


/**************************************************************************************************/



/**************************************************************************************************/

#endif
