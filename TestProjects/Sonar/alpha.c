#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "Does_It_work?";
const char *password = "12345678?";

ESP8266WebServer server(80);

#define TRIGGER_PIN D1
#define ECHO_PIN D2

int *distances;
int measurementCount = 0;

void handleRoot() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = (duration / 2) / 29.1;

  int *newDistances = (int *)realloc(distances, (measurementCount + 1) * sizeof(int));
  if (newDistances != NULL) {
    distances = newDistances;
    distances[measurementCount] = distance; 
    measurementCount++;                   
  } else {
    Serial.println("Memory reallocation failed!");
  }

  String csvData = "";
  for (int i = 0; i < measurementCount; i++) {
    csvData += String(i + 1) + "s | " + String(distances[i]) + "cm\n";
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

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  server.handleClient();
}

/* Results
1s | 13cm
2s | 13cm
3s | 12cm
4s | 13cm
5s | 13cm
6s | 13cm
7s | 13cm
8s | 13cm
9s | 13cm
10s | 13cm
11s | 13cm
12s | 13cm
13s | 13cm
14s | 12cm
15s | 12cm
16s | 13cm
17s | 12cm

*/
