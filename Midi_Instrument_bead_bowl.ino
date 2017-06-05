/*
   Andrew's piezo blues improvisor
*/
#include <MIDI.h>
#include "midi_notes.h"

// Constants
#define DEBUG 1  // Debug more defaults to 9600 baud

//Setup pad, switch and led
#define PAD1 0
#define SWITCH1 7
#define LED1 13

// If using notes
//#define NUMNOTES 13
// int scale[(NUMNOTES)] = {NOTE_C3, NOTE_Eb3, NOTE_F3, NOTE_Gb3, NOTE_G3, NOTE_Bb3, NOTE_C4, NOTE_Eb4, NOTE_F4, NOTE_Gb4, NOTE_G4, NOTE_Bb4, NOTE_C5};
int instrument = 26;  // Midi instrument

// DO NOT CHANGE
unsigned long time_on =  millis();
unsigned long current_time = time_on;
unsigned long previous_time = time_on;
long total = 0;
//smooth readings
const int numReadings = 20;
int readings[numReadings];
int readIndex = 0;
int totala = 0;
int average = 0;

long val = 0;      // Initializing the variable for the voltage value
byte note = 0;     // Initialising variable for note
byte last_note = 0; // Initialising variable for previous note
bool buttonState = 0;
int channel = 0;  // Channel variable for reset

MIDI_CREATE_DEFAULT_INSTANCE();
void setup()
{
  MIDI.begin();
  if (DEBUG) {
    Serial.begin(115200);
  }
  pinMode( SWITCH1, INPUT );    // Set pin for switch
  digitalWrite( SWITCH1, LOW );
  pinMode(LED1, OUTPUT);        // Set pin for LED

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop()
{

  totala = totala - readings[readIndex];
  readings[readIndex] = analogRead(PAD1);
  totala = totala + readings[readIndex];
  readIndex++;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = totala / numReadings;
  Serial.println(average);


  //  val = analogRead(PAD1);  // Read the voltage
  //  total += val;
  //  if ((millis() - previous_time) > 100) {
  //    Serial.println(total);
  //    Serial.print("\t");
  //    Serial.println(millis() - time_on);
  //  total = 0;
  //   previous_time = millis();
  // }
  delay(5);
  //  note = floor((val * (NUMNOTES + 1)) / 254);
  //  if (note > (NUMNOTES)) { // Sanity check
  //    note = (NUMNOTES);
  //  }
  //  if ((note != last_note) && (note > 0)) {  // Prevent repeated notes and prevent playing with no touch
  //    digitalWrite(LED1, HIGH);
  //    if (DEBUG) {
  //      Serial.println(scale[note - 1]); // print note for debugging subract one to account for array numbering
  //      delay(300);
  //    } else {
  //      MIDI.sendNoteOn(scale[note - 1], 100, 1);
  //      delay(300);
  //      // Note off if required
  //      // MIDI.sendNoteOff(scale[note-1],0,1);
  //    }
  //    digitalWrite(LED1, LOW);
  //    last_note = note;
  //  }

  buttonState = digitalRead(SWITCH1);  // Check for reset switch
  if (buttonState == HIGH)
  {
    MIDIsoftreset();
    delay(200);
    MIDI.sendProgramChange(instrument, 1);
  }
}


void MIDIsoftreset()  // switch off ALL notes on channel 1 to 16
{
  for (channel = 0; channel < 16; channel++)
  {
    MIDI.sendControlChange(123, 0, channel);
  }
}
