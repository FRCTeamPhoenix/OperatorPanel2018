#include <Joystick.h>
#include <SoftwareSerial.h>

//Written by Maya Yaakov 2/25/16
//This is for the Operator Control panel used by team 2342 

// Create the Joystick

// Simple initial method
//Joystick_ Joystick;

// Needs to be declared with non-default constructor to set Axes and Gamepad 
// profile in order for the driver station software to see the axes
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_GAMEPAD, 32, 0,
  true, true, true, false, false, false,
  false, true, false, false, false);
  


int ManipulatorIn_button = 3;
int ManipulatorOut_button = 2;
int ManipulatorClose_button = 4;
int ManipulatorOpen_button = 6;
int ClimbWingToggle = 5;
int ManipulatorInOrOff_switch = 8;
int ManipulatorOffOrOut_switch = 9;

//
int CascadeHeightSetting = A0;
int ManipulatorAngularSetting = A1;

// TODO: Need to add Serial 7-segment Rx pin
const int softwareTx = 12;
const int softwareRx = 13;
SoftwareSerial perDis(softwareRx, softwareTx);
char tempString[10]; // Will be used with sprintf to create strings


// Global state variables
volatile int lastManipulatorIn_buttonState = 0;
volatile int lastManipulatorOut_buttonState = 0;
volatile int lastManipulatorClose_buttonState = 0;
volatile int lastManipulatorOpen_buttonState = 0;
volatile int lastClimbWingToggleState = 0;
volatile int lastManipulatorInOrOff_switchState = 0;
volatile int lastSpareAState = 0;
volatile int lastManipulatorOffOrOut_switchState = 0;
volatile int lastCascadeHeightSettingState = 0;
volatile int lastManipulatorAngularSettingState = 0;


void setup() {
  // put your setup code here, to run once:

  // Set up switches
  pinMode(ManipulatorIn_button, INPUT);
  pinMode(ManipulatorOut_button, INPUT);
  pinMode(ManipulatorClose_button, INPUT); //ManipulatorClose_button
  pinMode(ManipulatorOpen_button, INPUT);
  pinMode(ClimbWingToggle, INPUT);
  pinMode(ManipulatorInOrOff_switch, INPUT);
  pinMode(ManipulatorOffOrOut_switch, INPUT);

  // Set up pots
  pinMode(CascadeHeightSetting, INPUT);
  pinMode(ManipulatorAngularSetting, INPUT);

  // TODO: Need to add Serial 7-segment Rx pin
  perDis.begin(9600);

  perDis.write(0x76);  // Clear display command
  perDis.write(0x7A);  // Set brightness command byte
  perDis.write(200);  // brightness data byte

  perDis.print("0000");
  delay(1000);
  perDis.print("   -");
  delay(250);
  perDis.print("  --");
  delay(250);
  perDis.print(" ---");
  delay(250);
  perDis.print("----");
  delay(250);
  perDis.print("--- ");
  delay(250);
  perDis.print("--  ");
  delay(250);
  perDis.print("-   ");
  delay(250);
  perDis.print("    ");
  delay(250);
 
  
  
  // Future possible interrupt method
  //attachInterrupt(FlyWheel )
  
  // Initialize Joystick Library
  Joystick.begin();

  // Initialize serial for seven-segment display
  // TODO set the pins
  //Serial.begin(9600);

}


void loop() {
  // put your main code here, to run repeatedly:
  
  readButtonState(ManipulatorIn_button, 5, lastManipulatorIn_buttonState); 
  readButtonState(ManipulatorOut_button, 4, lastManipulatorOut_buttonState); 
  readButtonState(ManipulatorClose_button, 1, lastManipulatorClose_buttonState); 
  readButtonState(ManipulatorOpen_button, 3, lastManipulatorOpen_buttonState); 
  readButtonState(ClimbWingToggle, 6, lastClimbWingToggleState); 
  readButtonState(ManipulatorInOrOff_switch, 2, lastManipulatorInOrOut_switchState);
  readButtonState(ManipulatorOffOrOut_switch, 9, lastManipulatorOfforOut_switchState); 

  readPotState(CascadeHeightSetting, 2, lastCascadeHeightSettingState);
  readPotState(ManipulatorAngularSetting, 1, lastManipulatorAngularSettingState);

    
  }

 void readButtonState(int pin, int button, volatile int &lastState) {
  int currentState = digitalRead(pin);
  if (currentState != lastState){
    Joystick.setButton(button, currentState);
    lastState = currentState;

    // Debounce for 50 mS
    delay(50);
    
    /*
    Serial.print("Button Press "); 
    Serial.print(button); 
    Serial.print(" ");
    Serial.print(currentState); 
    Serial.print('\n');
    */
    }
    
  }
  void readPotState(int pin, int axis, volatile int &lastState){
    int currentValue = analogRead(pin);
    
        
      }
    else if(axis == 4){

       int potValue = 1023 - currentValue;
       
       Joystick.setThrottle(potValue);
       
       int scaledValue = (int) ((float) potValue/10.23);
       sprintf(tempString, "%3d ", (int) scaledValue);
       perDis.print(tempString);
       
       delay(100);
      }

      /* 
      // For debugging
      Serial.print("Pot ");
      Serial.print(axis);
      Serial.print(" ");
      Serial.print(currentValue);
      Serial.print(" ");
      Serial.print(lastState);
      Serial.print('\n');
      */
    
    lastState = currentValue;
   }    
 }
