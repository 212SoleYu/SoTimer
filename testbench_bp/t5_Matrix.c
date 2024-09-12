/*
 * File name: t5_Matrix.c
 * Description: A single revursive Stassen Matrix multiplication.
 */


#include<testbench_bp/header.h>

static uint8_t a11[MATRIX_HALF][MATRIX_HALF];
static uint8_t a12[MATRIX_HALF][MATRIX_HALF];
static uint8_t a21[MATRIX_HALF][MATRIX_HALF];
static uint8_t a22[MATRIX_HALF][MATRIX_HALF];
static uint8_t b11[MATRIX_HALF][MATRIX_HALF];
static uint8_t b12[MATRIX_HALF][MATRIX_HALF];
static uint8_t b21[MATRIX_HALF][MATRIX_HALF];
static uint8_t b22[MATRIX_HALF][MATRIX_HALF];

static uint8_t m1[MATRIX_HALF][MATRIX_HALF];
static uint8_t m2[MATRIX_HALF][MATRIX_HALF];
static uint8_t m3[MATRIX_HALF][MATRIX_HALF];
static uint8_t m4[MATRIX_HALF][MATRIX_HALF];
static uint8_t m5[MATRIX_HALF][MATRIX_HALF];
static uint8_t m6[MATRIX_HALF][MATRIX_HALF];
static uint8_t m7[MATRIX_HALF][MATRIX_HALF];
static uint8_t tmp1[MATRIX_HALF][MATRIX_HALF];
static uint8_t tmp2[MATRIX_HALF][MATRIX_HALF];
static uint8_t tmp3[MATRIX_HALF][MATRIX_HALF];
static uint8_t tmp4[MATRIX_HALF][MATRIX_HALF];
static uint8_t tmp5[MATRIX_HALF][MATRIX_HALF];
static uint8_t tmp6[MATRIX_HALF][MATRIX_HALF];
static uint8_t tmp7[MATRIX_HALF][MATRIX_HALF];
static uint8_t tmp8[MATRIX_HALF][MATRIX_HALF];
static uint8_t tmp9[MATRIX_HALF][MATRIX_HALF];
static uint8_t tmp10[MATRIX_HALF][MATRIX_HALF];


void matrix_add(uint8_t a[MATRIX_HALF][MATRIX_HALF], uint8_t b[MATRIX_HALF][MATRIX_HALF], uint8_t c[MATRIX_HALF][MATRIX_HALF]);
void matrix_sub(uint8_t a[MATRIX_HALF][MATRIX_HALF], uint8_t b[MATRIX_HALF][MATRIX_HALF], uint8_t c[MATRIX_HALF][MATRIX_HALF]);
void matrix_mul(uint8_t a[MATRIX_HALF][MATRIX_HALF], uint8_t b[MATRIX_HALF][MATRIX_HALF], uint8_t c[MATRIX_HALF][MATRIX_HALF]);

void partition(const uint8_t src[MATRIX_SIZE][MATRIX_SIZE], uint8_t dst1[MATRIX_HALF][MATRIX_HALF], uint8_t dst2[MATRIX_HALF][MATRIX_HALF] ,uint8_t dst3[MATRIX_HALF][MATRIX_HALF],uint8_t dst4[MATRIX_HALF][MATRIX_HALF]);
void recover_matrix(uint8_t dst[MATRIX_SIZE][MATRIX_SIZE], uint8_t src1[MATRIX_HALF][MATRIX_HALF], uint8_t src2[MATRIX_HALF][MATRIX_HALF] ,uint8_t src3[MATRIX_HALF][MATRIX_HALF],uint8_t src4[MATRIX_HALF][MATRIX_HALF]);
void testbench_5()
{
    __no_operation();
    set_breakpoint;
      __no_operation();
      phase_update;

    // partition

    partition(A_MATRIX,a11,a12,a21,a22);
    partition(B_MATRIX,b11,b12,b21,b22);

    set_breakpoint;

    // compute add and sub

    matrix_add(a11,a22,tmp1);
    matrix_add(b11,b22,tmp2);
    set_breakpoint;
    matrix_add(a21,a22,tmp3);
    matrix_sub(b12,b22,tmp4);
    set_breakpoint;
    matrix_sub(b21,b11,tmp5);
    matrix_add(a11,a12,tmp6);
    set_breakpoint;
    matrix_sub(a21,a11,tmp7);
    matrix_add(b11,b12,tmp8);
    set_breakpoint;
    matrix_sub(a12,a22,tmp9);
    matrix_add(b21,b22,tmp10);

    set_breakpoint;
      __no_operation();
      phase_update;


    // multiply
    matrix_mul(tmp1,tmp2,m1);
    matrix_mul(tmp3,b11,m2);
    set_breakpoint;
    matrix_mul(tmp4,a11,m3);
    matrix_mul(tmp5,a22,m4);
    set_breakpoint;
    matrix_mul(tmp6,b22,m5);
    matrix_mul(tmp7,tmp8,m6);
    set_breakpoint;
    matrix_mul(tmp9,tmp10,m7);

//
    set_breakpoint;
    __no_operation();
    phase_update;
//    //recovery

    matrix_add(m1,m4,tmp1);
    matrix_sub(tmp1,m5,tmp1);
    matrix_add(tmp1,m7,tmp1);
    matrix_add(m3,m5,tmp2);
    set_breakpoint;
    matrix_add(m2,m4,tmp3);
    matrix_add(m1,m3,tmp4);
    matrix_sub(tmp4,m2,tmp4);
    matrix_add(tmp4,m6,tmp4);

    set_breakpoint;

    recover_matrix(C_MATRIX,tmp1,tmp2,tmp3,tmp4);
//
      set_breakpoint;
      __no_operation();
      phase_update;
}


