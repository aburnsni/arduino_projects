#include <Keyboard.h>
const int buttonPinL = 7;
const int buttonPinR = 6;
int buttonStateL = 0;
int buttonStateR = 0;
void setup() {
  pinMode(buttonPinL, INPUT);
  pinMode(buttonPinR, INPUT);
}
void loop() {
  buttonStateL = digitalRead(buttonPinL);
    buttonStateR = digitalRead(buttonPinR);
  if (buttonStateL == HIGH) {
    Keyboard.write(' ');
    delay(500);
  }
    if (buttonStateR == HIGH) {
    Keyboard.write(8);
    delay(500);
  }
}
