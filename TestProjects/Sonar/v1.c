#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "Does_It_work?";
const char *password = "12345678?";

ESP8266WebServer server(80);

// Define the pins where the sensor is connected
#define TRIGGER_PIN D1
#define ECHO_PIN D2

void handleRoot() {
 long duration, distance;
 
 digitalWrite(TRIGGER_PIN, LOW); 
 delayMicroseconds(2); 
 digitalWrite(TRIGGER_PIN, HIGH);
 delayMicroseconds(10); 
 digitalWrite(TRIGGER_PIN, LOW);
 
 duration = pulseIn(ECHO_PIN, HIGH);
 distance = (duration/2) / 29.1;
 
 String message = "Distance: " + String(distance) + " cm";
 server.send(200, "text/html", message);
 Serial.println(message); // Print the distance to the serial port
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

 // Define sensor pins as output and input
 pinMode(TRIGGER_PIN, OUTPUT);
 pinMode(ECHO_PIN, INPUT);
}

void loop() {
 server.handleClient();
 delay(1000); // Wait for 1 second
}

/* The place for guides:
Import this board manager: http://arduino.esp8266.com/stable/package_esp8266com_index.json in preferences. Then board manager and download ep8266. good luck

Connecting esp with sensor:

HC-SR04     |    ESP8266
---------------------------
VCC         |    VIN
Trigger     |    D1 (or any other GPIO pin)
Echo        |    D2 (or any other GPIO pin)
GND         |    GND

*/


/* The place for test data to go:
Distance: 6 cm
Distance: 7 cm
Distance: 10 
PRETTY ACCURATE TEST WITH DISTANCE ON FLAT SURFACE

*/
