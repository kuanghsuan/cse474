/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/10/21
 * This is the header file for task1(task1a, task1b)
 */

#ifndef TASK1_H
#define TASK1_H

// To confugure the data of GPIO
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
// GPIO Port F Addresses
#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))
// GPIO Port N Addresses
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))
// GPIO Port J Addresses
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))

#endif

// delay for LEDs, no input value, no return value
void delay();

// turn on LED1, no input value, no return value
void LED1_on();

// turn off LED1, no input value, no return value
void LED1_off();

// turn on LED2, no input value, no return value
void LED2_on();

// turn off LED2, no input value, no return value
void LED2_off();

// check if switch1 is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long switch1_is_pressed();

// check if switch2 is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long switch2_is_pressed();