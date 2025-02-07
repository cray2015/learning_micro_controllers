#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "xxxxx"; // your SSID
const char* password = "xxxxxx"; // your WIFI password
const char* pushgateway_url = "http://192.168.0.56:9091/metrics/job/esp32";
const int wifi_led = D2;
const int server_success_led = D3;

int airq_ppm_value;

void setup() {
  Serial.begin(115200);
  pinMode(wifi_led, OUTPUT);
  pinMode(server_success_led, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected!");
  digitalWrite(wifi_led, HIGH);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(pushgateway_url);
    http.addHeader("Content-Type", "text/plain");

    airq_ppm_value = analogRead(A0);

    // Prometheus metric format
    String metrics = "airq_ppm_val " + String(airq_ppm_value) + "\n";
    int httpResponseCode = http.POST(metrics);

    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);
    if (httpResponseCode == 200) {
      digitalWrite(server_success_led, HIGH);
    } else {
      digitalWrite(server_success_led, LOW);
    }

    http.end();
  }
  delay(2000);
}
