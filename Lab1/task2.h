/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/10/21
 * This is the header file for task2
 */

#ifndef TASK2_H
#define TASK2_H

// To confugure the data of GPIO
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
// GPIO Port L Addresses
#define GPIODIR_L (*((volatile uint32_t *)0x40062400))
#define GPIODEN_L (*((volatile uint32_t *)0x4006251C))
#define GPIODATA_L (*((volatile uint32_t *)0x400623FC))
#define GPIOAMSEL_L (*((volatile uint32_t *)0x40062528))
#define GPIOAFSEL_L (*((volatile uint32_t *)0x40062420))

#endif

// initialize the RGB LEDs, no input variable
void LED_init();

// initialize the system switch and pedestrian switch, no input variable
void extern_switch_init();

// check if system switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long sys_switch();

// check if pedestrian switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long ped_switch();

// FSM function, no input variable, no output value
void tffFunc();