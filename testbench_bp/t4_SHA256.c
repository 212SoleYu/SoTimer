/*
 * File name: t4_SHA256.c
 * Date: 2024/08/24
 * Description: artificial testbench for crypto operations.
 *              First we perform SHA256.
 */


#include<testbench_bp/header.h>





void testbench_4()
{
    uint32_t a, b, c, d, e, f, g, h;
    uint8_t buffer[64];
    uint32_t w[64];
    uint16_t i;
    uint16_t j;

    // padding
    uint16_t len = TEXT_LENGTH;
    uint32_t bit_len = len * 8;
    i = 0;
    j = 0;

    set_breakpoint;
      __no_operation();
      phase_update;


    for(i = 0;i<len;i++)
    {
        buffer[j++] = text[i];
    }
    buffer[j++] = 0x80;

    while(j<60)
    {
        buffer[j++] = 0x00;
    }
    buffer[60] = (bit_len >> 24) & 0xFF;
    buffer[61] = (bit_len >> 16) & 0xFF;
    buffer[62] = (bit_len >> 8) & 0xFF;
    buffer[63] = bit_len & 0xFF;

    // extend 64 words


    set_breakpoint;
      __no_operation();
      phase_update;


    for(i = 0; i < 16; i++ ){
        w[i] = ((uint32_t)(buffer[i * 4]) << 24) | ((uint32_t)(buffer[i * 4 + 1]) << 16) | ((uint32_t)(buffer[i * 4 + 2]) << 8) | (buffer[i * 4 + 3]);
    }
    for(i = 16; i < 64; i++) {
        w[i] = SIG1(w[i - 2]) + w[i - 7] + SIG0(w[i - 15]) + w[i - 16];
    }

//
    set_breakpoint;
      __no_operation();
      phase_update;

//    // main loop
    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];

    for (i = 0; i < 64; i++) {
       uint32_t t1 = h + SIG2(e) + CH(e, f, g) + K[i] + w[i];
       uint32_t t2 = SIG3(a) + MAJ(a, b, c);
       h = g;
       g = f;
       f = e;
       e = d + t1;
       d = c;
       c = b;
       b = a;
       a = t1 + t2;
   }
//
    // save
    sha_result[0] = a+H[0];
    sha_result[1] = b+H[1];
    sha_result[2] = c+H[2];
    sha_result[3] = d+H[3];
    sha_result[4] = e+H[4];
    sha_result[5] = f+H[5];
    sha_result[6] = g+H[6];
    sha_result[7] = h+H[7];


    set_breakpoint;
    __no_operation();
    phase_update;
}

