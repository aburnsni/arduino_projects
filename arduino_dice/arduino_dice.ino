/**
 * Copyright (c) 2017 Andrew Burns
 * Licensed under The MIT License (MIT)
 * License: ./LICENSE
 * Filenames: arduino_dice.ino
 * Board: ATtiny85
 * Speed: 1MHz
 * Programmer: Arduino as ISP
 */

#include <avr/sleep.h>
#include <avr/interrupt.h>

const int ledPin[] = {0, 1, 2, 4};
const int tiltPin = 3;

int buttonState;
int previousButtonState;
unsigned long previousThrowTime = 0;
unsigned long throwDelay = 2000;

int result = 0;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
  pinMode(tiltPin, INPUT);
}

void loop() {
  int buttonState = digitalRead(tiltPin);
  if (buttonState == HIGH && previousButtonState == LOW && millis() - previousThrowTime > throwDelay) {
    shuffle();
    ledsOff();
    result = random(6) + 1;
    switch (result) {
      case 1:
        digitalWrite(ledPin[0], HIGH);
        break;
      case 2:
        digitalWrite(ledPin[3], HIGH);
        break;
      case 3:
        digitalWrite(ledPin[0], HIGH);
        digitalWrite(ledPin[3], HIGH);
        break;
      case 4:
        digitalWrite(ledPin[2], HIGH);
        digitalWrite(ledPin[3], HIGH);
        break;
      case 5:
        digitalWrite(ledPin[0], HIGH);
        digitalWrite(ledPin[2], HIGH);
        digitalWrite(ledPin[3], HIGH);
        break;
      case 6:
        digitalWrite(ledPin[1], HIGH);
        digitalWrite(ledPin[2], HIGH);
        digitalWrite(ledPin[3], HIGH);
        break;
    }
    previousThrowTime = millis();
    previousButtonState = HIGH;
  } else if (buttonState == LOW && millis() - previousThrowTime > throwDelay) {
    previousButtonState = LOW;
  }
  if (millis() - previousThrowTime > 10000) {
    ledsOff();
    sleep();
  }
}

void ledsOff() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPin[i], LOW);
  }
}
void shuffle() {
  ledsOff();
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPin[2], LOW);
    digitalWrite(ledPin[1], HIGH);
    delay(100);
    digitalWrite(ledPin[1], LOW);
    digitalWrite(ledPin[3], HIGH);
    delay(100);
    digitalWrite(ledPin[3], LOW);
    digitalWrite(ledPin[2], HIGH);
    delay(100);
  }
}

void sleep() {

  GIMSK |= _BV(PCIE);                     // Enable Pin Change Interrupts
  PCMSK |= _BV(PCINT3);                   // Use PB3 as interrupt pin
  ADCSRA &= ~_BV(ADEN);                   // ADC off
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement

  sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
  sei();                                  // Enable interrupts
  sleep_cpu();                            // sleep

  cli();                                  // Disable interrupts
  PCMSK &= ~_BV(PCINT3);                  // Turn off PB3 as interrupt pin
  sleep_disable();                        // Clear SE bit
  ADCSRA |= _BV(ADEN);                    // ADC on

  sei();                                  // Enable interrupts
} // sleep

ISR(PCINT0_vect) {
  // This is called when the interrupt occurs, but I don't need to do anything in it
}



