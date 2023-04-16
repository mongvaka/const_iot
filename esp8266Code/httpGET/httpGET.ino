#include <SocketIoClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "wifipassword.h"
#define USER_SERIAL Serial
const char* ssid = "Repeater";
const char* pass = "88888888";
SocketIoClient webSocket;
void setup() {
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
  USER_SERIAL.begin(115200);
  connectWiFi();
  webSocket.begin("192.168.1.50", 8080);
  webSocket.on("hola", controlled);
  postApi();
}

void loop() {
  webSocket.loop();
}
void postApi(){
  
}
void controlled(const char* message, size_t length){
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, message);
    int pin = doc["pin"];
    int status= doc["status"];
    digitalWrite(pin,status);
}



void connectWiFi(){
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    USER_SERIAL.print(".");
    delay(1000);
  }
  USER_SERIAL.print("");
  USER_SERIAL.println("WiFi connected");
  USER_SERIAL.print("IP Address : ");
  USER_SERIAL.println(WiFi.localIP());
  
}
