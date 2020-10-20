#include <stdint.h>
#include "lab1.h"

void LED_init(void)
{
  volatile unsigned short delay = 0;

  // Enable Port L Gating Clock
  RCGCGPIO |= Port_L;
  delay++;
  delay++;
  // Disable PL2, PL3, PL4 analog function
  GPIOAMSEL_L &= ~PL2;
  GPIOAMSEL_L &= ~PL3;
  GPIOAMSEL_L &= ~PL4;
  // Select PN2PL2, PL3, PL4 regular port function
  GPIOAFSEL_C &= ~PL2;
  GPIOAFSEL_C &= ~PL3;
  GPIOAFSEL_C &= ~PL4;
  ​// Set PL2, PL3, PL4 to input direction
  GPIODIR_L |= PL2;
  GPIODIR_L |= PL3;
  GPIODIR_L |= PL4;
  ​// Enable PL2, PL3, PL4 digital function
  GPIODEN_L |= PL2;
  GPIODEN_L |= PL3;
  GPIODEN_L |= PL4;
}
// turn on Green LED
void Go_State(void)
{
  GPIODATA_L &= ~PL2;
  GPIODATA_L &= ~PL3;
  GPIODATA_L |= PL4;
}
// turn on Red LED
void Stop_State(void)
{
  GPIODATA_L |= PL2;
  GPIODATA_L &= ~PL3;
  GPIODATA_L &= ~PL4;
}
// turn on Yellow LED
void Warn_State(void)
{
  GPIODATA_L &= ~PL2;
  GPIODATA_L |= PL3;
  GPIODATA_L &= ~PL4;
}
// turn off all LEDs
void LED_off(void)
{
  GPIODATA_L &= ~PL2;
  GPIODATA_L &= ~PL3;
  GPIODATA_L &= ~PL4;
}

void extern_switch_init(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= Port_L;
  delay++;
  delay++;
  // Disable PL0, PL1 analog function
  GPIOAMSEL_L &= ~PL0;
  GPIOAMSEL_L &= ~PL1;
  // Select PL0, PL1 regular port function
  GPIOAFSEL_L &= ~PL0;
  GPIOAFSEL_L &= ~PL1;
  // Set PL0, PL1 to input direction
  GPIODIR_L &= ~PL0;
  GPIODIR_L &= ~PL1;
  // Enable PL0, PL1 digital function
  GPIODEN_L |= PL0;
  GPIODEN_L |= PL1;
}
unsigned long sys_switch(void)
{
  return (GPIODATA_L & PL0);
}

unsigned long ped_switch(void)
{
  return (GPIODATA_L & PL1);
}

int time = 0;
enum TFF_State
{
  TFF_Begin,
  TFF_S0,
  TFF_S1,
  TFF_S2,
  TFF_End
} TFF_State;
void tffFunc()
{
  switch (TFF_State)
  {
  case TFF_Begin:       // Transitions
    TFF_State = TFF_S0; // Initial transition
    break;
  case TFF_S0:
    if (sys_switch())
    {
      TFF_State = TFF_End;
    }
    else if (ped_switch())
    {
      TFF_State = TFF_S1;
      time = 0;
    }
    else if (time == 500000)
    {
      TFF_State = TFF_S2;
    }
    else
    {
      time++;
    }
    break;
  case TFF_S1:
    if (sys_switch())
    {
      TFF_State = TFF_End;
    }
    else if (time == 250000)
    {
      TFF_State = TFF_S2;
    }
    else
    {
      time++;
    }
    break;
  case TFF_S2:
    if (sys_switch())
    {
      TFF_State = TFF_End;
    }
    else if (time == 1000000)
    {
      TFF_State = TFF_S0;
      time = 0;
    }
    else
    {
      time++;
    }
    break;
  case TFF_End:
    LED_off();
    time = 0;
    if (sys_switch())
    {
      TFF_State = TFF_S0;
    }
    break;
  default:
    TFF_State = TFF_Begin;
    break;
  }
  switch (TFF_State)    // State actions
  {
  case TFF_S0:
    Go_State();
    break;
  case TFF_S1:
    Warn_State();
    break;
  case TFF_S2:
    Stop_State();
    break;
  case TFF_End:
    LED_off();
    break;
  default:
    break;
  }
}
int main()
{
  LED_init();
  extern_switch_init();
  while (1)
  {
    tffFunc();
  }
  return 0;
}
