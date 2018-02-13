#ifndef __STC15F2K60S2_H_
#define __STC15F2K60S2_H_
//If you include this header file, there is no need to include "reg51.h"

/////////////////////////////////////////////////
// Note: For STC15W4K32S4 series of chips, at power on 
// ports that also support PWM are in High impedance state,
// these ports should be set as quasi-bidirectional port
// or strong push-pull mode for normal use.
// Relevant IO: P0.6 / P0.7 / P1.6 / P1.7 / P2.1 / P2.2
// P2.3 / P2.7 / P3.7 / P4.2 / P4.4 / P4.5
/////////////////////////////////////////////////

#include <compiler.h>

                  //Reset value  Description

//Main Special Function Registers (SFRs)
SFR(ACC, 0xE0);   //0000 0000    Accumulator
SFR(B, 0xF0);     //0000 0000    B
SFR(PSW, 0xD0);   //0000 0000    Program Status Word
   SBIT(CY,  0xD0, 7);
   SBIT(AC,  0xD0, 6);
   SBIT(F0,  0xD0, 5);
   SBIT(RS1, 0xD0, 4);
   SBIT(RS0, 0xD0, 3);
   SBIT(OV,  0xD0, 2);
   SBIT(P,   0xD0, 0);
SFR(SP, 0x81);    //0000 0111    Stack Pointer
SFR(DPL, 0x82);   //0000 0000    Data Pointer Low
SFR(DPH, 0x83);   //0000 0000    Data Pointer High

//I/O Port SFRs
SFR(P0, 0x80);    //1111 1111    Port 0
   SBIT(P0_0, 0x80, 0); // Port 0 bit 0
   SBIT(P0_1, 0x80, 1); // Port 0 bit 1
   SBIT(P0_2, 0x80, 2); // Port 0 bit 2
   SBIT(P0_3, 0x80, 3); // Port 0 bit 3
   SBIT(P0_4, 0x80, 4); // Port 0 bit 4
   SBIT(P0_5, 0x80, 5); // Port 0 bit 5
   SBIT(P0_6, 0x80, 6); // Port 0 bit 6
   SBIT(P0_7, 0x80, 7); // Port 0 bit 7
SFR(P1, 0x90);    //1111 1111    Port 1
   SBIT(P1_0, 0x90, 0); // Port 1 bit 0
   SBIT(P1_1, 0x90, 1); // Port 1 bit 1
   SBIT(P1_2, 0x90, 2); // Port 1 bit 2
   SBIT(P1_3, 0x90, 3); // Port 1 bit 3
   SBIT(P1_4, 0x90, 4); // Port 1 bit 4
   SBIT(P1_5, 0x90, 5); // Port 1 bit 5
   SBIT(P1_6, 0x90, 6); // Port 1 bit 6
   SBIT(P1_7, 0x90, 7); // Port 1 bit 7
SFR(P2, 0xA0);    //1111 1111    Port 2
   SBIT(P2_0, 0xA0, 0); // Port 2 bit 0
   SBIT(P2_1, 0xA0, 1); // Port 2 bit 1
   SBIT(P2_2, 0xA0, 2); // Port 2 bit 2
   SBIT(P2_3, 0xA0, 3); // Port 2 bit 3
   SBIT(P2_4, 0xA0, 4); // Port 2 bit 4
   SBIT(P2_5, 0xA0, 5); // Port 2 bit 5
   SBIT(P2_6, 0xA0, 6); // Port 2 bit 6
   SBIT(P2_7, 0xA0, 7); // Port 2 bit 7
SFR(P3, 0xB0);    //1111 1111    Port 3
   SBIT(P3_0, 0xB0, 0); // Port 3 bit 0
   SBIT(P3_1, 0xB0, 1); // Port 3 bit 1
   SBIT(P3_2, 0xB0, 2); // Port 3 bit 2
   SBIT(P3_3, 0xB0, 3); // Port 3 bit 3
   SBIT(P3_4, 0xB0, 4); // Port 3 bit 4
   SBIT(P3_5, 0xB0, 5); // Port 3 bit 5
   SBIT(P3_6, 0xB0, 6); // Port 3 bit 6
   SBIT(P3_7, 0xB0, 7); // Port 3 bit 7
