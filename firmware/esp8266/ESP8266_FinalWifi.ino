#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Configure these locally. Never commit actual Wi-Fi credentials.
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

ESP8266WebServer server(80);

float circle = 0;
float idle = 0;
float right_left = 0;
float up_down = 0;
int count = 0;

String getMaxGesture() {
  float maxVal = circle;
  String gesture = "Circle";
  if (idle > maxVal) { maxVal = idle; gesture = "Idle"; }
  if (right_left > maxVal) { maxVal = right_left; gesture = "Right-Left"; }
  if (up_down > maxVal) { maxVal = up_down; gesture = "Up-Down"; }
  return gesture + " (" + String(maxVal) + ")";
}

void handleRoot() {
  String page = R"=====(
  <html>
  <head>
    <title>Gesture Monitor</title>
    <style>
      body { font-family: Arial; text-align:center; margin-top:50px; }
      #gesture { font-size: 48px; color: blue; font-weight: bold; }
      #values { margin-top: 20px; font-size: 22px; }
    </style>
    <script>
      function fetchData() {
        fetch('/data')
          .then(response => response.text())
          .then(text => {
            const parts = text.split(',');
            document.getElementById('gesture').textContent = parts[0];
            document.getElementById('circle').textContent = parts[1];
            document.getElementById('idle').textContent = parts[2];
            document.getElementById('right_left').textContent = parts[3];
            document.getElementById('up_down').textContent = parts[4];
          });
      }
      setInterval(fetchData, 50);
    </script>
  </head>
  <body>
    <h1>Detected Gesture</h1>
    <div id="gesture">Loading...</div>
    <div id="values">
      Circle: <span id="circle">0</span><br>
      Idle: <span id="idle">0</span><br>
      Right-Left: <span id="right_left">0</span><br>
      Up-Down: <span id="up_down">0</span>
    </div>
  </body>
  </html>
  )=====";
  server.send(200, "text/html", page);
}

void handleData() {
  String maxGesture = getMaxGesture();
  String out = maxGesture + "," + String(circle) + "," + String(idle) + "," + String(right_left) + "," + String(up_down);
  server.send(200, "text/plain", out);
}

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  Serial.println("Connecting to WiFi...");
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("ESP IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.onNotFound([]() { server.send(404, "text/plain", "Not Found"); });
  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  if (Serial.available()) {
    count++;
    digitalWrite(2, LOW);
    delay(20);
    digitalWrite(2, HIGH);
    String received = Serial.readStringUntil('\n');
    received.trim();
    float value = received.toFloat();
    switch (count) {
      case 2: circle = value; break;
      case 4: idle = value; break;
      case 6: right_left = value; break;
      case 8: up_down = value; break;
    }
    Serial.print("Received: ");
    Serial.println(received);
  }
  if (count >= 8) {
    Serial.println("\nAll data received. Resetting count.\n");
    Serial.print("Circle: "); Serial.println(circle);
    Serial.print("Idle: "); Serial.println(idle);
    Serial.print("Right-Left: "); Serial.println(right_left);
    Serial.print("Up-Down: "); Serial.println(up_down);
    count = 0;
  }
  server.handleClient();
  yield();
}
