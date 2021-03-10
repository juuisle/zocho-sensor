| Supported Targets | ESP32 |
| ----------------- | ----- |

# Zocho-Ten Smart Sensor

This software is powerd bythe ESP-IDF FreeRTOS framework. To learn more about ESP-IDF, please refer to the documentation at: 
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/index.html

### Hardware Required

* A development board with ESP32 SoC (e.g., ESP32-DevKitC, ESP-WROVER-KIT, etc.)
* A USB cable for power supply and programming

The capacitor moisture sensor is connected to `ADC_CHANNEL_6` of ESP32,  Vin of ESP32 is connected to VCC of the moisture sensor, and of course GND to GND. Please check the techical sheet of the board. ESP32 are powered by the 5V microUSB cable.


### Configure the project

```
idf.py menuconfig
```

### Configure in code

Change wifi setting in 'wifi.c' and mqtt setting in 'mqtt.c', you can use my testing mqtt server: "mqtt://64.225.97.160:8883", well, port 8883, but no worry, as there is no username and password or TSL/SSL. Please change to MQTT topic.

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)





