#include <SimpleDHT.h>
#include "OLED.h"

OLED display(4, 5);
char strdata[100];

unsigned char Relay_state = 16;
int pinDHT22 = 14;
SimpleDHT22 dht22;
int set_Temp = 15, set_Hum = 40, set_Light = 250;
int state, rx_state = 0;
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

byte rx_data = 0, rx_buffer = 0;
int val = 0;

    int err = SimpleDHTErrSuccess;
    if ((err = dht22.read(pinDHT22, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
    {
    Serial.print("Read DHT22 failed, err="); Serial.println(err);delay(1000);
    return;
    }
  val = analogRead(0);
delay(1000);
if(state == 0)
{
Serial.println("메뉴를 열려면 m키, 설정정보를 보려면 t키, 현재정보를 보려면 n키, 시작하려면 s키를 누르세요");
}
state = 1;

if(Serial.available())
{
  rx_data = Serial.read();
  if(rx_data == 'm')
  {
    Serial.println("=======================================");
    Serial.println("========Smart Room Setting Mode========");
    Serial.println("======== 1. Temperature        ========");
    Serial.println("======== 2. Humidity           ========");
    Serial.println("======== 3. Light              ========");
    Serial.println("=======================================");

    while(!(Serial.available()));
    if(Serial.available())
    {
      rx_buffer = Serial.read();
      if(rx_buffer == 0x31)
     {
       Serial.print("온도를 설정해 주세요.(20~40, 기본설정 : 15) : ");
       while(!(Serial.available()));

       set_Temp = Serial.parseInt();
       if(set_Temp >= 20 && set_Temp <= 40)
       {
       Serial.println(set_Temp);
       }
       else
       {
        Serial.println("온도를 다시 설정해 주세요.");
        set_Temp = 15;
       }
     }
     else if(rx_buffer == 0x32)
     {
      Serial.print("습도를 설정해 주세요.(50~100, 기본설정 : 40) : ");
      while(!(Serial.available()));

      set_Hum = Serial.parseInt();
      if(set_Hum >= 50 & set_Hum <= 100)
      {
      Serial.println(set_Hum);
      }
      else
      {
        Serial.println("습도를 다시 설정해 주세요.");
        set_Hum = 40;
      }
     }
     else if(rx_buffer == 0x33)
     {
      Serial.print("조도를 설정해 주세요.(300~1023, 기본설정 : 250) : ");
      while(!(Serial.available()));

      set_Light = Serial.parseInt();
      if(set_Light >= 300 & set_Light <= 1023)
      {
      Serial.println(set_Light);
      }
      else
      {
        Serial.println("조도를 다시 설정해 주세요.");
        set_Light = 250;
      }
     }
    }
  }
  else if(rx_data == 't')
  {
    Serial.print("설정온도: "); Serial.print(set_Temp); Serial.println(" *C, "); 
    Serial.print("설정습도: "); Serial.print(set_Hum); Serial.println(" H,");
    Serial.print("설정조도: "); Serial.print(set_Light); Serial.println(" V");
  }
  else if(rx_data == 'n')
  {
  Serial.print("현재온도: "); Serial.print((int)temperature); Serial.println(" *C, "); 
  Serial.print("현재습도: "); Serial.print((int)humidity); Serial.println(" H,");
  Serial.print("현재조도: "); Serial.print(val); Serial.println(" V");
  }
  else if(rx_data == 's')
  {
    rx_state = 1;
  }
  else
  {
    Serial.println("메뉴를 열려면 m키, 설정정보를 보려면 t키, 현재정보를 보려면 n키, 시작하려면 s키를 누르세요");
  }
 }
if(rx_state == 1)
{
 if(temperature >= set_Temp){
      digitalWrite(Relay_state, LOW);
    }
    else{
      digitalWrite(Relay_state, HIGH);
    }

    if (humidity  >= set_Hum){
      digitalWrite(13, LOW);
    }
    else{
     digitalWrite(13, HIGH);
    }

    if (val  <= set_Light){
     digitalWrite(2, LOW);
    }
    else{
     digitalWrite(2, HIGH);
    }
  }

  sprintf(strdata,"%.1f", (float)temperature);
  display.print(strdata, 0,3);
  display.print(strdata, 0,12);
  sprintf(strdata,"%.2f", (float)humidity);
  display.print(strdata, 1,3);
  display.print(strdata, 1,12);
  delay(500);
} 
