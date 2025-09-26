#pragma once

#include <Arduino.h>
#include "config.h"
#include "wifi_manager.h"
#include "bme688.h"
#include "http_client.h"

void print_sensor_values(float temperature, float humidity, float pressure, float gas);
