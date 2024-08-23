/*
 * File name: testbench_3_Cov.c
 * Description: 用于测试的第三个例程，该例程的初步构想为：
 *              1. 预先与另一台主机建立通讯，各自完成初始化任务
 *              2. 本机向从机发送信号，从机发送若干字节的数据，填充本机预留的矩阵，此处可选使用DMA来进行传输
 *              3. 本机接受后进行一次卷积，获得一个小的矩阵内容
 *              4. 进行一次池化，再获得一个更小一点的矩阵
 *              5. 将小的池化后的数组的内容返回给从机
 */
#include<testbench_bp/header.h>

uint16_t Convolution(uint8_t x, uint8_t y)
{
    uint16_t result = 0;
    uint8_t i,j;
    for (i = 0; i < KERNEL_LENGTH; i++) {
        for ( j = 0; j < KERNEL_LENGTH; j++) {
            result += input_matrix[x + i][y + j] * kernel_matrix[i][j];
        }
    }
    return result;
}

uint8_t MaxPool(uint8_t x, uint8_t y)
{
    uint8_t res = 0;
    uint8_t i,j;
    for(i = 0;i < POOL_KERNEL_LENGTH;i++)
    for(j = 0;j < POOL_KERNEL_LENGTH;j++)
        res = res > pool_matrix[i+x][j+y] ? res : pool_matrix[i+x][j+y];

    return res;

}


void testbench_3()
{
    set_breakpoint;
    __no_operation();
    phase_update;

    // phase 1 通过DMA传输将待计算矩阵从FRAM传输到RAM中进行操作
    __no_operation();
    DMA_disableTransfers(DMA_CHANNEL_0);
    DMA_setSrcAddress(DMA_CHANNEL_0,origin_matrix,DMA_DIRECTION_INCREMENT);
    DMA_setDstAddress(DMA_CHANNEL_0,input_matrix,DMA_DIRECTION_INCREMENT);
    DMA_setTransferSize(DMA_CHANNEL_0, INPUT_SIZE);

    DMA_enableTransfers(DMA_CHANNEL_0);
    DMA_startTransfer(DMA_CHANNEL_0);
    DMA_disableTransfers(DMA_CHANNEL_0);


    // phase 2 使用预设的卷积核来进行滑动点乘

    uint16_t i,j;

    for(i = 0; i < INPUT_LENGTH - KERNEL_LENGTH + 1; i++)
    {
        for(j = 0; j<INPUT_LENGTH - KERNEL_LENGTH + 1;j++)
        {
            pool_matrix[i][j] = Convolution(i,j);
        }

        if(i == 7)
            set_breakpoint;
    }

    set_breakpoint;
    __no_operation();
    phase_update;


    // phase 3 将获得的卷积结果矩阵再次进行池化
//    conv:
    for(i = 0; i < POOL_LENGTH;i += POOL_KERNEL_LENGTH)
    {
        for(j = 0;j < POOL_LENGTH;j += POOL_KERNEL_LENGTH)
        {
            output_matrix[i>>1][j>>1] = MaxPool(i,j);
        }
        if(i == 7)
            set_breakpoint;
    }
//    goto conv;
    set_breakpoint;
    __no_operation();
    phase_update;



    // phase 4 将池化后的结果输出,刻意设置到A0不要干扰A1的记录
//    EUSCI_A_UART_transmitData(EUSCI_A1_BASE, 'D');
    for(i = 0;i<OUTPUT_LENGTH;i++)
    {
        for(j = 0;j<OUTPUT_LENGTH;j++)
        {
            EUSCI_A_UART_transmitData(EUSCI_A0_BASE, output_matrix[i][j]);
//            printf("%d ",output_matrix[i][j]);
        }
//        printf("\n");
        EUSCI_A_UART_transmitData(EUSCI_A0_BASE, '\n');
    }

    set_breakpoint;
    __no_operation();
    phase_update;



}
