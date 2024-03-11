#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *MC_ssid = "Wifi_Network_WemosD1";
const char *MC_password = "DidntExpectThisPassword?";

ESP8266WebServer server(80);

void handleRoot() {
 String message = "Hello WORLD. Random Number I choose you!: " + String(random(1000));
 server.send(200, "text/html", message);
}

void setup() {
 Serial.begin(115200);

 // Connect to the Main characters's Wi-Fi network
 WiFi.mode(WIFI_STA);
 WiFi.begin(MC_ssid, MC_password);

 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
 }

 Serial.println("Node connected to the MC's network");
 Serial.print("IP Address: ");
 Serial.println(WiFi.localIP());

 // Define the server routes
 server.on("/", HTTP_GET, handleRoot);

 // Start the server
 server.begin();
}

void loop() {
 server.handleClient();
}
