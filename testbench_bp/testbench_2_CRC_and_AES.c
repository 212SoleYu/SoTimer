/*
 * File name: handwritten_mem.c
 * Date: 2024-03-13
 * Description: 手写的用于测试的分段程序，其功能如下：
 *              1. 使用CPU对内存中的CRC模块进行计算，得到一个软件结果SW_RESULT
 *              2. 使用CRC模块对相同结果进行计算，得到另一个模块结果RESULT，比较二者结果
 *              3. 使用AES加密模块对结果进行一轮解密
 */


#include<testbench_bp/header.h>

// CRC_LENGTH 512
void testbench_2()
{
    set_breakpoint;
    __no_operation();
    phase_update;

    uint16_t size = CRC_LENGTH;
    uint16_t i = 0;
    // phase 1 使用CPU对CRC进行计算，得到SW_RESULT

    SW_Results = CRC_INIT;
    const int round = (sizeof(CRC_Input) >> 1);
    for(i = 0; i < round; i++)
    {
        // First input upper byte
        SW_Results = CCITT_Update(SW_Results, (CRC_Input[i] >> 8) & 0xFF);

        // Then input lower byte
        SW_Results = CCITT_Update(SW_Results, CRC_Input[i] & 0xFF);

        // 共512次迭代，划分为4次
        if((i&0xFF) == 0x7F)
            set_breakpoint;
    }

    set_breakpoint;
    __no_operation();
    phase_update;

    // phase 2 使用CRC模块进行计算传输，size 大小为CRC_LENGTH 512
    CRC32_setSeed(0xFFFF, CRC16_MODE);


    for(i = 0; i < size; i++)
    {
        CRC32_set16BitData(CRC_Input[i],CRC16_MODE);

        // 共512次迭代，划分为4次
        if((i&0xFF) == 0x7F)
            set_breakpoint;
    }

    CRC_Result = CRC16INIRESW0;             // Save results (per CRC-CCITT standard)

    set_breakpoint;
    __no_operation();
    phase_update;
    // phase 3 CRC运算完毕后使用AES进行加密

//    AES256_clearInterrupt()
//    AES256_enableInterrupt(AES_BASE);
    uint8_t offset = 0;
    for(offset = 0;offset<32;offset++)
    {
        AES256_decryptData(AES_BASE, ciphertext + (offset*16), dataBuffer + (offset * 16));

        // 共32次迭代划分为两次
        if(offset == 16)
            set_breakpoint;
    }
//    AES256_disableInterrupt(AES_BASE);
    set_breakpoint;
    __no_operation();
    phase_update;

}


unsigned int CCITT_Update(unsigned int init, unsigned int input)
{
    unsigned int CCITT = (unsigned char) (init >> 8) | (init << 8);
    CCITT ^= input;
    CCITT ^= (unsigned char) (CCITT & 0xFF) >> 4;
    CCITT ^= (CCITT << 8) << 4;
    CCITT ^= ((CCITT & 0xFF) << 4) << 1;
    return CCITT;
}
