#include <Keyboard.h>

// KEYPAD //

#include <Keypad.h>

const byte ROWS = 2; //two rows
const byte COLS = 4; //four columns


//define the physical matrix layout
char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'},  //  the keyboard hardware is a 2x4 grid... 
  {'5', '6', '7', '8'},

};
byte rowPins[ROWS] = {4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9 };

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int midC = 60; // MIDI note value for middle C on a standard keyboard

const int transposePin1 = 22; // pins for the switch controlling transposing
const int transposePin2 = 23;
int transpose = 0;  // if = 0 no transposing
int transposeLeft = 0;
int transposeRight = 0;
int oldTransposeLeft = 0;
int oldTransposeRight = 0;
unsigned long transposeTimer = 0;  // for debouncing


// ROTARY ENCODER //

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

Encoder myEnc1(16, 10);
Encoder myEnc2(15, 14);
long position1  = -999;
long position2  = -999;
int encVals[12] = {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64}; // set initial value of encoder to mid range of 0-127
int encVals2[12] = {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64}; // set initial value of encoder to mid range of 0-127

// ROTARY SWITCH //

int cVal = 2;
int cVal2=2;
// POTENTIOMETERS //

const int pot1 = A1;  // potentiometer pins


int potVal1 = 0;

int lastPotVal1 = 0;

int modePushCounter = 0;     // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
const int ModeButton = A0;    // the pin that the Modebutton is attached to
const int Mode1= A2;
const int Mode2= A3;      

void setup() {

//  delay(15000);
  Serial.begin(115200); // enable serial communication
//  while(!Serial);
  Serial.print("Hello world!\n");
  pinMode(ModeButton, INPUT_PULLUP);  // initialize the button pin as a input:  
  pinMode(Mode1,OUTPUT); digitalWrite(Mode1,LOW);
  pinMode(Mode2,OUTPUT); digitalWrite(Mode2,LOW);
  //pinMode(transposePin1, INPUT_PULLUP);  // activate the input pullup resistor on all buttons/switches
  //pinMode(transposePin2, INPUT_PULLUP);  // means you won't need external resistors to read the buttons
  //pinMode(rotSwitch3, INPUT_PULLUP);
 // pinMode(rotSwitch4, INPUT_PULLUP);
 // pinMode(rotSwitch5, INPUT_PULLUP);
 // pinMode(rotSwitch6, INPUT_PULLUP);
  //pinMode(Xswitch, INPUT_PULLUP);
 // pinMode(Yswitch, INPUT_PULLUP);

}



void loop() {

readKeyPad();   
mainreadencoder();

  // read keypad + transpose switch
  readPots();         // read potentiometers
  //readJoystick();     // read joystick + on/off switches

}
