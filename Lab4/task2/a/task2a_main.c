/*
 * Name: Kuang_Hsuan Lin
 * Student ID: 2027209
 * Date: 2020/12/06
 * This is the main file for "Implement a virtual traffic light controller using the display module"
 */

#include "task2a_inits.h"
#include "task2a.h"

#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"

enum frequency freq = PRESET3; //  Select system clock frequency preset, 12MHz

int main()
{
    LCD_Init(); // Initialize LCD
    Touch_Init();
    GPTMInit();
    LCD_ColorFill(Color4[7]); // fill LCD with white color
    PLL_Init(freq);           // Set system clock frequency to 12 MHz
    TimerADCTriger_Init();    // Initialize Timer0A to trigger ADC0

    // print the traffic lights on the LCD
    Off_State();

    // print the virtual buttons on the LCD
    LCD_SetCursor(40, 200);

    LCD_DrawCircle(50,
                   200,
                   20,
                   Color4[9]);
    LCD_Printf("PED");
    LCD_SetCursor(260, 200);

    LCD_DrawCircle(270,
                   200,
                   20,
                   Color4[9]);
    LCD_Printf("SYS");
    while (1)
    {
        tffFunc();
    }

    return 0;
}

int time = 0; // declare time to count the time
int cnt = 0;
int prev = 0;

void GPTMInit()
{
    RCGCTIMER |= GPTM0_16_32; // Enable 16/32 Timer 0

    GPTMCTL_0 = GPTMA_DISABLE;      // Disable Timer A
    GPTMCFG_0 = TM_MODE_32;         // Select two timer to 32-bit mode
    GPTMTAMR_0 |= TAMR_PER_TM_MODE; // Set periodic timer mode
    GPTMTAMR_0 &= ~TACDIR_COUNT_UP; // Configure TACDIR0 to count down
    GPTMTAILR_0 = N16_MIL;          // Load value of 16 million into GPTMTAILR0
    GPTMCTL_0 |= GPTMA_ENABLE;      // Enable Timer A
}

int isReached()
{
    return (GPTMRIS_0 & 0x1);
}

void resetTimer()
{
    GPTMICR_0 |= 0x1;
}

void oneHertz(int n)
{
    resetTimer();
    int t = 0;
    while (t < n)
    {
        if (isReached())
        {
            t++;
            resetTimer();
        }
    }
}

void ADC0SS3_Handler(void)
{                           
    ADCISC |= 0x8;          // clear the ADC0 interrupt flag
}

// turn on Red LED
void Stop_State(void)
{

    LCD_DrawFilledCircle(170,
                         100,
                         20,
                         Color4[0]);
    LCD_DrawFilledCircle(276,
                         100,
                         20,
                         Color4[0]);
    LCD_DrawFilledCircle(53,
                         100,
                         20,
                         Color4[4]);
}
// turn on Yellow LED
void Warn_State(void)
{
    LCD_DrawFilledCircle(53,
                         100,
                         20,
                         Color4[0]);

    LCD_DrawFilledCircle(276,
                         100,
                         20,
                         Color4[0]);
    LCD_DrawFilledCircle(170,
                         100,
                         20,
                         Color4[14]);
}
// turn off all LEDs
void Go_State(void)
{
    LCD_DrawFilledCircle(53,
                         100,
                         20,
                         Color4[0]);
    LCD_DrawFilledCircle(170,
                   100,
                   20,
                   Color4[0]);
    LCD_DrawFilledCircle(276,
                         100,
                         20,
                         Color4[2]);
}
void Off_State(void)
{
    LCD_DrawCircle(53,
                   100,
                   20,
                   Color4[0]);
    LCD_DrawCircle(170,
                   100,
                   20,
                   Color4[0]);
    LCD_DrawCircle(276,
                   100,
                   20,
                   Color4[0]);
}

unsigned long is_sys_pressed()
{
    unsigned long x = Touch_ReadX();
    unsigned long y = Touch_ReadY();
    if (x + y >= 3500)
    {
        return 1;
    }
    return 0;
}

unsigned long is_ped_pressed()
{
    unsigned long x = Touch_ReadX();
    unsigned long y = Touch_ReadY();
    if (x + y >= 2600)
    {
        return 1;
    }
    return 0;
}

unsigned long sys_switch(void)
{

    int firstTime = is_sys_pressed();
    if (firstTime == 0)
        return 0;
    oneHertz(2);
    int secondTime = is_sys_pressed();
    return firstTime && secondTime;
}

unsigned long ped_switch(void)
{
    int firstTime = is_ped_pressed();
    if (firstTime == 0)
        return 0;
    oneHertz(2);
    int secondTime = is_ped_pressed();
    return firstTime && secondTime;
    
}


enum TFF_State
{
    TFF_Begin,
    TFF_S0,
    TFF_S1,
    TFF_S2,
    TFF_End
} TFF_State; // state variable declaration

void tffFunc()
{
    if (GPTMRIS_0 & 0x1)
    {
        cnt += 1;
        resetTimer();
    }

    switch (TFF_State)
    {
    case TFF_Begin:
        prev = cnt;
        TFF_State = TFF_S2;
        break;
    case TFF_S0:
        if (sys_switch())
        {
            TFF_State = TFF_End;
        }
        else if (ped_switch())
        {
            TFF_State = TFF_S1;
            time = 0;
        }
        //else if (time == 500000)
        else if (cnt - prev >= 5)
        {
            prev = cnt;
            TFF_State = TFF_S2;
        }
        else
            time++;
        break;
    case TFF_S1:

        if (sys_switch())
        {
            TFF_State = TFF_End;
        }
        else if (cnt - prev >= 5)
        {
            prev = cnt;
            TFF_State = TFF_S2;
        }
        else
            time++;
        break;
    case TFF_S2:

        if (sys_switch())
        {
            TFF_State = TFF_End;
        }
        else if (cnt - prev >= 5)
        {
            prev = cnt;
            TFF_State = TFF_S0;
            time = 0;
        }
        else
            time++;
        break;
    case TFF_End:
        LED_off();
        time = 0;
        if (sys_switch())
        {
            TFF_State = TFF_Begin;
        }
        break;
    default:
        TFF_State = TFF_Begin;
        break;
    }
    switch (TFF_State) // State actions
    {
    case TFF_S0:
        Go_State();
        break;
    case TFF_S1:
        Warn_State();
        break;
    case TFF_S2:
        Stop_State();
        break;
    case TFF_End:
        Off_State();
        break;
    default:
        break;
    }
}

