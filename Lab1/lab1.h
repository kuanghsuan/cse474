#ifndef __HEADER1_H__
#define __HEADER1_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))

// Port F Address
#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))

// Port N Address
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

// Port J Address
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))

#define Port_F 0x20
#define Port_N 0x1000
#define Port_J 0x100

// Port F Control
#define PF0 0x01 // connect to LED4
#define PF4 0x10 // connect to LED3
// Port N Control
#define PN0 0x1 // connect to LED2
#define PN1 0x2 // connect to LED1
// Port J Control
#define PJ0 0x1 // connect to SW1
#define PJ1 0x2 // connect to SW2

// LED
#define LED1 0x2
#define LED2 0x1
#define LED3 0x10
#define LED4 0x01

#endif ​ //__HEADER1_H__
