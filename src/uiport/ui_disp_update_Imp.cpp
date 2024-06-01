#include "ui_disp_update_Imp.h"

#include "nvs_data_handle.h"
#include "esp_timer.h"

// #include <esp_netif.h>
// #include <esp_netif_types.h>
// #include <esp_sntp.h>

#include <DS3231.h>
#include <Wire.h>
#include <mutex>

/************************************************
 *   全局变量声明
 ************************************************/

/************************************************
 *   界面显示更新相关
 ************************************************/

// 界面上显示信息
void lv_scwelcome_showMessage(const char *msg)
{
  String lstr = msg;
  _ui_label_set_property(ui_lbMessage, 0, lstr.c_str());
  Serial.println(lstr.c_str());
  delay(400);
}

void lv_sctoday_update_weather(String &wheather, String &wind, const lv_img_dsc_t *wicon)
{
  // 更换Today页面天气说明
  lv_label_set_text(ui_lbtemp, wheather.c_str());
  lv_label_set_text(ui_lbdesc, wind.c_str());
  // 更换Today页面天气图标
  lv_img_set_src(ui_ImgIcon, wicon);
}
void lv_scWeather_update_otherday_weather(lv_obj_t *lv_obj_panel, heart_Daily &daily,
                                          const lv_img_dsc_t *wicon)
{
  // #define UI_COMP_CMPANELWEATHER_IMGICON 1
  //  #define UI_COMP_CMPANELWEATHER_LBTEMP 2
  //  #define UI_COMP_CMPANELWEATHER_LBDATE 3
  //  #define UI_COMP_CMPANELWEATHER_LBDESC 4
  //  #define _UI_COMP_CMPANELWEATHER_NUM 5
  String wheather = daily.getWeather();
  String wind = daily.getWind();
  String date = daily.date.substring(5);
  // 更换当天图标
  int code_day = daily.code_day;
  int code_night = daily.code_night;

  lv_obj_t *_lbdate = ui_comp_get_child(lv_obj_panel, UI_COMP_CMPANELWEATHER_LBDATE);
  if (_lbdate != NULL)
  {
    lv_label_set_text(_lbdate, date.c_str());
  }

  lv_obj_t *lm_image = ui_comp_get_child(lv_obj_panel, UI_COMP_CMPANELWEATHER_IMGICON);
  // 更换Today页面天气图标
  if (lm_image != NULL)
  {
    lv_img_set_src(lm_image, wicon);
  }

  // 更换Today页面天气说明
  lv_obj_t *_lbtemp = ui_comp_get_child(lv_obj_panel, UI_COMP_CMPANELWEATHER_LBTEMP);
  if (_lbtemp != NULL)
  {
    lv_label_set_text(_lbtemp, wheather.c_str());
  }

  lv_obj_t *_lbdesc = ui_comp_get_child(lv_obj_panel, UI_COMP_CMPANELWEATHER_LBDESC);
  if (_lbdesc != NULL)
  {
    lv_label_set_text(_lbdesc, wind.c_str());
  }
}

void lv_all_update_location(String &city)
{
  // 更换所有页面定位

  lv_obj_t *_lbdate = ui_comp_get_child(ui_panelTop1, 3);
  if (_lbdate != NULL)
  {
    lv_label_set_text(_lbdate, city.c_str());
  }
  _lbdate = ui_comp_get_child(ui_panelTop2, 3);
  if (_lbdate != NULL)
  {
    lv_label_set_text(_lbdate, city.c_str());
  }
  _lbdate = ui_comp_get_child(ui_panelTop3, 3);
  if (_lbdate != NULL)
  {
    lv_label_set_text(_lbdate, city.c_str());
  }
}

void lv_all_update_panelTop_Day(String &sdate)
{
  lv_obj_t *_lbdate = ui_comp_get_child(ui_panelTop1, 4);
  if (_lbdate != NULL)
  {
    _ui_label_set_property(_lbdate, 0, sdate.c_str());
  }
  _lbdate = ui_comp_get_child(ui_panelTop2, 4);
  if (_lbdate != NULL)
  {
    _ui_label_set_property(_lbdate, 0, sdate.c_str());
  }
  _lbdate = ui_comp_get_child(ui_panelTop3, 4);
  if (_lbdate != NULL)
  {
    _ui_label_set_property(_lbdate, 0, sdate.c_str());
  }
}

void lv_sctoday_update_RTC_Time(String &hh, String &mm, String &ss)
{

  _ui_label_set_property(ui_hh, 0, hh.c_str());
  _ui_label_set_property(ui_mm, 0, mm.c_str());
  _ui_label_set_property(ui_ss, 0, ss.c_str());
}

void lv_scwelcome_update_tip()
{

  // 在welcome页面显示链接成功信息，
  String lsWifi = "成功连接：(将在8秒后关闭此页面)";
  lsWifi = lsWifi + "\nWIFI：" + WiFi.SSID().c_str();
  lsWifi = lsWifi + "\n闹钟IP：" + WiFi.localIP().toString().c_str();
  _ui_label_set_property(ui_lbwifiInstr, 0, lsWifi.c_str());

  Serial.print(lsWifi.c_str());
  Serial.print('\n');
}
void lv_all_update_wifi_status(int wf_status)
{

  // 更换wifi状态icon
  lv_obj_t *wifi_image = ui_comp_get_child(ui_panelTop1, 1);
  if (wifi_image != NULL)
  {
    lv_img_set_src(wifi_image, &ui_img_png_wifi_full_png);
  }
  wifi_image = ui_comp_get_child(ui_panelTop2, 1);
  if (wifi_image != NULL)
  {
    lv_img_set_src(wifi_image, &ui_img_png_wifi_full_png);
  }
  wifi_image = ui_comp_get_child(ui_panelTop3, 1);
  if (wifi_image != NULL)
  {
    lv_img_set_src(wifi_image, &ui_img_png_wifi_full_png);
  }
}