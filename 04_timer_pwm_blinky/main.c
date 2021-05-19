#include "8052.H"

SFR(P3M0, 0xB2);   //0000 0000 Port 3 mode register 0
SFR(P3M1, 0xB1);   //0000 0000 Port 3 mode register 1
SFR(AUXR , 0x8E);   //0000 0000 Auxiliary Register
SFR(INT_CLKO, 0x8F);   //0000 0000 External interrupt and clock output control register

#define OSCILLATOR_FREQ_HZ 11059200UL // Clock

#define PWM_DUTY 6000 // Define the period of PWM. The value is the number of clock cycles. If the main frequency of 24.576MHz is used, the PWM frequency is 6000Hz.

// Limit the minimum and maximum duty cycle of the PWM output.
#define PWM_HIGH_MIN 32 
#define PWM_HIGH_MAX (PWM_DUTY-PWM_HIGH_MIN)

typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned long u32;

#define P_PWM P2_5 // PWM output pin

u16     pwm;                //定义PWM输出高电平的时间的变量。用户操作PWM的变量。

u16     PWM_high,PWM_low;   //中间变量，用户请勿修改。

void    delay_ms(unsigned char ms);
void    LoadPWM(u16 i);


/******************** 主函数**************************/
void main(void)
{
    P_PWM = 0;

    // Set to Push Pull output
    P2M0 = 0; // P3M1.n,P3M0.n   =00--->Standard,    01--->push-pull
    P2M1 = 0;  //                 =10--->pure input,  11--->open drain

    TR0 = 0;        // Stop counting
    ET0 = 1;        // Allow Interrupt
    PT0 = 1;        // High priority interrupt
    TMOD &= ~0x03;  // Working mode, 0: 16-bit automatic reload
    AUXR |=  0x80;  // 1T
    TMOD &= ~0x04;  // Timing
    INT_CLKO |=  0x01;  // Output Clock

    TH0 = 0;
    TL0 = 0;
    TR0 = 1;    // Start Operation

    EA = 1;

    pwm = PWM_DUTY / 10;    // Start shipping to PWM an initial value, here is the 10% duty cycle line
    LoadPWM(pwm);           // Calculate the PWM reload value


    while (1)
    {
        while(pwm < (PWM_HIGH_MAX-8))
        {
            pwm += 8;       // PWM is gradually increased to the maximum
            LoadPWM(pwm);
            delay_ms(8);
        }
        while(pwm > (PWM_HIGH_MIN+8))
        {
            pwm -= 8;   // PWM is gradually reduced to a minimum
            LoadPWM(pwm);
            delay_ms(8);
        }
    }
}


//========================================================================
// Function: void delay_ms(unsigned char ms)
// Description: Delay function.
// Parameter: ms, the number of ms to be delayed, here only 1~255ms are supported. Automatically adapt to the main clock.
// Returns: none.
// Version: VER1.0
// Date: 2013-4-1
// Remarks:
//========================================================================
void  delay_ms(unsigned char ms)
{
     unsigned int i;
     do{
          i = OSCILLATOR_FREQ_HZ / 13000;
          while(--i)    ;
     }while(--ms);
}

/**************** Calculate PWM reload value function *******************/
void LoadPWM(u16 i)
{
    u16 j;

    if(i > PWM_HIGH_MAX)        i = PWM_HIGH_MAX;   //If writing data greater than the maximum duty cycle, it will be forced to the maximum duty cycle.
    if(i < PWM_HIGH_MIN)        i = PWM_HIGH_MIN;   //If writing data less than the minimum duty cycle, it will be forced to the minimum duty cycle.
    j = 65536UL - PWM_DUTY + i; // Calculate PWM low time
    i = 65536UL - i;            // Calculate PWM high level time
    EA = 0;
    PWM_high = i;   // Load PWM high level time
    PWM_low  = j;   // Load PWM low time
    EA = 1;
}

/********************* Timer0 interrupt function ************************/
void timer0_int(void) __interrupt(TF0_VECTOR)
{
    if(P_PWM)
    {
        TH0 = (u8)(PWM_low >> 8);   // If it is outputting a high level, load the low level time.
        TL0 = (u8)PWM_low;
    }
    else
    {
        TH0 = (u8)(PWM_high >> 8);  // If it is outputting low level, load high level time.
        TL0 = (u8)PWM_high;
    }
}