SFR(P4, 0xC0);    //1111 1111    Port 4
   SBIT(P4_0, 0xC0, 0); // Port 4 bit 0
   SBIT(P4_1, 0xC0, 1); // Port 4 bit 1
   SBIT(P4_2, 0xC0, 2); // Port 4 bit 2
   SBIT(P4_3, 0xC0, 3); // Port 4 bit 3
   SBIT(P4_4, 0xC0, 4); // Port 4 bit 4
   SBIT(P4_5, 0xC0, 5); // Port 4 bit 5
   SBIT(P4_6, 0xC0, 6); // Port 4 bit 6
   SBIT(P4_7, 0xC0, 7); // Port 4 bit 7
SFR(P5, 0xC8);    //xxxx 1111    Port 5
   SBIT(P5_0, 0xC8, 0); // Port 5 bit 0
   SBIT(P5_1, 0xC8, 1); // Port 5 bit 1
   SBIT(P5_2, 0xC8, 2); // Port 5 bit 2
   SBIT(P5_3, 0xC8, 3); // Port 5 bit 3
   SBIT(P5_4, 0xC8, 4); // Port 5 bit 4
   SBIT(P5_5, 0xC8, 5); // Port 5 bit 5
   SBIT(P5_6, 0xC8, 6); // Port 5 bit 6
   SBIT(P5_7, 0xC8, 7); // Port 5 bit 7
SFR(P6, 0xE8);    //0000 0000    Port 6
   SBIT(P6_0, 0xE8, 0); // Port 6 bit 0
   SBIT(P6_1, 0xE8, 1); // Port 6 bit 1
   SBIT(P6_2, 0xE8, 2); // Port 6 bit 2
   SBIT(P6_3, 0xE8, 3); // Port 6 bit 3
   SBIT(P6_4, 0xE8, 4); // Port 6 bit 4
   SBIT(P6_5, 0xE8, 5); // Port 6 bit 5
   SBIT(P6_6, 0xE8, 6); // Port 6 bit 6
   SBIT(P6_7, 0xE8, 7); // Port 6 bit 7
SFR(P7, 0xF8);    //0000 0000    Port 7
   SBIT(P7_0, 0xF8, 0); // Port 7 bit 0
   SBIT(P7_1, 0xF8, 1); // Port 7 bit 1
   SBIT(P7_2, 0xF8, 2); // Port 7 bit 2
   SBIT(P7_3, 0xF8, 3); // Port 7 bit 3
   SBIT(P7_4, 0xF8, 4); // Port 7 bit 4
   SBIT(P7_5, 0xF8, 5); // Port 7 bit 5
   SBIT(P7_6, 0xF8, 6); // Port 7 bit 6
   SBIT(P7_7, 0xF8, 7); // Port 7 bit 7
SFR(P0M0, 0x94);   //0000 0000 Port 0 mode register 0
SFR(P0M1, 0x93);   //0000 0000 Port 0 mode register 1
SFR(P1M0, 0x92);   //0000 0000 Port 1 mode register 0
SFR(P1M1, 0x91);   //0000 0000 Port 1 mode register 1
SFR(P2M0, 0x96);   //0000 0000 Port 2 mode register 0
SFR(P2M1, 0x95);   //0000 0000 Port 2 mode register 1
SFR(P3M0, 0xB2);   //0000 0000 Port 3 mode register 0
SFR(P3M1, 0xB1);   //0000 0000 Port 3 mode register 1
SFR(P4M0, 0xB4);   //0000 0000 Port 4 mode register 0
SFR(P4M1, 0xB3);   //0000 0000 Port 4 mode register 1
SFR(P5M0, 0xCA);   //0000 0000 Port 5 mode register 0
SFR(P5M1, 0xC9);   //0000 0000 Port 5 mode register 1
SFR(P6M0, 0xCC);   //0000 0000 Port 6 mode register 0
SFR(P6M1, 0xCB);   //0000 0000 Port 6 mode register 1
SFR(P7M0, 0xE2);   //0000 0000 Port 7 mode register 0
SFR(P7M1, 0xE1);   //0000 0000 Port 7 mode register 1

