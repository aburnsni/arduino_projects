/*
   Andrew's Christmas Light controller.  Operates up to 6 starnds of LEDs with various patterns.
   <aburnsni@gmail.com>
   TODO
   Lose delays
   Impliment button to change patern
*/

bool firstRun = 1;
int patternNum = 1;  // Initial pattern number
int numLeds = 3; // Number of LEDs attached

// LED setup
const int ledPin[] = {3, 5, 6, 9, 10, 11};  // Pins for LEDs (all pwm pins)
int ledVal[6];  // Array for LED values
int ledDir[6];  // Array for LED fade direction (1 for up, -1 for down)
int count = 0;  // Count for array loops

// Button setup
const int buttonPin = 2;
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

int wait = 50; // 50ms (.05 second) delay; shorten for faster fades
int longwait = wait * 6;
int DEBUG = 1; // DEBUG counter; if set to 1, will write values back via serial
int i = 0;

void setup()
{
  for (count = 0; count < numLeds; count++) {
    pinMode(ledPin[count], OUTPUT);  // Set LED pins for output
  }
  pinMode(buttonPin, INPUT);  // Set pin mode for button

  if (DEBUG) {           // If we want to see the pin values for debugging...
    Serial.begin(9600);  // ...set up the serial ouput on 0004 style
  }
}

// Main program
void loop() {
  switch (patternNum) {
    case 1:
      { //Slow Fades
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
        }
        // Debug
        if (DEBUG) {  // If we want to read the output
          for (count = 0; count < numLeds; count++) {
            Serial.print(ledVal[count]);  // Print value
            if (count != numLeds - 1) {
              Serial.print("\t");    // Print tab
            } else {
              Serial.println("");    // Print CR
            }
            if (i == 508) {
              DEBUG = 0;  // Only show debug output for one loop
            }
          }
        }
        i += 1;      // Increment counter

        // Fade LEDs
        for (count = 0; count < numLeds; count++) {
          if (ledVal[count] > 254 || ledVal[count] == 1) {
            ledDir[count] = -1 * ledDir[count];       // Change fade direction at extremes
          }
          ledVal[count] = ledVal[count] + ledDir[count];
          analogWrite(ledPin[count], ledVal[count]);
        }

        delay(wait); // Pause for 'wait' milliseconds before resuming the loop
        break;
      }
    case 2:
      for (count = 0; count < numLeds; count++) {
        digitalWrite(ledPin[count], HIGH);
        delay (longwait);
        digitalWrite(ledPin[count], LOW);
      }
      break;

    case 3:
      for (count = 0; count < numLeds; count++) {
        digitalWrite(ledPin[count], HIGH);
        delay (wait);
        digitalWrite(ledPin[count], LOW);
      }
      break;
  }
}

