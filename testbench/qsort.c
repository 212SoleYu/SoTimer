#include<testbench/declaration.h>



__nv uint16_t outer_index;
__nv uint16_t inner_index;
__nv uint16_t sorted[SORT_LENGTH];


void qsort_main()
{
    register uint16_t val_outer;
    register uint16_t val_inner;
    register uint16_t temp;

    outer_index = 0;
    inner_index = 1;
    for (temp = 0; temp < SORT_LENGTH; ++temp)
        sorted[temp] = raw[temp];

    task_inner_loop:

    for (temp = 0; temp < 6; ++temp) {

        val_outer = sorted[outer_index];
        val_inner = sorted[inner_index];
        if (val_outer > val_inner)
        {
            sorted[outer_index] = val_inner;
            sorted[inner_index] = val_outer;
        }
        if (++inner_index >= SORT_LENGTH)
            break;
    }

    if (inner_index < SORT_LENGTH)
        goto task_inner_loop;

    ++outer_index;
    inner_index = outer_index + 1;
    if (outer_index < SORT_LENGTH - 1)
        goto task_inner_loop;

    return;
}
