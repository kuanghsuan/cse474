#ifndef __HEADER1_H__
#define __HEADER1_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define Port_F 0x20
#define Port_N 0x1000
#define Port_J 0x100
#define Port_C 0x04
#define Port_L 0x400

// Port F Address
#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))

// Port N Address
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

#define GPIOAMSEL_N (*((volatile uint32_t *)0x40064528))
#define GPIOAFSEL_N (*((volatile uint32_t *)0x40064420))

// Port J Address
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))

// Port C Address
#define GPIODIR_C (*((volatile uint32_t *)0x4005A400))
#define GPIODEN_C (*((volatile uint32_t *)0x4005A51C))
#define GPIODATA_C (*((volatile uint32_t *)0x4005A3FC))

#define GPIOAMSEL_C (*((volatile uint32_t *)0x4005A528))
#define GPIOAFSEL_C (*((volatile uint32_t *)0x4005A420))

// Port L Address
#define GPIODIR_L (*((volatile uint32_t *)0x40062400))
#define GPIODEN_L (*((volatile uint32_t *)0x4006251C))
#define GPIODATA_L (*((volatile uint32_t *)0x400623FC))

#define GPIOAMSEL_L (*((volatile uint32_t *)0x40062528))
#define GPIOAFSEL_L (*((volatile uint32_t *)0x40062420))

// Port E Address
#define GPIODIR_E (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E (*((volatile uint32_t *)0x4005C51C))
#define GPIODATA_E (*((volatile uint32_t *)0x4005C3FC))

#define GPIOAMSEL_E (*((volatile uint32_t *)0x4005C528))
#define GPIOAFSEL_E (*((volatile uint32_t *)0x4005C420))

// Port M Address
#define GPIODIR_M (*((volatile uint32_t *)0x40063400))
#define GPIODEN_M (*((volatile uint32_t *)0x4006351C))
#define GPIODATA_M (*((volatile uint32_t *)0x400633FC))

#define GPIOAMSEL_M (*((volatile uint32_t *)0x40063528))
#define GPIOAFSEL_M (*((volatile uint32_t *)0x40063420))

// Port F Control
#define PF0 0x01 // connect to LED4
#define PF4 0x10 // connect to LED3

// Port N Control
#define PN0 0x1 // connect to LED2
#define PN1 0x2 // connect to LED1
#define PN2 0x4

// Port J Control
#define PJ0 0x1 // connect to SW1
#define PJ1 0x2 // connect to SW2

// Port C Control
#define PC4 0x10

// Port L Control
#define PL0 0x1  // connect to System ON/OFF button
#define PL1 0x2  // connect to Pedestrian ON/OFF button
#define PL2 0x4  // connect to Red LED
#define PL3 0x8  // connect to Yellow LED
#define PL4 0x10 // connect to Green LED

// Port E Control
#define PE0 0x1
#define PE1 0x2
#define PE2 0x4
#define PE3 0x8
#define PE5 0x20

// Port M Control
#define PM0 0x1
#define PM1 0x2
#define PM2 0x4
#define PM6 0x40
#define PM7 0x80

// OnBoard LED
#define LED1 0x2
#define LED2 0x1
#define LED3 0x10
#define LED4 0x01

#endif ​ //__HEADER1_H__
