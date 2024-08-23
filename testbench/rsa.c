#include<testbench/declaration.h>



__nv uint16_t candidate_e;
__nv uint16_t e_number;
__nv uint16_t enc_index;
__nv uint16_t dec_index;

__nv uint16_t public_n;
__nv uint16_t phi_n;
__nv uint16_t sqrt_candidate_e;

__nv uint16_t secret_d[RSA_MSGLENGTH];
__nv uint16_t public_e[RSA_MSGLENGTH];
__nv uint16_t enc_cipher[RSA_MSGLENGTH];
//__nv uint16_t plain[RSA_MSGLENGTH];
__nv uint16_t dec_plain[RSA_MSGLENGTH];

uint16_t RSA_PowerMod(uint16_t a, uint16_t b, uint16_t mod)
{
    uint16_t ans = 1;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1)
            ans = (ans * a) % mod;
        b = b / 2;
        a = (a * a) % mod;
    }
    return ans;
}

/* Square root by Newton's method. This code is from InK */
uint16_t RSA_Sqrt16(uint16_t x)
{
    uint16_t hi = 0xffff;
    uint16_t lo = 0;
    uint16_t mid = ((uint32_t)hi + (uint32_t)lo) >> 1;
    uint32_t s = 0;

    while (s != x && hi - lo > 1) {
        mid = ((uint32_t)hi + (uint32_t)lo) >> 1;
        s = (uint32_t)mid* (uint32_t)mid;
        if (s < x)
            lo = mid;
        else
            hi = mid;
    }

    return mid;
}


/* https://www.di-mgt.com.au/euclidean.html#extendedeuclidean */
uint16_t RSA_ModInv(uint16_t u, uint16_t v)
{
    uint16_t inv, u1, u3, v1, v3, t1, t3, q;
    int16_t iter;
    u1 = 1;
    u3 = u;
    v1 = 0;
    v3 = v;
    iter = 1;
    while (v3 != 0)
    {
        q = u3 / v3;
        t3 = u3 % v3;
        t1 = u1 + q * v1;
        u1 = v1; v1 = t1; u3 = v3; v3 = t3;
        iter = -iter;
    }
    if (iter < 0)
        inv = v - u1;
    else
        inv = u1;
    return inv;
}

uint8_t RSA_isPrime(uint16_t x, uint16_t sqrt_x)
{
    uint16_t i;
    for (i = 3; i <= sqrt_x; i += 2)
    {
        if (x % i == 0)
            return 0;
    }
    return 1;
}


void rsa_main()
{
    // Initialization
    uint16_t i;

    public_n = p * q;
    phi_n = (p - 1) * (q - 1);
    candidate_e = p + q - 1;
    e_number = 0;
    enc_index = 0;
    dec_index = 0;

    get_sqrt_e:
    sqrt_candidate_e = RSA_Sqrt16(candidate_e);

    if (RSA_isPrime(candidate_e, sqrt_candidate_e))
        public_e[e_number++] = candidate_e;

    if (e_number < RSA_MSGLENGTH)
    {
        candidate_e += 2;
        goto get_sqrt_e;
    }

    enc_main:
    i = enc_index++;
    enc_cipher[i] = RSA_PowerMod(rsa_msg[i], public_e[i], public_n);

    if (enc_index < RSA_MSGLENGTH)
        goto enc_main;

    calculate_d_main:
    i = dec_index;
    secret_d[i] = RSA_ModInv(public_e[i], phi_n);

    i = dec_index++;
    dec_plain[i] = RSA_PowerMod(enc_cipher[i], secret_d[i], public_n);

    if (dec_index < RSA_MSGLENGTH)
        goto calculate_d_main;

}

