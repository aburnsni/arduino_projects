/*
   Andrew's piezo blues improvisor
*/
#include <MIDI.h>
#include "midi_notes.h";

// Constants
#define DEBUG 0  // Debug more defaults to 9600 baud
#define PAD1 0
#define SWITCH1 7
#define LED1 13
#define NUMNOTES 13

int scale[(NUMNOTES)] = {C3, Eb3, F3, Gb3, G3, Bb3, C4, Eb4, F4, Gb4, G4, Bb4, C5};
int instrument = 26;  // Midi instrument

// DO NOT CHANGE
byte val = 0;      // Initializing the variable for the voltage value
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
}

void loop()
{
  val = analogRead(PAD1);  // Read the voltage
  //  if (val) {
  //    Serial.println(val);
  //  }
  note = floor((val * (NUMNOTES + 1)) / 254);
  if (note > (NUMNOTES)) { // Sanity check
    note = (NUMNOTES);
  }
  if ((note != last_note) && (note > 0)) {  // Prevent repeated notes and prevent playing with no touch
    digitalWrite(LED1, HIGH);
    if (DEBUG) {
      Serial.println(scale[note - 1]); // print note for debugging subract one to account for array numbering
      delay(300);
    } else {
      MIDI.sendNoteOn(scale[note - 1], 100, 1);
      delay(300);
      // Note off if required
      // MIDI.sendNoteOff(scale[note-1],0,1);
    }
    digitalWrite(LED1, LOW);
    last_note = note;
  }

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

