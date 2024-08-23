#include<Modules/redirection.h>


// 选择printf重定向到那个模块，0代表与EZ-fet通信，1代表与收发器通信，前提是两个UART模块都初始化完成。
#define MODULE_ENABLE    0

#if (MODULE_ENABLE == 0)

int fputc(int _c, register FILE *_fp)
{
  EUSCI_A_UART_transmitData(EUSCI_A0_BASE, (unsigned char) _c );
  return((unsigned char)_c);
}

int fputs(const char *_ptr, register FILE *_fp)
{
  unsigned int i, len;

  len = strlen(_ptr);

  for(i=0 ; i<len ; i++)
  {
    EUSCI_A_UART_transmitData(EUSCI_A0_BASE, (unsigned char) _ptr[i]);
  }

  return len;
}

#endif

#if (MODULE_ENABLE == 1)

int fputc(int _c, register FILE *_fp)
{
  EUSCI_A_UART_transmitData(EUSCI_A1_BASE, (unsigned char) _c );
  return((unsigned char)_c);
}

int fputs(const char *_ptr, register FILE *_fp)
{
  unsigned int i, len;

  len = strlen(_ptr);

  for(i=0 ; i<len ; i++)
  {
    EUSCI_A_UART_transmitData(EUSCI_A1_BASE, (unsigned char) _ptr[i]);
  }

  return len;
}


#endif

