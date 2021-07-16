//#include <MIDI.h>
//MIDI_CREATE_DEFAULT_INSTANCE();

const int matrix1 = 4;
const int matrix2 = 8;
const int matrix1pin[matrix1] = {2, 3, 4, 5};
const int matrix2pin[matrix2] = {6, 7, 8, 9, 10, 11, 12, 13};

int octave = 0; // add or subtract 8 for one octave
bool currentState[matrix1 * matrix2];
bool requestState[matrix1 * matrix2];

byte noteMap(int num);


#define NOTE_ON_CMD 0x90
#define NOTE_OFF_CMD 0x80
#define NOTE_VELOCITY 127


void setup() {

  //MIDI.begin();

  for (int i = 0; i < matrix1; i++) pinMode(matrix1pin[i], INPUT);

  for (int i = 0; i < matrix2; i++) pinMode(matrix2pin[i], INPUT);

  Serial.begin(115200);
}

void loop() {

  readKeys();
  writeKeys();
  delay(25);
}

void readKeys() {

  for(int i = 0; i < matrix2; i++) {

    for (int j = 0; j < matrix2; j++) pinMode(matrix2pin[j], INPUT);
    pinMode(matrix2pin[i], OUTPUT); // <-- (this is your first pin number)

    digitalWrite(matrix2pin[i], HIGH);
    delayMicroseconds(1000);

    for (int j = 0; j < matrix1; j++) requestState[i * matrix1 + j] = digitalRead(matrix1pin[j]);
  }
}

void writeKeys() {

  for(int i = 0; i < matrix1 * matrix2; i++) {

    if(requestState[i] == true && currentState[i] == false) {

      noteOn(noteMap(i));
      //Serial.println(noteMap(i));

      //noteOn(0, 36 + octave + (i * matrix2) % matrix1 * matrix2 + i / matrix1, 64);
      currentState[i] = true;
    }

    if(requestState[i] == false && currentState[i] == true) {

      noteOff(noteMap(i));

      //noteOff(0, 36 + octave + (i * matrix2) % matrix1 * matrix2 + i / matrix1, 64);
      currentState[i] = false;
    }
  }
}

void noteOn(int pitch) {

  Serial.write(NOTE_ON_CMD);
  Serial.write(pitch);
  Serial.write(NOTE_VELOCITY);
  //MIDI.sendNoteOn(pitch, 127, 1);
}

void noteOff(int pitch) {

  Serial.write(NOTE_OFF_CMD);
  Serial.write(pitch);
  Serial.write(NOTE_VELOCITY);
  //MIDI.sendNoteOff(pitch, 0, 1);
}

byte noteMap(int num) {

  switch(num) {

    case 28:
      return 56;
    case 24:
      return 57;
    case 20:
      return 58;
    case 16:
      return 59;
    case 12:
      return 60;
    case 8:
      return 61;
    case 4:
      return 62;
    case 0:
      return 63;
    case 29:
      return 64;
    case 25:
      return 65;
    case 21:
      return 66;
    case 17:
      return 67;
    case 13:
      return 68;
    case 9:
      return 69;
    case 5:
      return 70;
    case 1:
      return 71;
    case 30:
      return 72;
    case 26:
      return 73;
    case 22:
      return 74;
    case 18:
      return 75;
    case 14:
      return 76;
    case 10:
      return 77;
    case 6:
      return 78;
    case 2:
      return 79;
    case 31:
      return 80;
    case 27:
      return 81;
    case 23:
      return 82;
    case 19:
      return 83;
    case 15:
      return 84;
  }
}
