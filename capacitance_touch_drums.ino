#include <MIDI.h>
#include <CapacitiveSensor.h>

bool DEBUG = 0;

int note[] = {49, 55, 52, 57};

CapacitiveSensor cs[] = {CapacitiveSensor(2, 3), CapacitiveSensor(4, 5), CapacitiveSensor(6, 7), CapacitiveSensor(8, 9)};
long last_cap[] = {0, 0, 0, 0};
long cap[] = {0, 0, 0, 0};
int i = 0;

MIDI_CREATE_DEFAULT_INSTANCE();
void setup()
{
  MIDI.begin();
  if (DEBUG) {
    Serial.begin(115200);
  }
  for (i = 0; i < 4; i++) {
    cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example

  }
}

void loop()
{
  for (i = 0; i < 4; i++) {
    cap[i] = cs[i].capacitiveSensor(5);
  }
  for (i = 0; i < 4; i++) {


    if (abs(cap[i] - last_cap[i]) > 5000) {
      if (cap[i] > last_cap[i]) {

        MIDI.sendNoteOn(note[i], 100, 10);
        delay(100);
      }
      //Serial.println(cap[i]);
    }
    last_cap[i] = cap[i];
  }
}

