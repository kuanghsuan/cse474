/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/11/04
 * This is the main file for traffic light system w/ the timer
 */

#include <stdint.h>
#include "task1b.h"

int main()
{
    GPTMInit();
    LED_init();
    extern_switch_init();

    while (1)
    {
        tffFunc();
    }
    return 0;
}

int time = 0; // declare time to count the time
int cnt = 0;
int prev = 0;

void GPTMInit()
{
    RCGCTIMER |= GPTM0_16_32;           // Enable 16/32 Timer 0

    GPTMCTL0 = GPTMA_DISABLE;           // Disable Timer A
    GPTMCFG0 = TM_MODE_32;              // Select two timer to 32-bit mode
    GPTMTAMR0 |= TAMR_PER_TM_MODE;      // Set periodic timer mode
    GPTMTAMR0 &= ~TACDIR_COUNT_UP;      // Configure TACDIR0 to count down
    GPTMTAILR0 = N16_MIL;               // Load value of 16 million into GPTMTAILR0
    GPTMCTL0 |= GPTMA_ENABLE;           // Enable Timer A
}

int isReached()
{
    return (GPTMRIS0 & 0x1);
}

void resetTimer()
{
    GPTMICR0 |= 0x1;
}

void oneHertz(int n)
{
    resetTimer();
    int t = 0;
    while (t < n)
    {
        if (isReached())
        {
            t++;
            resetTimer();
        }
    }
}


void LED_init(void)
{
    // Enable Port L Gating Clock
    RCGCGPIO |= Port_L;
    
    // Disable PL2, PL3, PL4 analog function
    GPIOAMSEL_L &= ~0x4;
    GPIOAMSEL_L &= ~0x8;
    GPIOAMSEL_L &= ~0x10;
    // Select PL2, PL3, PL4 regular port function
    GPIOAFSEL_L &= ~0x4;
    GPIOAFSEL_L &= ~0x8;
    GPIOAFSEL_L &= ~0x10;
    // Set PL2, PL3, PL4 to input direction
    GPIODIR_L |= 0x4;
    GPIODIR_L |= 0x8;
    GPIODIR_L |= 0x10;
    // Enable PL2, PL3, PL4 digital function
    GPIODEN_L |= 0x4;
    GPIODEN_L |= 0x8;
    GPIODEN_L |= 0x10;
}
// turn on Green LED
void Go_State(void)
{
    GPIODATA_L &= ~0x4;
    GPIODATA_L &= ~0x8;
    GPIODATA_L |= 0x10;
}
// turn on Red LED
void Stop_State(void)
{
    GPIODATA_L |= 0x4;
    GPIODATA_L &= ~0x8;
    GPIODATA_L &= ~0x10;
}
// turn on Yellow LED
void Warn_State(void)
{
    GPIODATA_L &= ~0x4;
    GPIODATA_L |= 0x8;
    GPIODATA_L &= ~0x10;
}
// turn off all LEDs
void LED_off(void)
{
    GPIODATA_L &= ~0x4;
    GPIODATA_L &= ~0x8;
    GPIODATA_L &= ~0x10;
}

void extern_switch_init(void)
{
    RCGCGPIO |= 0x400;
    // Disable PL0, PL1 analog function
    GPIOAMSEL_L &= ~0x1;
    GPIOAMSEL_L &= ~0x2;
    // Select PL0, PL1 regular port function
    GPIOAFSEL_L &= ~0x1;
    GPIOAFSEL_L &= ~0x2;
    // Set PL0, PL1 to input direction
    GPIODIR_L &= ~0x1;
    GPIODIR_L &= ~0x2;
    // Enable PL0, PL1 digital function
    GPIODEN_L |= 0x1;
    GPIODEN_L |= 0x2;   
}

unsigned long sys_switch(void)
{
    int firstTime = GPIODATA_L & 0x1;
    if (firstTime == 0)
        return 0;
    oneHertz(2);
    int secondTime = GPIODATA_L & 0x1;
    return firstTime && secondTime;
}

unsigned long ped_switch(void)
{
    int firstTime = GPIODATA_L & 0x2;
    if (firstTime == 0)
        return 0;
    oneHertz(2);
    int secondTime = GPIODATA_L & 0x2;
    return firstTime && secondTime;
}

enum TFF_State
{
    TFF_Begin,
    TFF_S0,
    TFF_S1,
    TFF_S2,
    TFF_End
} TFF_State; // state variable declaration

void tffFunc()
{
    if (GPTMRIS0 & 0x1)
    {
        cnt += 1;
        resetTimer();
    }

    switch (TFF_State)
    {
    case TFF_Begin:
        prev = cnt;
        TFF_State = TFF_S2;
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
        //else if (time == 500000)
        else if (cnt - prev >= 5)
        {
            prev = cnt;
            TFF_State = TFF_S2;
        }
        else
            time++;
        break;
    case TFF_S1:

        if (sys_switch())
        {
            TFF_State = TFF_End;
        }
        else if (cnt - prev >= 5)
        {
            prev = cnt;
            TFF_State = TFF_S2;
        }
        else
            time++;
        break;
    case TFF_S2:

        if (sys_switch())
        {
            TFF_State = TFF_End;
        }
        else if (cnt - prev >= 5)
        {
            prev = cnt;
            TFF_State = TFF_S0;
            time = 0;
        }
        else
            time++;
        break;
    case TFF_End:
        LED_off();
        time = 0;
        if (sys_switch())
        {
            TFF_State = TFF_Begin;
        }
        break;
    default:
        TFF_State = TFF_Begin;
        break;
    }
    switch (TFF_State) // State actions
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