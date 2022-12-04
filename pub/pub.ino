#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "IoT_511";
const char* password = "IoT_Test@";
#define mqtt_server "192.168.0.66" // MQTT server 주소
#define mqtt_port 1883 // port 번호
#define mqtt_topic "test" // topic (자유롭게 작성}
#define mqtt_user "IoT" // username
#define mqtt_password "IoT_Test@" // password
unsigned char pinLED=2;
unsigned char S_connectLED=14;
unsigned char pinSwitch=0;
unsigned char pinState=HIGH;
WiFiClient espClient;
PubSubClient client(espClient);
void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
 //Serial.print("Attempting MQTT connection...");
 // Create a random client ID
 String clientId = "ESP8266Client-";
 clientId += String(random(0xffff), HEX);

 // Attempt to connect
 if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
 //Serial.println("connected");
 // Once connected, publish an announcement...
 digitalWrite(S_connectLED, LOW);
 client.subscribe(mqtt_topic);

 }
 else {
 //Serial.print("failed, rc=");
 //Serial.print(client.state());
 //Serial.println(" try again in 5 seconds");
 // Wait 5 seconds before retrying
 delay(5000);
 }
 }
}
void setup() {
 // put your setup code here, to run once:

 pinMode(pinLED, OUTPUT);
 pinMode(S_connectLED, OUTPUT);
 pinMode(pinSwitch, INPUT_PULLUP);

 pinState = digitalRead(pinSwitch);
 digitalWrite(pinLED, pinState);

 //Serial.begin(115200);
 randomSeed(micros());

 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED){
 digitalWrite(S_connectLED, HIGH);
 delay(500);
 }

 //broker connected
 digitalWrite(S_connectLED, LOW);

 client.setServer(mqtt_server, mqtt_port);
 client.setCallback(callback);

}
void loop(){
 // put your main code here, to run repeatedly:
 if(!client.connected()){
 //client.connect("ESP8266Client", mqtt_user, mqtt_password);
 //client.subscribe(mqtt_topic);
 digitalWrite(S_connectLED, HIGH);
 reconnect();
 }
 else;

 client.loop();

 if(pinState != digitalRead(pinSwitch)){
 pinState = !pinState;
 client.publish(mqtt_topic, pinState ? "LED OFF" : "LED ON");
 }
 else;
}
void callback(char* topic, byte* payload, unsigned int length){
 String Msg = "";
 unsigned int count =0;

 // message received
 while (count<length)
 Msg += (char)payload[count++];
 if(Msg =="LED_State"){
 client.publish(mqtt_topic, (digitalRead(pinLED) ? "LED OFF" : "LED ON"));
 return;
 }
 else if(Msg == "LED ON")
 digitalWrite(pinLED, LOW);
 else if(Msg == "LED OFF")
 digitalWrite(pinLED, HIGH);
 else;
}
