/**
  * This code is for the JHU ECE Arduino Competition in Spring 
  * 2015. This project was to make a laser guitar. 
  *
  * Team: Anthonie Best, Andrew Rauch, Ej Connor, Jeffrey Sham
  */


/*************************************************
 * Public Constants
 *************************************************/

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

//Analog Pins
int photoResistorPin1 = 0;
int photoResistorPin2 = 1;
int photoResistorPin3 = 2;
int photoResistorPin4 = 3;

//Digital Pins
int ledPin1 = 20;
int ledPin2 = 24;
int ledPin3 = 28;
int ledPin4 = 32;

//On Button
int onButton = 34;
int onButtonState = HIGH;
int onButtonReading;
int onButtonPrevious = LOW;
long onButtonTime = 0;

//Cool Music Button
int musicButton = 35;
int musicButtonState = LOW;
int musicButtonReading;
int musicButtonPrevious = HIGH;
long musicButtonTime = 0;

//Debounce Time
long debounce = 200;

//Laser Pins
int laserPin1 = 2;
int laserPin2 = 3;
int laserPin3 = 4;
int laserPin4 = 5;

//Speaker Pins
int speakerPin1 = 37;

//Button Pins
int buttonPinRow1[] = {40, 41, 42, 43};
int buttonPinRow2[] = {43, 44, 45, 46};

//Button States
int buttonStateRow1[] = {LOW, LOW, LOW, LOW};
int buttonStateRow2[] = {LOW, LOW, LOW, LOW};

//Trip resistance. This is the resistance that if it goes under, then we should do something
int tripThreshold = 550;
//Note Duration
//Quarter Note
int quarterNote = 1000/4;
//Half Note
int halfNote = 1000/2;
//Eighth Note
int eightNote = 1000/8;

//Pause betweeen notes
int pauseBetweenNotes = quarterNote * 1.30;

//Notes in Melody (75 notes)
//Rush - YYZ
int melody[] = {
  NOTE_C4, NOTE_C4,NOTE_CS4, NOTE_DS4, NOTE_E4,NOTE_FS4, NOTE_GS4, NOTE_A4, NOTE_B4, NOTE_CS5, NOTE_DS5, NOTE_E5, NOTE_DS5, NOTE_B4, NOTE_C5, NOTE_C5,
  0, NOTE_B4, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_FS4, 0, 0,
  NOTE_D5, NOTE_D5, NOTE_D5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4,
  NOTE_A4, NOTE_A4, NOTE_FS4, NOTE_A4, NOTE_FS4, NOTE_F4, NOTE_E4, NOTE_CS4,
  NOTE_A4, NOTE_A4, NOTE_FS4, NOTE_A4, NOTE_FS4, NOTE_E4, NOTE_CS4, NOTE_C4, NOTE_B3, NOTE_CS4, NOTE_FS3,
  NOTE_A4, NOTE_A4, NOTE_FS4, NOTE_A4, NOTE_FS4, NOTE_F4, NOTE_E4, NOTE_CS4,
  NOTE_A4, NOTE_A4, NOTE_FS4, NOTE_A4, NOTE_FS4, NOTE_E4, NOTE_CS4, NOTE_C4, NOTE_B3, NOTE_CS4, NOTE_FS3
  };
  
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {32,32,16,16,16, 16,16,16,16, 16,16,16,16, 16,3,16,
                        8,32,16,16,16,16,4,12,
                        24,24,24,16,16, 16,16,16,16, 4,4,4,4,
                        16,16,16,16, 16,16,8, 2,
                        16,16,16,16, 16,16,16,16, 6,6, 8,
                        16,16,16,16, 16,16,8, 2,
                        16,16,16,16, 16,16,16,16, 6,6, 8};

void setup() {
  //Set LEDs to output
  //Row 1
  pinMode(ledPin1, OUTPUT);
  
  //Row 2
  pinMode(ledPin2, OUTPUT);
  
  //Row 3
  pinMode(ledPin3, OUTPUT);
  
  //Row 4
  pinMode(ledPin4, OUTPUT);
  
  //On button and music button
  pinMode(onButton, INPUT);
  pinMode(musicButton, INPUT);
  
  //Button Pin Row 1
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPinRow1[i], INPUT);
  }
  
  //Button Pin Row 2
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPinRow2[i], INPUT);
  }
  
  //Set Laser pins to output
  pinMode(laserPin1, OUTPUT);
  pinMode(laserPin2, OUTPUT);
  pinMode(laserPin3, OUTPUT);
  pinMode(laserPin4, OUTPUT);
  
  Serial.begin(9600);
}

