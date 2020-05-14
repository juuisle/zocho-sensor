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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "zocho_gpio.h"

#define BLINK_GPIO 2
#define SOLENOID1_GPIO 23
#define SOLENOID2_GPIO 22
#define SOLENOID3_GPIO 1
#define SOLENOID4_GPIO 3
#define SOLENOID5_GPIO 21
#define SOLENOID6_GPIO 19
#define SOLENOID7_GPIO 18
#define SOLENOID8_GPIO 5


void zocho_gpio_init(void)
{
  gpio_pad_select_gpio(BLINK_GPIO);
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

}

void zocho_on_board_led_blink_once(void)
{
  zocho_on_board_led_on();
  vTaskDelay(1000 / portTICK_RATE_MS);
  zocho_on_board_led_off();
  vTaskDelay(1000 / portTICK_RATE_MS);

}

void zocho_on_board_led_on(void) 
{
  gpio_set_level(BLINK_GPIO, 1);
}

void zocho_on_board_led_off(void) 
{
  gpio_set_level(BLINK_GPIO, 0);
}
