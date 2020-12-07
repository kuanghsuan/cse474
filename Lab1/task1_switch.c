#include <stdint.h>
#include "lab1.h"

int main()
{
  // Enable N, J port
  RCGCGPIO |= Port_N;
  RCGCGPIO |= Port_J;
  // Enable PN0, PN1
  GPIODEN_N |= PN0;
  GPIODEN_N |= PN1;
  // Enable PJ0, PJ1
  GPIODEN_J |= PJ0;
  GPIODEN_J |= PJ1;

  // Set PN0, PN1 as output
  GPIODIR_N |= PN0;
  GPIODIR_N |= PN1;

  // Set PJ0, PJ1 as input
  GPIODIR_J = 0x0;

  // Attach PJ0, PJ1 to pull-up resistors
  GPIOPUR_J |= PJ0;
  GPIOPUR_J |= PJ1;

  while (1)
  {
    int SW1 = GPIODATA_J & 0x2;
    int SW2 = GPIODATA_J & 0x1;
    if (SW1 != 0x2 && SW2 != 0x1)
    {
      GPIODATA_N |= LED1;
      GPIODATA_N |= LED2;
    }
    else if (SW1 != 0x2)
    {
      GPIODATA_N |= LED2;
    }
    else if (SW2 != 0x1)
    {
      GPIODATA_N |= LED1;
    }
    else
    {
      GPIODATA_N = 0x0;
    }
  }

  return 0;
}
