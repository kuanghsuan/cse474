/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/12/06
 * This is the header file for task2a
 */

#ifndef TASK2A_H_
#define TASK2A_H_

// To set up and change the data of GPIO
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
// Port E addresses
#define GPIOAMSEL_E (*((volatile uint32_t *)0x4005C528))
#define GPIODIR_E (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E (*((volatile uint32_t *)0x4005C51C))
#define GPIOAFSEL_E (*((volatile uint32_t *)0x4005C420))
#define GPIODATA_E (*((volatile uint32_t *)0x4005C3FC))

// Port J addresses
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))

// Port A Address
#define GPIODIR_A (*((volatile uint32_t *)0x40058400))
#define GPIODEN_A (*((volatile uint32_t *)0x4005851C))

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

// traffice light controller, FSM function, Moore Machine, no input variable, no output value
void tffFunc();

// initialize the Timer0
void GPTMInit();

// check if the timer reach to 1 sec, return value is 0 (unreached) or 1 (if reached)
int isReached();

// input variable n to keep n seconds
void oneHertz(int n);

// reset the timer
void resetTimer();

// Turn on green light
void Go_State();

// Turn on yellow light
void Warn_State();

// Turn on red light
void Stop_State();

// Turn off all lights
void Off_State();

// check if system switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long sys_switch();

// check if pedestrian switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long ped_switch();

// check if ped is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long is_sys_pressed();

// check if ys is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long is_ped_pressed();
#endif