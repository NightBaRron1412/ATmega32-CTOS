# Drivers For Atmega32

A repository for drivers built specifically for **Atmega32 AVR Micro-controller** with **layered Architecture** applied.  
This was developed during my time enrolled in Embedded Systems diploma by ITI in 2021 and it's still under development.
This repository can be useful to anyone in the process of learning Embedded Systems, and working with AVR.

This work is licensed under **MIT license**, read LICENSE file for more info. Please consider referring my work if you would ever use it in any of your own projects.


## List of Existing Drivers (most recent)
1. DIO (MCAL Layer)
2. GIE (MCAL Layer)
3. EXTI/Interrupt (MCAL Layer)
4. ADC (MCAL Layer)
5. TMR (MCAL Layer)
6. WDT (MCAL Layer)
7. USART (MCAL Layer)
8. SPI (MCAL Layer)
9. TWI (MCAL Layer)
10. CLCD (HAL Layer)
11. KPD (HAL Layer)
12. EEPROM (HAL Layer)
13. LED (HAL Layer)
14. BTN (HAL Layer)
15. SSD (HAL Layer)

## How to use
Each driver is encapsulated in a folder, to use any of the drivers you should read the `interface.h` file (fully commented on what every function does). 
It's then as easy as just including the `interface.h` file in your work and compiling the driver implementation files with your object file using the compiler. 

## Contributing 
If you'd like to contribute in building more drivers for AVR Atmega32 on this repository, feel free to fork and PR you work. I am always open to contributions and growing this work to give back to the community.

<h4 align='center'>Made with :heart:</h4>
