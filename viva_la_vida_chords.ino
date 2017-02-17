#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <MIDI.h>
//#include <CapacitiveSensor.h>
#include "midi_notes.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();
// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

const bool DEBUG = 0;
int* song[] = {CHORD_Db, CHORD_Eb, CHORD_Ab, CHORD_Fm};
//int duration = 500;
int instrument = 50;

MIDI_CREATE_DEFAULT_INSTANCE();
void setup()
{
  while (!Serial);        // needed to keep leonardo/micro from starting too fast!

  MIDI.begin();
  if (DEBUG) {
    Serial.begin(115200);  // needed for hairless midi
  }
  if (!cap.begin(0x5A)) {
    // Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  delay(1000);
  MIDIsoftreset();  // Midi Reset
  delay(200);
  MIDI.sendProgramChange(instrument, 1);
}

void loop()
{
  // Get the currently touched pads
  currtouched = cap.touched();

  for (uint8_t i = 0; i < 4; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      playChord(song[i], 1);

    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      stopChord(song[i], 1);
    }
  }

  // reset our state
  lasttouched = currtouched;

  // put a delay so it isn't overwhelming
  delay(20);
}

void playChord(int i[], int channel) {
  for (uint8_t note = 0; note < 6; note++) {
    if (i[note]) {
      MIDI.sendNoteOn((i[note]), 100, channel);
    }
  }
}

void stopChord(int i[], int channel) {
  for (uint8_t note = 0; note < 6; note++) {
    if (i[note]) {
      MIDI.sendNoteOff((i[note]), 100, channel);
    }
  }
}

void MIDIsoftreset()  // switch off ALL notes on channel 1 to 16
{
  for (int channel = 0; channel < 16; channel++)
  {
    MIDI.sendControlChange(123, 0, channel);
  }
}

