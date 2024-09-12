/*
 * File name: t3_Dij.c
 * Date: 2024/08/24
 * Description: Perform DIJ algorithm.
 */
#include <testbench_bp/header.h>

void testbench_3()
{
    uint8_t srcnode = 0;
    uint8_t flag[DIJ_NODE_NUMBER] = {0};
    uint16_t dist[DIJ_NODE_NUMBER] = {0};


    uint16_t i, j, k;
    uint16_t min;

    // init
    for(i = 0;i<DIJ_NODE_NUMBER;i++)
    {
        flag[i] = 0;
        dist[i] = adj_Matrix[0][i];
    }
    flag[srcnode] = 1;
    dist[i] = 0;

    for (i =1;i<DIJ_NODE_NUMBER;i++)
    {
        min = MAX_DIS;
        for(j = 0;j<DIJ_NODE_NUMBER;j++)
        {
            if(flag[j]==0 && dist[j] < min)
            {
                min = dist[j];
                k = j;
            }
        }
        flag[k] = 1;

        for(j = 0;j<DIJ_NODE_NUMBER;j++)
        {
            if(flag[j]== 0 && adj_Matrix[k][j]>0)
            {
                uint16_t tmp = min + adj_Matrix[k][j];
                if(tmp < dist[j])
                    dist[j] = tmp;
            }
        }
    }

    for(i = 0;i<DIJ_NODE_NUMBER;i++)
    {
        dist_result[i] = dist[i];
    }
}
