#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "Does_It_work?";
const char *password = "12345678?";

ESP8266WebServer server(80);

#define SENSOR_PIN A0

int *sensorReadings;
int readingCount = 0;

void handleRoot() {
  int sensorValue = analogRead(SENSOR_PIN);

  int *newReadings = (int *)realloc(sensorReadings, (readingCount + 1) * sizeof(int));
  if (newReadings != NULL) {
    sensorReadings = newReadings;
    sensorReadings[readingCount] = sensorValue; 
    readingCount++;                   
  } else {
    Serial.println("Memory reallocation failed!");
  }

  String csvData = "";
  for (int i = 0; i < readingCount; i++) {
    csvData += String(i + 1) + "s | " + String(sensorReadings[i]) + "\n";
  }
  server.send(200, "text/plain", csvData);
  Serial.print(csvData); 
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.println("ESP8266 AP Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, handleRoot);

  server.begin();
}

void loop() {
  server.handleClient();
}
