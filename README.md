# Embedded-System-Projects
# Projects based on PIC18F4620 Microcontroller
## Car Temperature controller 
- The temperature sensor starts to read the temperature of the motor and inform the user by a message on the LCD and two LEDS.
- If the temperature is between 90 Celsius and 105 Celsius that meaning that the temperature is normal and everything is ok, but when the temperature starts increasing above 105 Celsius, the motor starts overheating so a message displayed on LCD and one of LEDS turned on to inform the user and the motor started to work as a fan trying to decrease the Temperature.
- If the temperature doesn't change and still increasing, we inform the user with a message on the LCD and two LEDS turn on that the motor's temperature becomes dangerous and the user should leave the car.
  
## Safe Automated Garage System
- For the first time you should set the password using EEPROM and after that system wait until the sensors read that there is a car near to gates.
- If the entry gate reads that there is a car near the entry gate, the system asks the user for the password then if the password is true the entry gate starts to open and wait until the car enters then closes the gate automatically
- If the exit gate reads there is a car near the exit gate , the gate opens and waits until the car exits then closes the gate automatically.
  
## Smart Home
- There are two microcontrollers to controll the operations of smart home, each microcontroller has its own code.
- Project has two modes Admin Mode and Guest Mode

- Admin Mode for the user which owns the Home which has the privilege to control all Rooms, TV and Air conditioning. 
- Guest Mode for any other users which has the privilege to control all Rooms only.

- First like any devices for the first time you should set passwords of all users in admin or Guest Mode and store permanently in EEPROM, then choose one of the modes by keypad and LCD
Based on mode, you can control the Rooms, TV and Air conditioning.

- You can control leds of Rooms and TV by master microcontroller and then use SPI Protocol to send Data to Slave microcontroller to turn on leds or turn off them.

- for Air conditioning, you can set the temperature of Air conditioning, control the Air conditioning by master microcontroller and the temperature of Rooms is sent by Slave microcontroller.

- Air conditioning works only when temperature entered is lower than temperature sent by Slave microcontroller and Air conditioning turned on.
- If the temperature entered is higher than temperature sent by Slave microcontroller, the Air conditioning turned off.

## PIC18F4620 Device Driver
- contain the device driver than contain the implemenataion of components that used in projects.
 
# Projects based on AVR Microcontroller
## Final Project (Smart Tredmill)

- First the PIR Sensor wait to detect the person and when the sensor detects that there is a person near to the treadmill, the Timer Starts and the motor works at the lowest speed as an initialization for the treadmill.

- There are four switches to control the features of the treadmill:
1- Increase Motor Speed: Used to increase the speed of the treadmill
2- decrease Motor Speed: Used to decrease the speed of the treadmill 
3- Stop Treadmill: used to pause the treadmill (stop motor and the timer)
4- Resume Treadmill: used to Resume the treadmill (Resume motor and the timer with the last status)

## Fan Controller System 
- Implement the following Fan Controller system with the specifications listedbelow:
- The aim of this project is to design a temperature-controlled fan using ATmega32
microcontroller, in which the fan is automatically turned ON or OFF according to the
temperature. Use ATmega32 Microcontroller with frequency 1Mhz.
- In this project, the LM35 temperature sensor will give continuous analog output
corresponding to the temperature sensed by it. This analog signal is given to the ADC,
which converts the analog values to digital values.
- The digital output of the ADC is equivalent to sensed analog voltage.
- In order to get the temperature from the sensed analog voltage, we need to perform some
calculations in the programming for the microcontroller.
- Once the calculations are done by the microcontroller according to the logic, the
temperature is displayed on the LCD.
- The microcontroller will continuously monitor the temperature and based on the
temperature value; the microcontroller will drive the fan like that:
1. If the temperature is less than 30C turn off the fan.
2. If the temperature is greater than or equal 30C turn on the fan with 25% of its
maximum speed.
3. If the temperature is greater than or equal 60C turn on the fan with 50% of its
maximum speed.
4. If the temperature is greater than or equal 90C turn on the fan with 75% of its
maximum speed.
5. If the temperature is greater than or equal 120C turn on the fan with 100% of its
maximum speed.

- The main principle of the circuit is to switch on/off the fan connected to DC motor based
on temperature value. The DC-Motor rotates in clock-wise direction or stopped based on
the fan state.

## Voltameter Challange
- The project used to perform the function of Voltameter.
- The microcontroller reads the value of Voltage using ADC module then print the value on the LCD which represent the voltage after voltage divider circuit.

## AVR Device Driver
- Contains the device driver that contains the implemenataion of each component that is used in projects.

