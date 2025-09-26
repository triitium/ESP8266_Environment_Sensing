#include "sensor_bme688.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

#define BME_ADDR 0x76

static Adafruit_BME680 bme;

bool sensor_init() {
    Wire.begin(D2, D1);
    if (!bme.begin(BME_ADDR)) {
        Serial.println("Konnte BME688 Sensor nicht finden!");
        return false;
    }
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setGasHeater(320, 150);
    return true;
}

bool sensor_read(float &temperature, float &humidity, float &pressure, float &gas_resistance) {
    if (!bme.performReading()) {
        Serial.println("Sensorlesen fehlgeschlagen!");
        return false;
    }
    temperature = bme.temperature;
    humidity = bme.humidity;
    pressure = bme.pressure / 100.0F;
    gas_resistance = bme.gas_resistance;
    return true;
}