void matrix_add(uint8_t a[MATRIX_HALF][MATRIX_HALF], uint8_t b[MATRIX_HALF][MATRIX_HALF], uint8_t c[MATRIX_HALF][MATRIX_HALF])
{
    uint8_t i,j;
    for(i = 0;i<MATRIX_HALF;i++)
    {
        for(j = 0; j < MATRIX_HALF; j++)
        {
            c[i][j] = a[i][j]+b[i][j];
        }
    }
}

void matrix_sub(uint8_t a[MATRIX_HALF][MATRIX_HALF], uint8_t b[MATRIX_HALF][MATRIX_HALF], uint8_t c[MATRIX_HALF][MATRIX_HALF])
{
    uint8_t i,j;
    for(i = 0;i<MATRIX_HALF;i++)
    {
        for(j = 0; j < MATRIX_HALF; j++)
        {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
}

void matrix_mul(uint8_t a[MATRIX_HALF][MATRIX_HALF], uint8_t b[MATRIX_HALF][MATRIX_HALF], uint8_t c[MATRIX_HALF][MATRIX_HALF])
{
    uint8_t i,j,k;
    for(i = 0;i<MATRIX_HALF;i++)
    {
        for(j = 0; j < MATRIX_HALF; j++)
        {
            for(k =0;k<MATRIX_HALF;k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }

        }
    }
}

void partition(const uint8_t src[MATRIX_SIZE][MATRIX_SIZE], uint8_t dst1[MATRIX_HALF][MATRIX_HALF], uint8_t dst2[MATRIX_HALF][MATRIX_HALF] ,uint8_t dst3[MATRIX_HALF][MATRIX_HALF],uint8_t dst4[MATRIX_HALF][MATRIX_HALF])
{
    uint8_t i,j;
    for(i = 0;i<MATRIX_SIZE;i++)
    {
        for(j = 0;j<MATRIX_SIZE;j++)
        {
            if(i < MATRIX_HALF && j < MATRIX_HALF)
            {
                dst1[i][j] = src[i][j];
            }
            else if (i < MATRIX_HALF && j >= MATRIX_HALF )
            {
                dst2[i][j - MATRIX_HALF] = src[i][j];
            }
            else if (i >= MATRIX_HALF && j < MATRIX_HALF)
            {
                dst3[i - MATRIX_HALF][j] = src[i][j];
            }
            else if (i >= MATRIX_HALF && j >= MATRIX_HALF)
            {
                dst4[i - MATRIX_HALF][j-MATRIX_HALF] = src[i][j];
            }
        }
    }
}

void recover_matrix(uint8_t dst[MATRIX_SIZE][MATRIX_SIZE], uint8_t src1[MATRIX_HALF][MATRIX_HALF], uint8_t src2[MATRIX_HALF][MATRIX_HALF] ,uint8_t src3[MATRIX_HALF][MATRIX_HALF],uint8_t src4[MATRIX_HALF][MATRIX_HALF])
{
    uint8_t i,j;
    for(i = 0;i<MATRIX_SIZE;i++)
    {
        for(j = 0;j<MATRIX_SIZE;j++)
        {
            if(i < MATRIX_HALF && j < MATRIX_HALF)
            {
                dst[i][j] = src1[i][j];
            }
            else if (i < MATRIX_HALF && j >= MATRIX_HALF )
            {
                dst[i][j] = src2[i][j - MATRIX_HALF];
            }
            else if (i >= MATRIX_HALF && j < MATRIX_HALF)
            {
                dst[i][j] = src3[i - MATRIX_HALF][j];
            }
            else if (i >= MATRIX_HALF && j >= MATRIX_HALF)
            {
                dst[i][j] = src4[i -MATRIX_HALF][j - MATRIX_HALF];
            }
        }
    }
}
