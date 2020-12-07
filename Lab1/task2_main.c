/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/10/21
 * This is the main file for traffic light system
 */
#include <stdint.h>
#include "lab1.h"

int time = 0; // declare time to count the time
enum TFF_State {TFF_Begin, TFF_S0, TFF_S1, TFF_S2, TFF_End} TFF_State; // state variable declaration

int main() {
    // initialize all the components
    LED_init();
    extern_switch_init();

    while (1)
    {
        tffFunc(); // loop the FSM
    }
    return 0;
}

void LED_init(void) {
    volatile unsigned short delay = 0;

    // Enable Port L Gating Clock
    RCGCGPIO |= 0x400;
    delay++;
    delay++;
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
void Go_State(void) {
    GPIODATA_L &= ~0x4;
    GPIODATA_L &= ~0x8;
    GPIODATA_L |= 0x10;
}
// turn on Red LED
void Stop_State(void) {
    GPIODATA_L |= 0x4;
    GPIODATA_L &= ~0x8;
    GPIODATA_L &= ~0x10;
}
// turn on Yellow LED
void Warn_State(void) {
    GPIODATA_L &= ~0x4;
    GPIODATA_L |= 0x8;
    GPIODATA_L &= ~0x10;
}
// turn off all LEDs
void LED_off(void) {
    GPIODATA_L &= ~0x4;
    GPIODATA_L &= ~0x8;
    GPIODATA_L &= ~0x10;
}

void extern_switch_init(void) {
    volatile unsigned short delay = 0;
    
    RCGCGPIO |= 0x400;
    delay++;
    delay++;
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

unsigned long sys_switch(void) {
    return (GPIODATA_L & 0x1);
}

unsigned long ped_switch(void) {
    return (GPIODATA_L & 0x2);
}

void tffFunc() {
    switch (TFF_State)
    {
    case TFF_Begin:
        TFF_State = TFF_S0;
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
            time++;
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
            time++;
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
            time++;
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

