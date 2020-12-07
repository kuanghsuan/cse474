/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/11/19
 * This is the main file for showing the "Return-to-Sender" function
 */

#include <stdint.h>
#include <stdio.h>
#include "task2b_inits.h"
#include "task2b.h"

uint32_t ADC_value;
float temperature;
enum frequency freq = PRESET3; //  Select system clock frequency preset, 12MHz

void UART_Init()
{
    //RCGCUART |= 0x1; // Enable UART module 0
    RCGCUART |= 0x4; // Enable UART module 2

    RCGCGPIO |= 0x1; // Enable Port A clock

    GPIOPCTL |= (0x1 << 6); // Enable port control PA6
    GPIOPCTL |= (0x1 << 7); // Enable port control PA7

    UARTCTL2 &= ~0x1;       // Disable UART
    UARTCTL2 |= (0x3 << 8); // Enable UART transmission/reception

    UARTCC2 = 0x5; // Clock source is precision oscillator

    UARTIBRD2 = 104; // Write integer part of BRD to UARTIBRD
    UARTFBRD2 = 11;  // Write fractional part of BRD to UARTFBRD

    UARTLCRH2 |= (0x3 << 5); // 8-bit, no parity, 1 stop bit
    UARTCTL2 |= 0x1;         // Enable UART

    GPIOAFSEL |= (0x1 << 6); // Enable alt functions PA6
    GPIOAFSEL |= (0x1 << 7); // Enable alt functions PA7

    GPIODEN_A |= (0x1 << 6); // Enable Port A pins 6
    GPIODEN_A |= (0x1 << 7); // Enable Port A pins 7

    GPIODIR_A &= ~(0x1 << 6); // set PA0 to input(RXD)
    GPIODIR_A |= (0x1 << 7);  // set PA0 to output(TXD)
}

int main()
{
    PLL_Init(freq);        // Set system clock frequency to 12 MHz
    switchesInit();        // Initialize SW1, SW2 (GPIO)
    ADCReadPot_Init();     // Initialize ADC0 to read from the internal temperature sensor
    TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
    UART_Init();
    while (1)
    {
        while (UARTFR2 & 0x10) // wait til RXFE is 0
        {
        }
        char value = UARTDR2;
        while (UARTFR2 & 0x20) // wait til TXFF is 0
        {
        }

        UARTDR2 = value;
    }
    return 0;
}
void ADC0SS3_Handler(void)
{
    ADCISC |= 0x8;          // clear the ADC0 interrupt flag
    GPTMICR_0 |= 0x1;       // clear timed out
    ADC_value = ADCSSFIFO3; // save the ADC value to global variable ADC_value
    temperature = 147.5 - ((75.0 * (3.3 - 0.0) * ADC_value) / 4096.0);
}