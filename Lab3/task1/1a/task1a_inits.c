/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/11/19
 * This is the initialized file for changing the LED by measuring the resistance /w ADC
 */

#include "PLL_Header.h"
#include "task1a_inits.h"

// STEP 0a: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

int PLL_Init(enum frequency freq)
{
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4); // Power up MOSC
    MOSCCTL &= ~(0x8); // Enable MOSC
    while ((RIS & 0x100) == 0)
    {
    };                       // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20); // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24); // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60; // Set MINT field
    PLLFREQ1 |= 0x4;  // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6)); // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0)); // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5)); // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28); // Temporarilly bypass PLL

    switch (freq)
    {
    case 120:
        MEMTIM0 |= (0x6 << 22) | (0x6 << 6); // Set FBCHT and EBCHT
        MEMTIM0 |= (0x5 << 16) | (0x5 << 0); // Set EWS and FWS
        RSCLKCFG |= 0x3;                     // Set PSYSDIV to use 120 MHZ clock
        RSCLKCFG &= ~0x3FC;                  // Update PSYSDIV field
        break;
    case 60:
        MEMTIM0 |= (0x3 << 22) | (0x3 << 6); // Set FBCHT and EBCHT
        MEMTIM0 |= (0x2 << 16) | (0x2 << 0); // Set EWS and FWS
        RSCLKCFG |= 0x7;                     // Set PSYSDIV to use 60 MHZ clock
        RSCLKCFG &= ~0x3F8;                  // Update PSYSDIV field
        break;
    case 12:
        MEMTIM0 |= (0x1 << 21) | (0x1 << 5); // Set FBCE and EBCE
        RSCLKCFG |= 0x27;                    // Set PSYSDIV to use 12 MHZ clock
        RSCLKCFG &= ~0x3D8;                  // Update PSYSDIV field
        break;
    default:
        return -1;
    }

    RSCLKCFG |= (0x1 << 30); // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23); // Power up PLL
    while ((PLLSTAT & 0x1) == 0)
    {
    }; // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28); // Use PLL and update Memory Timing Register
    return 1;
}

void LED_Init(void)
{
    // STEP 1: Initialize the 4 on board LEDs by initializing the corresponding
    // GPIO pins.
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

    // YOUR CODE HERE
}

void ADCReadPot_Init(void)
{

    volatile unsigned short delay = 0;
    RCGCADC |= 0x1; // 2.1: Enable the ADC0 clock
    delay++;        // 2.2: Delay for RCGCADC (Refer to page 1073)
    delay++;

    PLLFREQ0 |= 0x00800000; // 2.3: Power up the PLL (if not already)
    while (PLLSTAT != 0x1)
        ; // 2.4: Wait for the PLL to lock

    ALTCLKCFG |= 0x0; // specify the alternate clock source as PIOSC
    ADCCC |= 0x1;     // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG

    RCGCGPIO |= 0x10; // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1), GPIO port E
    delay++;          // 2.7: Delay for RCGCGPIO
    delay++;
    GPIOAFSEL_E &= ~0x8; // 2.8: Set the GPIOAFSEL bits for the ADC input pins
    GPIODEN_E &= ~0x8;   // 2.9: Clear the GPIODEN bits for the ADC input pins
    GPIOAMSEL_E |= 0x8;  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)

    ADCACTSS &= ~(0x1 << 3); // 2.11: Disable sample sequencer 3 (SS3)

    ADCEMUX |= (0x5 << 12);  // 2.12: Select timer as the trigger for SS3
    //ADCEMUX = 0xF

    ADCSSEMUX3 &= ~(0xF); // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
    ADCSSMUX3 &= ~(0xF);
    ADCSSCTL3 &= ~(0x1 << 3); // 2.14: Configure ADCSSCTL3 register
    ADCSSCTL3 |= (0x1 << 2);
    ADCSSCTL3 |= (0x1 << 1);
    ADCIM |= (0x1 << 3);    // 2.15: Set the SS3 interrupt mask
    INTERRUPT_ENABLE0 |= (0x1 << 17); // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
    ADCACTSS |= (0x1 << 3); // 2.17: Enable ADC0 SS3
}

void TimerADCTriger_Init(void)
{
    volatile unsigned short delay = 0;
    RCGCTIMER |= 0x1; // GPTM timer0
    delay++;
    delay++;

    GPTMCTL_0 &= ~0x1;       // timer0 A is disabled
    GPTMCFG_0 |= 0x0;        // select the 32-bit timer configuration
    GPTMTAMR_0 |= 0x2;       // periodic timer mode
    GPTMTAMR_0 &= ~0x10;     // the timer counts down

    GPTMCTL_0 |= (0x1 << 5); // timer0 A ADC trigger is enabled
    GPTMADCEV_0 |= 0x1;      // timer0 A time out event ADC trigger is enabled

    GPTMTAILR_0 = 0xF42400;  // load the value 16,000,000
    GPTMICR_0 |= 0x1;        // clear timed out
    GPTMCTL_0 |= 0x1;        // timer0 A is enabled
}

// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler