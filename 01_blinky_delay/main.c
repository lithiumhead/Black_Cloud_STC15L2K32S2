#include "8051.H" // Not using any special features of STC15L2K32S2, using only generic features of 8051

// No operation in assembly
#define nop()  \
     __asm     \
         nop   \
     __endasm  \

void Delay8ms() {  //@11.0592MHz
  // Code Generated using stc-isp-15xx-v6.88E
  unsigned char i=87, j=12;
  nop();
  nop();
  do {
    while (--j);
  } while (--i);
}

main() {
  char count = 0x00;
  P2 = 0xFF; // Setting all Pins of PORT2 High.

  while (1) {
    P2 = count; // Output the contents of the variable "count" on PORT2.
                // LEDs are connected to Red, Blue, Green connected to P2.5, P2.6, P2.7 respectively
    count = count + 1; // Increment the contents of "count" variable.
    Delay8ms();
    // This means P2_0 will go through one on/off cycle every 16 ms
    // ...and hence P2_1 will go through one on/off cycle every 32 ms
    // ...
    // ...P2.5 (Red LED) will go through an on/off cycle every 512 ms (approx half a second)
    // ...P2.6 (Blue LED) will go through an on/off cycle every 1024 ms (approx 1 second)
    // ...P2.7 (Green LED) will go through an on/off cycle every 2048 ms (approx 2 seconds)
  };
}
