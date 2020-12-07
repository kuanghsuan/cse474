/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/10/21
 * This is the main file for LEDs periodic task
 */

#include <stdint.h>
#include "task1.h"

int main()
{
    RCGCGPIO |= 0x20;   // GPIO port F
    RCGCGPIO |= 0x1000; // GPIO port N

    GPIODEN_F |= 0x01;  // enable port PF0
    GPIODEN_F |= 0x10;  // enable port PF4
    GPIODEN_N |= 0x1;   // enable port PN0
    GPIODEN_N |= 0x2;   // enable port PN1

    GPIODIR_F |= 0x01;  // set PF0 as output
    GPIODIR_F |= 0x10;  // set PF4 as output
    GPIODIR_N |= 0x1;   // set PN0 as output
    GPIODIR_N |= 0x2;   // set PN1 as output

    GPIODATA_F &= ~0x01; // set PF0 to 0
    GPIODATA_F &= ~0x10; // set PF4 to 0
    GPIODATA_N &= ~0x1;  // set PN0 to 0
    GPIODATA_N &= ~0x2;  // set PN1 to 0

    while (1)
    {
        GPIODATA_N = 0x2; // turn on LED1
        delay();
        GPIODATA_N = 0x0; // turn off LED1
        delay();
        GPIODATA_N = 0x1; // turn on LED2
        delay();
        GPIODATA_N = 0x0; // turn off LED2
        delay();
        GPIODATA_F = 0x10; // turn on LED3
        delay();
        GPIODATA_F = 0x0; // turn off LED3
        delay();
        GPIODATA_F = 0x1; // turn on LED4
        delay();
        GPIODATA_F = 0x0; // turn off LED4
        delay();
    }
    return 0;
}

void delay()
{
    for (int i = 0; i < 1000000; i++)
    {
    }
}
