#ifndef TASK1B_H_
#define TASK1B_H_

// To set up and change the data of GPIO
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
// GPIO Port E addresses
#define GPIOAMSEL_E (*((volatile uint32_t *)0x4005C528))
#define GPIODIR_E (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E (*((volatile uint32_t *)0x4005C51C))
#define GPIOAFSEL_E (*((volatile uint32_t *)0x4005C420))
#define GPIODATA_E (*((volatile uint32_t *)0x4005C3FC))
// GPIO Port J addresses
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))

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

// To set up ADC and change the ADC
#define RCGCADC (*((volatile uint32_t *)0x400FE638))
// ADC 0 addresses
#define ADCCC (*((volatile uint32_t *)0x40038FC8))
#define ALTCLKCFG (*((volatile uint32_t *)0x400FE138))
#define ADCACTSS (*((volatile uint32_t *)0x40038000))
#define ADCEMUX (*((volatile uint32_t *)0x40038014))
#define ADCSSEMUX3 (*((volatile uint32_t *)0x400380B8))
#define ADCSSMUX3 (*((volatile uint32_t *)0x400380A0))
#define ADCSSCTL3 (*((volatile uint32_t *)0x400380A4))
#define ADCSSFIFO3 (*((volatile uint32_t *)0x400380A8))
// Interrupt configuration
#define ADCIM (*((volatile uint32_t *)0x40038008))
#define EN0 (*((volatile uint32_t *)0xE000E100))
#define ADCRIS (*((volatile uint32_t *)0x40038004))
#define ADCISC (*((volatile uint32_t *)0x4003800C))

// check if switch1 is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long is_switch1_pressed();

// check if switch2 is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long is_switch2_pressed();

#endif