/*
   Andrew's Christmas Light controller.  Operates up to 6 starnds of LEDs with various patterns.
   <aburnsni@gmail.com>
   TODO
   Lose delays
   Impliment button to change patern
*/

bool firstRun = 1;  // Bool for setup within each pattern
int patternNum = 5;  // Initial pattern number
int numLeds = 3; // Number of LEDs attached

long prevLed[6];

// LED setup
const int ledPin[] = {3, 5, 6, 9, 10, 11};  // Pins for LEDs (all pwm pins)
int ledVal[6];  // Array for LED values
int count = 0;  // Count for array loops

int interval[] = {31, 144, 144, 0, 0, 0};  // Assign initial intervals to LEDs (Do not start at 1 or 254 as this will mess with the direction)
int ledDir[] = {1, 1, -1, 0, 0, 0};     // Assign initial direction to LEDs


// Button setup
const int buttonPin = 13;
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

const int pwmIntervals = 200;
// The R value in the graph equation
float R;
int brightness = 0;
int brightnessA[6];

int wait = 50; // 50ms (.05 second) delay; shorten for faster fades

int DEBUG = 1; // DEBUG counter; if set to 1, will write values back via serial
int i = 0;


void setup()
{
  for (count = 0; count < numLeds; count++) {
    pinMode(ledPin[count], OUTPUT);  // Set LED pins for output
  }
  pinMode(buttonPin, INPUT);  // Set pin mode for button

  R = (pwmIntervals * log10(2)) / (log10(255)); // Calculate R value for brightness curve

  long currentMillis = millis(); // Initialise current time array
  for (count = 0; count < numLeds; count++) {
    prevLed[count] = currentMillis;
  }
  if (DEBUG) {           // If we want to see the pin values for debugging...
    Serial.begin(9600);  // ...set up the serial ouput on 0004 style
  }
}

// Main program
void loop() {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      patternNum++;
      if (patternNum == 5) {
        patternNum = 1;
      }
    }

  switch (patternNum) {
    case 1:
      //Slow Fades
      if (firstRun) {
        int ledValTemp[] = {2, 170, 170, 0, 0, 0};  // Assign initial values to LEDs (Do not start at 1 or 254 as this will mess with the direction)
        int ledDirTemp[] = {1, 1, -1, 0, 0, 0};     // Assign initial direction to LEDs
        memcpy(ledVal, ledValTemp, 6);              //
        memcpy (ledDir, ledDirTemp, 6);             //
        firstRun = 0;
        if (DEBUG) {
          for (count = 0; count < numLeds; count++) {
            Serial.print ("LED");
            Serial.print (count);
            if (count != numLeds - 1) {
              Serial.print ("\t");
            } else {
              Serial.println("");
            }
          }
        }

        //        // Debug
        //        if (DEBUG) {  // If we want to read the output
        //          for (count = 0; count < numLeds; count++) {
        //            Serial.print(ledVal[count]);  // Print value
        //            if (count != numLeds - 1) {
        //              Serial.print("\t");    // Print tab
        //            } else {
        //              Serial.println("");    // Print CR
        //            }
        //            if (i == 508) {
        //              DEBUG = 0;  // Only show debug output for one loop
        //            }
        //          }
        //        }
        //        i++;      // Increment counter

        // Fade LEDs
        if (millis() - prevLed[0] >= wait) {
          for (count = 0; count < numLeds; count++) {
            if (ledVal[count] > 254 || ledVal[count] == 1) {
              ledDir[count] = -1 * ledDir[count];       // Change fade direction at extremes
            }
            ledVal[count] = ledVal[count] + ledDir[count];
            analogWrite(ledPin[count], ledVal[count]);
          }
          prevLed[0] = millis();
        }
        break;
      }

    case 2:
      digitalWrite(ledPin[count], HIGH);
      if (millis() - prevLed[0] >= wait * 6) {
        digitalWrite(ledPin[count], LOW);
        count++;
        prevLed[0] = millis();
      }
      if (count == numLeds) {
        count = 0;
      }
      break;

    case 3:
      digitalWrite(ledPin[count], HIGH);
      if (millis() - prevLed[0] >= wait) {
        digitalWrite(ledPin[count], LOW);
        count++;
        prevLed[0] = millis();
      }
      if (count == numLeds) {
        count = 0;
      }
      break;

    case 4:
      for (count = 0; count < numLeds; count++) {
        for (i = 0; i < pwmIntervals; i++) {
          brightness = pow (2, (i / R)) - 1;
          analogWrite(ledPin[count], brightness);
          delay(wait / 5);
        }
        for (i = pwmIntervals; i >= 0; i--) {
          brightness = pow (2, (i / R)) - 1;
          analogWrite(ledPin[count], brightness);
          delay(wait / 5);
        }
      }
      break;
    case 5:
      if (millis() - prevLed[0] >= wait/2) {
        prevLed[0] = millis();

        for (count = 0; count < numLeds; count++) {

          brightnessA[count] = pow (2, (interval[count] / R)) - 1;
          analogWrite(ledPin[count], brightnessA[count]);
          interval[count] = interval[count] + ledDir[count];
          if (interval[count] == pwmIntervals || interval[count] == 30) {
            ledDir[count] = ledDir[count] * -1;
          }
        }
      }
      break;

  }
}

