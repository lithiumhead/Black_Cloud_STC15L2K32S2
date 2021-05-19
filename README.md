# Hacking the AI-Thinker ESP8266 Black Board T5 

I got my hands on the this cheap demo board a few years ago. It is made by [AI-Thinker](http://www.ai-thinker.com) which is a licensed manufacturer of modules based on WiFi/Bluetooth enabled microcontrollers made by [Espressif](https://www.espressif.com).

## Board Specifications

### Hardware

- Two 3.3V Logic Microcontrollers:
  - ESP8266MOD WiFi Module (Microcontroller with built-in WiFi and TCP/IP Stack by Espressif)
  - STC15L2K32S2 8051 Microcontroller with 32K Program Memory, 2K SRAM, 2 UARTs, ADC etc
- Peripherals connected to STC15L2K32S2:
  - 2 Tactile Switches connected to P1.3 and P1.4
  - 3 SMD LEDs: Red, Blue, Green connected to P2.5, P2.6, P2.7 respectively
  - DHT11 Temperature and Humidity Sesnor connected to P3.5
  - Piezoelectric buzzer connected to P3.4
  - A 5 volt relay capable of switching 230VAC controlled by P3.3
  - TXD/RXD/GND bought out on to a 3 header which can be used to re-flash STC15L2K32S2 over UART
  - P1.0, P1.1, P1.2, P1.5 and GND have been brought out on a white 0.1" header
- ESP8266MOD's TXD/RXD connected to STC15L2K32S2's RXD2/TXD2. There are 0.1" jumpers that can be dismounted to disconnect them.
- ESP8266MOD's power is controlled by STC15L2K32S2's P5.4
- STC15L2K32S2 runs on internal 11.0592 MHz clock
- The board is powered using three 1.5V AA batteries in connected in series

### Software

The board's STC15L2K32S2 (the 8051 microcontroller) comes with pre-loaded with some firmware and you are supposed to use it with and Android App. 8051's firmware can be built using Keil's uVision IDE/Compiler. Since most perihpherals are connect to the 8051, it's firmware has been written to allow it to be the master and ESP8266 to be the slave. The 8051 issues AT commands to ESP8266 to control it. An accompanying Android App allows the user to connect to the board over wifi and control the various peripherals and read the temperature/humidity from the sensor.

The original source code and schematics are hard to come by. [This](https://mjcsystem.tumblr.com/post/140963546940/compl%C3%A9ment-dinfo-sur-la-mini-carte-espiotdemo) blog post did link to the forum posts on AI-Thinker's forums where they had attached the artifacts but all those links are dead now.

A [gitbooks post](https://anxinke.gitbooks.io/balckboard/content/index.html) describes the Android app (includes screenshots) and the board usage in Chinese.

## What have people done with it

A user that goes by the name PuceBaboon desoldered the 8051 microcontroller on his board and rewired the peripherals directly to ESP8266 and wrote some Arduino code for ESP8266. His code uploads the readings from DHT11 to a server using MQTT
His efforts are documented on his [blog](https://esp8266hints.wordpress.com/2015/12/07/reworking-the-ai-thinker-t5-board/) and the good is posted in oine of his [github repositories](https://github.com/PuceBaboon/ESP8266-AIT-T5)

## What I want to do

I want to avoid any desoldering or even soldering for that matter. So I thought of re-programming the 8051 to be the Slave and ESP8266 to be the master. Since the UART pins of both the microcontrollers can be accessed easily via pin-headers, they both can be re-flashed easily.

I was lucky enough to have downloaded the schematic and the original C code for STC15L2K32S2. But I didn't care much for it since Keil's uVision is not a free compiler. I decided to use the free and open source [SDCC - Small Device C Compiler](http://sdcc.sourceforge.net/) instead to develop code for STC15L2K32S2. And [Arduino](https://www.arduino.cc/) is the popular choice for developing code for the ESP8266.

Another aim is to just have fun writing programs for newer 8051 as well as ESP8266.

## Some Links

 - [STC15L2K32S2 Datasheet](http://www.stcmicro.com/datasheet/STC15F2K60S2-en.pdf)
 - STC's In-System-Programming (ISP) Software for Windows can be dowloaded from http://www.stcmicro.com/rjxz.html.
   - The latest working link as of May 2021 was [stc-isp-15xx-v6.86E.exe](http://www.stcmicro.com/rar/stc-isp6.86e.rar).
     But, when you run this, it informs you to download an updated version [stc-isp-15xx-v6.88E.zip](http://www.stcmcudata.com/STCISP/stc-isp-15xx-v6.88E.zip) from stcmcudata.com
 - [stcgal](https://github.com/grigorig/stcgal) which is a  python base open source flashing tool for STC Micros
 - I have 2 older posts on my blog before I decided to switched to github.com:
   - [Hacking "ESP8266 Black Board T5" Part 1 - Blinky on Keil](https://www.electronicsfaq.com/2018/02/hacking-esp8266-black-cloud-features.html)
   - [Hacking "ESP8266 Black Board T5" Part 2 - Blinky and Hello World on SDCC ](https://www.electronicsfaq.com/2018/07/hacking-esp8266-black-board-t5-part-2.html)
 - [SDCC Download for Windows 64 bit](https://sourceforge.net/projects/sdcc/files/sdcc-win64/). Latest version as of May 2021 was 4.1.0.
 - [Arduino](https://www.arduino.cc/en/software). Latest version as of May 2021 was 1.8.15.

## What do I have in this repository

The code for STC15L2K32S2 Compiles using SDCC. The code for ESP8266 compiles using Arduino.

 - .gitignore Makes sure that the build SDCC artifacts are not uploaded along with the git repository
 - **STC15F2K60S2.H** Header file for use with SDCC when compiling for this microcontroller.
 - [01_blinky_delay](01_blinky_delay/README.md) - Code for STC15L2K32S2: Blinks the 3 LEDs using software delay
 - [02_blinky_timer](02_blinky_timer/README.md) - Code for STC15L2K32S2: Blinks the 3 LEDs using Timer 0
 - **02_uart_echo** - Code for STC15L2K32S2: Receives a character over UART, increments it and sends it back (115200 bps 8-N-1)


## Generic Instructions

TODO

### Compiling code for STC15F2K60S2 using SDCC

TODO

### Attaching USB-UART to STC15F2K60S2

TODO

### Flashing STC15F2K60S2

TODO

#### Using STC ISP on Windows

TODO

#### Using stcgal on Linux

TODO

### Compiling for and Flashing ESP8266 using Arduino

TODO