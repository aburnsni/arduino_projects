//#define NOTE_C0 12
//#define NOTE_Db0 13 // C#
//#define NOTE_D0 14
//#define NOTE_Eb0 15 // D#
//#define NOTE_E0 16
//#define NOTE_F0 17
//#define NOTE_Gb0 18 // F#
//#define NOTE_G0 19
//#define NOTE_Ab0 20 // G#
//#define NOTE_A0 21
//#define NOTE_Bb0 22 // A#
//#define NOTE_B0 23
//#define NOTE_C1 24
//#define NOTE_Db1 25
//#define NOTE_D1 26
//#define NOTE_Eb1 27
//#define NOTE_E1 28
//#define NOTE_F1 29
//#define NOTE_Gb1 30
//#define NOTE_G1 31
//#define NOTE_Ab1 32
//#define NOTE_A1 33
//#define NOTE_Bb1 34
//#define NOTE_B1 35
#define NOTE_C2 36
#define NOTE_Db2 37
#define NOTE_D2 38
#define NOTE_Eb2 39
#define NOTE_E2 40
#define NOTE_F2 41
#define NOTE_Gb2 42
#define NOTE_G2 43
#define NOTE_Ab2 44
#define NOTE_A2 45
#define NOTE_Bb2 46
#define NOTE_B2 47
#define NOTE_C3 48
#define NOTE_Db3 49
#define NOTE_D3 50
#define NOTE_Eb3 51
#define NOTE_E3 52
#define NOTE_F3 53
#define NOTE_Gb3 54
#define NOTE_G3 55
#define NOTE_Ab3 56
#define NOTE_A3 57
#define NOTE_Bb3 58
#define NOTE_B3 59
#define NOTE_C4 60
#define NOTE_Db4 61
#define NOTE_D4 62
#define NOTE_Eb4 63
#define NOTE_E4 64
#define NOTE_F4 65
#define NOTE_Gb4 66
#define NOTE_G4 67
#define NOTE_Ab4 68
#define NOTE_A4 69
#define NOTE_Bb4 70
#define NOTE_B4 71
#define NOTE_C5 72
#define NOTE_Db5 73
#define NOTE_D5 74
#define NOTE_Eb5 75
#define NOTE_E5 76
#define NOTE_F5 77
#define NOTE_Gb5 78
#define NOTE_G5 79
#define NOTE_Ab5 80
#define NOTE_A5 81
#define NOTE_Bb5 82
#define NOTE_B5 83
//#define NOTE_C6 84
//#define NOTE_Db6 85
//#define NOTE_D6 86
//#define NOTE_Eb6 87
//#define NOTE_E6 88
//#define NOTE_F6 89
//#define NOTE_Gb6 90
//#define NOTE_G6 91
//#define NOTE_Ab6 92
//#define NOTE_A6 93
//#define NOTE_Bb6 94
//#define NOTE_B6 95
//#define NOTE_C7 96
//#define NOTE_Db7 97
//#define NOTE_D7 98
//#define NOTE_Eb7 99
//#define NOTE_E7 100
//#define NOTE_F7 101
//#define NOTE_Gb7 102
//#define NOTE_G7 103
//#define NOTE_Ab7 104
//#define NOTE_A7 105
//#define NOTE_Bb7 106
//#define NOTE_B7 107
//#define NOTE_C8 108
//#define NOTE_Db8 109
//#define NOTE_D8 110
//#define NOTE_Eb8 111
//#define NOTE_E8 112
//#define NOTE_F8 113
//#define NOTE_Gb8 114
//#define NOTE_G8 115
//#define NOTE_Ab8 116
//#define NOTE_A8 117
//#define NOTE_Bb8 118
//#define NOTE_B8 119
//#define NOTE_C9 120
//#define NOTE_Db9 121
//#define NOTE_D9 122
//#define NOTE_Eb9 123
//#define NOTE_E9 124
//#define NOTE_F9 125
//#define NOTE_Gb9 126
//#define NOTE_G9 127

int CHORD_C[] = {0, NOTE_C3, NOTE_E3, NOTE_G3, NOTE_C4, NOTE_E4};
int CHORD_C7[] = {0, NOTE_C3, NOTE_E3, NOTE_Bb3, NOTE_C4, NOTE_E4};
int CHORD_Cm[] = {0, NOTE_C3, NOTE_G3, NOTE_C4, NOTE_Eb4, NOTE_G4};
int CHORD_Cmaj7[] = {0, NOTE_C3, NOTE_E3, NOTE_B3, NOTE_C4, NOTE_E4};
int CHORD_Cm6_Eb[] = {NOTE_Eb2, NOTE_A2, NOTE_Eb3, NOTE_G3, NOTE_C4, 0};

