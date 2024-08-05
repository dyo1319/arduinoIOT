#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "RaadHeno";
const char* pswd = "Raad12340";

WiFiClient client;
int server_port = 80; //http

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
  // הגדרת מספר רכיב וערוץ
  const int deviceID = 1121; // מספר רכיב שלך (תיקנתי ל-11 כפי שצויין)
  const int channel = 1;   // מספר ערוץ שלך

  // יצירת כתובת ה-URL עם הפרמטרים הנדרשים
  String dataURL = "http://api.kits4.me/GEN/api.php?ACT=SET&DEV=" + String(deviceID) + "&CH=" + String(channel) + "&VAL=" + String(pressDuration);

  // התחלת בקשת HTTP
  http.begin(client, dataURL);

  // שליחת בקשת GET
  int httpCode = http.GET();

  // הדפסת הקוד שהתקבל מהשרת (אופציונלי)
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("Response: " + payload);
  } else {
    Serial.println("Error in HTTP request");
  }
  http.end();
}