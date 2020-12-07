/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/11/04
 * This is the main file for Turn off and on the user LEDs in a periodic pattern w/ timer
 */

#include <stdint.h>
#include "task1a.h"

void main()
{
    GPIOPortFInit();
    GPTMInit();

    while (1)
    {
        GPIODATA_F |= 0x01;
        while (!oneHertz())
        {
        }
        GPIODATA_F = 0x0;
        while (!oneHertz())
        {
        }
        GPIODATA_F |= 0x10;
        while (!oneHertz())
        {
        }
        GPIODATA_F = 0x0;
        while (!oneHertz())
        {
        }
        GPIODATA_N |= 0x1;
        while (!oneHertz())
        {
        }
        GPIODATA_N = 0x0;
        while (!oneHertz())
        {
        }
        GPIODATA_N |= 0x2;
        while (!oneHertz())
        {
        }
        GPIODATA_N = 0x0;
        while (!oneHertz())
        {
        }
    }
}

void GPTMInit()
{
    RCGCTIMER |= GPTM0_16_32;      // Enable 16/32 Timer 0

    GPTMCTL0 = GPTMA_DISABLE;      // Disable Timer A
    GPTMCFG0 = TM_MODE_32;         // Select 32-bit mode
    GPTMTAMR0 |= TAMR_PER_TM_MODE; // Set periodic timer mode
    GPTMTAMR0 &= ~TACDIR_COUNT_UP; // Configure TACDIR to count down
    GPTMTAILR0 = N16_MIL;          // Load value of 16 million into GPTMTAILR0
    GPTMCTL0 |= GPTMA_ENABLE;      // Enable Timer A
}

void GPIOPortFInit()
{
    // Enable N, F port
    RCGCGPIO |= Port_N;
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
}

int oneHertz()
{
    if (GPTMRIS0 & 0x1 == 0x1)
    {
        GPTMICR0 |= 0x1; // reset timer
        return 1;        // 1 second has finished
    }
    else
    {
        return 0; // 1 second has not yet finished
    }
}

