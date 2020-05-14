/*------------------------------------------------------------------------------------------------
ZochoTen Smart Garden EcoSystem 

The MIT License (MIT)
Copyright © 2020 Juuis Le

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the “Software”), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software 
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies 
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS 
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
---------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/adc.h"

#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"
#include "esp_adc_cal.h"

#include "zocho_wifi.h"
#include "zocho_mqtt.h"
#include "zocho_gpio.h"


/* Change these infomation if needed */
#define NO_OF_SAMPLES 64
#define STACK_SIZE 2048

struct MQTTMessage
{
  char *mqTopic;
  char *mqPayload;
} xMessage;

QueueHandle_t xQueue_mqtt;

static void mqtt_publish_task(void *pvParameters)
{
  zocho_mqtt_init();
  vTaskDelay(pdMS_TO_TICKS(1000));

  struct MQTTMessage *mqRxedMessage;

  while (1)
  {
    if (xQueue_mqtt != 0)
    {
      /* Receive a message on the created queue.  Block for 10 ticks if a
         * message is not immediately available. */
      if (xQueueReceive(xQueue_mqtt, &(mqRxedMessage), (TickType_t)10 == pdPASS))
      {
        /* Publish data to the MQTT Broker */
        zocho_mqtt_publish(mqRxedMessage->mqTopic, mqRxedMessage->mqPayload, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
      }
    }
  }
}

static void moisture_sensor_task(void *pvParameters)
{
  /* Configure ADC */
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC_CHANNEL_6, ADC_ATTEN_11db);

  xQueue_mqtt = xQueueCreate(10, sizeof(struct MQTTMessage *));
  if (xQueue_mqtt == 0)
    printf("failed to create Q");

  uint32_t adc_reading = 0;
  char mqtt_message[10];

  struct MQTTMessage *mqMessage;
  mqMessage = &xMessage;
  while (1)
  {
    /* Multisampling */
    for (int i = 0; i < NO_OF_SAMPLES; i++)
    {
      adc_reading += adc1_get_raw((adc1_channel_t)ADC_CHANNEL_6);
    }
    adc_reading /= NO_OF_SAMPLES;
    sprintf(mqtt_message, "%d", adc_reading);

    mqMessage->mqTopic = "data/moisture";
    mqMessage->mqPayload = mqtt_message;

    xQueueSend(xQueue_mqtt, (void *)&mqMessage, (TickType_t)0);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void app_main(void)
{
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ESP_ERROR_CHECK(nvs_flash_init());
  }

  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());

  zocho_gpio_init();
  zocho_wifi_init();

  /* Similar to vanilla freeRTOS xTaskCreate function, but can run multi threads - with 2 CPU cores */
  xTaskCreatePinnedToCore(moisture_sensor_task, "moisture-sensor", STACK_SIZE, NULL, (tskIDLE_PRIORITY + 5), NULL, 0);
  xTaskCreatePinnedToCore(mqtt_publish_task, "mqtt-publish-task", STACK_SIZE, NULL, (tskIDLE_PRIORITY + 5), NULL, 1);
}
