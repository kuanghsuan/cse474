#ifndef __HEADER1_H__
#define __HEADER1_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define Port_L 0x400
#define Port_F 0x20

// Timer
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))

#define GPTMCFG0 (*((volatile uint32_t *)0x40030000))
#define GPTMCFG1 (*((volatile uint32_t *)0x40031000))

#define GPTMCTL0 (*((volatile uint32_t *)0x4003000C))
#define GPTMCTL1 (*((volatile uint32_t *)0x4003100C))

#define GPTMTAMR0 (*((volatile uint32_t *)0x40030004))
#define GPTMTAMR1 (*((volatile uint32_t *)0x40031004))

#define GPTMTAILR0 (*((volatile uint32_t *)0x40030028))
#define GPTMTAILR1 (*((volatile uint32_t *)0x40031028))

#define GPTMRIS0 (*((volatile uint32_t *)0x4003001C))
#define GPTMRIS1 (*((volatile uint32_t *)0x4003001C))

#define GPTMICR0 (*((volatile uint32_t *)0x40030024))
#define GPTMICR1 (*((volatile uint32_t *)0x40031024))

// Interrupt
#define GPTMIMR0 (*((volatile uint32_t *)0x40030018))
#define GPTMIMR1 (*((volatile uint32_t *)0x40031018))

#define INTERRUPT_ENABLE0 (*((volatile uint32_t *)0xE000E100))
#define INTERRUPT_ENABLE1 (*((volatile uint32_t *)0xE000E104))

#define TATOIM_ENABLE 0x1
#define INT_19_ENABLE 0x80000
#define INT_51_ENABLE 0x80000
#define INT_53_ENABLE 0x200000

#define GPIORIS_J (*((volatile uint32_t *)0x40060414))
#define GPIOICR_J (*((volatile uint32_t *)0x4006041C))
#define GPIOICR_J (*((volatile uint32_t *)0x4006041C))
#define GPIOIM_J (*((volatile uint32_t *)0x40060410))

// Port L Address
#define GPIODIR_L (*((volatile uint32_t *)0x40062400))
#define GPIODEN_L (*((volatile uint32_t *)0x4006251C))
#define GPIODATA_L (*((volatile uint32_t *)0x400623FC))
#define GPIOAMSEL_L (*((volatile uint32_t *)0x40062528))
#define GPIOAFSEL_L (*((volatile uint32_t *)0x40062420))

// Port L Control
#define PL0 0x1  // connect to System ON/OFF button
#define PL1 0x2  // connect to Pedestrian ON/OFF button
#define PL2 0x4  // connect to Red LED
#define PL3 0x8  // connect to Yellow LED
#define PL4 0x10 // connect to Green LED

// initialize the RGB LEDs, no input variable
void LED_init();

// Turn on green light
void Go_State();

// Turn on yellow light
void Warn_State();

// Turn on red light
void Stop_State();

// Turn off all LEDs
void LED_off();

// initialize the Timer0
void timer0Init();

// initialize the Timer1
void timer1Init();

// disable the Timer0
void timer0Disable();

// enable the Timer0
void timer0Enable();

// reset Timer0
void resetTimer0A();

// reset Timer1
void resetTimer1A();

// initialize the system switch and pedestrian switch, no input variable
void sys_init();

// initialize the system switch and pedestrian switch, no input variable
void ped_init();

// check if system switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long is_sys_pressed();

// check if pedestrian switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long is_ped_pressed();

// pedestrian controller, FSM function, Mealy Machine, no input variable, no output value
void pedFunction();

// system controller, FSM function, Mealy Machine, no input variable, no output value
void sysFunction();

// traffice light controller, FSM function, Moore Machine, no input variable, no output value
void tffFunction();

#endif ​ //__HEADER1_H__