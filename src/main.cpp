#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "CHIN_2.4G";
const char* password = "043236826";

WebServer server(80);

// put function declarations here:
int myFunction(int, int);

int sensorValue = 0; // Declare sensorValue globally

// HR202 Sensor Test
const int sensorPin = 33; // Define the digital pin D34 connected to HR202

float readHumidity() {
    int sensorValue = analogRead(sensorPin);
    float humidity = (sensorValue - 0) * (100.0 - 0.0) / (4095.0 - 0.0) + 0.0; // Example calibration formula
    return humidity;
}

void readSensor() {
    float humidity = readHumidity();
    Serial.print("Humidity: ");
    Serial.println(humidity);
}

void handleRoot() {
  server.send(200, "text/plain", "Welcome to ESP32 HTTP Server");
}

void handleGetSensor() {
  float humidity = readHumidity();
  String json = "{\"humidity\": " + String(humidity) + "}";
  server.sendHeader("Access-Control-Allow-Origin", "*"); // Allow CORS
  server.send(200, "application/json", json);
}

void handlePostControl() {
  if (server.hasArg("plain")) {
    String body = server.arg("plain");
    // Process the received command (example: turn on/off LED)
    Serial.println("Received command: " + body);
    server.send(200, "text/plain", "Command received");
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  // put your setup code here, to run once:
  int result = myFunction(2, 3);

  // Configure HTTP Server
  server.on("/", handleRoot);
  server.on("/sensor", HTTP_GET, handleGetSensor);
  server.on("/control", HTTP_POST, handlePostControl);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  readSensor(); // Call the function to read sensor value
  delay(2000); // Delay for 2 seconds
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}