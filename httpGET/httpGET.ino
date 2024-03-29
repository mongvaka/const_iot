#include <SocketIoClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h> 

#define USER_SERIAL Serial


const char* ssid = "Anan_2G_2";
const char* pass = "12383401";

// int R = D1;
// int G = D2;
// int B = D3;




SocketIoClient webSocket;


void setup() {

  // pinMode(R, OUTPUT);
  // pinMode(G, OUTPUT);
  // pinMode(B, OUTPUT);


  USER_SERIAL.begin(115200);

  searchWiFi();
  connectWiFi();
  requestPostApi();
  // webSocket.begin("203.159.93.42", 3000);
  // webSocket.on("message", controlled);
}

void loop() {
  // webSocket.loop();

}
void requestPostApi(){
    WiFiClient client; 
    const int httpPort = 80; 
    if (!client.connect(host, httpPort)) 
    { 
    Serial.println("connection failed"); 
    return; 
    } 
    Serial.print("Requesting URL: "); 
    Serial.println(url); //Post Data 
    String postData = "adcreading=" + String(adcvalue); 
    String address = host + url; 
    HTTPClient http; 
    http.begin(address); 
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
    auto httpCode = http.POST(postData); 
    Serial.println(httpCode); //Print HTTP return code 
    String payload = http.getString(); 
    Serial.println(payload); //Print request response payload 
    http.end(); //Close connection Serial.println(); 
    Serial.println("closing connection");
}
void controlled(const char* message, size_t length){
//  USER_SERIAL.println(message);


  // DynamicJsonDocument doc(1024);
  // deserializeJson(doc, message);

  // double r = doc["r"];
  // double g = doc["g"];
  // double b = doc["b"];


  // analogWrite(R, (r * 255));
  // analogWrite(G, (g * 255));
  // analogWrite(B, (b * 255));
  
}




void searchWiFi(){
  int numberOfNetwork = WiFi.scanNetworks();
  USER_SERIAL.println("----");
  
  for(int i = 0; i < numberOfNetwork; i++ ){
    USER_SERIAL.print("Network name: ");
    USER_SERIAL.println(WiFi.SSID(i));
    USER_SERIAL.print("Signal strength: ");
    USER_SERIAL.println(WiFi.RSSI(i));
    USER_SERIAL.println("--------------");
  }
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
