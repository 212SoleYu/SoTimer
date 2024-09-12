/*
 * File name: t6_BC.c
 * Date: 2024/8/25
 * Description: Multiplt methods of bitcount
 */


#include<testbench_bp/header.h>

uint8_t bitcount_recursive(uint32_t);


void testbench_6()
{

    uint8_t count;
    uint16_t i;
    uint32_t tmp;

    set_breakpoint;
    __no_operation();
    phase_update;
    // naive
    for(i = 0;i<BIT_INPUT_LENGTH;i++)
    {
        count = 0;
        tmp = bit_input[i];
        while(tmp)
        {
            count += tmp&1;
            tmp = tmp >>1;
        }
        bit_result[i] = count;

        if((i&0xFF) == 0x7F)
            set_breakpoint;
    }
    // bk

    for(i = 0; i< BIT_INPUT_LENGTH;i++)
    {
        count = 0;
        tmp = bit_input[i];
        while(tmp)
        {
            tmp = tmp & (tmp - 1);
            count++;
        }
        bit_result[i] = count;

        if((i&0xFF) == 0x7F)
            set_breakpoint;
    }

    // recursive

    for(i = 0;i <BIT_INPUT_LENGTH; i++)
    {
        tmp = bit_input[i];
        bit_result[i] = bitcount_recursive(tmp);

        if((i&0xFF) == 0x7F)
            set_breakpoint;
    }

    set_breakpoint;
    __no_operation();
    phase_update;

//    // lookup table
    for(i =0;i<BIT_INPUT_LENGTH;i++)
    {
        tmp = bit_input[i];
        bit_result[i] = bit_table[tmp & 0xff] + bit_table[(tmp>>8) & 0xff] + bit_table[(tmp >> 16) & 0xff] + bit_table[(tmp >> 24) & 0xff];

        if((i&0xFF) == 0x7F)
            set_breakpoint;
    }

    set_breakpoint;
    __no_operation();
    phase_update;
    // hamming weight
    for(i = 0;i<BIT_INPUT_LENGTH;i++)
    {
        tmp = bit_input[i];
        tmp = tmp - ((tmp >> 1) & 0x55555555);
        tmp = (tmp & 0x33333333) + ((tmp >> 2) & 0x33333333);
        tmp = (tmp + (tmp >> 4)) & 0x0F0F0F0F;
        tmp = tmp + (tmp >> 8);
        tmp = tmp + (tmp >> 16);
        bit_result[i] = tmp & 0x3F;


        if((i&0xFF) == 0x7F)
            set_breakpoint;
    }

    set_breakpoint;
    __no_operation();
    phase_update;
}

uint8_t bitcount_recursive(uint32_t n)
{
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return (n & 1) + bitcount_recursive(n >> 1);
    }
}

