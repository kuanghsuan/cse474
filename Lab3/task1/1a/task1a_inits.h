/**
 * EE/CSE 474: Lab3 drivers header file
 */

// NOTE: All necessary functions for Task 1a have been declared in
// this header file, and thus you should not modify it for task 1a.
// However, you may modify it if you want to reuse it for other tasks.

#ifndef _Lab3_Inits_H_
#define _Lab3_Inits_H_

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define Port_F 0x20
#define Port_N 0x1000
#define Port_E 0x10

// To set up timers and change the timers
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
// GPTM Timer 0 addresses
#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))
#define GPTMADCEV_0 (*((volatile uint32_t *)0x40030070))
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define GPTMIMR_0 (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))

// ADC
#define RCGCADC (*((volatile uint32_t *)0x400FE638))
#define ADCACTSS (*((volatile uint32_t *)0x40038000))
#define ADCEMUX (*((volatile uint32_t *)0x40038014))
#define ADCSSCTL3 (*((volatile uint32_t *)0x40080A4))
#define ADCIM (*((volatile uint32_t *)0x40038008))
#define ADCSSFIFO3 (*((volatile uint32_t *)0x400380A8))
#define ADCISC (*((volatile uint32_t *)0x4003800C))
#define ALTCLKCFG (*((volatile uint32_t *)0x400FE138))
#define ADCCC (*((volatile uint32_t *)0x40038FC8))

#define ADCSSEMUX3 (*((volatile uint32_t *)0x400380B8))
#define ADCSSMUX3 (*((volatile uint32_t *)0x400380A0))

// Interrupt
#define GPTMIMR0 (*((volatile uint32_t *)0x40030018))
#define GPTMIMR1 (*((volatile uint32_t *)0x40031018))
#define GPIORIS_J (*((volatile uint32_t *)0x40060414))
#define GPIOICR_J (*((volatile uint32_t *)0x4006041C))
#define GPIOIM_J (*((volatile uint32_t *)0x40060410))

// Interrupt Configuation
#define INTERRUPT_ENABLE0 (*((volatile uint32_t *)0xE000E100))
#define INTERRUPT_ENABLE1 (*((volatile uint32_t *)0xE000E104))
#define TATOIM_ENABLE 0x1
#define INT_19_ENABLE 0x80000
#define INT_51_ENABLE 0x80000

// Port F Address
#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))

// Port N Address
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

// Port E Address
#define GPIODIR_E (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E (*((volatile uint32_t *)0x4005C51C))
#define GPIODATA_E (*((volatile uint32_t *)0x4005C3FC))

#define GPIOAMSEL_E (*((volatile uint32_t *)0x4005C528))
#define GPIOAFSEL_E (*((volatile uint32_t *)0x4005C420))

// Port J Address
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))

// Port F Control
#define PF0 0x01 // connect to LED4
#define PF4 0x10 // connect to LED3

// Port N Control
#define PN0 0x1 // connect to LED2
#define PN1 0x2 // connect to LED1

// Port E Control
#define PE0 0x1
#define PE1 0x2
#define PE2 0x4
#define PE3 0x8
// Preset frequency for 120 MHZ, 60 MHZ, and 12 MHZ clock
// Pass in the preset to Timer1_Init and PLL_Init to configure
// the system clock to specified frequency
enum frequency
{
    PRESET1 = 120,
    PRESET2 = 60,
    PRESET3 = 12
};

// Initializes the PLL module and generates a system clock frequency
// that equal to the frequency preset.
// Returns 1 if configured successfully, -1 if you select a non-exist preset.
int PLL_Init(enum frequency freq);

// Initializes the 4 onboard LEDs.
void LED_Init(void);

// Initializes ADC Module 0 Sample Sequencer 3. The module is triggered by
// Timer module 0 subtimer A at 1 HZ. The interupt of ADC0 SS3 will be
// generated whenever the A/D conversion is done.
void ADCReadPot_Init(void);

// Initializes Timer 0A to trigger ADC0 at 1 HZ.
void TimerADCTriger_Init(void);

#endif // _Lab3_Inits_H_