/* MinimOSD-ng */

#include <stdio.h>
#include "uart.h"

#define DEBUG

int main(void)
{
  init_uart(19200);
#ifdef DEBUG
  printf("\nRESET!\n\n");
  printf("MinimOSD-ng\n");
#endif
  while (1)
  {
  }
}

