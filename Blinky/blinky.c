#include "../STC15F2K60S2.H"

void delay()
{
	int i, j;

	for ( i = 0; i < 7; i++)
	{
		for ( j = 0; j < 800; j++)
		{
					//Do nothing in this inner for loop.
					//
					//NOTE: The maximum values for the inner and outer loops are randomly
					//choosen to be 800 and 7.
		}
	}
}

main()					//"main" function, program execution will begin from here.
{
	char count=0x00;		//declaring and initializing an 8-bit variable called "count".
	P2=0xFF;			//Setting all Pins of PORT2 High.

	while(1)			//<-- Super Loop.
	{
		P2=count;		//Output the contents of the variable "count" on PORT2.
					//LEDs are connected to PORT2.

		count=count+1;		//Increment the contents of "count" variable.
					//So that means the LEDs on PORT2 would be show the binary counting
					//pattern from 0 to 255.

		delay();		//Some Delay.

					//A microcontroller performs operations very fast,
					//so if this delay is avoided then a human might
					//not be able to make out if the LEDs are blinking,
					//If the delay is very less then the LEDs would be
					//blinking so fast that the only thing you would
					//see is that the various LEDs have lit up with
					//varying brightness, you wont be able to make out
					//the difference between one pattern and the next
					//
					//In our case (Using P89V51RD2 with UNI-51-SDK),
					//the crystal is running at 11.0592 MHz
					//So the microcontroller is executing
					//11059200 / 12 = 921600 instructions per second
	};
}
