# ESP8266 Environment Sensing

This project implements a modular IoT environmental sensing solution using the **ESP8266** and a **BME688 sensor**. It measures temperature, humidity, pressure, and gas resistance, averages the values over multiple samples, and sends them via HTTP POST to a server.

---

## Features

* **ESP8266 with Arduino Core**
* **BME688 sensor** (temperature, humidity, pressure, gas resistance)
* **Measurement averaging** using configurable `SAMPLE_SIZE`
* **Configurable parameters** (WiFi, Server URL, API Key, Device Name) via `platformio.ini`
* **HTTP POST** of averaged values in `application/x-www-form-urlencoded` format
* **Clean, modular C++ structure**

  * `sys/src/` for source files
  * `sys/inc/` for header files
  * `main.h` for central includes and helper functions

---

## Project Structure

```
ESP8266_Environment_Sensing/
├── platformio.ini
└── sys/
    ├── main.cpp
    ├── main.h
    ├── src/
    │   ├── wifi_manager.cpp
    │   ├── bme688.cpp
    │   └── http_client.cpp
    └── inc/
        ├── wifi_manager.h
        ├── bme688.h
        ├── http_client.h
        └── config.h
```

---

## Installation

1. **Install PlatformIO**: [https://platformio.org/install](https://platformio.org/install)
2. Open the project directory in **PlatformIO IDE**.
3. Update `platformio.ini` with your configuration:

   ```ini
   -D DEVICE_NAME="ESP8266_Station1"
   -D SAMPLE_SIZE=10
   -D WIFI_SSID="YOUR_WIFI_SSID"
   -D WIFI_PASS="YOUR_WIFI_PASSWORD"
   -D SERVER_URL="http://YOUR_SERVER:PORT"
   -D API_KEY="YOUR_API_KEY"
   ```
4. Connect the ESP8266 and **build & upload** the firmware using PlatformIO.

---

## Usage

* On startup, the ESP8266 connects to WiFi and initializes the BME688 sensor.
* In the loop, `SAMPLE_SIZE` measurements are taken, averaged, and sent via HTTP POST to the server.
* All sensor readings are printed to the serial console.

---

## Configuration

| Parameter   | Description                       |
| ----------- | --------------------------------- |
| DEVICE_NAME | Name of the device                |
| SAMPLE_SIZE | Number of measurements to average |
| WIFI_SSID   | WiFi SSID                         |
| WIFI_PASS   | WiFi password                     |
| SERVER_URL  | URL of the server for HTTP POST   |
| API_KEY     | API Key for server authentication |

All parameters can be directly modified in `platformio.ini`.

---

## Dependencies

* ESP8266 Board Package for PlatformIO
* Arduino Core for ESP8266
* Adafruit BME680 Library (BME688 compatible)
* ESP8266HTTPClient Library
* Wire Library

---

## License

This project is licensed under the **MIT License**. You are free to use, modify, and distribute it.

---

## Notes

* Ensure proper I²C connections for the BME688 sensor (SDA → D2, SCL → D1).
* The HTTP POST function expects a server that can receive `application/x-www-form-urlencoded` data.
