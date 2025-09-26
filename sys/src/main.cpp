#include <Arduino.h>
#include "wifi_manager.h"
#include "sensor_bme688.h"
#include "http_client.h"
#include "config.h"

void setup() {
    Serial.begin(115200);

    wifi_init();

    if (!sensor_init()) {
        Serial.println("Sensor konnte nicht initialisiert werden. Stop.");
        while (1) delay(1000);
    }
}

void loop() {
    float tempSum = 0, humSum = 0, presSum = 0, gasSum = 0;

    for (int i = 0; i < SAMPLE_SIZE; i++) {
        float t, h, p, g;
        if (sensor_read(t, h, p, g)) {
            tempSum += t;
            humSum += h;
            presSum += p;
            gasSum += g;
        }
        delay(100); // kurzes Intervall zwischen Samples
    }

    float tempAvg = tempSum / SAMPLE_SIZE;
    float humAvg  = humSum / SAMPLE_SIZE;
    float presAvg = presSum / SAMPLE_SIZE;
    float gasAvg  = gasSum / SAMPLE_SIZE;

    Serial.printf("Gemittelte Werte: T=%.2f°C H=%.2f%% P=%.2fhPa Gas=%.2fΩ\n",
                  tempAvg, humAvg, presAvg, gasAvg);

    http_post(tempAvg, humAvg, presAvg, gasAvg);

    delay(300000); // 5 Minuten
}
