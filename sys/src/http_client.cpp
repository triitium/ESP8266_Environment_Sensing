#include "http_client.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "config.h"

void http_post(float temperature, float humidity, float pressure, float gas_resistance) {
    if (WiFi.status() != WL_CONNECTED) return;

    WiFiClient client;
    HTTPClient http;

    http.begin(client, SERVER_URL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String postData = "apikey=" + String(API_KEY) +
                      "&device=" + String(DEVICE_NAME) +
                      "&temp=" + String(temperature) +
                      "&hum=" + String(humidity) +
                      "&pres=" + String(pressure) +
                      "&gas=" + String(gas_resistance);

    int httpResponseCode = http.POST(postData);
    if (httpResponseCode > 0) {
        Serial.print("HTTP Antwort: ");
        Serial.println(httpResponseCode);
    } else {
        Serial.print("Fehler beim HTTP POST: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}
