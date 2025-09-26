#pragma once
#include <Arduino.h>

bool sensor_init();
bool sensor_read(float &temperature, float &humidity, float &pressure, float &gas_resistance);
