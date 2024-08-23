#include <Modules/driver_include.h>
#include <testbench/declaration.h>
// Shared Variables

__nv uint32_t _v_seed;
__nv uint16_t _v_iter;
__nv uint16_t _v_func;
__nv uint16_t _v_n_0;
__nv uint16_t _v_n_1;
__nv uint16_t _v_n_2;
__nv uint16_t _v_n_3;
__nv uint16_t _v_n_4;
__nv uint16_t _v_n_5;
__nv uint16_t _v_n_6;


int Bitcount_RecursiveCnt(uint32_t x)
{
    int cnt = bc_bits[(int)(x & 0x0000000FL)];

    if (0L != (x >>= 4))
        cnt += Bitcount_RecursiveCnt(x);

    return cnt;
}

int Bitcount_NonRecursiveCnt(uint32_t x)
{
    int cnt = bc_bits[(int)(x & 0x0000000FL)];

    while (0L != (x >>= 4)) {
        cnt += bc_bits[(int)(x & 0x0000000FL)];
    }

    return cnt;
}
void bc_main()
{
    union {
        unsigned char ch[4];
        long y;
    } U;
    uint32_t tmp_seed;
    uint32_t temp;
    uint16_t __cry;
    unsigned char * Ptr;
    int Accu;
    unsigned i, nn;


    _v_func = 0;
    _v_n_1 = _v_n_2 = _v_n_3 = _v_n_4 = _v_n_5 = _v_n_6 = 0;

    Func_Select:
    _v_seed = (uint32_t)BITCOUNT_SEED;
    _v_iter = 0;
    switch(_v_func++)
    {
    case 0:     goto func0;
    case 1:     goto func1;
    case 2:     goto NTBL0;
    case 3:     goto NTBL1;
    case 4:     goto BW_BTBL;
    case 5:     goto AR_BTBL;
    case 6:     goto Bit_Shifter;
    default:    return;
    }

    func0:
    tmp_seed = _v_seed;
    _v_seed = tmp_seed + 13;
    temp = 0;

    if (tmp_seed) do
        temp++;
    while ( 0 != (tmp_seed = tmp_seed & (tmp_seed - 1)) );

    _v_n_0 += temp;
    _v_iter++;
    if (_v_iter < BITCOUNT_ITER)
        goto func0;
    else
        goto Func_Select;

    func1:
    tmp_seed = _v_seed;
    _v_seed = tmp_seed + 13;

    tmp_seed = ((tmp_seed & 0xAAAAAAAAL) >>  1) + (tmp_seed & 0x55555555L);
    tmp_seed = ((tmp_seed & 0xCCCCCCCCL) >>  2) + (tmp_seed & 0x33333333L);
    tmp_seed = ((tmp_seed & 0xF0F0F0F0L) >>  4) + (tmp_seed & 0x0F0F0F0FL);
    tmp_seed = ((tmp_seed & 0xFF00FF00L) >>  8) + (tmp_seed & 0x00FF00FFL);
    tmp_seed = ((tmp_seed & 0xFFFF0000L) >> 16) + (tmp_seed & 0x0000FFFFL);

    _v_n_1 += (int)tmp_seed;
    _v_iter++;
    if (_v_iter < BITCOUNT_ITER)
        goto func1;
    else
        goto Func_Select;

    NTBL0:
    tmp_seed = _v_seed;
    _v_n_2 += Bitcount_NonRecursiveCnt(tmp_seed);
    _v_seed = tmp_seed + 13;

    _v_iter++;
    if(_v_iter < BITCOUNT_ITER)
        goto NTBL0;
    else
        goto Func_Select;

    NTBL1:
    __cry = _v_seed;

    _v_n_3 += bc_bits[ (int) (__cry & 0x0000000FUL)] +
            bc_bits[ (int)((__cry & 0x000000F0UL) >> 4) ] +
            bc_bits[ (int)((__cry & 0x00000F00UL) >> 8) ] +
            bc_bits[ (int)((__cry & 0x0000F000UL) >> 12)] +
            bc_bits[ (int)((__cry & 0x000F0000UL) >> 16)] +
            bc_bits[ (int)((__cry & 0x00F00000UL) >> 20)] +
            bc_bits[ (int)((__cry & 0x0F000000UL) >> 24)] +
            bc_bits[ (int)((__cry & 0xF0000000UL) >> 28)] ;

    tmp_seed = _v_seed;
    _v_seed = tmp_seed + 13;
    _v_iter++;
    if(_v_iter < BITCOUNT_ITER)
        goto NTBL1;
    else
        goto Func_Select;

    BW_BTBL:
    U.y = _v_seed;
    _v_n_4 += bc_bits[ U.ch[0] ] + bc_bits[ U.ch[1] ] +
            bc_bits[ U.ch[3] ] + bc_bits[ U.ch[2] ];

    tmp_seed = _v_seed;
    _v_seed = tmp_seed + 13;
    _v_iter++;
    if(_v_iter < BITCOUNT_ITER)
        goto BW_BTBL;
    else
        goto Func_Select;

    AR_BTBL:
    Ptr = (unsigned char *) &_v_seed;
    Accu  = bc_bits[ *Ptr++ ];
    Accu += bc_bits[ *Ptr++ ];
    Accu += bc_bits[ *Ptr++ ];
    Accu += bc_bits[ *Ptr ];
    _v_n_5 += Accu;

    tmp_seed = _v_seed;
    _v_seed = tmp_seed + 13;
    _v_iter++;
    if(_v_iter < BITCOUNT_ITER)
        goto AR_BTBL;
    else
        goto Func_Select;

    Bit_Shifter:

    tmp_seed = _v_seed;
    for (i = nn = 0;
            tmp_seed && (i < (sizeof(long) * BITCOUNT_CHARBIT));
            ++i, tmp_seed >>= 1)
    {
        nn += (unsigned)(tmp_seed & 1L);
    }

    _v_n_6 += nn;

    tmp_seed = _v_seed;
    _v_seed = tmp_seed + 13;
    _v_iter++;
    if(_v_iter < BITCOUNT_ITER)
        goto Bit_Shifter;
    else
        goto Func_Select;
}
