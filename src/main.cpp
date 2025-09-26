#include "main.h"

void setup() {
    Serial.begin(115200);

    wifi_init();

    if (!sensor_init()) {
        Serial.println("Sensor init failed!");
        while(1) delay(1000);
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
        delay(100);
    }

    float tempAvg = tempSum / SAMPLE_SIZE;
    float humAvg  = humSum / SAMPLE_SIZE;
    float presAvg = presSum / SAMPLE_SIZE;
    float gasAvg  = gasSum / SAMPLE_SIZE;

    // print_sensor_values(tempAvg, humAvg, presAvg, gasAvg);    Commented, for better negligibly energy efficiency
    http_post(tempAvg, humAvg, presAvg, gasAvg);

    delay(300000);
}

void print_sensor_values(float temperature, float humidity, float pressure, float gas) {
    Serial.printf("Averages: T=%.2f°C H=%.2f%% P=%.2fhPa Gas=%.2fΩ\n",
                  temperature, humidity, pressure, gas);
}