//System Management SFRs
SFR(PCON,  0x87);   //0001 0000 Power Control Register
SFR(AUXR , 0x8E);   //0000 0000 Auxiliary Register
SFR(AUXR1, 0xA2);   //0000 0000 Auxiliary Register 1
SFR(P_SW1, 0xA2);   //0000 0000 Peripheral port switch register 1
SFR(CLK_DIV, 0x97); //0000 0000 Clock divider control register
SFR(BUS_SPEED, 0xA1); //xx10 x011 Bus speed control register
SFR(P1ASF, 0x9D);   //0000 0000 Port 1 analog function configuration register
SFR(P_SW2, 0xBA);   //0xxx x000 Peripheral port switch register

//Interrupt SFRs
SFR(IE, 0xA8);       //0000 0000 Interrupt control register
   SBIT(EA,   0xA8, 7);
   SBIT(ELVD, 0xA8, 6);
   SBIT(EADC, 0xA8, 5);
   SBIT(ES,   0xA8, 4);
   SBIT(ET1,  0xA8, 3);
   SBIT(EX1,  0xA8, 2);
   SBIT(ET0,  0xA8, 1);
   SBIT(EX0,  0xA8, 0);
SFR(IP, 0xB8);      //0000 0000 Interrupt priority register
   SBIT(PPCA, 0xB8, 7);
   SBIT(PLVD, 0xB8, 6);
   SBIT(PADC, 0xB8, 5);
   SBIT(PS,   0xB8, 4);
   SBIT(PT1,  0xB8, 3);
   SBIT(PX1,  0xB8, 2);
   SBIT(PT0,  0xB8, 1);
   SBIT(PX0,  0xB8, 0);
SFR(IE2, 0xAF);     //0000 0000 Interrupt control register 2
SFR(IP2, 0xB5);     //xxxx xx00 Interrupt priority register 2
SFR(INT_CLKO, 0x8F);   //0000 0000 External interrupt and clock output control register

//Timer SFRs
SFR(TCON, 0x88);   //0000 0000 T0/T1 control register
   SBIT(TF1, 0x88, 7);
   SBIT(TR1, 0x88, 6);
   SBIT(TF0, 0x88, 5);
   SBIT(TR0, 0x88, 4);
   SBIT(IE1, 0x88, 3);
   SBIT(IT1, 0x88, 2);
   SBIT(IE0, 0x88, 1);
   SBIT(IT0, 0x88, 0);
SFR(TMOD,  0x89);   //0000 0000 T0/T1 mode register
SFR(TL0,   0x8A);   //0000 0000 T0 low byte
SFR(TL1,   0x8B);   //0000 0000 T1 low byte
SFR(TH0,   0x8C);   //0000 0000 T0 high byte
SFR(TH1,   0x8D);   //0000 0000 T1 high byte
SFR(T4T3M, 0xD1);   //0000 0000 T3/T4 mode register
SFR(T3T4M, 0xD1);   //0000 0000 T3/T4 mode register
SFR(T4H,   0xD2);   //0000 0000 T4 high byte
SFR(T4L,   0xD3);   //0000 0000 T4 low byte
SFR(T3H,   0xD4);   //0000 0000 T3 high byte
SFR(T3L,   0xD5);   //0000 0000 T3 low byte
SFR(T2H,   0xD6);   //0000 0000 T2 high byte
SFR(T2L,   0xD7);   //0000 0000 T2 low byte
SFR(WKTCL, 0xAA);   //0000 0000 Power-down wake-up timer low byte
SFR(WKTCH, 0xAB);   //0000 0000 Power-down wake-up timer high byte
SFR(WDT_CONTR, 0xC1);   //0000 0000 Watchdog control register

