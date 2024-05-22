#include "lv_disp_flush_Imp.h"

#include "nvs_data_handle.h"
#include "esp_timer.h"
#include "heartWeather.h"
#include "heartParseJson.h"
#include <DS3231.h>
#include <Wire.h>
#include <mutex>

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
bool Century = false;
bool h12 = false;
bool PM;
std::mutex my_mutex;
const char *zWeek[7] = {
    "星期日",
    "星期一",
    "星期二",
    "星期三",
    "星期四",
    "星期五",
    "星期六"};

const char *ntpServer = "ntp1.aliyun.com"; // 阿里云NTP网络时间服务器
const long gmtOffset_sec = 28800;
const int daylightOffset_sec = 0;

void getNtpTime()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

char *intToCharPtr(int value)
{
  char *result = new char[20];    // 分配足够的内存来存储整数的字符串形式
  sprintf(result, "%02d", value); // 将整数转换为字符串
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
 *   定时函数及设置
 ************************************************/
esp_timer_handle_t timer0 = 0;
esp_timer_handle_t timer1 = 0;
esp_timer_handle_t timer2 = 0;
/************************************************
 *   网络时钟获取数据
 ************************************************/

int getNtpTimeL(global_Time &gl_time)
{
  tm timeinfo;
  Serial.print("获取网络时间...\n");
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
    Serial.print("成功获取网络时间：\n");
    Serial.println(&timeinfo, "%A, %Y-%m-%d %H:%M:%S");
    Serial.print("时：");
    Serial.println(timeinfo.tm_hour);
    Serial.print("月：");
    Serial.println(timeinfo.tm_mon);

    int hh = timeinfo.tm_hour < 12 ? timeinfo.tm_hour : timeinfo.tm_hour + 6;

    Serial.print("更新RTC时钟的时间。\n");
    my_mutex.lock();
    Clock.setClockMode(h12);
    Clock.setSecond(timeinfo.tm_sec);      // Set the second
    Clock.setMinute(timeinfo.tm_min);      // Set the minute
    Clock.setHour(hh);       // Set the hour
    Clock.setDoW(timeinfo.tm_wday);        // Set the day of the week
    Clock.setDate(timeinfo.tm_mday);       // Set the date of the month
    Clock.setMonth(timeinfo.tm_mon + 1);   // Set the month of the year
    Clock.setYear(timeinfo.tm_year - 100); // Set the year (Last two digits of the year)
    my_mutex.unlock();

    // gl_time.second = timeinfo.tm_sec;
    // gl_time.minute = timeinfo.tm_min;
    // gl_time.hour = timeinfo.tm_hour;
    // gl_time.wday = timeinfo.tm_wday;
    // gl_time.date = timeinfo.tm_mday;
    // gl_time.month = timeinfo.tm_mon;
    // gl_time.year = int(timeinfo.tm_year);

    // gl_time.ssecond = intToCharPtr(timeinfo.tm_sec);
    // gl_time.sminute = intToCharPtr(timeinfo.tm_min);
    // gl_time.shour = intToCharPtr(timeinfo.tm_hour);

    // gl_time.syear = int(timeinfo.tm_year); // 2022年的y值为122，所以加上1900后再显示
    // gl_time.week = int(timeinfo.tm_wday);  // 星期一
  }
  return WiFi.status();
}

// 获取天气的函数
void timer1_reqWeather_Callback(void *arg)
{
  getNtpTimeL(gl_time); // 更新时间
}

// 获取硬件时钟RTC的函数
void timer2_get_RTC_Callback(void *arg)
{
  global_Time *ptime = (global_Time *)arg;

  byte year, month, date, DoW, hour, minute, second;

  Clock.getTime(year, month, date, DoW, hour, minute, second);
  month = Clock.getMonth(Century);
  String hh, mm, ss, sdate, stime;
  hh = intToCharPtr(hour);
  mm = intToCharPtr(minute);
  ss = intToCharPtr(second);
  sdate = String(year + 2000) + "年" + String(month) + "月" + String(date) + "日  " + zWeek[DoW];
  stime = hh + ":" + mm + ":" + ss;
  lv_obj_t *_lbdate = ui_comp_get_child(ui_panelTop2, 4);
  if (_lbdate != NULL)
  {
    _ui_label_set_property(_lbdate, 0, sdate.c_str());
  }

  _ui_label_set_property(ui_hh, 0, hh.c_str());
  _ui_label_set_property(ui_mm, 0, mm.c_str());
  _ui_label_set_property(ui_ss, 0, ss.c_str());
  // ptime->second = second;
  // ptime->minute = minute;
  // ptime->hour = hour;
  // ptime->date = date;
  // ptime->month = month;
  // ptime->year = year;
  // ptime->year = ptime->year + 2000;
  // ptime->wday = DoW;
  // ptime->week = zWeek[DoW];

  ptime->temperature = Clock.getTemperature();

  // ptime->shour = intToCharPtr(ptime->hour);
  // ptime->sminute = intToCharPtr(ptime->minute);
  // ptime->ssecond = intToCharPtr(ptime->second);

  // ptime->sdate = String(year) + "年" + String(month) + "月" + String(date) + "日  " + ptime->week;
  // ptime->stime = ptime->shour + ":" + ptime->sminute + ":" + ptime->ssecond;

  Serial.print(sdate);
  Serial.print('\n');
  Serial.print(stime);
  Serial.print('\n');
  Serial.print("Temperature=");
  Serial.print(ptime->temperature);
  Serial.print('\n');
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
      .name = "controller"};
  esp_timer_create_args_t timer1_arg = {
      .callback = &timer0__Callback,
      .arg = NULL,
      .name = "heartWeather"};

  esp_timer_create(&timer0_arg, &timer0);
  esp_timer_start_once(timer0, 8 * 1000 * 1000); // 8s后执行一次

  esp_timer_create(&timer1_arg, &timer1);
  esp_timer_start_periodic(timer1, 600 * 1000 * 1000); // 天气15分钟执行一次，周期执行

  delay(500);
  esp_timer_create_args_t timer2_arg = {
      .callback = &timer2_get_RTC_Callback,
      .arg = &gl_time,
      .name = "RTC"};
  esp_timer_create(&timer2_arg, &timer2);
  esp_timer_start_periodic(timer2, 1000 * 1000); // RTC时钟1s执行一次,周期执行
}
