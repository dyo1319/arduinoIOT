#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress apIP(55, 55, 55, 55); 
const char* src_ssid = "TalkingArduino"; 

ESP8266WebServer server(80); 

void WifiSetup() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(src_ssid); 
  server.on("/", handleRoot); 
  server.onNotFound(handleNotFound); 
  server.begin(); 
}

void wifi_loop() {
  server.handleClient();
  delay(10);
} 

void handleNotFound(){
  String message = "File Not Found \n \n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

void handleRoot() {
  String page = "<html><body><h1>Performance Display</h1><table border='1'>";
  page += "<tr><th>Press Number</th><th>Duration (ms)</th></tr>";

  int numPresses = getNumPresses(); 
  unsigned long* pressDurations = getPressDurations(); 

  for (int i = 0; i < numPresses; i++) {
    page += "<tr>";
    page += "<td>" + String(i + 1) + "</td>";
    page += "<td>" + String(pressDurations[i]) + "</td>";
    page += "</tr>";
  }

  page += "</table></body></html>";
  server.send(200, "text/html", page);
}


