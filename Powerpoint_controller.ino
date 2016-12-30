#include <Keyboard.h>
const int buttonPin = 7;
int buttonState = 0;
void setup() {
  pinMode(buttonPin, INPUT);
}
void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Keyboard.write(' ');
    delay(500);
  }
}                                            
