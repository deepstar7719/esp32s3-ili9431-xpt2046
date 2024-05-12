#include "lv_disp_flush_Imp.h"

#include "espWifiConfig.h"
#include "nvs_data_handle.h"
#include "esp_timer.h"
#include "heartWeather.h"
#include "heartParseJson.h"
#include <DS3231.h>
#include <Wire.h>
const lv_img_dsc_t *wp_0 = &ui_img_white_wl_0_sm_png;
const lv_img_dsc_t *wp_1 = &ui_img_white_wl_1_sm_png;
const lv_img_dsc_t *wp_2 = &ui_img_white_wl_2_sm_png;
const lv_img_dsc_t *wp_3 = &ui_img_white_wl_3_sm_png;
const lv_img_dsc_t *wp_4 = &ui_img_white_wl_4_sm_png;
const lv_img_dsc_t *wp_5 = &ui_img_white_wl_5_sm_png;
const lv_img_dsc_t *wp_6 = &ui_img_white_wl_6_sm_png;
const lv_img_dsc_t *wp_7 = &ui_img_white_wl_7_sm_png;
const lv_img_dsc_t *wp_8 = &ui_img_white_wl_8_sm_png;

const lv_img_dsc_t *wl_icon[9] = {wp_0, wp_1, wp_2, wp_3, wp_4, wp_5, wp_6, wp_7, wp_8};

/************************************************
 *   全局变量声明
 ************************************************/

extern request_Result req_Result;
DS3231 Clock;
bool Century=false;
bool h12;
bool PM;

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
/************************************************
 *   RTC时钟获取数据
 ************************************************/
void ReadDS3231()
{
  int second, minute, hour, date, month, year, temperature;
  second = Clock.getSecond();
  minute = Clock.getMinute();
  hour = Clock.getHour(h12, PM);
  date = Clock.getDate();
  month = Clock.getMonth(Century);
  year = Clock.getYear();

  temperature = Clock.getTemperature();

  Serial.print("20");
  Serial.print(year, DEC);
  Serial.print('-');
  Serial.print(month, DEC);
  Serial.print('-');
  Serial.print(date, DEC);
  Serial.print(' ');
  Serial.print(hour, DEC);
  Serial.print(':');
  Serial.print(minute, DEC);
  Serial.print(':');
  Serial.print(second, DEC);
  Serial.print('\n');
  Serial.print("Temperature=");
  Serial.print(temperature);
  Serial.print('\n');
}

/************************************************
 *   定时函数及设置
 ************************************************/
esp_timer_handle_t timer0 = 0;
esp_timer_handle_t timer1 = 0;
esp_timer_handle_t timer2 = 0;

// 一次时定时函数
void timer0__Callback(void *arg)
{
  esp_timer_stop(timer1);   // 删除前需要停止
  esp_timer_delete(timer1); // 删除定时器
  esp_timer_stop(timer2);   // 删除前需要停止
  esp_timer_delete(timer2); // 删除定时器
}

// 获取天气的函数
void timer1_reqWeather_Callback(void *arg)
{
}

// 获取硬件时钟RTC的函数
void timer2_get_RTC_Callback(void *arg)
{
  ReadDS3231();
}

void initTimer(void)
{
  
  // esp_timer_create_args_t timer0_arg = {
  //     .callback = &timer1_reqWeather_Callback,
  //     .arg = NULL,
  //     .name ="controller"
  //     };
  esp_timer_create_args_t timer1_arg = {
      .callback = &timer0__Callback,
      .arg = NULL,
      .name = "heartWeather"
      };
  esp_timer_create_args_t timer2_arg = {
      .callback = &timer2_get_RTC_Callback,
      .arg = NULL,
      .name="RTC"
      };
  // esp_timer_create(&timer0_arg, &timer0);
  // esp_timer_start_once(timer0, 5 * 1000 * 1000); // 5s后执行一次

  esp_timer_create(&timer1_arg, &timer1);
  esp_timer_start_periodic(timer1, 600 * 1000 * 1000); // 天气15分钟执行一次，周期执行

  esp_timer_create(&timer2_arg, &timer2);
  esp_timer_start_periodic(timer2, 1000 * 1000); // RTC时钟1s执行一次,周期执行
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