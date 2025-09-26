#include "wifi_manager.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Arduino.h>

void wifi_init() {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("Verbinde mit WLAN");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Verbunden unter IP: ");
    Serial.println(WiFi.localIP());
}