//Serial port SFRs
SFR(SCON, 0x98);   //0000 0000 Serial port 1 control register
   SBIT(SM0, 0x98, 7);
   SBIT(SM1, 0x98, 6);
   SBIT(SM2, 0x98, 5);
   SBIT(REN, 0x98, 4);
   SBIT(TB8, 0x98, 3);
   SBIT(RB8, 0x98, 2);
   SBIT(TI , 0x98, 1);
   SBIT(RI , 0x98, 0);
SFR(SBUF,  0x99);   //xxxx xxxx Serial port 1 data register
SFR(S2CON, 0x9A);   //0000 0000 Serial port 2 control register
SFR(S2BUF, 0x9B);   //xxxx xxxx Serial port 2 data register
SFR(S3CON, 0xAC);   //0000 0000 Serial port 3 control register
SFR(S3BUF, 0xAD);   //xxxx xxxx Serial port 3 data register
SFR(S4CON, 0x84);   //0000 0000 Serial port 4 control register
SFR(S4BUF, 0x85);   //xxxx xxxx Serial port 4 data register
SFR(SADDR, 0xA9);   //0000 0000 Slave address register
SFR(SADEN, 0xB9);   //0000 0000 Slave address mask registe

//ADC SFRs
SFR(ADC_CONTR, 0xBC);   //0000 0000 A/D conversion control register
SFR(ADC_RES,   0xBD);   //0000 0000 A/D conversion result high byte
SFR(ADC_RESL,  0xBE);   //0000 0000 A/D conversion result low byte

//SPI SFRs
SFR(SPSTAT, 0xCD);   //00xx xxxx SPI Status register
SFR(SPCTL,  0xCE);   //0000 0100 SPI Control register
SFR(SPDAT,  0xCF);   //0000 0000 SPI Data register

//IAP/ISP SFRs
SFR(IAP_DATA,  0xC2);   //0000 0000 EEPROM data register
SFR(IAP_ADDRH, 0xC3);   //0000 0000 EEPROM address high byte
SFR(IAP_ADDRL, 0xC4);   //0000 0000 EEPROM address low byte
SFR(IAP_CMD,   0xC5);   //xxxx xx00 EEPROM command register
SFR(IAP_TRIG,  0xC6);   //0000 0000 EEPROM command trigger register
SFR(IAP_CONTR, 0xC7);   //0000 x000 EEPROM control register

//PCA/PWM SFRs
SFR(CCON,      0xD8);   //00xx xx00 PCA control register
   SBIT(CF,   0xD8, 7);
   SBIT(CR,   0xD8, 6);
   SBIT(CCF2, 0xD8, 2);
   SBIT(CCF1, 0xD8, 1);
   SBIT(CCF0, 0xD8, 0);
SFR(CMOD,      0xD9);   //0xxx x000 PCA operating mode register
SFR(CL,        0xE9);   //0000 0000 PCA counter low byte
SFR(CH,        0xF9);   //0000 0000 PCA counter high byte
SFR(CCAPM0,    0xDA);   //0000 0000 PCA module 0 PWM register
SFR(CCAPM1,    0xDB);   //0000 0000 PCA module 1 PWM register
SFR(CCAPM2,    0xDC);   //0000 0000 PCA module 2 PWM register
SFR(CCAP0L,    0xEA);   //0000 0000 PCA module 0 capture / compare register low byte
SFR(CCAP1L,    0xEB);   //0000 0000 PCA module 1 capture / compare register low byte
SFR(CCAP2L,    0xEC);   //0000 0000 PCA Module 2 Capture / Compare Register Low Byte
SFR(PCA_PWM0,  0xF2);   //xxxx xx00 PWM Register for PCA Module 0
SFR(PCA_PWM1,  0xF3);   //xxxx xx00 PWM Register for PCA Module 1
SFR(PCA_PWM2,  0xF4);   //xxxx xx00 PWM Register for PCA Module 2
SFR(CCAP0H,    0xFA);   //0000 0000 PCA Module 0 Capture / Compare Register High Byte
SFR(CCAP1H,    0xFB);   //0000 0000 PCA Module 1 Capture / Compare Register High Byte
SFR(CCAP2H,    0xFC);   //0000 0000 PCA Module 2 Capture / Compare Register High Byte

