
#include<testbench/declaration.h>



__nv uint16_t SW_Results;
__nv uint16_t cnt;


uint16_t CRCheck_CCITT_Update(uint16_t init, uint16_t input)
{
    uint16_t CCITT = (uint8_t) (init >> 8) | (init << 8);
    CCITT ^= input;
    CCITT ^= (uint8_t) (CCITT & 0xFF) >> 4;
    CCITT ^= (CCITT << 8) << 4;
    CCITT ^= ((CCITT & 0xFF) << 4) << 1;
    return CCITT;
}


void crc_main()
{

    cnt = 0;
    SW_Results = CRC_INIT;

    run:

    SW_Results = CRCheck_CCITT_Update(SW_Results, CRC_Input[cnt] & 0xFF);
    SW_Results = CRCheck_CCITT_Update(SW_Results, (CRC_Input[cnt] >> 8) & 0xFF);
    ++cnt;

    SW_Results = CRCheck_CCITT_Update(SW_Results, CRC_Input[cnt] & 0xFF);
    SW_Results = CRCheck_CCITT_Update(SW_Results, (CRC_Input[cnt] >> 8) & 0xFF);
    ++cnt;

    SW_Results = CRCheck_CCITT_Update(SW_Results, CRC_Input[cnt] & 0xFF);
    SW_Results = CRCheck_CCITT_Update(SW_Results, (CRC_Input[cnt] >> 8) & 0xFF);
    ++cnt;

    SW_Results = CRCheck_CCITT_Update(SW_Results, CRC_Input[cnt] & 0xFF);
    SW_Results = CRCheck_CCITT_Update(SW_Results, (CRC_Input[cnt] >> 8) & 0xFF);
    ++cnt;

    if(cnt < CRC_LENGTH)
        goto run;

    return;
}
