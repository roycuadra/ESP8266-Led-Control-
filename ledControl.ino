#include <ESP8266WiFi.h>
#include <pgmspace.h>

// Replace with your network credentials
const char* ssid = "ESP8266-AP";
const char* password = "12345678";

// Set web server port number to 80
WiFiServer server(80);

const int ledPin = 2; // D4 on Wemos D1 Mini
bool ledState = LOW; // Initial state of the LED

// HTML content stored in flash memory
const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html { font-family: Helvetica; display: inline-block; margin: 0 auto; text-align: center; }
    .button { background-color: #0275d8; border: none; border-radius: 30px; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; }
    .button2 { background-color: #d9534f; }
  </style>
</head>
<body>
  <h1>LED CONTROL</h1>
  <p>ESP8266</p>
  <p>LED - State %s</p>
  <p><a href="/led/%s"><button class="button %s">%s</button></a></p>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) {
    Serial.println("New Client.");
    String request = "";

    while (client.connected() && !client.available()) { delay(1); }

    while (client.available()) {
      char c = client.read();
      request += c;
      Serial.write(c);
    }

    if (request.indexOf("GET /led/on") != -1) {
      Serial.println("LED ON");
      ledState = HIGH;
    } else if (request.indexOf("GET /led/off") != -1) {
      Serial.println("LED OFF");
      ledState = LOW;
    }

    digitalWrite(ledPin, ledState);
    sendResponse(client);
    client.stop();
    Serial.println("Client disconnected.");
  }
}

void sendResponse(WiFiClient &client) {
  char buffer[1024];
  const char* stateText = (ledState == HIGH) ? "ON" : "OFF";
  const char* toggleText = (ledState == HIGH) ? "off" : "on";
  const char* buttonClass = (ledState == HIGH) ? "button2" : "button";
  const char* buttonText = (ledState == HIGH) ? "OFF" : "ON";

  snprintf_P(buffer, sizeof(buffer), htmlPage, stateText, toggleText, buttonClass, buttonText);

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(buffer);
}
