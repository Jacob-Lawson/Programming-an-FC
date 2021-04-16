/*
    Potentionmeter Control Of Servo Position
    Created by: Jacob Lawson
    Date: 03/08/2020
*/

#include <Servo.h>  // required library for the commands used below

// RGB LED output ports
#define BLUE 3
#define GREEN 5
#define RED 6

#define WINDOW_SIZE 5

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards



int INDEX = 0;
int SUM = 0;
int READINGS[WINDOW_SIZE];
int AVERAGED = 0;

void setup() {

  // servo setup
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(pos); 
  delay(750);
  
  // set pins to output
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // write to pins
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  analogWrite(BLUE, 100);
  analogWrite(GREEN, 50);
  analogWrite(RED, 150);
  
  // put your setup code here, to run once:
  pinMode(POTPin, INPUT);
  Serial.begin(9600); 

  Serial.println("Potentionmeter test!");

  Serial.println("Please enter Frequency of data collection");
  Serial.println("Values of 20+ are suitable");
  while(Serial.available()==0){
        // makes the code wait until a number is entered 
  }
  DataFreq1 = Serial.parseInt();
  DataFreq2 = 5 * DataFreq1;
  
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
  delay(DataFreq2);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(DataFreq1);

  POTreadvalue = analogRead(POTPin);
  SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
  READINGS[INDEX] = POTreadvalue;           // Add the newest reading to the window
  SUM = SUM + POTreadvalue;                 // Add the newest reading to the sum
  INDEX = (INDEX+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size
  AVERAGED = SUM / WINDOW_SIZE;      // Divide the sum of the window by the window size for the result
  Voltage = AVERAGED/204.6;
  
  Serial.print(POTreadvalue);
  Serial.print(",");
  Serial.println(AVERAGED);
  
  delay(DataFreq1);

      myservo.write(POTreadvalue/5.7);  // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
      
      Serial.println(Voltage);
  }
  if ( Voltage < 1.00){

      greenValue = Voltage * 51;
      analogWrite(GREEN, greenValue);
      analogWrite(RED, 0);
      analogWrite(BLUE, 0);
      delay(DataFreq1);

      myservo.write(POTreadvalue/5.7);  // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
      
      Serial.println(Voltage);
  }
  if ( Voltage > 1.00 && Voltage < 4.00){

      redValue = Voltage * 51;
      analogWrite(RED, redValue);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 0);
      delay(DataFreq1);

      myservo.write(POTreadvalue/5.7);  // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position

      Serial.println(Voltage);
  }
  
}
