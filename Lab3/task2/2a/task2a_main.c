/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/11/19
 * This is the main file for showing the temperature on the PuTTY
 */

#include <stdint.h>
#include <stdio.h>
#include "task2a_inits.h"
#include "task2a.h"

uint32_t ADC_value;
float temperature;
enum frequency freq = PRESET3; //  Select system clock frequency preset, 12MHz

int main()
{
    PLL_Init(freq);        // Set system clock frequency to 12 MHz
    
    ADCReadPot_Init();     // Initialize ADC0 to read from the internal temperature sensor
    TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
    UART_Init();
    while (1)
    {
    }

    return 0;
}

void ADC0SS3_Handler(void)
{                           
    ADCISC |= 0x8;          // clear the ADC0 interrupt flag
    GPTMICR_0 |= 0x1;       // clear timed out
    ADC_value = ADCSSFIFO3; // save the ADC value to global variable ADC_value
    temperature = 147.5 - ((75.0 * (3.3 - 0.0) * ADC_value) / 4096.0);

    char buffer[50];
    int length = sprintf(buffer, "%f\n\r", temperature); // convert "%f\n\r" into char[] and store it into buffer, return the length of char[]
    for (int i = 0; i < length; i++)
    {
        while (UARTFR & 0x20) // wait til TXFF is 0
        {
        }
        UARTDR = buffer[i];
    }
}


