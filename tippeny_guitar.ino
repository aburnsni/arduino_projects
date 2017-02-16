#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <MIDI.h>
#include "midi_notes.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

// Change these only!!!
const bool DEBUG = 0;
int strum = 5;  // delay between each note of strum
//int* song[] = {CHORD_G, CHORD_Em, CHORD_C, CHORD_D,
//              CHORD_Cm6_Eb, CHORD_B7, CHORD_E7, CHORD_Am9,
//              CHORD_Am7b5_D, CHORD_D7, CHORD_D7add13, CHORD_Em7
//             };  // All I Want For Christmas is You
//int* song[] = {CHORD_C, CHORD_Am, CHORD_F, CHORD_G,
//               CHORD_Dm, CHORD_Em, CHORD_F7, CHORD_G7,
//               DRUM_BASS, DRUM_SIDE, CYM_1, CYM_2
//              };  // Simple Chords
int* song[] = {CHORD_E, CHORD_B, CHORD_B7, CHORD_Gbm,
               CHORD_Gb, CHORD_E7, CHORD_A, CHORD_Dbm,
               CHORD_Gbm, CHORD_Db, 0, 0
              };  // Diamonds are a Girls Best Friend
// 0's in song prevent that key from sounding

int midiChannel[] = {1, 1, 1, 1,
                     1, 1, 1, 1,
                     1, 1, 10, 10
                    }; // midi channel for each button
int instruments[] = {26, 999, 999, 999,
                     999, 999, 999, 999,
                     999, 999 /*Drums*/, 999, 999,
                     999, 999, 999, 999
                    };  // instruments for each channel.  Setting to 999 prevents change

// Charlieplex LED setup
#define A 9
#define B 10
#define C 11
#define D 12
#define PIN_CONFIG 0
#define PIN_STATE 1
#define LED_COUNT 12

int matrix[LED_COUNT][2][4] = {
  //           PIN_CONFIG                  PIN_STATE
  //    A       B       C      D         A     B    C    D
  { { OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW } }, // AB 0
  { { OUTPUT, OUTPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW } }, // BA 1
  { { INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW } }, // BC 2
  { { INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, HIGH, LOW, LOW } }, // CB 3
  { { INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // CD 4
  { { INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, HIGH, LOW } }, // DC 5
  { { OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW } }, // AC 6
  { { OUTPUT, INPUT, OUTPUT, INPUT }, { HIGH, LOW, LOW, LOW } }, // CA 7
  { { INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // BD 8
  { { INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, HIGH, LOW, LOW } }, // DB 9
  { { OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // AD 10
  { { OUTPUT, INPUT, INPUT, OUTPUT }, { HIGH, LOW, LOW, LOW } }  // DA 11
};
void turnOnLED( int led ) {
  pinMode( A, matrix[led][PIN_CONFIG][0] );
  pinMode( B, matrix[led][PIN_CONFIG][1] );
  pinMode( C, matrix[led][PIN_CONFIG][2] );
  pinMode( D, matrix[led][PIN_CONFIG][3] );
  digitalWrite( A, matrix[led][PIN_STATE][0] );
  digitalWrite( B, matrix[led][PIN_STATE][1] );
  digitalWrite( C, matrix[led][PIN_STATE][2] );
  digitalWrite( D, matrix[led][PIN_STATE][3] );
}
void turnOffLEDs( void ) {
  pinMode( A, INPUT );
  pinMode( B, INPUT );
  pinMode( C, INPUT );
  pinMode( D, INPUT );
  digitalWrite( A, LOW );
  digitalWrite( B, LOW );
  digitalWrite( C, LOW );
  digitalWrite( D, LOW );
}
// End Charlieplex setup

MIDI_CREATE_DEFAULT_INSTANCE();
void setup() {
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
  for (uint8_t i = 0; i < 16; i++) {  // Set instruments for all 16 MIDI channels
    if (instruments[i] < 128) {
      MIDI.sendProgramChange(instruments[i], i + 1);
    }
  }
}

void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      if (song[i]) {
        turnOnLED(i);
        playChord(song[i], midiChannel[i]);
      }
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      if (song[i]) {
        turnOffLEDs();
      }
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
      delay(strum);
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

