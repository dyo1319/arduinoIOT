#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "RaadHeno";
const char* pswd = "Raad12340";

WiFiClient client;
int server_port = 80; 

void wifiClient_Setup() {
  Serial.println("wifiSetup");
  WiFi.begin(ssid, pswd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("trying ...");
    delay(100);
  }
  Serial.println("Connected to network");
}

void SendBtnPressed() {
  HTTPClient http;
  const int deviceID = 1121; 
  const int channel = 1;   

  String dataURL = "http://api.kits4.me/GEN/api.php?ACT=SET&DEV=" + String(deviceID) + "&CH=" + String(channel) + "&VAL=" + String(pressDuration);

  http.begin(client, dataURL);

  int httpCode = http.POST("");

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("Response: " + payload);
  } else {
    Serial.println("Error in HTTP request");
  }
  http.end();
}

long readCurrentDurationFromServer() {
  HTTPClient http;
  const int deviceID = 1121; 
  const int channel = 1;   

  String dataURL = "http://api.kits4.me/GEN/api.php?ACT=GET&DEV=" + String(deviceID) + "&CH=" + String(channel);

  http.begin(client, dataURL);

  int httpCode = http.GET();
  long currentDuration = -1;

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("Response: " + payload);
    currentDuration = payload.toInt();
  } else {
    Serial.println("Error in HTTP request");
  }
  http.end();

  return currentDuration;
}