/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/10/21
 * This is the main.c for switches independently contol LEDs task
 */

#include <stdint.h>
#include "task1.h"

int main()
{
    RCGCGPIO |= 0x20;   // GPIO port F
    RCGCGPIO |= 0x1000; // GPIO port N
    RCGCGPIO |= 0x100;  // GPIO port J

    GPIODEN_J |= 0x1; // enable PJ0
    GPIODEN_J |= 0x2; // enable PJ1
    GPIODEN_N |= 0x1; // enable PN0
    GPIODEN_N |= 0x2; // enable PN1

    GPIODIR_N |= 0x1;  // set PN0 as output
    GPIODIR_N |= 0x2;  // set PN1 as output
    GPIODIR_J &= ~0x1; // set PJO as input
    GPIODIR_J &= ~0x2; // set PJ1 as input

    GPIOPUR_J |= 0x1;  // attach the pull-up resistor to PJ0
    GPIOPUR_J |= 0x2;  // attach the pull-up resistor to PJ1

    while (1) {
        if (switch1_is_pressed()) {
            LED1_on();
            LED2_off();
        }
        else if (switch2_is_pressed()) {
            LED1_off();
            LED2_on();
        }
        else // both SW1 and SW2 are not pressed
        { 
            LED1_off();
            LED2_off();
        }
    }

    return 0;
}

void LED1_on()
{
    GPIODATA_N |= 0x2;
}

void LED1_off()
{
    GPIODATA_N &= ~0x2;
}

void LED2_on()
{
    GPIODATA_N |= 0x1;
}

void LED2_off()
{
    GPIODATA_N &= ~0x1;
}

// check the PJ0 value
unsigned long switch1_is_pressed()
{
    return !(GPIODATA_J & 0x1);
}

// check the PJ1 value
unsigned long switch2_is_pressed()
{
    return !(GPIODATA_J & 0x2);
}