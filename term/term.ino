#include <SimpleDHT.h>
#include "OLED.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "IoT_511";
const char* password = "IoT_Test@";
#define mqtt_server "192.168.0.66" // MQTT server 주소
#define mqtt_port 1883 // port 번호
#define mqtt_topic "test" // topic (자유롭게 작성}
#define mqtt_user "IoT" // username
#define mqtt_password "IoT_Test@" // password

unsigned char pinState=HIGH;
WiFiClient espClient;

OLED display(4, 5);
char strdata[100];

unsigned char Red = 2, Green = 15, Blue = 16;
int pinDHT22 = 14;
SimpleDHT22 dht22;
int set_Temp = 22, set_Hum = 30;
int set_Light1 = 250, set_Light2 = 500, set_Light3 = 750;
byte temperature = 0;
byte humidity = 0;

void setup() {
  Serial.begin(115200);

  pinMode(2, OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  
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
    digitalWrite(Red, HIGH);
    digitalWrite(Green,LOW);
    digitalWrite(Blue, LOW);
  }
  else if (val > set_Light1 && val <= set_Light2){
    digitalWrite(Red, LOW);
    digitalWrite(Green,HIGH);
    digitalWrite(Blue, LOW);
  }
  else{
    digitalWrite(Red, LOW);
    digitalWrite(Green,LOW);
    digitalWrite(Blue, HIGH);
  }

  Serial.println(val);
  sprintf(strdata,"%.1f", (float)temperature);
  display.print(strdata, 0,3);
  sprintf(strdata,"%.1f", (float)set_Temp);
  display.print(strdata, 0,12);
  sprintf(strdata,"%.1f", (float)humidity);
  display.print(strdata, 1,3);
  sprintf(strdata,"%.1f", (float)set_Hum);
  display.print(strdata, 1,12);
  delay(500);
} 
