// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: sq_esp32_320_240_tft

#include "../ui.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
    #define LV_ATTRIBUTE_MEM_ALIGN
#endif

// IMAGE DATA: assets/wifi_dis.png
const LV_ATTRIBUTE_MEM_ALIGN uint8_t ui_img_wifi_dis_png_data[] = {
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xC6,0x18,0x00,0xF7,0xBE,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x04,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xBD,0xD7,0x00,0xE7,0x3C,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    0xFF,0xFF,0x08,0xBD,0xF7,0xD4,0xFF,0xFF,0x2D,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xBD,0xF7,0x00,0xEF,0x7D,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xE7,0x1C,0x84,0x94,0xB2,0xFF,0xFF,0xFF,0x0A,0xFF,0xFF,0x01,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xC6,0x38,0x00,0xF7,0xBE,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x94,0xB2,0xFF,0xF7,0xBE,0x6E,0xFF,0xFF,0x00,0xFF,0xFF,0x01,0xFF,0xFF,0x01,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x0C,
    0xFF,0xFF,0x55,0xDE,0xFB,0x7D,0xB5,0x96,0xB8,0xB5,0x96,0xCA,0xC6,0x18,0xCC,0xA5,0x14,0xCA,0xE7,0x1C,0x72,0xFF,0xFF,0x59,0x9C,0xF3,0xFB,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x2B,0xD6,0x9A,0x9B,0x94,0xB2,0xF0,0x6B,0x4D,0xFF,0x52,0x8A,0xFF,0x63,0x2C,0xFF,0x6B,0x6D,0xFF,0x5A,0xCB,0xFF,0x5A,0xCB,0xFF,0xF7,0xBE,0x85,0xC6,0x38,0xC4,0xE7,0x3C,0x92,0xEF,0x5D,0x8E,0xD6,0x9A,0x85,0xFF,0xFF,0x10,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x08,0xE7,0x1C,0x94,0x84,0x10,0xFF,0x39,0xC7,0xFF,0x63,0x0C,0xFF,0x94,0x92,0xF3,0xD6,0x9A,0xAE,0xEF,0x7D,0x8D,0xF7,0xBE,0x63,0xF7,0xBE,0x60,0xFF,0xFF,0x60,0xFF,0xFF,0x62,0xAD,0x55,0xD0,0xF7,0xBE,0x4D,0x63,0x0C,0xFF,0x4A,0x69,0xFF,0xA5,0x14,0xE9,0xF7,0xBE,0x5D,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x33,0xA5,0x34,0xD9,0x52,0x8A,0xFF,0x63,0x0C,0xFF,0xBD,0xD7,0xC9,0xFF,0xFF,0x5D,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x5A,0xCB,0x00,0xB5,0xB6,0xDB,0xD6,0xBA,0x92,0xFF,0xFF,0x00,0xEF,0x5D,0x83,0x94,0xB2,0xEC,0x4A,0x49,0xFF,0x6B,0x4D,0xFF,0xD6,0x9A,0xA0,0xFF,0xFF,0x0F,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xAD,0x55,0xF1,0x7B,0xEF,0xFF,0x8C,0x71,0xFB,0xF7,0x9E,0x66,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xE7,0x3C,0x40,0xE7,0x3C,0x6A,0xC6,0x38,0x98,0xE7,0x3C,0x7E,0xFF,0xFF,0x33,0x9C,0xD3,0xFE,0xFF,0xFF,0x20,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x0E,0xDE,0xDB,0xA3,0x63,0x0C,0xFF,0x7B,0xEF,0xFF,0xEF,0x5D,0x97,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x5E,0xAD,0x75,0xC5,0xFF,0xFF,0x32,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xE7,0x3C,0x6B,0xAD,0x55,0xD5,0x84,0x30,0xFF,0x52,0xAA,0xFF,0x7B,0xEF,0xFF,0xE7,0x3C,0x95,0xD6,0x9A,0xA8,0xDE,0xDB,0x9B,0xEF,0x7D,0x85,
    0xAD,0x55,0xC9,0xFF,0xFF,0x4D,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xE7,0x1C,0x81,0xAD,0x75,0xBF,0xFF,0xFF,0x2B,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x7B,0xEF,0x00,0x7B,0xEF,0x00,0xFF,0xFF,0x37,0xA5,0x34,0xD3,0x52,0xAA,0xFF,0x5A,0xCB,0xFF,0x8C,0x51,0xFF,0xBD,0xF7,0xC6,0xE7,0x1C,0x92,0xFF,0xFF,0x42,0xB5,0x96,0xDF,0xFF,0xFF,0x4C,0x8C,0x71,0xFF,0x29,0x45,0xFF,0x7B,0xEF,0xFF,0xCE,0x79,0x98,0xFF,0xFF,0x0F,0xFF,0xFF,0x00,0x7B,0xEF,0x00,0x7B,0xEF,0x00,0xFF,0xFF,0x01,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x07,0xAD,0x55,0xEE,0x39,0xC7,0xFF,0x8C,0x71,0xFF,0xFF,0xDF,0x87,0xF7,0xBE,0x19,0xFF,0xFF,0x00,0x7B,0xEF,0x00,0xCE,0x59,0xAD,0xBD,0xD7,0xCA,0xFF,0xFF,0x00,0xFF,0xFF,0x45,0xCE,0x79,0xAD,0x6B,0x4D,0xFF,0x5A,0xCB,0xFF,0xCE,0x79,0x9B,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x02,0xF7,0xBE,0x5A,0x9C,0xF3,0xCC,0xFF,0xFF,0x33,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x25,0xFF,0xFF,0x23,0x9C,0xF3,0xFE,0xFF,0xFF,0x4E,0xFF,0xFF,0x12,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xE7,0x3C,0x7A,0xB5,0xB6,0xC0,0xFF,0xFF,0x2B,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x32,0x94,0xB2,0xCB,0xD6,0xBA,0xAA,0xD6,0xBA,0x92,0xD6,0x9A,0xB3,0xF7,0xBE,0x71,0x6B,0x4D,0xFA,0xD6,0xBA,0x90,0xFF,0xFF,0x14,0xFF,0xFF,0x00,0x5A,0xCB,0x00,0x5A,0xCB,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x09,0x94,0xB2,0xFF,0x42,0x28,0xFF,0xFF,0xFF,0x4A,0xB5,0xB6,0xDA,0xFF,0xFF,0x4D,0xD6,0xBA,0xAB,0x39,0xC7,0xFF,0x5A,0xCB,0xFF,0xE7,0x1C,0x9B,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x01,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x02,0xFF,0xFF,0x02,0xFF,0xFF,0x00,0xEF,0x7D,0x72,0xE7,0x1C,0x98,0xE7,0x3C,0x83,0xAD,0x75,0xE4,0xFF,0xFF,0x00,0xFF,0xFF,0x03,0xE7,0x3C,0x7D,0xBD,0xF7,0xBC,0xFF,0xFF,0x21,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x01,0xFF,0xFF,0x01,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x94,0x92,0xF6,0xF7,0xBE,0x75,0xFF,0xFF,0x25,0xFF,0xFF,0x0E,0xFF,0xFF,0x00,0x5A,0xCB,0x00,0x5A,0xCB,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xF7,0xBE,0x6A,0xBD,0xD7,0xD6,0xFF,0xFF,0x5A,0x52,0x8A,0xFF,0xDE,0xDB,0x9D,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x9C,0xF3,0xFE,0xFF,0xFF,0x6C,0xFF,0xFF,0x2A,0x9C,0xD3,0xCB,0xFF,0xFF,0x22,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xF7,0x9E,0x5C,0x94,0xB2,0xFF,0xFF,0xFF,0x08,0xFF,0xFF,0x00,0xDE,0xFB,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    0xFF,0xFF,0x2F,0xFF,0xFF,0x3B,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x02,0xFF,0xFF,0x01,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x01,0xFF,0xFF,0x01,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    
};
const lv_img_dsc_t ui_img_wifi_dis_png = {
    .header.always_zero = 0,
    .header.w = 24,
    .header.h = 24,
    .data_size = sizeof(ui_img_wifi_dis_png_data),
    .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
    .data = ui_img_wifi_dis_png_data
};

