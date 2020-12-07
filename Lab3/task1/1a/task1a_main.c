/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/11/19
 * This is the main file for changing the LED by measuring the resistance /w ADC
 */

#include <stdint.h>
#include "task1a_inits.h"
#include "task1a.h"

uint32_t ADC_value;

int main(void)
{
    // Select system clock frequency preset
    enum frequency freq = PRESET2; // 60 MHz
    PLL_Init(freq);                // Set system clock frequency to 60 MHz
    LED_Init();                    // Initialize the 4 onboard LEDs (GPIO)
    ADCReadPot_Init();             // Initialize ADC0 to read from the potentiometer
    TimerADCTriger_Init();         // Initialize Timer0A to trigger ADC0
    float resistance;

    while (1)
    {                                             // STEP 5: Change the pattern of LEDs based on the resistance.
        resistance = (ADC_value / 4095.0) * 10.0; // 5.1: Convert ADC_value to resistance in kilo-ohm
        if (resistance < 2.5)
        { // 5.2: Change the pattern of LEDs based on the resistance
            LED1_on();
            LED2_off();
            LED3_off();
            LED4_off();
        }
        else if (resistance < 5.0)
        {
            LED1_on();
            LED2_on();
            LED3_off();
            LED4_off();
        }
        else if (resistance < 7.5)
        {
            LED1_on();
            LED2_on();
            LED3_on();
            LED4_off();
        }
        else
        {
            LED1_on();
            LED2_on();
            LED3_on();
            LED4_on();
        }
    }
    return 0;
}

void ADC0SS3_Handler(void)
{                           // STEP 4: Implement the ADC ISR.
    ADCISC |= 0x8;          // 4.1: Clear the ADC0 interrupt flag
    GPTMICR_0 |= 0x1;       // clear timed out
    ADC_value = ADCSSFIFO3; // 4.2: Save the ADC value to global variable ADC_value
}

void LED1_on()
{
    GPIODATA_N |= 0x2; // turn on LED1
}

void LED1_off()
{
    GPIODATA_N &= ~0x2; // turn off LED1
}

void LED2_on()
{
    GPIODATA_N |= 0x1; // turn on LED2
}

void LED2_off()
{
    GPIODATA_N &= ~0x1; // turn off LED2
}

void LED3_on()
{
    GPIODATA_F |= 0x10; // turn on LED3
}

void LED3_off()
{
    GPIODATA_F &= ~0x10; // turn off LED3
}

void LED4_on()
{
    GPIODATA_F |= 0x1; // turn on LED4
}

void LED4_off()
{
    GPIODATA_F &= ~0x1; // turn off LED4
}