// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: sq_esp32_320_240_tft

#ifndef _SQ_ESP32_320_240_TFT_UI_H
#define _SQ_ESP32_320_240_TFT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "components/ui_comp.h"
#include "components/ui_comp_hook.h"
#include "ui_events.h"

#include "ui_img_manager.h"
// SCREEN: ui_scWelcome
void ui_scWelcome_screen_init(void);
extern lv_obj_t * ui_scWelcome;
extern lv_obj_t * ui_panelTop1;
extern lv_obj_t * ui_lbwelcome;
extern lv_obj_t * ui_lbwifiInstr;
extern lv_obj_t * ui_lbMessage;
// SCREEN: ui_scToday
void ui_scToday_screen_init(void);
extern lv_obj_t * ui_scToday;
extern lv_obj_t * ui_hh;
extern lv_obj_t * ui_mm;
extern lv_obj_t * ui_mmsymbol;
extern lv_obj_t * ui_ssymbol;
extern lv_obj_t * ui_ss;
extern lv_obj_t * ui_panelTop2;
extern lv_obj_t * ui_ImgIcon;
extern lv_obj_t * ui_lbtemp;
extern lv_obj_t * ui_lbdesc;
// SCREEN: ui_scWeather
void ui_scWeather_screen_init(void);
extern lv_obj_t * ui_scWeather;
extern lv_obj_t * ui_panelTop3;
extern lv_obj_t * ui_cmPanelWeather1;
extern lv_obj_t * ui_cmPanelWeather2;
extern lv_obj_t * ui____initial_actions0;


extern lv_img_dsc_t ui_img_wifi_dis_png;   // assets/wifi_dis.png
void ui_img_wifi_dis_png_load();
extern lv_img_dsc_t ui_img_locate_png;   // assets/locate.png
void ui_img_locate_png_load();
extern lv_img_dsc_t ui_img_black_wl_0_icon_png;   // assets/black/wl_0_icon.png
void ui_img_black_wl_0_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_1_icon_png;   // assets/black/wl_1_icon.png
void ui_img_black_wl_1_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_10_icon_png;   // assets/black/wl_10_icon.png
void ui_img_black_wl_10_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_11_icon_png;   // assets/black/wl_11_icon.png
void ui_img_black_wl_11_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_12_icon_png;   // assets/black/wl_12_icon.png
void ui_img_black_wl_12_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_13_icon_png;   // assets/black/wl_13_icon.png
void ui_img_black_wl_13_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_14_icon_png;   // assets/black/wl_14_icon.png
void ui_img_black_wl_14_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_15_icon_png;   // assets/black/wl_15_icon.png
void ui_img_black_wl_15_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_16_icon_png;   // assets/black/wl_16_icon.png
void ui_img_black_wl_16_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_17_icon_png;   // assets/black/wl_17_icon.png
void ui_img_black_wl_17_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_18_icon_png;   // assets/black/wl_18_icon.png
void ui_img_black_wl_18_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_19_icon_png;   // assets/black/wl_19_icon.png
void ui_img_black_wl_19_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_20_icon_png;   // assets/black/wl_20_icon.png
void ui_img_black_wl_20_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_21_icon_png;   // assets/black/wl_21_icon.png
void ui_img_black_wl_21_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_22_icon_png;   // assets/black/wl_22_icon.png
void ui_img_black_wl_22_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_23_icon_png;   // assets/black/wl_23_icon.png
void ui_img_black_wl_23_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_24_icon_png;   // assets/black/wl_24_icon.png
void ui_img_black_wl_24_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_25_icon_png;   // assets/black/wl_25_icon.png
void ui_img_black_wl_25_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_26_icon_png;   // assets/black/wl_26_icon.png
void ui_img_black_wl_26_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_27_icon_png;   // assets/black/wl_27_icon.png
void ui_img_black_wl_27_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_28_icon_png;   // assets/black/wl_28_icon.png
void ui_img_black_wl_28_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_29_icon_png;   // assets/black/wl_29_icon.png
void ui_img_black_wl_29_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_2_icon_png;   // assets/black/wl_2_icon.png
void ui_img_black_wl_2_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_30_icon_png;   // assets/black/wl_30_icon.png
void ui_img_black_wl_30_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_31_icon_png;   // assets/black/wl_31_icon.png
void ui_img_black_wl_31_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_32_icon_png;   // assets/black/wl_32_icon.png
void ui_img_black_wl_32_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_33_icon_png;   // assets/black/wl_33_icon.png
void ui_img_black_wl_33_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_34_icon_png;   // assets/black/wl_34_icon.png
void ui_img_black_wl_34_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_35_icon_png;   // assets/black/wl_35_icon.png
void ui_img_black_wl_35_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_36_icon_png;   // assets/black/wl_36_icon.png
void ui_img_black_wl_36_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_37_icon_png;   // assets/black/wl_37_icon.png
void ui_img_black_wl_37_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_38_icon_png;   // assets/black/wl_38_icon.png
void ui_img_black_wl_38_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_3_icon_png;   // assets/black/wl_3_icon.png
void ui_img_black_wl_3_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_4_icon_png;   // assets/black/wl_4_icon.png
void ui_img_black_wl_4_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_5_icon_png;   // assets/black/wl_5_icon.png
void ui_img_black_wl_5_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_6_icon_png;   // assets/black/wl_6_icon.png
void ui_img_black_wl_6_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_7_icon_png;   // assets/black/wl_7_icon.png
void ui_img_black_wl_7_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_8_icon_png;   // assets/black/wl_8_icon.png
void ui_img_black_wl_8_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_99_icon_png;   // assets/black/wl_99_icon.png
void ui_img_black_wl_99_icon_png_load();
extern lv_img_dsc_t ui_img_black_wl_9_icon_png;   // assets/black/wl_9_icon.png
void ui_img_black_wl_9_icon_png_load();
extern lv_img_dsc_t ui_img_wifi_full_png;   // assets/wifi_full.png
void ui_img_wifi_full_png_load();


LV_FONT_DECLARE(ui_font_dincoros128);
LV_FONT_DECLARE(ui_font_dincoros64);
LV_FONT_DECLARE(ui_font_syHeiTi16);
LV_FONT_DECLARE(ui_font_syHeiTi28);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
