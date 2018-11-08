//Program Description: Read DHT11 and send to UART
//Author: Anurag Chugh

#define DHT11_pin       P3_5

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

unsigned char DHT11_data[5];

void SendData(BYTE dat);
void SendString(char *s);
void DHT11_init();
unsigned short DHT11_get_byte();
unsigned short DHT11_get_data();

void main() {
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
  AUXR = 0x14;                //T2 is in 1T mode, and start Timer 2.
  AUXR |= 0x01;               //Select Timer 2 as the baud rate generator of serial port 1.
  ES = 1;                     //Enable serial port 1 interrupt.
  EA = 1;
 
  DHT11_init();

  SendString("STC15L2K32S2\r\nUART1 @ 115200 bps!\r\nDHT11 @ P3.5:\r\n");
  while(1);
}
 
// UART Interrupt service routine
void Uart(void) __interrupt(SI0_VECTOR) {
  BYTE received_byte=0;
  if (RI) {
    RI = 0;
    received_byte = SBUF;
    received_byte += 1;
    SendData(received_byte);
    P2_2 = RB8;
  }
  if (TI) {
    TI = 0;
    busy = 0;
  }
}

// Send a character over UART
void SendData(BYTE dat) {
  while (busy);               //Waiting for the previous data to be sent
  ACC = dat;                  //Get check bit (PSW.0)
  if (P) {                    //Set check bit according to Parity
#if (PARITYBIT == ODD_PARITY)
    TB8 = 0;                //Set Check Bit to 0
#elif (PARITYBIT == EVEN_PARITY)
    TB8 = 1;                //Set Check Bit to 1
#endif
  } else {
#if (PARITYBIT == ODD_PARITY)
    TB8 = 1;                //Set Check Bit to 1
#elif (PARITYBIT == EVEN_PARITY)
    TB8 = 0;                //Set Check Bit to 0
#endif
  }
  busy = 1;
  SBUF = ACC;                 //Write data to the UART data register
}

// Send a whole string over UART
void SendString(char *s) {
  while (*s) {                //Detect string end character '\0'
    SendData(*s++);         //Send current character
  }
}

// DHT11 Data pin initialization
void DHT11_init() {
  DHT11_pin = 1;
  { //1 second delay @11.0592MHz
    unsigned char i = 43, j = 6, k = 203;
    _nop_();
    _nop_();
    do {
      do {
        while (--k);
      } while (--j);
    } while (--i);
  }
}

// Get a byte from DHT11
unsigned short DHT11_get_byte() {
  unsigned short s = 0;
  unsigned short value = 0;
  for(s = 0; s < 8; s += 1)
  {
    value <<= 1;
    while((DHT11_pin == 0));
    { //30 us delay @11.0592MHz
      unsigned char i = 80;
      _nop_();
      _nop_();
      while (--i);
    }
    if(DHT11_pin == 1) {
        value |= 1;
    }
    while(DHT11_pin == 1);
  }
  return value;
}

//Get a complete reading from DHT11
unsigned short DHT11_get_data() {
  bit chk;
  unsigned short s = 0;
  unsigned char check_sum = 0;

  DHT11_pin = 1;
  DHT11_pin = 0;
  { //18 ms delay @11.0592MHz
    unsigned char i = 1, j = 194, k = 160;
    do {
      do {
        while (--k);
      } while (--j);
    } while (--i);
  }
  DHT11_pin = 1;
  { //26 us delay @11.0592MHz
    unsigned char i = 69;
    _nop_();
    _nop_();
    while (--i);
  }

  chk = DHT11_pin;

  if(chk) {
    return 1;
  }
  { //80 us delay @11.0592MHz
    unsigned char i = 1, j = 217;
    _nop_();
    do {
      while (--j);
    } while (--i);
  }

  chk = DHT11_pin;
  if(!chk) {
    return 2;
  }
  { //80 us delay @11.0592MHz
    unsigned char i = 1, j = 217;
    _nop_();
    do {
      while (--j);
    } while (--i);
  }

  for(s = 0; s <= 4; s += 1) {
     DHT11_data[s] = DHT11_get_byte();
  }

  DHT11_pin = 1;

  for(s = 0; s < 4; s += 1) {
     check_sum += DHT11_data[s];
  }

  if(check_sum != DHT11_data[4]) {
    return 3;
  } else {
    return 0;
  }
}
