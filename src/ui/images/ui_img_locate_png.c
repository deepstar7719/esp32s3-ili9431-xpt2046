// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: sq_esp32_320_240_tft

#include "../ui.h"


// IMAGE DATA: assets/locate.png
lv_img_dsc_t ui_img_locate_png = {
    .header.always_zero = 0,
    .header.w = 24,
    .header.h = 24,
    .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
};

void ui_img_locate_png_load()
{
    ui_img_locate_png.data = UI_LOAD_IMAGE("S:assets/ui_img_locate_png.bin", 1728);
    ui_img_locate_png.data_size = 1728;
}
