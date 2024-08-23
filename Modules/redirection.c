#include<Modules/redirection.h>


// ѡ��printf�ض����Ǹ�ģ�飬0������EZ-fetͨ�ţ�1�������շ���ͨ�ţ�ǰ��������UARTģ�鶼��ʼ����ɡ�
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

