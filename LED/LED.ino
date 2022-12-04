#include <Wire.h>
#include "OLED.h"

OLED display(4, 5);
char strdata[100];

// defines pins numbers
const int trigPin = 13;
const int echoPin = 12;

// defines variables
int duration;
float distance;
int val = 0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output  
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  display.begin();
  display.print("Distance");
  display.print("L =", 1,0);
}

void loop() {
  // Clears the trigPin
  val = analogRead(0);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.println(duration);
  Serial.print(" ");
  Serial.println(distance);
  sprintf(strdata,"%.2f", distance);
  display.print(strdata, 1,4);
  Serial.println(val);
  
  if (val <= 400)
  {
    if(distance <= 10)
    {
      digitalWrite(2, LOW);
      digitalWrite(15, LOW);
      digitalWrite(16, HIGH);
     }
    else if (distance > 10 && distance <= 20)
    {
     digitalWrite(2, LOW);
     digitalWrite(15, HIGH);
     digitalWrite(16, LOW);
    }
    else if(distance > 30)
    {
     digitalWrite(2, HIGH);
     digitalWrite(15, LOW);
     digitalWrite(16, LOW);
    }
  }
  else
  {
    digitalWrite(2, LOW);
    digitalWrite(15, LOW);
    digitalWrite(16, LOW);
  }
 
 delay(500);
} 
