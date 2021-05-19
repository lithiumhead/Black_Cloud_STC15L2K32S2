// Program Description: Receive characters, increment and send it back on the UART at 115200 bps 8-N-1
// Author: Anurag Chugh

#include "../STC15F2K60S2.H"

typedef unsigned char BYTE;

// *****************************************
// UART Stuff 
// *****************************************
#define OSCILLATOR_FREQ_HZ 11059200L
#define BAUD_BPS 115200L

#define BAUD_RELOAD (65536L - (OSCILLATOR_FREQ_HZ / 4L / BAUD_BPS))
#define BAUD_RELOAD_L ((BAUD_RELOAD) & 0xff)
#define BAUD_RELOAD_H ((BAUD_RELOAD>>8) & 0xff)

#define NONE_PARITY 0
#define ODD_PARITY 1
#define EVEN_PARITY 2
#define MARK_PARITY 3
#define SPACE_PARITY 4

#define PARITYBIT NONE_PARITY

#define S1_S0 0x40 // P_SW1.6
#define S1_S1 0x80 // P_SW1.7

char busy;

// UART Init
void UartInit() {
  // P0M0 = 0x00;
  // P0M1 = 0x00;
  // P1M0 = 0x00;
  // P1M1 = 0x00;
  // P2M0 = 0x00;
  // P2M1 = 0x00;
  // P3M0 = 0x00;
  // P3M1 = 0x00;
  // P4M1 = 0x00;
  // P5M0 = 0x00;
  // P5M1 = 0x00;
  // P6M0 = 0x00;
  // P6M1 = 0x00;
  // P7M0 = 0x00;
  // P7M1 = 0x00;
  // P4M0 = 0x00;

  ACC = P_SW1;
  ACC &= ~(S1_S0 | S1_S1); // S1_S0=0 S1_S1=0
  P_SW1 = ACC;             // Use P3.0/RxD, P3.1/TxD

#if (PARITYBIT == NONE_PARITY)
  SCON = 0x50; // 8-bit variable baud rate
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) ||               \
    (PARITYBIT == MARK_PARITY)
  SCON = 0xda; // 9-bit variable baud rate, parity bit is initially 1
#elif (PARITYBIT == SPACE_PARITY)
  SCON = 0xd2; // 9-bit variable baud rate, parity bit is initially 0
#endif

  T2L = BAUD_RELOAD_L; // Set baud rate reload value
  T2H = BAUD_RELOAD_H;
  AUXR = 0x14;  // T2 is in 1T mode, and start Timer 2.
  AUXR |= 0x01; // Select Timer 2 as the baud rate generator of serial port 1.
  ES = 1;       // Enable serial port 1 interrupt.
  EA = 1;
}

// Send a character over UART
void UartSendData(BYTE dat) {
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
void UartSendString(char *s) {
  while (*s) {      // Detect string end character '\0'
    UartSendData(*s++); // Send current character
  }
}

// UART Interrupt Service Routine
void UartIsr(void) __interrupt(SI0_VECTOR) {
  BYTE received_byte = 0;
  if (RI) { // Byte Received
    RI = 0;
    received_byte = SBUF;
    received_byte += 1;
    UartSendData(received_byte);
    P2_2 = RB8;
  }
  if (TI) { // Byte done transmitting
    TI = 0;
    busy = 0;
  }
}

// *****************************************
// DHT11 Stuff 
// *****************************************

#define DHT11_PIN P3_5

int I_RH,D_RH,I_Temp,D_Temp,CheckSum; 

void timer_delay20ms()    /* Timer0 delay function */
{
  TMOD = 0x01;
  TH0 = 0xB8;   /* Load higher 8-bit in TH0 */
  TL0 = 0x0C;   /* Load lower 8-bit in TL0 */
  TR0 = 1;    /* Start timer0 */
  while(TF0 == 0);  /* Wait until timer0 flag set */
  TR0 = 0;    /* Stop timer0 */
  TF0 = 0;    /* Clear timer0 flag */
}

void timer_delay30us()    /* Timer0 delay function */
{
  TMOD = 0x01;    /* Timer0 mode1 (16-bit timer mode) */
  TH0 = 0xFF;   /* Load higher 8-bit in TH0 */
  TL0 = 0xF1;   /* Load lower 8-bit in TL0 */
  TR0 = 1;    /* Start timer0 */
  while(TF0 == 0);  /* Wait until timer0 flag set */
  TR0 = 0;    /* Stop timer0 */
  TF0 = 0;    /* Clear timer0 flag */
}

void Request()      /* Microcontroller send request */
{
  DHT11_PIN = 0;    /* set to low pin */
  timer_delay20ms();  /* wait for 20ms */
  DHT11_PIN = 1;    /* set to high pin */
}

void Response()     /* Receive response from DHT11_PIN */
{
  while(DHT11_PIN==1);
  while(DHT11_PIN==0);
  while(DHT11_PIN==1);
}

int Receive_data()    /* Receive data */
{
  int q,c=0;  
  for (q=0; q<8; q++)
  {
    while(DHT11_PIN==0);/* check received bit 0 or 1 */
    timer_delay30us();
    if(DHT11_PIN == 1)  /* If high pulse is greater than 30ms */
    c = (c<<1)|(0x01);/* Then its logic HIGH */
    else    /* otherwise its logic LOW */
    c = (c<<1);
    while(DHT11_PIN==1);
  }
  return c;
}

void main() {
  UartInit();
  UartSendString("STC15L2K32S2\r\nUART1 Test 115200 bps!\r\n");
  while (1) {
    Request();  /* send start pulse */
    Response(); /* receive response */
    
    I_RH=Receive_data();  /* store first eight bit in I_RH */
    D_RH=Receive_data();  /* store next eight bit in D_RH */
    I_Temp=Receive_data();  /* store next eight bit in I_Temp */
    D_Temp=Receive_data();  /* store next eight bit in D_Temp */
    CheckSum=Receive_data();/* store next eight bit in CheckSum */

    // if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum) {
    //   UartSendString("Checksum Error");
    //   UartSendData(((CheckSum%100)/10)+'0');
    //   UartSendData(((CheckSum%10))+'0');
    //   UartSendData('\r');
    //   UartSendData('\n');
    // } else {
      UartSendString("Humidity: ");
      UartSendData(((I_RH%100)/10)+'0');
      UartSendData(((I_RH%10))+'0');
      UartSendData((D_RH)+'0');
      UartSendString(" % | Temperature: ");
      UartSendData(((I_Temp%100)/10)+'0');
      UartSendData(((I_Temp%10))+'0');
      UartSendData((D_Temp)+'0');
      UartSendString(" Celsius\r\n");
    // }
  }
}