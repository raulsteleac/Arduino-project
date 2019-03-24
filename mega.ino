#include <AFMotor.h>

AF_DCMotor motorA(1);
AF_DCMotor motorB(2);
AF_DCMotor motorD(3);
AF_DCMotor motorC(4);

//Analogical pins used for sending information from NodeMcu to Adruino Mega
int p1 = A8; 
int p2 = A9;   
int p3 = A11; 
int p4 = A10; 
int p5 = A12;
int p6 = A13;
int val ;

//Musical Notes 
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

const int trigPin = 42;
const int echoPin = 44;

//Defines related to the singing part of the project
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };
  int k=1;

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
  Serial.begin(9600);// sets the digital pin 7 as input
}

void loop()
{    
  long duration, inches, cm;
  
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  cm = microsecondsToCentimeters(duration);

 // Reading the pin p2 (A9) related to backward motion
 if(analogRead(p2)>150)
     {k=0; 
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
    else
  // Reading the pin p3 (A10) related to left  motion
     if(analogRead(p3)>150)    
     {  
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
      k=0;
      }
    else
 // Reading the pin p4 (A11) related to right  motion
        if(analogRead(p4)>150)    
        {  
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
          k=0;
         }
          else
 // Reading the pin p5 (A12) for stopping the motors
            if(analogRead(p5)>150)
            {
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
              k=0;
            }
              else
 // Reading the pin p6 (A13) for singing
                if(analogRead(p6)>200)
                {
                  motorA.run(RELEASE);
                  motorB.run(RELEASE);
                  motorD.run(RELEASE);
                  motorC.run(RELEASE);
                  digitalWrite(28, HIGH);   
                  delay(500);
                  digitalWrite(30, HIGH);    
                  delay(500);    
                  digitalWrite(28, LOW);      
                  delay(500);        
                  digitalWrite(30, LOW); 
                   delay(500);   
                   if(k==0)
                    GameOfThrones();
                  k=1; 
                }
                 else
 // Reading the pin p1 (A14) for fowrwad motion 
                     if(analogRead(p1)>200)
                     {
                      //Ultrasonic sensor check to avoid crashing
                       if(cm<25)
                      {  
                        motorA.run(RELEASE);
                        motorB.run(RELEASE);
                        motorD.run(RELEASE);
                        motorC.run(RELEASE);
                        for (int thisNote = 0; thisNote < 3; thisNote++) {
                          int noteDuration = 1000/noteDurations[thisNote];
                          tone(40, melody[thisNote],noteDuration);
                          int pauseBetweenNotes = noteDuration * 1.30;
                          delay(pauseBetweenNotes);
                          noTone(8);}
                      k=0;
                      }
                        else
                           {
                            k=0;  
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
}
 
long microsecondsToCentimeters(long microseconds)
{  return microseconds / 29 / 2;
}
//The loop that creates the song 
void GameOfThrones()
  {
    for(int i=0; i<4; i++)
    {
    tone(40, NOTE_G4);
    delay(500);
    noTone(40);
    tone(40, NOTE_C4);
    delay(500);
    noTone(40);
    tone(40, NOTE_DS4);
    delay(250);
    noTone(40);
    tone(40, NOTE_F4);
    delay(250);
    noTone(40);
    }
    for(int i=0; i<4; i++)
    {
    tone(40, NOTE_G4);
    delay(500);
    noTone(40);
    tone(40, NOTE_C4);
    delay(500);
    noTone(40);
    tone(40, NOTE_E4);
    delay(250);
    noTone(40);
    tone(40, NOTE_F4);
    delay(250);
    noTone(40);
    }
        tone(40, NOTE_G4);
        delay(500);
        noTone(40);
        tone(40, NOTE_C4);
        delay(500);
        tone(40, NOTE_DS4);
        delay(250);
        noTone(40);
        tone(40, NOTE_F4);
        delay(250);
        noTone(40);
        tone(40, NOTE_D4);
        delay(500);
        noTone(40);
    for(int i=0; i<3; i++)
    {
    tone(40, NOTE_G3);
    delay(500);
    noTone(40);
    tone(40, NOTE_AS3);
    delay(250);
    noTone(40);
    tone(40, NOTE_C4);
    delay(250);
    noTone(40);
    tone(40, NOTE_D4);
    delay(500);
    noTone(40);
    }
        tone(40, NOTE_G3);
        delay(500);
        noTone(40);
        tone(40, NOTE_AS3);
        delay(250);
        noTone(40);
        tone(40, NOTE_C4);
        delay(250);
        noTone(40);
        tone(40, NOTE_D4);
        delay(1000);
        noTone(40);
        
        tone(40, NOTE_F4);
        delay(1000);
        noTone(40);
        tone(40, NOTE_AS3);
        delay(1000);
        noTone(40);
        tone(40, NOTE_DS4);
        delay(250);
        noTone(40);
        tone(40, NOTE_D4);
        delay(250);
        noTone(40);
        tone(40, NOTE_F4);
        delay(1000);
        noTone(40);
        tone(40, NOTE_AS3);
        delay(1000);
        noTone(40);
        tone(40, NOTE_DS4);
        delay(250);
        noTone(40);
        tone(40, NOTE_D4);
        delay(250);
        noTone(40);
        tone(40, NOTE_C4);
        delay(500);
        noTone(40);
    for(int i=0; i<3; i++)
    {
    tone(40, NOTE_GS3);
    delay(250);
    noTone(40);
    tone(40, NOTE_AS3);
    delay(250);
    noTone(40);
    tone(40, NOTE_C4);
    delay(500);
    noTone(40);
    tone(40, NOTE_F3);
    delay(500);
    noTone(40);
    }
          tone(40, NOTE_G4);
          delay(1000);
          noTone(40);
          tone(40, NOTE_C4);
          delay(1000);
          noTone(40);
          tone(40, NOTE_DS4);
          delay(250);
          noTone(40);
          tone(40, NOTE_F4);
          delay(250);
          noTone(40);
          tone(40, NOTE_G4);
          delay(1000);
          noTone(40);
          tone(40, NOTE_C4);
          delay(1000);
          noTone(40);
          tone(40, NOTE_DS4);
          delay(250);
          noTone(40);
          tone(40, NOTE_F4);
          delay(250);
          noTone(40);
          tone(40, NOTE_D4);
          delay(500);
          noTone(40);
   
}
