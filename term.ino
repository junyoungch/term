#include <SimpleDHT.h>
#include "OLED.h"

OLED display(4, 5);
char strdata[100];

unsigned char Red = 2, Green = 15, Blue = 16;
int pinDHT22 = 14;
SimpleDHT22 dht22;
int set_Temp = 28, set_Hum = 80;
int set_Light1 = 250, set_Light2 = 500, set_Light3 = 750;
byte temperature = 0;
byte humidity = 0;

void setup() {
  Serial.begin(115200);
  display.begin();
  display.print("NT=");
  display.print(", ST=", 0,7);
  display.print("NH=", 1,0);
  display.print(", SH=", 1,7);
}

void loop() {

  int val = 0;

  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read(pinDHT22, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
  Serial.print("Read DHT22 failed, err="); Serial.println(err);delay(1000);
  return;
  }
  val = analogRead(0);
  delay(1000);

  if(temperature >= set_Temp){
    digitalWrite(13, LOW);
    }
  else{
    digitalWrite(13, HIGH);
  }

  if (humidity  >= set_Hum){
    digitalWrite(12, LOW);
  }
  else{
    digitalWrite(12, HIGH);
  }

  if (val  <= set_Light1){
    digitalWrite(Red, LOW);
    digitalWrite(Green,HIGH);
    digitalWrite(Blue, HIGH);
  }
  else if (val > set_Light1 && val <= set_Light2){
    digitalWrite(Red, HIGH);
    digitalWrite(Green,LOW);
    digitalWrite(Blue, HIGH);
  }
  else{
    digitalWrite(Red, HIGH);
    digitalWrite(Green,HIGH);
    digitalWrite(Blue, LOW);
  }

  sprintf(strdata,"%.1f", (float)temperature);
  display.print(strdata, 0,3);
  sprintf(strdata,"%.1f", (float)se_temp);
  display.print(strdata, 0,12);
  sprintf(strdata,"%.1f", (float)humidity);
  display.print(strdata, 1,3);
  sprintf(strdata,"%.1f", (float)set_hum);
  display.print(strdata, 1,12);
  delay(500);
} 
