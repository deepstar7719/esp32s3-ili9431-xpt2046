// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: sq_esp32_320_240_tft

#include "../ui.h"


// IMAGE DATA: assets/black/wl_5_icon.png
lv_img_dsc_t ui_img_black_wl_5_icon_png = {
    .header.always_zero = 0,
    .header.w = 60,
    .header.h = 44,
    .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
};

void ui_img_black_wl_5_icon_png_load()
{
    ui_img_black_wl_5_icon_png.data = UI_LOAD_IMAGE("S:assets/black/ui_img_black_wl_5_icon_png.bin", 7920);
    ui_img_black_wl_5_icon_png.data_size = 7920;
}