void loop(){
  //Set Lasers to on
  digitalWrite(laserPin1, HIGH);
  digitalWrite(laserPin2, HIGH);
  digitalWrite(laserPin3, HIGH);
  digitalWrite(laserPin4, HIGH);
  
  onButtonReading = digitalRead(onButton);
  musicButtonReading = digitalRead(musicButton);
  
  if (onButtonReading == HIGH && onButtonPrevious == LOW && millis() - onButtonTime > debounce) {
     if (onButtonState == HIGH)
          onButtonState = LOW;
     else
          onButtonState = HIGH; 
     
     onButtonTime = millis();
  }
  
  if (musicButtonReading == HIGH && musicButtonPrevious == LOW && millis() - musicButtonTime > debounce) {
     if (musicButtonState == HIGH)
          musicButtonState = LOW;
     else
          musicButtonState = HIGH; 
          
     musicButtonTime = millis();
  }
  
  onButtonPrevious = onButtonReading;
  musicButtonPrevious = musicButtonReading;
  
  if (onButtonState == HIGH) {
    
    //Get value of buttons
    for (int i = 0; i < 4; i++) {
       buttonStateRow1[i] = digitalRead(buttonPinRow1[i]);
    }
    
    for (int i = 0; i < 4; i++) {
       buttonStateRow2[i] = digitalRead(buttonPinRow2[i]);
    }
    
    //Need to connect photoResistors to HIGH voltage and the analog pin
    //Then connect to a resistor (10K) then to ground
    Serial.println("Photo Resistor 1: " + analogRead(photoResistorPin1));
    //Row 1
    //E string
    if(analogRead(photoResistorPin1) < tripThreshold){
      digitalWrite(ledPin1, LOW);
      
      //TODO play tone based off buttons
      if (buttonStateRow1[0] == HIGH) {
         tone(speakerPin1, NOTE_GS3, quarterNote);
      } else if (buttonStateRow1[1] == HIGH) {
         tone(speakerPin1, NOTE_G3, quarterNote);
      } else if (buttonStateRow1[2] == HIGH) {
         tone(speakerPin1, NOTE_FS3, quarterNote); 
      } else if (buttonStateRow1[3] == HIGH) {
         tone(speakerPin1, NOTE_F3, quarterNote); 
      } else {
         tone(speakerPin1, NOTE_E3, quarterNote); 
      }
      delay(pauseBetweenNotes);
      noTone(speakerPin1);
    } else{
      digitalWrite(ledPin1, HIGH);
    }
    
    //Row 2
    //A string
    Serial.println("Photo Resistor 2: " + analogRead(photoResistorPin2));
    if(analogRead(photoResistorPin2) < tripThreshold){
      digitalWrite(ledPin2, LOW);
      
      //TODO play tone based off buttons
      if (buttonStateRow1[0] == HIGH) {
         tone(speakerPin1, NOTE_CS4, quarterNote);
      } else if (buttonStateRow1[1] == HIGH) {
         tone(speakerPin1, NOTE_C4, quarterNote);
      } else if (buttonStateRow1[2] == HIGH) {
         tone(speakerPin1, NOTE_B4, quarterNote); 
      } else if (buttonStateRow1[3] == HIGH) {
         tone(speakerPin1, NOTE_AS4, quarterNote); 
      } else {
         tone(speakerPin1, NOTE_A4, quarterNote); 
      }
      delay(pauseBetweenNotes);
      noTone(speakerPin1);
    } else{
      digitalWrite(ledPin2, HIGH);
    }
    
    //Row 3
    //D string
    Serial.println("Photo Resistor 3: " + analogRead(photoResistorPin3));
    if(analogRead(photoResistorPin3) < tripThreshold){
      digitalWrite(ledPin3, LOW);
      
      //TODO play tone based off buttons
      if (buttonStateRow2[0] == HIGH) {
         tone(speakerPin1, NOTE_FS5, quarterNote);
      } else if (buttonStateRow2[1] == HIGH) {
         tone(speakerPin1, NOTE_F5, quarterNote);
      } else if (buttonStateRow2[2] == HIGH) {
         tone(speakerPin1, NOTE_E5, quarterNote); 
      } else if (buttonStateRow2[3] == HIGH) {
         tone(speakerPin1, NOTE_DS5, quarterNote); 
      } else {
         tone(speakerPin1, NOTE_D5, quarterNote); 
      }
      delay(pauseBetweenNotes);
      noTone(speakerPin1);
    } else{
      digitalWrite(ledPin3, HIGH);
    }
    
    //Row 4
    //G string
    Serial.println("Photo Resistor 4: " + analogRead(photoResistorPin4));
    if(analogRead(photoResistorPin4) < tripThreshold){
      digitalWrite(ledPin4, LOW);
      
      //TODO play tone based off buttons
      if (buttonStateRow2[0] == HIGH) {
         tone(speakerPin1, NOTE_B5, quarterNote);
      } else if (buttonStateRow2[1] == HIGH) {
         tone(speakerPin1, NOTE_AS5, quarterNote);
      } else if (buttonStateRow2[2] == HIGH) {
         tone(speakerPin1, NOTE_A5, quarterNote); 
      } else if (buttonStateRow2[3] == HIGH) {
         tone(speakerPin1, NOTE_GS5, quarterNote); 
      } else {
         tone(speakerPin1, NOTE_G5, quarterNote); 
      }
      delay(pauseBetweenNotes);
      noTone(speakerPin1);
    } else{
      digitalWrite(ledPin4, HIGH);
    }
  } else if (musicButtonState == HIGH) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    
    //Play Melody
    for (int thisNote = 0; thisNote < 75; thisNote++) {
      int theDuration = 1000/noteDurations[thisNote];
      tone(speakerPin1, melody[thisNote],theDuration);
      
      int thePause = theDuration * 1.30;
      delay(thePause);
      noTone(speakerPin1);
    }
  }
}