int CHORD_Db[] = {0, 0, NOTE_Db3, NOTE_Ab3, NOTE_Db4, NOTE_F4};
int CHORD_Dbm[] = {0, 0, NOTE_Db3, NOTE_Ab3, NOTE_Db4, NOTE_E4};

int CHORD_D[] = {0, 0, NOTE_D3, NOTE_A3, NOTE_D4, NOTE_Gb4};
int CHORD_D7[] = {0, 0, NOTE_D3, NOTE_A3, NOTE_B3, NOTE_Gb4};
int CHORD_Dm[] = {0, 0, NOTE_D3, NOTE_A3, NOTE_D4, NOTE_F4};
int CHORD_D7add13[] = {0, NOTE_D3, NOTE_Gb3, NOTE_C4, NOTE_D4, NOTE_B4};

int CHORD_E[] =  {NOTE_E2, NOTE_B2, NOTE_E3, NOTE_Ab3, NOTE_B3, NOTE_E4};
int CHORD_E7[] = {NOTE_E2, NOTE_B2, NOTE_E3, NOTE_Ab3, NOTE_D4, NOTE_E4};
int CHORD_Em[] = {NOTE_E2, NOTE_B2, NOTE_E3, NOTE_G3, NOTE_B3, NOTE_E4};
int CHORD_Em7[] = {NOTE_E2, NOTE_B2, NOTE_E3, NOTE_G3, NOTE_D4, NOTE_E4};

int CHORD_F[] = {NOTE_F2, NOTE_C3, NOTE_F3, NOTE_A3, NOTE_C4, NOTE_F4};
int CHORD_F7[] = {NOTE_F2, NOTE_C3, NOTE_F3, NOTE_A3, NOTE_Eb4, NOTE_F4};
int CHORD_Fm[] = {NOTE_F2, NOTE_C3, NOTE_F3, NOTE_Ab3, NOTE_C4, NOTE_F4};

int CHORD_Gb[] = {NOTE_Gb2, NOTE_Db3, NOTE_Gb3, NOTE_Bb3, NOTE_Db4, NOTE_Gb4};
int CHORD_Gbm[] = {NOTE_Gb2, NOTE_Db3, NOTE_Gb3, NOTE_A3, NOTE_Db4, NOTE_Gb4};

int CHORD_G[] = {NOTE_G2, NOTE_B2, NOTE_D3, NOTE_G3, NOTE_B3, NOTE_G4};
int CHORD_G7[] = {NOTE_G2, NOTE_B2, NOTE_D3, NOTE_G3, NOTE_B3, NOTE_F4};
int CHORD_Gm[] = {NOTE_G2, NOTE_D3, NOTE_G3, NOTE_Bb3, NOTE_D4, NOTE_G4};
int CHORD_Gm7[] = {NOTE_G2, NOTE_D3, NOTE_F3, NOTE_Bb3, NOTE_F4, NOTE_G4};

int CHORD_A[] = {0, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_Db4, NOTE_E4};
int CHORD_A7[] = {0, NOTE_A2, NOTE_E3, NOTE_G3, NOTE_Db4, NOTE_E4};
int CHORD_Am[] = {0, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_C4, NOTE_E4};
int CHORD_Am9[] = {NOTE_A2, NOTE_E3, NOTE_G3, NOTE_C4, NOTE_E4, NOTE_B4};
int CHORD_Am7b5_D[] = {0, NOTE_D3, NOTE_A3, NOTE_Eb4, NOTE_G4, NOTE_C5};

int CHORD_Bb7[] = {0, NOTE_Bb2, NOTE_F3, NOTE_Ab3, NOTE_D4, NOTE_F4};

int CHORD_B[] = {0, NOTE_B2, NOTE_Gb3, NOTE_B3, NOTE_Eb3, NOTE_Gb4};
int CHORD_B7[] = {0, NOTE_B2, NOTE_Eb3, NOTE_A3, NOTE_B3, NOTE_Gb4};
int CHORD_Bm[] = {0, NOTE_B2, NOTE_Gb3, NOTE_B3, NOTE_D3, NOTE_Gb4};

int DRUM_BASS[] = {36, 0, 0, 0, 0, 0};
int DRUM_SIDE[] = {37, 0, 0, 0, 0, 0};
int CYM_1[] = {51, 0, 0, 0, 0, 0};
int CYM_2[] = {49, 0, 0, 0, 0, 0};
