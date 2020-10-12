#include <stdint.h>
#include "lab1.h"

void delay() // cause a delay
{
      for (int i = 0; i < 900000; i++)
      {
      }
}
int main()
{
      // Enable N, F port
      RCGCGPIO |= Port_N;
      RCGCGPIO |= Port_J;
      RCGCGPIO |= Port_F;

      // Enable PN0, PN1
      GPIODEN_N |= PN0;
      GPIODEN_N |= PN1;
      // Enable PF0, PF1
      GPIODEN_F |= PF0;
      GPIODEN_F |= PF4;

      // Set PN0, PN1 as input
      GPIODIR_N |= PN0;
      GPIODIR_N |= PN1;
      // Set PF0, PF4 as input
      GPIODIR_F |= PF0;
      GPIODIR_F |= PF4;

      while (1)
      {
            GPIODATA_F |= LED4;
            delay();
            GPIODATA_F = 0x0;
            delay();
            GPIODATA_F |= LED3;
            delay();
            GPIODATA_F = 0x0;
            delay();
            GPIODATA_N |= LED2;
            delay();
            GPIODATA_N = 0x0;
            delay();
            GPIODATA_N |= LED1;
            delay();
            GPIODATA_N = 0x0;
            delay();
      }

      return 0;
}
