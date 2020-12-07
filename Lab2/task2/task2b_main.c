/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/10/21
 * This is the main file for Controlling the timer from a user switch (GPIO Interrupt)
 */

#include <stdint.h>
#include "task2b.h"

void main()
{

    GPTMInit();      // initialize GP timer
    switchesInit();  // initialize user switches
    ledInit();       // initial led
    interruptInit(); // initialize interrupt

    while (1)
    {
    }
}

void GPTMInit()
{
    RCGCTIMER |= GPTM0_16_32;       // Enable 16/32 Timer 0
    GPTMCTL0 = GPTMA_DISABLE;       // Disable Timer A
    GPTMCFG0 = TM_MODE_32;          // Select 32-bit mode

    GPTMTAMR0 |= TAMR_PER_TM_MODE;  // Set periodic timer mode
    GPTMTAMR0 &= ~TACDIR_COUNT_UP;  // Configure TACDIR to count down

    GPTMTAILR0 = N16_MIL;           // Load value of 16 million into GPTMTAILR
    GPTMCTL0 |= GPTMA_ENABLE;       // Enable Timer A
}

void interruptInit()
{
    GPTMIMR0 = TATOIM_ENABLE; // Enable Timer A Time-Out Interrupt

    INTERRUPT_ENABLE0 |= INT_19_ENABLE; // Enable interrupt 19
    INTERRUPT_ENABLE1 |= INT_51_ENABLE; // Enable interrupt 51
}

void switchesInit()
{
    RCGCGPIO |= Port_J;

    GPIODEN_J |= PJ0;             // enable PJ0
    GPIODEN_J |= PJ1;             // enable PJ1

    GPIODIR_J &= ~PJ0;            // set PJO as input
    GPIODIR_J &= ~PJ1;            // set PJ1 as input

    GPIOPUR_J |= PJ0;             // attach pull-up resistor to PJ0
    GPIOPUR_J |= PJ1;             // attach pull-up resistor to PJ1

    GPIOIM_J |= PJ0;              // PJ0 interrupt mask enable
    GPIOIM_J |= PJ1;              // PJ1 interrupt mask enable

    INTERRUPT_ENABLE1 |= INT_51_ENABLE; // enable GPIO Port J interrupt
}

void ledInit()
{
    // Enable N port
    RCGCGPIO |= Port_N;
    // Enable PN0, PN1
    GPIODEN_N |= PN0;
    GPIODEN_N |= PN1;
    // Set PN0, PN1 as output
    GPIODIR_N |= PN0;
    GPIODIR_N |= PN1;
}

void LED1_toggle()
{
    GPIODATA_N ^= 0x2;
}


void Timer0A_Handler()
{
    GPTMICR0 |= 0x1; // reset timer
    LED1_toggle();
}

unsigned long switch1_is_pressed()
{
    return (GPIORIS_J & 0x1);
}

unsigned long switch2_is_pressed()
{
    return (GPIORIS_J & 0x2);
}

void GPIO_PortJ_Handler(void)
{

    if (switch1_is_pressed())    // switch SW1 is pressed
    {                            
        GPTMCTL0 = GPTMA_DISABLE; // Disable Timer A
        GPIODATA_N |= PN0;        // Turn ON LED2
    }
    if (switch2_is_pressed())     // switch SW2 is pressed
    {                             
        GPTMCTL0 |= GPTMA_ENABLE; // Enable Timer A
        GPIODATA_N &= ~PN0;       // Turn OFF LED2
    }
    GPIOICR_J |= 0x3;
}











