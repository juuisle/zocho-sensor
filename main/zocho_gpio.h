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

#ifndef __ZOCHO_GPIO_H__
#define __ZOCHO_GPIO_H__


/*@brief initilize GPIO Pin
* @usage: call zocho_gpio_init() in main()*/
void zocho_gpio_init(void);

/* @brief blink the onbard LED once */
void zocho_on_board_led_blink_once(void);

/* @brief turn on the onbard LED */
void zocho_on_board_led_on(void);

/* @brief turn off the onbard LED */
void zocho_on_board_led_off(void);

#endif
