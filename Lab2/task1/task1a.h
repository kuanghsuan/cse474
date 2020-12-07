#ifndef __HEADER1_H__
#define __HEADER1_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define Port_F 0x20
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
#define GPTM0_16_32 0x1 // Enable 16/32 Timer 0
#define GPTM1_16_32 0x2 // Enable 16/32 Timer 1

#define GPTMA_DISABLE 0x0         // Disable Timer A
#define GPTMA_ENABLE 0x1          // Enable Timer A
#define TM_MODE_32 0x0            // Select 32-bit mode
#define TAMR_PER_TM_MODE 0x2      // Configure TAMR bit of GPTMTAMR to be in periodic timer mode
#define TACDIR_COUNT_UP 0x10000   // Configure TACDIR bit of GPTMTAMR to count down
#define TACDIR_COUNT_DOWN 0x10000 // Configure TACDIR bit of GPTMTAMR to count down
#define N16_MIL 0xF42400          // load the value 16,000,000

// Port F Address
#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))

// Port N Address
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

// Port F Control
#define PF0 0x01 // connect to LED4
#define PF4 0x10 // connect to LED3

// Port N Control
#define PN0 0x1 // connect to LED2
#define PN1 0x2 // connect to LED1

// initialize Timer
void GPTMInit();

// initial the inteerupt
void interruptInit();

// initialize Timer
void GPIOPortFInit();

// count for one second
void oneHerze();

#endif ​ //__HEADER1_H__