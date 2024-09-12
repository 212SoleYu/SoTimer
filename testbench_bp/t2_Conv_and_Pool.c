/*
 * File name: t2_Conv_and_Pool.c
 * Description: ���ڲ��Եĵ���������
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


void testbench_2()
{
    set_breakpoint;
    __no_operation();
    phase_update;

    // phase 1 ͨ��DMA���佫����������FRAM���䵽RAM�н��в���
    __no_operation();
    DMA_disableTransfers(DMA_CHANNEL_0);
    DMA_setSrcAddress(DMA_CHANNEL_0,origin_matrix,DMA_DIRECTION_INCREMENT);
    DMA_setDstAddress(DMA_CHANNEL_0,input_matrix,DMA_DIRECTION_INCREMENT);
    DMA_setTransferSize(DMA_CHANNEL_0, INPUT_SIZE);

    DMA_enableTransfers(DMA_CHANNEL_0);
    DMA_startTransfer(DMA_CHANNEL_0);
    DMA_disableTransfers(DMA_CHANNEL_0);


    // phase 2 ʹ��Ԥ��ľ���������л������

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


    // phase 3 ����õľ����������ٴν��гػ�
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



    // phase 4 ���ػ���Ľ�����,�������õ�A0��Ҫ����A1�ļ�¼
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
