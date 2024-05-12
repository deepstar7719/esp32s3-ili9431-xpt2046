#include "lvgldisplayImp.h"


const lv_img_dsc_t *wp_0 = &ui_img_black_wl_0_icon_png;
const lv_img_dsc_t *wp_1 = &ui_img_black_wl_1_icon_png;
const lv_img_dsc_t *wp_2 = &ui_img_black_wl_2_icon_png;
const lv_img_dsc_t *wp_3 = &ui_img_black_wl_3_icon_png;
const lv_img_dsc_t *wp_4 = &ui_img_black_wl_4_icon_png;
const lv_img_dsc_t *wp_5 = &ui_img_black_wl_5_icon_png;
const lv_img_dsc_t *wp_6 = &ui_img_black_wl_6_icon_png;
const lv_img_dsc_t *wp_7 = &ui_img_black_wl_7_icon_png;
const lv_img_dsc_t *wp_8 = &ui_img_black_wl_8_icon_png;
 

 
 const lv_img_dsc_t *wl_icon[9] = {wp_0,wp_1,wp_2,wp_3,wp_4,wp_5,wp_6,wp_7,wp_8};
 


// 界面上显示信息
void showMessage(const char *msg)
{
  String lstr = msg;
  _ui_label_set_property(ui_lbMessage, 0, lstr.c_str());
  Serial.println(lstr.c_str());
  delay(400);
}



/*
// 定时器1中断函数
void tickerIsr()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(wifi_LED, !(digitalRead(wifi_LED)));
  }
  else
  {
    digitalWrite(wifi_LED, 1);
  }
  timeClient.update(); // 更新时间
  hour = timeClient.getHours();
  minute = timeClient.getMinutes();
  sec = timeClient.getSeconds();
  count++;
  count1++;
  if (count1 > 0 && count1 <= 5)
  {
    mode = 1;
  }
  else if (count1 > 5 && count1 <= 10)
  {
    mode = 2;
  }
  else if (count1 > 10 && count1 <= 15)
  {
    mode = 3;
  }
  else
  {
    count1 = 0;
  }
  if (count > 300)
  { // 每5分钟复位一次，重新获取时间、天气
    Serial.println("重新获取时间、天气....");
    count = 0;
    requestsWeatherTime = true;
  }
}
*/