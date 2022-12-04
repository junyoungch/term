#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "IoT_511";
const char* password = "IoT_Test@";

#define mqtt_server "192.168.0.66" // MQTT server 주소
#define mqtt_port 1883 // port 번호
#define mqtt_topic "test" // topic (자유롭게 작성}
#define mqtt_user "IoT" // username
#define mqtt_password "IoT_Test@" // password

int pinLED = 2;
int pinSwitch = 5;
int pinState = HIGH;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) delay(500);
pinMode(pinLED, OUTPUT);
pinMode(pinSwitch, INPUT_PULLUP);
pinState = digitalRead(pinSwitch);
digitalWrite(pinLED, pinState);
client.setServer(mqtt_server, mqtt_port);
client.setCallback(callback);
}
void loop() {
if (!client.connected()) {
client.connect("ESP8266Client", mqtt_user, mqtt_password);
client.subscribe(mqtt_topic);
}
if (pinState != digitalRead(pinSwitch)) {
pinState = !pinState;
client.publish(mqtt_topic, pinState? "LED OFF" : "LED ON");
}
client.loop();
}
void callback(char* topic, byte* payload, unsigned int length) {
String Msg = "";
int i=0;
while (i<length) Msg += (char)payload[i++];
if (Msg == "Push") {
digitalWrite(pinLED, !digitalRead(pinLED));
client.publish(mqtt_topic, (digitalRead(pinLED) ? "LED OFF"
: "LED ON"));
return;
}
if (Msg == "LED ON") digitalWrite(pinLED, LOW);
if (Msg == "LED OFF") digitalWrite(pinLED, HIGH);
}
