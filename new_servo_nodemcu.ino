#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

 
//Enter your wifi credentials
const char* ssid = "";  // Your WiFi SSID 
const char* password =  ""; // Your WiFi Password
const char* mqttServer = "";    //Enter Your mqttServer address (same server used in python code)
const int mqttPort = 15193;       //Port number
const char* mqttUser = ""; //User
const char* mqttPassword = ""; //Password

Servo myservo; 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
  delay(1000);
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(MQTTcallback);
  myservo.attach(D4);
  myservo.write(0);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.println(client.state());  //If you get state 5: mismatch in configuration
      delay(2000);
 
    }
  }
 
  //client.publish("esp/test", "Hello from ESP8266");
  client.subscribe("servo");
 
}
 
void MQTTcallback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
 
  String message;
  Serial.println("hye");
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];  //Conver *byte to String
  }
  Serial.println("hello");
   Serial.print(message);
  if(message == "1") {myservo.write(90);}   //LED on  
  if(message == "0") {myservo.write(0);} //LED off
 
  Serial.println();
  Serial.println("-----------------------");  
}
 
void loop() {
  client.loop();
}
