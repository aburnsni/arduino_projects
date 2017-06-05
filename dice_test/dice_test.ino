const int ledPin[] = {4, 5, 6, 7};
const int tiltPin = 9;
int buttonState;
int previousButtonState;
unsigned long previousThrowTime = 0;
unsigned long throwDelay = 5000;

int result = 0;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
  pinMode(tiltPin, INPUT);
}


void loop() {
  int buttonState = digitalRead(tiltPin);
  Serial.println(buttonState);
  if (buttonState == HIGH && previousButtonState == LOW && millis() - previousThrowTime > throwDelay) {
    shuffle();
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPin[i], LOW);
    }
    result = random(6) + 1;
    switch (result) {
      case 1:
        digitalWrite(ledPin[0], HIGH);
        break;
      case 2:
        digitalWrite(ledPin[1], HIGH);
        break;
      case 3:
        digitalWrite(ledPin[0], HIGH);
        digitalWrite(ledPin[1], HIGH);
        break;
      case 4:
        digitalWrite(ledPin[1], HIGH);
        digitalWrite(ledPin[2], HIGH);
        break;
      case 5:
        digitalWrite(ledPin[0], HIGH);
        digitalWrite(ledPin[1], HIGH);
        digitalWrite(ledPin[2], HIGH);
        break;
      case 6:
        digitalWrite(ledPin[1], HIGH);
        digitalWrite(ledPin[2], HIGH);
        digitalWrite(ledPin[3], HIGH);
        break;
    }
    previousThrowTime = millis();
    previousButtonState = HIGH;
  } else if (buttonState == LOW) {
    previousButtonState = LOW;
  }
}


void shuffle() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPin[i], LOW);
  }
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

