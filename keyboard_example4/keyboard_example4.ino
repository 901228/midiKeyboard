#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int buttonApin = 12;  //footswitch A
int buttonBpin = 11;   //footswitch B
int buttonCpin = 10;   //footswitch C
int buttonDpin = 9;
int buttonEpin = 8;

int analogpot1 = A0;  //knob 1
int analogpot2 = A1;  //knob 2

int analogpot1Old = 0;
int analogpot2Old = 0;
int analogpot1New = 0;
int analogpot2New = 0;

#define analogpot1CC 54
#define analogpot2CC 55

void setup() {
  // put your setup code here, to run once:
MIDI.begin (); // MIDI START

pinMode(buttonApin, INPUT_PULLUP);
pinMode(buttonBpin, INPUT_PULLUP);
pinMode(buttonCpin, INPUT_PULLUP);
pinMode(buttonDpin, INPUT_PULLUP);
pinMode(buttonEpin, INPUT_PULLUP);

pinMode(analogpot1, INPUT);
pinMode(analogpot2, INPUT);

//Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

static bool buttonAvalueOld = HIGH;
static bool buttonBvalueOld = HIGH;
static bool buttonCvalueOld = HIGH;
static bool buttonDvalueOld = HIGH;
static bool buttonEvalueOld = HIGH;

//footswitches
bool buttonAvalueNew = digitalRead(buttonApin);
bool buttonBvalueNew = digitalRead(buttonBpin);
bool buttonCvalueNew = digitalRead(buttonCpin);
bool buttonDvalueNew = digitalRead(buttonDpin);
bool buttonEvalueNew = digitalRead(buttonEpin);

    if (buttonAvalueNew != buttonAvalueOld){
      if (buttonAvalueNew == LOW){
      MIDI.sendNoteOn(60, 127, 1);
      //Serial.println("Note C On");
      }
      else {
      MIDI.sendNoteOff(60, 0, 1);
      //Serial.println("Note C Off");
      }
      buttonAvalueOld = buttonAvalueNew;
    }

      if (buttonBvalueNew != buttonBvalueOld){
      if (buttonBvalueNew == LOW){
      MIDI.sendNoteOn(64, 127, 1);
      //Serial.println("Note E On");
      }
      else {
      MIDI.sendNoteOff(64, 0, 1);
      //Serial.println("Note E Off");
      }
      buttonBvalueOld = buttonBvalueNew;
    }

      if (buttonCvalueNew != buttonCvalueOld){
      if (buttonCvalueNew == LOW){
      MIDI.sendNoteOn(65, 127, 1);
      //Serial.println("Note F On");
      }
      else {
      MIDI.sendNoteOff(65, 0, 1);
      //Serial.println("Note F Off");
      }
      buttonCvalueOld = buttonCvalueNew;
    }
    
      if (buttonDvalueNew != buttonDvalueOld){
      if (buttonDvalueNew == LOW){
      MIDI.sendNoteOn(67, 127, 1);
      //Serial.println("Note G On");
      }
      else {
      MIDI.sendNoteOff(67, 0, 1);
      //Serial.println("Note G Off");
      }
      buttonDvalueOld = buttonDvalueNew;
    }
    
      if (buttonEvalueNew != buttonEvalueOld){
      if (buttonEvalueNew == LOW){
      MIDI.sendNoteOn(69, 127, 1);
      //Serial.println("Note A On");
      }
      else {
      MIDI.sendNoteOff(69, 0, 1);
     // Serial.println("Note A Off");
      }
      buttonEvalueOld = buttonEvalueNew;
    }


//potentiometers

int pot1 = analogRead(A0);
int pot2 = analogRead(A1);
int analogpot1New = analogRead(A0);
int analogpot2New = analogRead(A1);

    if (analogpot1New - analogpot1Old >= 35 || analogpot1Old - analogpot1New >= 35) {
      analogpot1Old = analogpot1New;
      analogpot1New = (map(analogpot1New, 1023, 0, 0, 120));
      analogpot1New = (constrain(analogpot1New, 0, 120));
      MIDI.sendControlChange(analogpot1CC, analogpot1New, 1);
//      Serial.print ("pot: ");
//      Serial.println(pot1);
//      Serial.print("potread: ");
//      Serial.println(analogpot1New); 
    }
    
    if (analogpot2New - analogpot2Old >= 35 || analogpot2Old - analogpot2New >= 35) {
      analogpot2Old = analogpot2New;
      analogpot2New = (map(analogpot2New, 1023, 0, 0, 120));
      analogpot2New = (constrain(analogpot2New, 0, 120));
      MIDI.sendControlChange(analogpot2CC, analogpot2New, 1);
//      Serial.print ("pot: ");
//      Serial.println(pot2);
//      Serial.print("potread: ");
//      Serial.println(analogpot2New); 
    }

delay(25);
}