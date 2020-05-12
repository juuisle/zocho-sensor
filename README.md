| Supported Targets | ESP32 |
| ----------------- | ----- |

# ZochoTen Smart Sensor

This is a part of a final year project. The piece of software you are viewing is written in freeRTOS style with the ESP-IDF framework, provided by the manufactor of the ESP32. To learn more about ESP-IDF, please refer to the documentation at: 
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/index.html

### Hardware Required

* A development board with ESP32 SoC (e.g., ESP32-DevKitC, ESP-WROVER-KIT, etc.)
* A USB cable for power supply and programming

The capacitor moisture sensor is connected to `ADC_UNIT_1`, the Vin of ESP32 is connected to VCC of the moisture sensor, and of course GND to GND. They are powered by the 5V microUSB cable. 

### Configure the project

```
idf.py menuconfig
```

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)





