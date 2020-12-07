/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/12/06
 * This is the main file for Resistive Touch Screen
 */

#include <stdint.h>
#include <stdio.h>

#include "task1c_inits.h"
#include "task1c.h"

#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"

uint32_t ADC_value;
float temperature;
enum frequency freq = PRESET3; //  Select system clock frequency preset, 12MHz

int main()
{
    LCD_Init(); // Initialize LCD
    Touch_Init();
    LCD_ColorFill(Color4[2]); // fill LCD with green color
    PLL_Init(freq);           // Set system clock frequency to 12 MHz
    ADCReadPot_Init();        // Initialize ADC0 to read from the internal temperature sensor
    TimerADCTriger_Init();    // Initialize Timer0A to trigger ADC0
    LCD_SetCursor(30, 200);

    // print the virtual buttons on the LCD
    LCD_DrawCircle(50,
                   200,
                   20,
                   Color4[14]);
    LCD_Printf("120M Hz");
    LCD_SetCursor(250, 200);

    LCD_DrawCircle(270,
                   200,
                   20,
                   Color4[14]);
    LCD_Printf(" 12M Hz");
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

    unsigned long x = Touch_ReadX();
    unsigned long y = Touch_ReadY();
    if (x + y >= 3500)
    {
        freq = PRESET3; // set system clock frequency to 12 MHz
        PLL_Init(freq);
        GPTMTAILR_0 = 0xB71B00; // set max count down value to 12 million
        TimerADCTriger_Init();
    }
    else if (x + y >= 2600)
    {
        freq = PRESET1; // set system clock frequency to 120 MHz
        PLL_Init(freq);
        GPTMTAILR_0 = 0x7270E00; // set max count down value to 120 million
        TimerADCTriger_Init();
    }
    // set text cursor to top left of screen
    LCD_SetCursor(0, 0); 
    LCD_Printf("The current temperature is ");
    LCD_PrintFloat(temperature);
    LCD_Printf(" C, ");
    LCD_PrintFloat((temperature * 1.8) + 32.0);
    LCD_Printf(" F.\n");
    LCD_Printf("The current clock frequency is %d MHz.", freq);
}