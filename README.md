# Cube Timer Protoboard
My first ever Arduino project. A timer designed for solving a rubiks cube using Arduino Nano

# Features
* powered by Arduino Nano
* up to 99.99 seconds timer onto a 4-digit Seven segment display driven by a shift register
* two buttons to start and pause
* a reset button
* a buzzer for start
* buzzer warning for 30, 60, 90, seconds

# Components
* 1x Arduino Nano
* 1x 4-digit seven segment display (SH5461AS)
* 1x 74HC595 shift register
* 7x 330 Ω resistor
* 3x 10 kΩ resistor
* 3x switch button (2x 10mm, 1x 5mm)
* 1x buzzer

# For the protoboard assembly
* protoboard (3" x 5")
* female hedear pins for Arduino Nano (or an IC socket designed for Nano)
* 16-pin IC socket
* jumper wires
* copper tape (for ground connections)

# Operation
0. The timer starts at '0.00' and is not running. The red light is on
1. Press L and R buttons to start the timer. The yellow light will now turn on to confirm that the buttons are pressed.
2. Once the green light is on, you may now release it and start the timer.
3. To stop, press either L or R button, and the 7-segment display will record your time.
4. Reset the timer by pressing the middle button.
5. To start again, go to (1).

# Concerns
* Check if the time is calibrated, i.e. run a stopwatch along with the timer
* Upon pressing R and L buttons, when you release one button while holding the other, the timer will automatically start and stop at '0.01'.

# Further improvements
* Replace L and R buttons with a capacitive touch sensor
