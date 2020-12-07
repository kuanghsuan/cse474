/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/11/04
 * This is the main file for traffic light system w/ the interrupt
 */

#include <stdint.h>
#include "task2c.h"

int main()
{
    // initialize
    timer0Init();
    timer1Init();
    resetTimer0A();
    resetTimer1A();
    LED_init();
    sys_init();
    ped_init();

    SY_State = SY_start;
    PED_State = PED_start;
    TFF_State = TFF_start;

    while (1)
    {
        sysFuction();
        pedFunction();
        tffFunction();
    }

    return 0;
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
    ​// Set PL2, PL3, PL4 to input direction
    GPIODIR_L |= 0x4;
    GPIODIR_L |= 0x8;
    GPIODIR_L |= 0x10;
    ​// Enable PL2, PL3, PL4 digital function
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

void timer0Init()
{
    RCGCTIMER |= 0x1;             // GPTM Timer0

    GPTMCTL0 &= ~0x1;             // disable Timer0 A
    GPTMCFG0 |= 0x0;              // select the 32-bit timer configuration
    GPTMTAMR0 |= 0x2;             // periodic timer mode
    GPTMTAMR0 &= ~0x10;           // the timer counts down
    GPTMTAILR0 = 0xF42400;        // load the value 16,000,000
    GPTMIMR0 |= 0x1;              // Timer0 A timed-out interrupt enabled
    INTERRUPT_ENABLE0 |= 0x80000; // enable Timer0 A interrupt
    GPTMCTL0 |= 0x1;              // Timer0 A is enabled
}

void timer1Init()
{
    RCGCTIMER |= Port_F;           // GPTM Timer1

    GPTMCTL1 &= ~0x1;              // disable Timer1 A
    GPTMCFG1 |= 0x0;               // select the 32-bit timer configuration
    GPTMTAMR1 |= 0x2;              // periodic timer mode
    GPTMTAMR1 &= ~0x10;            // the timer counts down
    GPTMTAILR1 = 0xF42400;         // load the value 16,000,000
    GPTMIMR1 |= 0x1;               // Timer1 A timed-out interrupt enabled
    INTERRUPT_ENABLE0 |= 0x200000; // enable Timer1 A interrupt
    GPTMCTL1 |= 0x1;               // Timer1 A is enabled
}

void timer0Disable()
{
    GPTMCTL0 &= ~0x1;
}

void timer0Enable()
{
    GPTMCTL0 |= 0x1;
}

void resetTimer0A()
{
    GPTMICR0 |= 0x1;
}

void resetTimer1A()
{
    GPTMICR1 |= 0x1;
}

void sys_init()
{
    RCGCGPIO |= Port_F;

    GPIOAMSEL_L &= ~0x1;
    GPIOAFSEL_L &= ~0x1;
    GPIODIR_L &= ~0x1;
    GPIODEN_L |= 0x1;
}

unsigned long is_sys_pressed()
{
    return (GPIODATA_L & 0x1);
}

void ped_init()
{
    RCGCGPIO |= Port_F;

    GPIOAMSEL_L &= ~0x2;
    GPIOAFSEL_L &= ~0x2;
    GPIODIR_L &= ~0x2;
    GPIODEN_L |= 0x2;
}

unsigned long is_ped_pressed()
{
    return (GPIODATA_L & 0x2);
}

unsigned char sysCount; // record and accumulate the time (use for system button)
unsigned char sysMode;  // determine the system button state (offer to Moore Machine)

enum SY_States
{
    SY_start,
    SY_s0,
    SY_s1
} SY_State;

// Mealy machine
void sysFunction()
{ 
    switch (SY_State)
    {
    case SY_start:
        SY_State = SY_s0;
        timer0Disable();
        sysCount = 0;
        sysMode = 0;
        break;
    case SY_s0:
        if (is_sys_pressed())
        {
            SY_State = SY_s1;
            timer0Enable();
        }
        else
        {
            SY_State = SY_s0;
        }
        break;
    case SY_s1:
        if (sysCount == 2)
        {
            SY_State = SY_start;
            sysMode = 1;
        }
        else if (is_sys_pressed())
        {
            SY_State = SY_s1;
        }
        else
        {
            SY_State = SY_start;
        }
        break;
    }
}

unsigned char pedCount; // record and accumulate the time (use for pedestrian button)
unsigned char pedMode;  // determine the pedestrian button state (offer to Moore Machine)

enum PED_States
{
    PED_start,
    PED_s0,
    PED_s1
} PED_State;

// Mealy machine
void pedFunction()
{ 
    switch (PED_State)
    {
    case PED_start:
        PED_State = PED_s0;
        timer0Disable();
        pedCount = 0;
        pedMode = 0;
        break;
    case PED_s0:
        if (is_ped_pressed())
        {
            PED_State = PED_s1;
            timer0Enable();
        }
        else
        {
            PED_State = PED_s0;
        }
        break;
    case PED_s1:
        if (pedCount == 2)
        {
            PED_State = PED_start;
            pedMode = 1;
        }
        else if (is_ped_pressed())
        {
            PED_State = PED_s1;
        }
        else
        {
            PED_State = PED_start;
        }
        break;
    }
}

unsigned char count; // record and accumulate the time

enum TFF_States
{
    TFF_start,
    TFF_S0,
    TFF_S1,
    TFF_S2,
    TFF_end
} TFF_State;

// Moore machine
void tffFunction()
{ 
    switch (TFF_State)
    {
    case TFF_start:
        TFF_State = TFF_S0;
        count = 0;
        break;
    case TFF_S0:
        if (sysMode == 1)
        {
            TFF_State = TFF_end;
            count = 0;
        }
        else if (pedMode == 1)
        {
            TFF_State = TFF_S0;
            count = 0;
        }
        else if (count == 5)
        {
            TFF_State = TFF_S2;
            count = 0;
        }
        else
        {
            TFF_State = TFF_S0;
        }
        break;
    case TFF_S1:
        if (sysMode == 1)
        {
            TFF_State = TFF_end;
            count = 0;
        }
        else if (count == 5)
        {
            TFF_State = TFF_S0;
            count = 0;
        }
        else
        {
            TFF_State = TFF_S1;
        }
        break;
    case TFF_S2:
        if (sysMode == 1)
        {
            TFF_State = TFF_end;
            count = 0;
        }
        else if (pedMode == 1)
        {
            TFF_State = TFF_S1;
            count = 0;
        }
        else if (count == 5)
        {
            TFF_State = TFF_S0;
            count = 0;
        }
        else
        {
            TFF_State = TFF_S2;
        }
        break;
    case TFF_end:
        if (sysMode == 1)
        {
            TFF_State = TFF_start;
            count = 0;
        }
        else
        {
            TFF_State = TFF_end;
        }
        break;
    default:
        TFF_State = TFF_start;
        break;
    }

    switch (TFF_State)
    {
    case TFF_S0:
        Stop_State();
        break;
    case TFF_S1:
        Warn_State();
        break;
    case TFF_S2:
        Go_State();
        break;
    case TFF_end:
        LED_off();
        break;
    default:
        break;
    }
}

void Timer0A_Handler()
{
    resetTimer0A();
    if (is_sys_switch_pressed())
    {
        sysCount++;
    }
    if (is_ped_switch_pressed())
    {
        pedCount++;
    }
}

void Timer1A_Handler()
{
    resetTimer1A();
    count++;
}

