# Automated_Smart-Parking_System
The automated smart parking system is designed to enhance parking management by automating the detection and allocation of parking spaces. This system leverages the Arduino Uno microcontroller and IR (Infrared) sensors to detect the presence or absence of vehicles in parking spots.he primary goal is to provide a real-time update on parking availability and guide users to free spaces, thereby reducing the time spent searching for parking and improving overall parking efficiency.

## Overview
The Automated Smart Parking System is designed to manage parking spaces efficiently using an Arduino Uno, IR sensors, a servo motor, LEDs, and an LCD display. This system automates the detection and allocation of parking slots, reducing the time spent searching for parking and improving overall efficiency.

## Components
- *Arduino Uno:* Central controller
- *IR Sensors:* Detects presence of vehicles in parking slots
- *Servo Motor:* Controls the barrier gate for entry and exit
- *LEDs:* Indicate whether a parking slot is occupied or empty
- *LCD Display:* Shows real-time updates on parking availability
- *Wires and Breadboard:* For connections

## Circuit Diagram
Make sure to connect components as per the following:
- *IR Sensors:* 
  - Car Slot 1: Pin 9
  - Car Slot 2: Pin 6
  - Car Slot 3: Pin 7
  - Car Slot 4: Pin 8
  - Entry Sensor: Pin 2
  - Exit Sensor: Pin 4
- *LEDs:*
  - Slot 1: Pin 10
  - Slot 2: Pin 11
  - Slot 3: Pin 12
  - Slot 4: Pin 13
- *Servo Motor:* Pin 3
- *LCD Display:* I2C pins (SDA and SCL)

## Installation and Setup
1. *Hardware Setup:*
   - Connect the IR sensors, LEDs, and servo motor to the Arduino Uno as per the circuit diagram.
   - Connect the LCD display using I2C interface (SDA and SCL pins).

2. *Software Setup:*
   - Install the required Arduino libraries:
     - Servo
     - LiquidCrystal_I2C
   - Upload the provided Arduino sketch to the Arduino Uno using the Arduino IDE.

