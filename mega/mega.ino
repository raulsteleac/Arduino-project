#include <AFMotor.h>
#include "music.h"

AF_DCMotor motorA(1);
AF_DCMotor motorB(2);
AF_DCMotor motorD(3);
AF_DCMotor motorC(4);

enum States{
  Idle,
  Forward,
  Backward,
  Left,
  Right,
  Sing,
  Singing
};

int CurrentState = Idle;

//Analogical pins used for sending information from NodeMcu to Adruino Mega
int p1 = A8; 
int p2 = A9;   
int p3 = A11; 
int p4 = A10; 
int p5 = A12;
int p6 = A13;

const int trigPin = 42;
const int echoPin = 44;
long duration, inches, cm;

//Initialization of the speed of each motor and pins
void setup()
{  
  motorA.setSpeed(250);
  motorB.setSpeed(250);
  motorD.setSpeed(250);
  motorC.setSpeed(250);
  pinMode(23, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);// sets the digital pin 7 as input
}

void runCurrentState()
{
  switch(CurrentState)
  {
    case Idle : SM_Idle();break;
    case Forward : SM_Forward();break;
    case Backward : SM_Backward();break;
    case Left : SM_Left();break;
    case Right : SM_Right();break;
    case Sing : SM_StartSing();break;
    case Singing: SM_Sing();break;
  }
}

void SM_Forward()
{
  //Ultrasonic sensor check to avoid crashing
  if(cm < 25)
  {  
    sang_flag = 0;
    motorA.run(RELEASE);
    motorB.run(RELEASE);
    motorD.run(RELEASE);
    motorC.run(RELEASE);
    for (int thisNote = 0; thisNote < 3; thisNote++) 
    {
      int noteDuration = 1000/noteDurations[thisNote];
      tone(40, melody[thisNote],noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(8);
    }
  }
  else
  {
    sang_flag = 0;  
    motorA.run(FORWARD);
    motorB.run(FORWARD);
    motorD.run(FORWARD);
    motorC.run(FORWARD);
    digitalWrite(23, LOW);   
    digitalWrite(49, LOW);
    digitalWrite(47, HIGH);              
    digitalWrite(51, HIGH);   
    delay(500); 
    digitalWrite(47,LOW );             
    digitalWrite(51, LOW);   
    delay(500); 
    }
}


void SM_Backward()
{
  sang_flag = 0; 
  motorA.run(BACKWARD);
  motorB.run(BACKWARD);
  motorD.run(BACKWARD);
  motorC.run(BACKWARD);

  digitalWrite(47, LOW);   
  digitalWrite(51, LOW);      
  digitalWrite(23, HIGH);              
  digitalWrite(49, HIGH);   
  delay(700); 
  digitalWrite(23, LOW );             
  digitalWrite(49, LOW);   
  delay(700); 
}

void SM_Left()
{
  sang_flag = 0;
  digitalWrite(23, LOW);
  digitalWrite(47, LOW);
  
  motorA.run(RELEASE);
  motorB.run(FORWARD);
  motorD.run(FORWARD);
  motorC.run(RELEASE); 
  
  digitalWrite(49, HIGH);             
  digitalWrite(51, HIGH);   
  delay(700); 
  digitalWrite(49,LOW );             
  digitalWrite(51, LOW);   
  delay(700); 
}

void SM_Right()
{
  sang_flag = 0;
  digitalWrite(49, LOW);
  digitalWrite(51, LOW);
  
  motorA.run(FORWARD);
  motorB.run(RELEASE);
  motorD.run(RELEASE);
  motorC.run(FORWARD);
  
  digitalWrite(23, HIGH);            
  digitalWrite(47, HIGH);   
  delay(700); 
  digitalWrite(23,LOW );        
  digitalWrite(47, LOW);   
  delay(700);
}

void SM_Idle()
{
  sang_flag = 0;
  motorA.run(RELEASE);
  motorB.run(RELEASE);
  motorD.run(RELEASE);
  motorC.run(RELEASE);
  
  digitalWrite(47, HIGH);    
  digitalWrite(49, HIGH);    
  delay(500);
  digitalWrite(51, HIGH);
  digitalWrite(23, HIGH);  
  delay(500);    
  digitalWrite(47, LOW);     
  digitalWrite(49, LOW);
  delay(500);        
  digitalWrite(51, LOW);   
  digitalWrite(23, LOW); 
  delay(500); 
}

void SM_StartSing()
{
  notePointer = 0;
  motorA.run(RELEASE);
  motorB.run(RELEASE);
  motorD.run(RELEASE);
  motorC.run(RELEASE);
}

void SM_Sing()
{
  if(notePointer < GOT_Number)
  {
    tone(40, GOT_NOTES[notePointer]);
    delay(GOT_LENGHTS[notePointer]);
    noTone(40);
    notePointer++;
  }
  else
    CurrentState = Idle;
}

void loop()
{    
  digitalWrite(trigPin, LOW); //Clearing the trigger pin
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH); // Setting the trigger pin to output for 10 ms then set it back to low
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); //Read the echo pin that return the travel time of the pulse in ms
  cm = microsecondsToCentimeters(duration);

 
 if(analogRead(p2) > 150) // Reading the pin p2 (A9) related to backward motion
 {
   CurrentState = Backward;
 }
 else if(analogRead(p3)>150)    // Reading the pin p3 (A10) related to left  motion
 {  
    CurrentState = Left;
 }
 else if(analogRead(p4) > 150)   // Reading the pin p4 (A11) related to right  motion 
 {  
    CurrentState = Right;
 }
 else if(analogRead(p5)>150) // Reading the pin p5 (A12) for stopping the motors 
 {
    CurrentState = Idle;
 }
 else if(analogRead(p6) > 150) // Reading the pin p6 (A13) for singing
 {
    if(CurrentState !=  Sing && CurrentState != Singing)
    {
      CurrentState = Sing;
    }
    else
      CurrentState = Singing;
 }
 else if(analogRead(p1) > 150)  // Reading the pin p1 (A14) for fowrwad motion 
 {
    CurrentState = Forward;
 }
 
 runCurrentState();
}
 
long microsecondsToCentimeters(long microseconds)
{  return microseconds / 29 / 2;
}
                 
