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
extern global_Time gl_time;
extern request_Result req_Result;
DS3231 Clock;
bool Century=false;
bool h12;
bool PM;
char *intToCharPtr(int value)
{
  char *result = new char[20];  // 分配足够的内存来存储整数的字符串形式
  sprintf(result, "%d", value); // 将整数转换为字符串
  return result;
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
/************************************************
 *   RTC时钟获取数据
 ************************************************/


/************************************************
 *   定时函数及设置
 ************************************************/
esp_timer_handle_t timer0 = 0;
esp_timer_handle_t timer1 = 0;
esp_timer_handle_t timer2 = 0;


int getNtpTimeL(tm& timeinfo)
{

  Serial.println("获取网络时间...");
  if (!getLocalTime(&timeinfo))
  {
    delay(2000);
    if (WiFi.status() != WL_CONNECTED)
    {
   
      Serial.println("网络时间超时!...");
      return WiFi.status();
    }
  }
  else
  {
    String s;
    String m;
    String h;
    String d;
    String mon;
    String montrue;
    String T;
    int y;
    int w;
    String Zero[1] = {"0"};
    String week[8] = {"Sun", "Mon", "Tues", "Wednes", "Thur", "Fri", "Sat"};

 

    s = timeinfo.tm_sec; // 获取时间参数
    m = timeinfo.tm_min;
    h = timeinfo.tm_hour;
    d = timeinfo.tm_mday;
    mon = timeinfo.tm_mon;
    int ss = int(timeinfo.tm_sec);
    int mm = int(timeinfo.tm_min);
    int hh = int(timeinfo.tm_hour);
    int dayd = int(timeinfo.tm_mday);
    int monm = int(timeinfo.tm_mon); // 转换成int类型，用于判断是否需要补0
    if (ss < 10)
    {
      s = Zero[0] + s;
    } // 如果小于10的数字在前面补0
    if (mm < 10)
    {
      m = Zero[0] + m;
    }
    if (hh < 10)
    {
      h = Zero[0] + h;
    }
    if (dayd < 10)
    {
      d = Zero[0] + d;
    }
    montrue = monm + 1; // 月份为0~11所以要加1
    if (monm < 10)
    {
      montrue = Zero[0] + montrue;
    }
    y = int(timeinfo.tm_year) + 1900; // 2022年的y值为122，所以加上1900后再显示
    w = int(timeinfo.tm_wday);        // 星期一

    Serial.println(&timeinfo, "%A, %Y-%m-%d %H:%M:%S");
  }
  return WiFi.status();
}

// 获取天气的函数
void timer1_reqWeather_Callback(void *arg)
{
  
}

// 获取硬件时钟RTC的函数
void timer2_get_RTC_Callback(void *arg)
{
   global_Time *ptime = (global_Time *)arg;
  ptime->second = Clock.getSecond();
  ptime->minute = Clock.getMinute();
  ptime->hour = Clock.getHour(h12, PM);
  ptime->date = Clock.getDate();
  ptime->month = Clock.getMonth(Century);
  ptime->year = Clock.getYear();
  ptime->year = ptime->year + 2000;
  ptime->temperature = Clock.getTemperature();

  ptime->sdate = String(ptime->year) + "年" + String(ptime->month) + "月" + String(ptime->date) + "日";
  ptime->stime = String(ptime->hour) + ":" + String(ptime->minute) + ":" + String(ptime->second);

  Serial.print(ptime->sdate);
  Serial.print('\n');
  Serial.print(ptime->stime);
  Serial.print('\n');
  Serial.print("Temperature=");
  Serial.print(ptime->temperature);
  Serial.print('\n');

  lv_obj_t *_lbdate = ui_comp_get_child(ui_panelTop2, 4);
  if (_lbdate != NULL)
  {
    _ui_label_set_property(_lbdate, 0, ptime->sdate.c_str());
  }

  char *hh = intToCharPtr(ptime->hour);
  char *mm = intToCharPtr(ptime->minute);
  char *ss = intToCharPtr(ptime->second);
  _ui_label_set_property(ui_hh, 0, hh);
  _ui_label_set_property(ui_mm, 0, mm);
  _ui_label_set_property(ui_ss, 0, ss);

}
// 一次时定时函数
void timer0__Callback(void *arg)
{

}
void initTimer(void)
{
  
  esp_timer_create_args_t timer0_arg = {
      .callback = &timer1_reqWeather_Callback,
      .arg = NULL,
      .name ="controller"
      };
  esp_timer_create_args_t timer1_arg = {
      .callback = &timer0__Callback,
      .arg = NULL,
      .name = "heartWeather"
      };

  esp_timer_create(&timer0_arg, &timer0);
  esp_timer_start_once(timer0, 8 * 1000 * 1000); // 8s后执行一次

  esp_timer_create(&timer1_arg, &timer1);
  esp_timer_start_periodic(timer1, 600 * 1000 * 1000); // 天气15分钟执行一次，周期执行

  esp_timer_create_args_t timer2_arg = {
      .callback = &timer2_get_RTC_Callback,
      .arg = &gl_time,
      .name="RTC"
      };
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