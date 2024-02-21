#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "Wifi_Network_WemosD1";
const char *password = "DidntExpectThisPassword?";

ESP8266WebServer server(80);

void handleRoot() {
  String message = "Hello World. Random Number I choose you!: " + String(random(1000));
  server.send(200, "text/html", message);
}

void setup() {
  Serial.begin(115200);

  // Set ESP8266 as an Access Point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.println("ESP8266 AP Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Define the server routes
  server.on("/", HTTP_GET, handleRoot);

  // Start the server
  server.begin();
}

void loop() {
  server.handleClient();
}

// Import this board manager: http://arduino.esp8266.com/stable/package_esp8266com_index.json in preferences. Then board manager and download ep8266. good luck
