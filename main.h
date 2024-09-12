/*
 * File name: main.h
 * Date: 2024-03-07
 * Description:  This file is to give some necessary declarations to the main.c file.
 */

#ifndef _MAIN_H
#define _MAIN_H



/****************************testbench*********************************/

/*
 * Function name: testbench_run
 * DescriptionL This function runs all the testbench continously.
 * Input: None.
 * Output: None.
 * Return: None.
 */
void testbench_run();

/*
 * Function name:testbench_breakpoint
 * Description: This function just runs some testbench with breakpoints set manually.
 * Input: None.
 * Output: None.
 * Return: None.
 */
void testbench_breakpoint();

void change_freq(unsigned int freq_mode);


extern unsigned int current_working_freq;

// power table for different tasks in different working frequency

#define FREQUENCY_NUMBER            5                           // the number of different working frequency, can be more than 3
#define TASK_NUMBER                 7                           // the number of different tasks
#define PHASE_NUMBER                4                           // the number of different phases cutted, all for 3 and 1 gap phase.

extern const uint32_t cycle_cost[FREQUENCY_NUMBER][TASK_NUMBER][PHASE_NUMBER];

extern const unsigned int freqlist[FREQUENCY_NUMBER];

#define DATA_RANGE                 10000
extern const float log_result[DATA_RANGE];
#endif
