// Program Description: Read DHT11 and send to UART
// Author: Anurag Chugh

#include "../STC15F2K60S2.H"

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 11059200L
#define BAUD 115200

#define NONE_PARITY 0
#define ODD_PARITY 1
#define EVEN_PARITY 2
#define MARK_PARITY 3
#define SPACE_PARITY 4

#define PARITYBIT EVEN_PARITY

#define S1_S0 0x40 // P_SW1.6
#define S1_S1 0x80 // P_SW1.7

char busy;

// DHT11 Bytes
unsigned char TP_H = 0;
unsigned char TP_L = 0;
unsigned char RH_H = 0;
unsigned char RH_L = 0;
unsigned char CR_D = 0;
#define DHT11_pin P3_5

void SendData(BYTE dat);
void SendString(char *s);

void delay_5us(unsigned char us);
void delay_ms(unsigned long cnt);

void DHT11_init();
__bit DHT11_ReadBit(void);

void uitoa(unsigned int value, char *string, int radix);
void itoa(int value, char *string, int radix);

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
  ACC &= ~(S1_S0 | S1_S1); // S1_S0=0 S1_S1=0
  P_SW1 = ACC;             //(P3.0/RxD, P3.1/TxD)

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
  SCON = 0x50; // 8-bit variable baud rate
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) ||               \
    (PARITYBIT == MARK_PARITY)
  SCON = 0xda; // 9-bit variable baud rate, parity bit is initially 1
#elif (PARITYBIT == SPACE_PARITY)
  SCON = 0xd2; // 9-bit variable baud rate, parity bit is initially 0
#endif

  T2L = (65536 - (FOSC / 4 / BAUD)); // Set baud rate reload value
  T2H = (65536 - (FOSC / 4 / BAUD)) >> 8;
  AUXR = 0x14;  // T2 is in 1T mode, and start Timer 2.
  AUXR |= 0x01; // Select Timer 2 as the baud rate generator of serial port 1.
  ES = 1;       // Enable serial port 1 interrupt.
  EA = 1;

  DHT11_init();

  SendString("STC15L2K32S2\r\nUART1 @ 115200 bps!\r\nDHT11 @ P3.5:\r\n");
  while (1) {
    char reading[4] = {0}; // Store Temperature/Humidity String here
    DHT11_Read();
    SendString("Humidity: ");
    uitoa(RH_H, reading, 10);
    SendString(reading);
    SendString(" % | Temperature: ");
    uitoa(TP_H, reading, 10);
    SendString(reading);
    SendString(" Celsius\r\n");
    delay_ms(1000);
  };
}

// UART Interrupt service routine
void Uart(void) __interrupt(SI0_VECTOR) {
  BYTE received_byte = 0;
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
  while (busy)
    ;        // Waiting for the previous data to be sent
  ACC = dat; // Get check bit (PSW.0)
  if (P) {   // Set check bit according to Parity
#if (PARITYBIT == ODD_PARITY)
    TB8 = 0; // Set Check Bit to 0
#elif (PARITYBIT == EVEN_PARITY)
    TB8 = 1;   // Set Check Bit to 1
#endif
  } else {
#if (PARITYBIT == ODD_PARITY)
    TB8 = 1; // Set Check Bit to 1
#elif (PARITYBIT == EVEN_PARITY)
    TB8 = 0;   // Set Check Bit to 0
#endif
  }
  busy = 1;
  SBUF = ACC; // Write data to the UART data register
}

// Send a whole string over UART
void SendString(char *s) {
  while (*s) {      // Detect string end character '\0'
    SendData(*s++); // Send current character
  }
}

// Delay function
void delay_5us(unsigned char us) {
  unsigned char i = 0;
  for (; us; us--)
    for (i = 0; i < 14; i++)
      ;
}

// Delay function
void delay_ms(unsigned long cnt) {
  for (; cnt; cnt--)
    delay_5us(200);
}

// DHT11 Data pin initialization
void DHT11_init() {
  DHT11_pin = 1;
  delay_ms(1000);
}

// Read DHT11 Bit
__bit DHT11_ReadBit(void) {
  unsigned char t = 0;
  delay_5us(6);
  while (DHT11_pin == 0)
    ;
  for (t = 0; DHT11_pin; t++)
    delay_5us(1);
  if (t > 10)
    return 1;
  else
    return 0;
}

void DHT11_Read(void) {
  unsigned char i;
  DHT11_pin = 0;
  Delay2(20);
  DHT11_pin = 1;
  delay_5us(10);
  while (DHT11_pin == 0)
    ;
  delay_5us(6);
  while (DHT11_pin)
    ;
  for (i = 0; i < 8; i++) {
    if (DHT11_ReadBit())
      TP_H = ((TP_H << 1) + 1);
    else
      TP_H <<= 1;
  }
  for (i = 0; i < 8; i++) {
    if (DHT11_ReadBit())
      TP_L = ((TP_L << 1) + 1);
    else
      TP_L <<= 1;
  }
  for (i = 0; i < 8; i++) {
    if (DHT11_ReadBit())
      RH_H = ((RH_H << 1) + 1);
    else
      RH_H <<= 1;
  }
  for (i = 0; i < 8; i++) {
    if (DHT11_ReadBit())
      RH_L = ((RH_L << 1) + 1);
    else
      RH_L <<= 1;
  }
  for (i = 0; i < 8; i++) {
    if (DHT11_ReadBit())
      CR_D = ((CR_D << 1) + 1);
    else
      CR_D <<= 1;
  }
}

#define NUMBER_OF_DIGITS 16 // space for NUMBER_OF_DIGITS + '\0'

void uitoa(unsigned int value, char *string, int radix) {
  unsigned char index, i;

  index = NUMBER_OF_DIGITS;
  i = 0;

  do {
    string[--index] = '0' + (value % radix);
    if (string[index] > '9')
      string[index] += 'A' - ':'; // continue with A, B,..
    value /= radix;
  } while (value != 0);

  do {
    string[i++] = string[index++];
  } while (index < NUMBER_OF_DIGITS);

  string[i] = 0; // string terminator
}

void itoa(int value, char *string, int radix) {
  if (value < 0 && radix == 10) {
    *string++ = '-';
    uitoa(-value, string, radix);
  } else {
    uitoa(value, string, radix);
  }
}
