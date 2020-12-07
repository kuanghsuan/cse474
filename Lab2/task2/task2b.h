#ifndef __HEADER1_H__
#define __HEADER1_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define Port_J 0x100
#define Port_N 0x1000

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
#define GPTM0_16_32 0x1             // Enable 16/32 Timer 0
#define GPTM1_16_32 0x2             // Enable 16/32 Timer 1

#define GPTMA_DISABLE 0x0           // Disable Timer A
#define GPTMA_ENABLE 0x1            // Enable Timer A
#define TM_MODE_32 0x0              // Select 32-bit mode
#define TAMR_PER_TM_MODE 0x2        // Configure TAMR bit of GPTMTAMR to be in periodic timer mode
#define TACDIR_COUNT_UP 0x10000     // Configure TACDIR bit of GPTMTAMR to count down
#define TACDIR_COUNT_DOWN 0x10000   // Configure TACDIR bit of GPTMTAMR to count down
#define N16_MIL 0xF42400            // load the value 16,000,000

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

// Port J Address
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))

// Port N Address
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

// Port J Control
#define PJ0 0x1 // connect to SW1
#define PJ1 0x2 // connect to SW2

// Port N Control
#define PN0 0x1 // connect to LED2
#define PN1 0x2 // connect to LED1

// initialize Timer
void GPTMInit();

// initialize onboard switches
void switchesInit();

// initialize onboard leds
void ledInit();

// initialize interrupt
void interruptInit();

// Turn on LED1 if OFF / Turn off LED1 if ON
void LED1_toggle();

// check if system switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long switch1_is_pressed();

// check if pedestrian switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long switch2_is_pressed();

#endif ​ //__HEADER1_H__