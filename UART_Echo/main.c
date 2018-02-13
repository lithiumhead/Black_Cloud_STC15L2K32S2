//Program Description: 	Emulate a simple integer calculator over a Serial Link
//Author: Anurag Chugh

#include "../STC15F2K60S2.H"
 
typedef unsigned char BYTE;
typedef unsigned int WORD;
 
#define FOSC 11059200L
#define BAUD 115200
 
#define NONE_PARITY     0
#define ODD_PARITY      1
#define EVEN_PARITY     2
#define MARK_PARITY     3
#define SPACE_PARITY    4
 
#define PARITYBIT EVEN_PARITY
 
#define S1_S0 0x40              //P_SW1.6
#define S1_S1 0x80              //P_SW1.7
 
char busy;
 
void SendData(BYTE dat);
void SendString(char *s);
 
void main()
{
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    P6M0 = 0x00;
    P6M1 = 0x00;
    P7M0 = 0x00;
    P7M1 = 0x00;
 
    ACC = P_SW1;
    ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=0
    P_SW1 = ACC;                //(P3.0/RxD, P3.1/TxD)
     
//  ACC = P_SW1;
//  ACC &= ~(S1_S0 | S1_S1);    //S1_S0=1 S1_S1=0
//  ACC |= S1_S0;               //(P3.6/RxD_2, P3.7/TxD_2)
//  P_SW1 = ACC;  
//  
//  ACC = P_SW1;
//  ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=1
//  ACC |= S1_S1;               //(P1.6/RxD_3, P1.7/TxD_3)
//  P_SW1 = ACC;  
 
#if (PARITYBIT == NONE_PARITY)
    SCON = 0x50;                //8-bit variable baud rate
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    SCON = 0xda;                //9-bit variable baud rate, parity bit is initially 1
#elif (PARITYBIT == SPACE_PARITY)
    SCON = 0xd2;                //9-bit variable baud rate, parity bit is initially 0
#endif
 
    T2L = (65536 - (FOSC/4/BAUD));   //Set baud rate reload value
    T2H = (65536 - (FOSC/4/BAUD))>>8;
    AUXR = 0x14;                //T2为1T模式, 并启动定时器2
    AUXR |= 0x01;               //选择定时器2为串口1的波特率发生器
    ES = 1;                     //使能串口1中断
    EA = 1;
 
    SendString("STC15L2K32S2\r\nUART1 Test 115200 bps!\r\n");
    while(1);
}
 
/*----------------------------
UART Interrupt service routine
-----------------------------*/
void Uart(void) __interrupt(SI0_VECTOR)
{
    BYTE received_byte=0;
      if (RI)
    {
        RI = 0;
                received_byte = SBUF;
              received_byte += 1;
              SendData(received_byte);
        P2_2 = RB8;
    }
    if (TI)
    {
        TI = 0;
        busy = 0;
    }
}
 
/*----------------------------
Send serial data
----------------------------*/
void SendData(BYTE dat)
{
    while (busy);               //等待前面的数据发送完成
    ACC = dat;                  //获取校验位P (PSW.0)
    if (P)                      //根据P来设置校验位
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 0;                //设置校验位为0
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 1;                //设置校验位为1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 1;                //设置校验位为1
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 0;                //设置校验位为0
#endif
    }
    busy = 1;
    SBUF = ACC;                 //写数据到UART数据寄存器
}
 
/*----------------------------
发送字符串
----------------------------*/
void SendString(char *s)
{
    while (*s)                  //检测字符串结束标志
    {
        SendData(*s++);         //发送当前字符
    }
}