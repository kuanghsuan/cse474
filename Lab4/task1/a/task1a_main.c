/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/12/06
 * This is the main file for LCD Driver
 */

#include <stdint.h>
#include <stdio.h>

#include "task1a_inits.h"
#include "task1a.h"

#include "SSD2119_Display.h"

uint32_t ADC_value;
float temperature;
//  Select system clock frequency preset, 12MHz
enum frequency freq = PRESET3; 

int main()
{
    LCD_Init(); // Initialize LCD
    
    PLL_Init(freq);           // Set system clock frequency to 12 MHz
    ADCReadPot_Init();        // Initialize ADC0 to read from the internal temperature sensor
    TimerADCTriger_Init();    // Initialize Timer0A to trigger ADC0

    LCD_ColorFill(Color4[2]); // fill LCD with green color
    while (1)
    {
    }

    return 0;
}

void ADC0SS3_Handler(void)
{                           // implement the ADC ISR.
    ADCISC |= 0x8;          // clear the ADC0 interrupt flag
    GPTMICR_0 |= 0x1;       // clear timed out  
}