/****************************************
  Example Sound Level Sketch for the
  Adafruit Microphone Amplifier
****************************************/
int signalPin = A5;
int ledPin[] = {9, 10, 11, 12, 13, 14, 15};
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
int maxScale = 7;
int amp = 8;

void setup()
{
  Serial.begin(9600);
  for (int i; i < maxScale; i++ ) {
    pinMode(ledPin[i], OUTPUT);
  }
  for (int i = 0; i < maxScale; i++) {
    digitalWrite(ledPin[i], HIGH);
    delay(200);
    digitalWrite(ledPin[i], LOW);
  }
  for (int i = maxScale - 2; i >= 0; i--) {
    digitalWrite(ledPin[i], HIGH);
    delay(200);
    digitalWrite(ledPin[i], LOW);
  }
}


void loop()
{
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(signalPin);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  peakToPeak = peakToPeak * amp;
  //  double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
  int displayPeak = map(peakToPeak, 20 * amp, 1023, 0, maxScale);
  if (displayPeak > maxScale) {
    displayPeak = maxScale;
  }
  if (displayPeak == 0) {
    for (int i = 0; i < maxScale; i++) {
      digitalWrite(ledPin[i], LOW);
    }
  } else {
    for (int i = 0; i < displayPeak; i++) {
      digitalWrite(ledPin[i], HIGH);
    }
    for (int i = displayPeak; i < maxScale; i++) {
      digitalWrite(ledPin[i], LOW);
    }
  }
  delay(100);
}

