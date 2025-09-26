#include "http_client.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "config.h"

void http_post(float temperature, float humidity, float pressure, float gas_resistance) {
    if (WiFi.status() != WL_CONNECTED) return;

    WiFiClient client;
    HTTPClient http;

    http.begin(client, SERVER_URL);
    http.addHeader("Content-Type", "application/json");  // set JSON content type

    // build JSON payload
    String jsonData = "{";
    jsonData += "\"apikey\":\"" + String(API_KEY) + "\",";
    jsonData += "\"device\":\"" + String(DEVICE_NAME) + "\",";
    jsonData += "\"temperature\":" + String(temperature) + ",";
    jsonData += "\"humidity\":" + String(humidity) + ",";
    jsonData += "\"pressure\":" + String(pressure) + ",";
    jsonData += "\"gas\":" + String(gas_resistance);
    jsonData += "}";

    int httpResponseCode = http.POST(jsonData);
    if (httpResponseCode > 0) {
        Serial.print("HTTP response code: ");
        Serial.println(httpResponseCode);
    } else {
        Serial.print("HTTP POST failed, error: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}
