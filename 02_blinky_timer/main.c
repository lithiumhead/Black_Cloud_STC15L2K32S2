#include "8051.H" // Not using any special features of STC15L2K32S2, using only generic features of 8051

volatile unsigned char leds=0x00;

void timer0ISR() __interrupt(TF0_VECTOR) {
  P2=leds;     // Output the value of the variable "leds" to PORT2.
  leds=~leds;  // Complement all the bits of the variable "leds".
               // This will blink all three LEDs together.
  TH0 = 0;
  TL0 = 0;
}

void main() {
  P2=0xff;            // Setting all Pins of PORT2 High.
  TMOD = 0b00000001;  // Timer 0 in 16-bit Timer Mode
  TH0 = 0;            // Maximum count from 0x0000 to 0xFFFF for maximum delay ...
  TL0 = 0;            // ... so that blinking is visible to human eyes
  IE = 0x86;          // Enable Interrupts
  TR0 =1;             //
  while(1) {          // Do nothing in Super Loop since it is interrupt driven
  }
}
