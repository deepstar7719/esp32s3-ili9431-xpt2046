#include "ui_disp_update_Imp.h"

#include "nvs_data_handle.h"
#include "esp_timer.h"
#include "heartWeather.h"
// #include <esp_netif.h>
// #include <esp_netif_types.h>
//#include <esp_sntp.h>

#include <DS3231.h>
#include <Wire.h>
#include <mutex>

/************************************************
 *   全局变量声明
 ************************************************/
 
 

 


void lvUpdateUIElements()
{
}


/************************************************
 *   界面显示更新相关
 ************************************************/

void changewifistatus(uint8_t wl_wifistatus)
{
  if (wl_wifistatus == WL_CONNECTED)
  {
  }
  else
  {
  }
}
// 界面上显示信息
void showMessage(const char *msg)
{
  String lstr = msg;
  _ui_label_set_property(ui_lbMessage, 0, lstr.c_str());
  Serial.println(lstr.c_str());
  delay(400);
}

void lv_sctoday_update_weather(String &city,String &wheather,String &wind,const lv_img_dsc_t *wicon)
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
      lv_label_set_text(_lbdate,   city.c_str());
    }
    //更换Today页面天气说明
    lv_label_set_text(ui_lbtemp, wheather.c_str());
    lv_label_set_text(ui_lbdesc, wind.c_str());
    //更换Today页面天气图标
    lv_img_set_src(ui_ImgIcon, &wicon );
}

void lv_update_RTC_Time(String &sdate, String &hh, String &mm, String &ss)
{
  lv_obj_t *_lbdate = ui_comp_get_child(ui_panelTop2, 4);
  if (_lbdate != NULL)
  {
    _ui_label_set_property(_lbdate, 0, sdate.c_str());
  }

  _ui_label_set_property(ui_hh, 0, hh.c_str());
  _ui_label_set_property(ui_mm, 0, mm.c_str());
  _ui_label_set_property(ui_ss, 0, ss.c_str());
}

void lv_scwelcome_update_tip()
{
  
    // 在welcome页面显示链接成功信息，
    String lsWifi = "成功连接:(将在8秒后关闭此页面。)";
    lsWifi = lsWifi + "\nWIFI:" + WiFi.SSID().c_str();
    lsWifi = lsWifi + "\n闹钟IP:" + WiFi.localIP().toString().c_str();
    _ui_label_set_property(ui_lbwifiInstr, 0, lsWifi.c_str());

    Serial.print(lsWifi.c_str());
    Serial.print('\n');

}
void lv_update_wifi_status(int wf_status)
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