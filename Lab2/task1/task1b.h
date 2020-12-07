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

// Timer Configuation
#define GPTM0_16_32 0x1           // Enable 16/32 Timer 0
#define GPTM1_16_32 0x2           // Enable 16/32 Timer 1

#define GPTMA_DISABLE 0x0         // Disable Timer A
#define GPTMA_ENABLE 0x1          // Enable Timer A
#define TM_MODE_32 0x0            // Select 32-bit mode
#define TAMR_PER_TM_MODE 0x2      // Configure TAMR bit of GPTMTAMR to be in periodic timer mode
#define TACDIR_COUNT_UP 0x10000   // Configure TACDIR bit of GPTMTAMR to count down
#define TACDIR_COUNT_DOWN 0x10000 // Configure TACDIR bit of GPTMTAMR to count down
#define N16_MIL 0xF42400          // load the value 16,000,000

// Port L Address
#define GPIODIR_L   (*((volatile uint32_t *)0x40062400))
#define GPIODEN_L   (*((volatile uint32_t *)0x4006251C))
#define GPIODATA_L  (*((volatile uint32_t *)0x400623FC))
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

// reset the timer
void resetTimer();

// initialize the Timer0
void GPTMInit();

// input variable n to keep n seconds
void oneHertz(int n);

// initialize the system switch and pedestrian switch, no input variable
void extern_switch_init();

// check if system switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long sys_switch();

// check if pedestrian switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long ped_switch();

// check if the timer reach to 1 sec, return value is 0 (unreached) or 1 (if reached)
int isReached();

// traffice light controller, FSM function, Moore Machine, no input variable, no output value
void tffFunc();

#endif ​ //__HEADER1_H__