/*******************************************************************************
 * Touch libraries:
 * XPT2046: https://github.com/PaulStoffregen/XPT2046_Touchscreen.git
 *
 * Capacitive touchscreen libraries
 * TouchLib: https://github.com/mmMicky/TouchLib.git
 ******************************************************************************/

#include <Arduino.h>
/* uncomment for XPT2046 */
#ifndef _TOUCH_PAD_
#define _TOUCH_PAD_
#define TOUCH_XPT2046
#define TOUCH_XPT2046_SCK 12
#define TOUCH_XPT2046_MISO 13
#define TOUCH_XPT2046_MOSI 11
#define TOUCH_XPT2046_CS 17
#define TOUCH_XPT2046_INT 18
#define TOUCH_XPT2046_ROTATION 3
#define TOUCH_XPT2046_SAMPLES 50

// uncomment for most capacitive touchscreen
// #define TOUCH_MODULES_FT5x06 // GT911 / CST_SELF / CST_MUTUAL / ZTW622 / L58 / FT3267 / FT5x06
// #define TOUCH_MODULE_ADDR FT5x06_ADDR // CTS328_SLAVE_ADDRESS / L58_SLAVE_ADDRESS / CTS826_SLAVE_ADDRESS / CTS820_SLAVE_ADDRESS / CTS816S_SLAVE_ADDRESS / FT3267_SLAVE_ADDRESS / FT5x06_ADDR / GT911_SLAVE_ADDRESS1 / GT911_SLAVE_ADDRESS2 / ZTW622_SLAVE1_ADDRESS / ZTW622_SLAVE2_ADDRESS
// #define TOUCH_SCL 5
// #define TOUCH_SDA 6
// #define TOUCH_RES -1
// #define TOUCH_INT -1

 



void touch_init(int16_t w, int16_t h, uint8_t r);
bool touch_has_signal();
void translate_touch_raw();
bool touch_touched();
bool touch_released();
#endif
