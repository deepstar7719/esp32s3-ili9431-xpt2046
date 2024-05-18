

#include "lv_disp_flush_Imp.h"

#include "espWifiConfig.h"
#include "nvs_data_handle.h"
#include "esp_timer.h"
#include "heartWeather.h"
#include "heartParseJson.h"
#include <DS3231.h>
#include <Wire.h>
#include <TimeLib.h>
#include <NtpClientLib.h>


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
bool h12;
bool PM;

const char *zWeek[7] = {
    "星期一",
    "星期二",
    "星期三",
    "星期四",
    "星期五",
    "星期六",
    "星期日"};
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
 *   网络时钟获取数据
 ************************************************/
/*******************httpclient.c***********************************************/
// char *SntpServerNames[3] = {
//     "ntp1.aliyun.com",
//     "ntp2.aliyun.com",
//     "ntp3.aliyun.com"};
// //ATaskSntp任务
// void ATaskSntp( void *pvParameters ){
//     STATION_STATUS Status;
//     uint32 time;
//     do{
//         Status = wifi_station_get_connect_status();
//         vTaskDelay(100);
//     }while(Status != STATION_GOT_IP);
//     printf("task is SNTP\n");
//     printf("STATION_GOT_IP!\n");
//     sntp_setservername(0,SntpServerNames[0]);
//     sntp_setservername(1,SntpServerNames[1]);
//     sntp_setservername(2,SntpServerNames[2]);
//     sntp_init();
//     for(;;){
//         time = sntp_get_current_timestamp();
//         if(time){
//             printf("current date:%s\n",sntp_get_real_time(time));
//         }
//         vTaskDelay(500);
//     }
//     vTaskDelete(NULL);
// }
// //Sntp_init 初始化
// void Sntp_init(void){
//     xTaskCreate(ATaskSntp, "Sntp", 512, NULL, 4, NULL);
// }

/************************************************
 *   定时函数及设置
 ************************************************/
esp_timer_handle_t timer0 = 0;
esp_timer_handle_t timer1 = 0;
esp_timer_handle_t timer2 = 0;


int8_t timeZone = 8;
const PROGMEM char *ntpServer = "ntp1.aliyun.com";

void getNtpTime()
{
   NTP.setInterval (600);
  NTP.setNTPTimeout (1500);
  NTP.begin (ntpServer, timeZone, false);
}
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

    gl_time.ssecond = intToCharPtr(timeinfo.tm_sec);
    gl_time.sminute = intToCharPtr(timeinfo.tm_min);
    gl_time.shour = intToCharPtr(timeinfo.tm_hour);

    gl_time.syear = int(timeinfo.tm_year) + 1900; // 2022年的y值为122，所以加上1900后再显示
    gl_time.week = int(timeinfo.tm_wday);         // 星期一

    Serial.println(&timeinfo, "%A, %Y-%m-%d %H:%M:%S");
  }
  return WiFi.status();
}

// 获取天气的函数
void timer1_reqWeather_Callback(void *arg)
{

  getNtpTimeL(gl_time); // 更新时间

  Clock.setSecond(gl_time.second); // Set the second
  Clock.setMinute(gl_time.minute); // Set the minute
  Clock.setHour(gl_time.hour);     // Set the hour
  Clock.setDoW(gl_time.wday);      // Set the day of the week
  Clock.setDate(gl_time.date);     // Set the date of the month
  Clock.setMonth(gl_time.month);   // Set the month of the year
  Clock.setYear(gl_time.year);     // Set the year (Last two digits of the year)
}

// 获取硬件时钟RTC的函数
void timer2_get_RTC_Callback(void *arg)
{
  global_Time *ptime = (global_Time *)arg;

  byte year, month, date, DoW, hour, minute, second;

  Clock.getTime(year, month, date, DoW, hour, minute, second);
  ptime->second = second;
  ptime->minute = minute;
  ptime->hour = hour;
  ptime->date = date;
  ptime->month = month;
  ptime->year = year;
  ptime->year = ptime->year + 2000;
  ptime->wday = DoW;
  ptime->week=zWeek[DoW];

  ptime->temperature = Clock.getTemperature();

  ptime->shour = intToCharPtr(ptime->hour);
  ptime->sminute = intToCharPtr(ptime->minute);
  ptime->ssecond = intToCharPtr(ptime->second);

  ptime->sdate = String(ptime->year) + "年" + String(ptime->month) + "月" + String(ptime->date) + "日  " +ptime->week;
  ptime->stime = ptime->shour + ":" + ptime->sminute + ":" + ptime->ssecond;

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

  _ui_label_set_property(ui_hh, 0, ptime->shour.c_str());
  _ui_label_set_property(ui_mm, 0, ptime->sminute.c_str());
  _ui_label_set_property(ui_ss, 0, ptime->ssecond.c_str());
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

  esp_timer_create_args_t timer2_arg = {
      .callback = &timer2_get_RTC_Callback,
      .arg = &gl_time,
      .name = "RTC"};
  esp_timer_create(&timer2_arg, &timer2);
  esp_timer_start_periodic(timer2, 1000 * 1000); // RTC时钟1s执行一次,周期执行
}
