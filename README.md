# Load-Shedding-Time-Management-System-Using-Arduino
Final Year Project
Load Shedding Time Management System Using Arduino

This project is an Arduino-based load management system that automates the ON/OFF control of multiple electrical loads based on time scheduling and manual switching. It is designed to be simple, reliable, and low-cost, with practical applications for households and small-scale power systems where load shedding is a concern.

Features

Control of three loads (White, Blue, Yellow) through relays

4x4 Keypad interface for:

Manual load ON/OFF toggle

Selecting one or more loads for countdown control

Entering countdown time in seconds

16x2 I2C LCD display showing:

Real-time load status (ON/OFF)

Countdown progress and remaining time

User prompts during selection and time entry

Automatic restoration of loads after countdown ends

Safe switching using relay and transistor drivers

Powered through transformer, rectifier, and buck converter for stable operation

Components Used

Arduino Uno R3

3 × Relay Modules (5V, 10A)

4x4 Matrix Keypad

16x2 I2C LCD Display

Step-down Transformer (12V AC)

Bridge Rectifier

Buck Converter (to regulate 14V down to 12V DC for Arduino)

Bulbs (White, Blue, Yellow) as loads

Supporting components: Transistors, diodes, resistors, wires, breadboards

Working Principle

Initialization

All loads are ON by default at startup.

LCD displays the status of White, Blue, and Yellow bulbs.

Manual Control

Keys 1, 4, and 7 toggle White, Blue, and Yellow loads respectively.

Selection Mode

Keys A, B, and C select White, Blue, and Yellow loads.

Multiple loads can be selected simultaneously.

Key * proceeds to countdown time entry.

Countdown Mode

Time is entered using numeric keys.

Key D confirms the entry.

Selected loads turn OFF immediately and automatically restore ON after the countdown finishes.

Cancel and Reset

Key # cancels current selection or time entry.

Key C clears the chosen loads in selection mode.

Circuit Overview

AC 220V supply is stepped down to 12V AC by a transformer.

Bridge rectifier converts AC to DC (~14V).

Buck converter regulates the voltage down to a stable 12V DC for Arduino.

Relays act as electronic switches to control bulbs.

Keypad provides user input.

LCD provides real-time feedback of system state.

Code

The full Arduino code is available in the repository (main.ino).
It manages keypad input, relay control, LCD output, countdown logic, and state management of the loads.

Future Improvements

Integration of a current sensor (ACS712 / INA219) to detect overload conditions and perform automatic load shedding.

Addition of a buzzer for alerts on overload or countdown completion.

User-defined current threshold configuration via keypad.

Incorporation of a Real-Time Clock (DS3231) for scheduling based on actual time of day.

Project Photo


Arduino Uno with LCD, keypad, relay module, transformer, rectifier, buck converter, and bulbs.

Achievements

Awarded highest lab mark (14/15) for design, implementation, and documentation.

Recognized as a practical and effective solution for automated load shedding.
