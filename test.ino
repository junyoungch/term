#include <ESP8266WiFi.h>  //ESP8266
#include <PubSubClient.h>
 
const char* ssid = "IoT_511";
const char* password = "IoT_Test@";

#define mqtt_server "192.168.0.66" // MQTT server 주소
#define mqtt_port 1883 // port 번호
#define mqtt_topic "test" // topic (자유롭게 작성}
#define mqtt_user "IoT" // username
#define mqtt_password "IoT_Test@" // password
 
WiFiClient espClient;
PubSubClient client(espClient);

 void setup() {
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) delay(500);

    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}
void loop() {
    if (!client.connected()) {
    client.connect("ESP8266Client", mqtt_user, mqtt_password);
    client.subscribe(mqtt_topic);
    }

    client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String msg = "";
  for (int i = 0; i < length; i++) {
    msg +=(char)payload[i];
  }
  Serial.print(msg);
  Serial.println();
}