//Comparator SFRs
SFR(CMPCR1,    0xE6);   //0000 0000 Comparator Control Register 1
SFR(CMPCR2,    0xE7);   //0000 0000 Comparator Control Register 2

//Enhanced PWM Waveform Generator SFRs
SFR(PWMCFG,    0xf1);   //x000 0000 PWM configuration Register
SFR(PWMCR,     0xf5);   //0000 0000 PWM control register
SFR(PWMIF,     0xf6);   //x000 0000 PWM interrupt flag register
SFR(PWMFDCR,   0xf7);   //xx00 0000 PWM External Abnormality Detection Control Register

//The following special function registers are located in the extended RAM area
//To access these registers, you must first P_SW2 the BIT7 is set to 1, can be normal read and write
__xdata volatile unsigned int __at(0xfff0) PWMC;
SFRX(PWMCH,   0xfff0);
SFRX(PWMCL,   0xfff1);
SFRX(PWMCKS,  0xfff2);
__xdata volatile unsigned int __at(0xff00) PWM2T1;
SFRX(PWM2T1H, 0xff00);
SFRX(PWM2T1L, 0xff01);
__xdata volatile unsigned int __at(0xff02) PWM2T2;
SFRX(PWM2T2H, 0xff02);
SFRX(PWM2T2L, 0xff03);
SFRX(PWM2CR,  0xff04);
__xdata volatile unsigned int __at(0xff10) PWM3T1;
SFRX(PWM3T1H, 0xff10);
SFRX(PWM3T1L, 0xff11);
__xdata volatile unsigned int __at(0xff12) PWM3T2;
SFRX(PWM3T2H, 0xff12);
SFRX(PWM3T2L, 0xff13);
SFRX(PWM3CR,  0xff14);
__xdata volatile unsigned int __at(0xff20) PWM4T1;
SFRX(PWM4T1H, 0xff20);
SFRX(PWM4T1L, 0xff21);
__xdata volatile unsigned int __at(0xff22) PWM4T2;
SFRX(PWM4T2H, 0xff22);
SFRX(PWM4T2L, 0xff23);
SFRX(PWM4CR,  0xff24);
__xdata volatile unsigned int __at(0xff30) PWM5T1;
SFRX(PWM5T1H, 0xff30);
SFRX(PWM5T1L, 0xff31);
__xdata volatile unsigned int __at(0xff32) PWM5T2;
SFRX(PWM5T2H, 0xff32);
SFRX(PWM5T2L, 0xff33);
SFRX(PWM5CR,  0xff34);
__xdata volatile unsigned int __at(0xff40) PWM6T1;
SFRX(PWM6T1H, 0xff40);
SFRX(PWM6T1L, 0xff41);
__xdata volatile unsigned int __at(0xff42) PWM6T2;
SFRX(PWM6T2H, 0xff42);
SFRX(PWM6T2L, 0xff43);
SFRX(PWM6CR,  0xff44);
__xdata volatile unsigned int __at(0xff50) PWM7T1 ;       
SFRX(PWM7T1H, 0xff50);
SFRX(PWM7T1L, 0xff51);
__xdata volatile unsigned int __at(0xff52) PWM7T2;
SFRX(PWM7T2H, 0xff52);
SFRX(PWM7T2L, 0xff53);
SFRX(PWM7CR,  0xff54);

/* Interrupt numbers: address = (number * 8) + 3 */
#define IE0_VECTOR      0       /* 0x03 external interrupt 0 */
#define TF0_VECTOR      1       /* 0x0b timer 0 */
#define IE1_VECTOR      2       /* 0x13 external interrupt 1 */
#define TF1_VECTOR      3       /* 0x1b timer 1 */
#define SI0_VECTOR      4       /* 0x23 serial port 0 */

#endif

