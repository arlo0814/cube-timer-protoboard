/*
  RUBIKS CUBE TIMER 1.0
  This is a cube timer project using a 4-digit 7-segment display.
  It uses a 74HC595 shift register with the SevSegShift library.
  created May 2020 by arlo14
*/

#include "SevSegShift.h"

// SevSeg Display setup with a Shift Register
#define SHIFT_PIN_DS 2
#define SHIFT_PIN_STCP 3
#define SHIFT_PIN_SHCP 4

SevSegShift sevsegshift(SHIFT_PIN_DS, 
                SHIFT_PIN_SHCP, 
                SHIFT_PIN_STCP, 
                1, // number of shift register
                true); // digits are directly connected to Arduino
 

const int RED_LED = 9, YELLOW_LED = 10, GREEN_LED = 11; // LED pins
const int BUZZ_PIN = 12; // Buzzer Pin

int L_BUTTON = 5, M_BUTTON = 6, R_BUTTON = 7; // BUTTON pins
int L_Val, M_Val, R_Val; // Button value tracker
int stopWatchState = 0; // 0 - stop, 1 - running, 2 - stop/reset

// STOPWATCH 
static int decaMilliSeconds = 0; // refers to 10 miliiSeconds, I created the name
unsigned long timer = 0;

void setup() {
  byte numDigits = 4; 
  byte digitPins[] = {A1, A2, A3, A4}; // SevSeg digit pins, LeftToRight
  byte segmentPins[] = {7, 0, 2, 4, 5, 6, 1, 3}; 
      // shift register pins (Q0 - Q7) to sevSeg A - H(DP) segments
  bool resistorsOnSegments = false; // resistors on digit pins
  byte hardwareConfig = COMMON_CATHODE; 
  bool updateWithDelays = false;
  bool leadingZeros = false;
  bool disableDecPoint = false;

  sevsegshift.begin(hardwareConfig, numDigits, digitPins, 
                segmentPins, resistorsOnSegments, 
                updateWithDelays, leadingZeros, disableDecPoint);
  sevsegshift.setBrightness(90);

  for (int i = 9; i <=12; i++) {
    pinMode(i, OUTPUT); // set pins 9 to 12 as output
  }
  for (int i = 5; i <=7; i++) {
    pinMode(i, INPUT); // set pins 5 to 7 an input
  }
}

void loop() {
  readButtonVal(); // read button states

  if (stopWatchState == 0) {
    // STOP STATE
    if (L_Val == 0 && R_Val == 0) {
      // display a yellow or 'ready' LED while turning other LEDs off
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      tone(BUZZ_PIN, 440); 
        // play an A4 note until buttons are released
      while (L_Val == 0 && R_Val == 0) {
        readButtonVal();
        // wait until buttons are released
      }
      // set-up stopwatch
      timer = millis();
      decaMilliSeconds = 0;
      tone(BUZZ_PIN, 660, 500); // play an E5 note for 500 mS
      stopWatchState = 1; // running state
      delay(200); // debounce delay
    }
    // show value when starting again
    sevsegshift.setNumber(decaMilliSeconds, 2);
    sevsegshift.refreshDisplay();
  }

  if (stopWatchState == 1) {
    startTimer();
    // display a green or 'go' LED while turning other LEDs off
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    readButtonVal();
    if (L_Val == 0 || R_Val == 0) {
      stopWatchState = 2; // stop state
      delay(200);
    }
  }

  if (stopWatchState == 2) {
    // display the value when the stopwatch is stopped
    sevsegshift.setNumber(decaMilliSeconds, 2);
    sevsegshift.refreshDisplay();
    readButtonVal();
    // display a red or 'stop' LED while turning other LEDs off
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    if (M_Val == 0) {
      // reset timer
      decaMilliSeconds = 0;
      stopWatchState = 0; // initial state (for starting again)
      delay(200);
    }
  }
  if (decaMilliSeconds == 3000 || decaMilliSeconds == 6000 || decaMilliSeconds == 9000) {
    // warning sound for 30, 60, and 90 seconds
    tone(BUZZ_PIN, 988, 1000); // play a B5 note for 1 second
  }
  if (decaMilliSeconds > 9700) {
    // timer is running out (limit is 100 seconds);
    tone(BUZZ_PIN, 1245, 750); // play a D#6 note until reset is pressed
  }
}

void startTimer() {
  if (millis() - timer >= 10) {
    timer += 10; // increase by 10 mS
    decaMilliSeconds++; // increment every 10 mS
    sevsegshift.setNumber(decaMilliSeconds, 2);
  }
  sevsegshift.refreshDisplay();
}

void readButtonVal() {
  // reads button states 
  L_Val = digitalRead(L_BUTTON);
  M_Val = digitalRead(M_BUTTON);
  R_Val = digitalRead(R_BUTTON);
}