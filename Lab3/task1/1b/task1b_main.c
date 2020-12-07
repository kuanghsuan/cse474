/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/11/19
 * This is the main file for showing the temperature measuring the resistance /w ADC
 */

#include <stdint.h>
#include <stdio.h>
#include "task1b_inits.h"
#include "task1b.h"

uint32_t ADC_value;
float temperature;
enum frequency freq = PRESET3; //  Select system clock frequency preset, 12MHz

int main()
{
    PLL_Init(freq);        // Set system clock frequency to 12 MHz
    switchesInit();        // Initialize SW1, SW2 (GPIO)
    ADCReadPot_Init();     // Initialize ADC0 to read from the internal temperature sensor
    TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0

    while (1)
    {
    }

    return 0;
}

void ADC0SS3_Handler(void)
{                           // STEP 4: Implement the ADC ISR.
    ADCISC |= 0x8;          // 4.1: Clear the ADC0 interrupt flag
    GPTMICR_0 |= 0x1;       // clear timed out
    ADC_value = ADCSSFIFO3; // 4.2: Save the ADC value to global variable ADC_value
    temperature = 147.5 - ((75.0 * (3.3 - 0.0) * ADC_value) / 4096.0);

    if (is_switch1_pressed())
    {
        freq = PRESET3;         // Set system clock frequency to 12 MHz
        PLL_Init(freq);
        GPTMTAILR_0 = 0xB71B00; // set max count down value to 12 million
        TimerADCTriger_Init();
        printf("SW1\n");
    }
    if (is_switch2_pressed())
    {
        freq = PRESET1;          // Set system clock frequency to 120 MHz
        PLL_Init(freq);
        GPTMTAILR_0 = 0x7270E00; // set max count down value to 120 million
        TimerADCTriger_Init();
        printf("SW2\n");
    }
    printf("%f\n", temperature);
}

unsigned long is_switch1_pressed()
{
    return !(GPIODATA_J & 0x1);
}

unsigned long is_switch2_pressed()
{
    return !(GPIODATA_J & 0x2);
}