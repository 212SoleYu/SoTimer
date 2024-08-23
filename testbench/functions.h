/*
 * Declare the testbenches.
 *
 * Functions can be selected from MiBench, they should include all kinds of testbench, CPU, Memory. I/O
 *
 *  We set a timer overflow as a ROUTINE, about 65ms.
 *
 */
#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H


void bc_main();                     // 1.67 ROUTINE
void qsort_main();                  // 2.90 ROUTINE
void dij_main();                    // 2.6 ROUTINE
void rsa_main();                    // 4.27 ROUTINE
void crc_main();                    // 2.07 ROUTINE

#endif
