# Load-Shedding-Time-Management-System-Using-Arduino
Final Year Project
This project is an Arduino-based load management system designed to automate ON/OFF control of multiple electrical loads (bulbs) based on time scheduling and manual toggle options. It aims to provide a simple, reliable, and low-cost solution for household or small-scale load shedding scenarios.

🔧 Features

Control 3 loads (White, Blue, Yellow) via relay module

4×4 Keypad interface for:

Manual bulb ON/OFF toggle

Selecting bulbs for countdown control

Entering countdown duration in seconds

16×2 I2C LCD Display for:

Real-time bulb ON/OFF status

Countdown status and remaining time

User prompts during selection and entry

Automatic load restoration after countdown ends

Safe switching using relays and transistor drivers

Powered by 12 V transformer + rectifier + buck converter (stable 12 V to Arduino)

🖥️ Components Used

Arduino Uno R3

3 × Relay modules (5V, 10A)

4×4 Matrix Keypad

16×2 I2C LCD display

Step-down transformer (12V AC)

Bridge rectifier + Buck converter

Bulbs (White, Blue, Yellow) as loads

Supporting components: Transistors, diodes, resistors, wires, breadboards

⚙️ Working Principle

Startup: All bulbs are ON by default, shown on the LCD.

Manual Control:

Keys 1, 4, 7 toggle White, Blue, Yellow bulbs respectively.

Selection Mode:

Keys A, B, C select White, Blue, Yellow bulbs.

Multiple bulbs can be selected at once.

Key * proceeds to time entry.

Countdown Mode:

User enters duration (seconds) via keypad.

Press D to confirm.

Selected bulbs turn OFF immediately and are restored ON when countdown finishes.

Cancel/Reset:

Key # cancels any ongoing selection or entry.

📟 Circuit Overview

AC 220 V → 12 V AC transformer → Bridge rectifier → Buck converter → 12 V regulated DC for Arduino.

Relays act as isolated switches to control bulbs.

Keypad sends inputs to Arduino.

LCD provides real-time feedback.

🧩 Code

Full Arduino code is available in main.ino
.
It handles keypad input, relay control, LCD display, countdown timer logic, and load state tracking.

🚀 Future Improvements

Add current sensor (ACS712 / INA219) to monitor load current and perform automatic load shedding on overload.

Add buzzer alert for overload or countdown completion.

Allow user-defined current thresholds via keypad.

Add RTC module (DS3231) to schedule loads based on real-time clock.

📸 Project Photo


(Arduino Uno with LCD, keypad, relay module, transformer, rectifier, buck converter, and bulbs.)

🏆 Achievements

Scored 14/15 (highest mark) in university lab evaluation.

Recognized for clean design, proper documentation, and practical application.
