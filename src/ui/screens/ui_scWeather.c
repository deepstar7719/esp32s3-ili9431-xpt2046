// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: sq_esp32_320_240_tft

#include "../ui.h"

void ui_scWeather_screen_init(void)
{
    ui_scWeather = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_scWeather, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_panelTop3 = ui_cmPanelTop_create(ui_scWeather);
    lv_obj_set_x(ui_panelTop3, 0);
    lv_obj_set_y(ui_panelTop3, -102);




    ui_cmPanelWeather1 = ui_cmPanelWeather_create(ui_scWeather);
    lv_obj_set_x(ui_cmPanelWeather1, -80);
    lv_obj_set_y(ui_cmPanelWeather1, 16);




    ui_cmPanelWeather2 = ui_cmPanelWeather_create(ui_scWeather);
    lv_obj_set_x(ui_cmPanelWeather2, 80);
    lv_obj_set_y(ui_cmPanelWeather2, 16);





}
