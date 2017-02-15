#include <MIDI.h>
#include <CapacitiveSensor.h>
#include "midi_notes.h"

int* song[] = {CHORD_Db, CHORD_Eb, CHORD_Ab, CHORD_Fm};
int duration = 500;
int instrument = 50;

CapacitiveSensor cs[] = {CapacitiveSensor(2, 3), CapacitiveSensor(4, 5), CapacitiveSensor(6, 7), CapacitiveSensor(8, 9)};
long last_cap[] = {0, 0, 0, 0};
long cap[] = {0, 0, 0, 0};
int i = 0;

MIDI_CREATE_DEFAULT_INSTANCE();
void setup()
{
  MIDI.begin();
  Serial.begin(115200);
  for (i = 0; i < 4; i++) {
    cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example

  }

  MIDI.sendProgramChange(instrument, 1);
}

void loop()
{
  for (i = 0; i < 4; i++) {
    cap[i] = cs[i].capacitiveSensor(5);
  }
  for (i = 0; i < 4; i++) {


    if (abs(cap[i] - last_cap[i]) > 5000) {
      if (cap[i] > last_cap[i]) {
        playChord(song[i], 1);
        delay(100);
      }
      //Serial.println(cap[i]);
    }
    last_cap[i] = cap[i];
  }
}

void playChord(int i[], int channel) {
  for (uint8_t note = 0; note < 6; note++) {
    if (i[note]) {
      MIDI.sendNoteOn((i[note]), 100, channel);
    }
  }
  delay(duration);
  for (uint8_t note = 0; note < 6; note++) {
    if (i[note]) {
      MIDI.sendNoteOff((i[note]), 100, channel);
    }
  }
}

