const int ledPin[] = {0, 1, 2, 4};
const int tiltPin = 3;
int value = 0;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
  pinMode(tiltPin, INPUT);
}


void loop() {
  buttonState = digitalRead(tiltPin);
  if (buttonState == HIGH) {
    value = random(6) + 1;
    switch (value) {
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
    delay(2000);
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPin[i], LOW);
    }
  }
}

