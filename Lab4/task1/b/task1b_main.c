/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/12/06
 * This is the main file for Temperature Readings
 */

#include <stdint.h>
#include <stdio.h>

#include "task1b_inits.h"
#include "task1b.h"

#include "SSD2119_Display.h"

uint32_t ADC_value;
float temperature;
enum frequency freq = PRESET3; //  Select system clock frequency preset, 12MHz

int main()
{
    LCD_Init(); // Initialize LCD
    LCD_ColorFill(Color4[2]); // fill LCD with green color
    PLL_Init(freq);           // Set system clock frequency to 12 MHz
    switchesInit();           // Initialize SW1, SW2 (GPIO)
    ADCReadPot_Init();        // Initialize ADC0 to read from the internal temperature sensor
    TimerADCTriger_Init();    // Initialize Timer0A to trigger ADC0

    while (1)
    {
    }

    return 0;
}

void ADC0SS3_Handler(void)
{                           // implement the ADC ISR.
    ADCISC |= 0x8;          // clear the ADC0 interrupt flag
    GPTMICR_0 |= 0x1;       // clear timed out
    ADC_value = ADCSSFIFO3; // save the ADC value to global variable ADC_value
    temperature = 147.5 - ((75.0 * (3.3 - 0.0) * ADC_value) / 4096.0);
    int num = freq;

    if (is_switch2_pressed())
    {
        freq = PRESET3; // set system clock frequency to 12 MHz
        PLL_Init(freq);
        GPTMTAILR_0 = 0xB71B00; // set max count down value to 12 million
        TimerADCTriger_Init();
    }
    else if (is_switch1_pressed())
    {
        freq = PRESET1; // set system clock frequency to 120 MHz
        PLL_Init(freq);
        GPTMTAILR_0 = 0x7270E00; // set max count down value to 120 million
        TimerADCTriger_Init();
    }

    LCD_SetCursor(0, 0); // set text cursor to top left of screen
    LCD_Printf("The current temperature is ");
    LCD_PrintFloat(temperature);
    LCD_Printf(" C, ");
    LCD_PrintFloat((temperature * 1.8) + 32.0);
    LCD_Printf(" F.\n");
    LCD_Printf("The current clock frequency is %d MHz.", freq);
}

unsigned long is_switch1_pressed()
{
    return !(GPIODATA_J & 0x1);
}

unsigned long is_switch2_pressed()
{
    return !(GPIODATA_J & 0x2);
}