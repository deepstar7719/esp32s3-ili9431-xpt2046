#include "ui_action_Imp.h"
#include "esp_timer.h"
#include "heartWeather.h"
#include "nvs_data_handle.h"
#include <esp_sntp.h>
#include <time.h>
#include "esp_log.h"

#include <DS3231.h>
#include <Wire.h>
#include <mutex>

TaskHandle_t handleTaskWeather;

/************************************************
 *   定时函数及设置
 ************************************************/

esp_timer_handle_t timerRTC = 0;
esp_timer_handle_t timerScreenAnim = 0;
/************************************************
 *   全局变量声明
 ************************************************/
extern global_Time gl_time;
extern global_Parameter global_Para;
extern request_Result req_Result;
extern uint8_t wifi_status;

extern heartWeather myWeather;
 

const char *ntpServer = "ntp1.aliyun.com"; // 阿里云NTP网络时间服务器
const long gmtOffset_sec = 28800;
const int daylightOffset_sec = 0;

DS3231 Clock;
bool Century = false;
bool h12 = false;
bool PM;

SemaphoreHandle_t xMutex; // 互斥锁句柄
/**********互斥锁句柄用法**************************/
//    if (xSemaphoreTake(xMutex, portMAX_DELAY))
//     {

//       xSemaphoreGive(xMutex);
//     }
/**********互斥锁句柄用法**************************/

#define MAX_SCREEN_NUM 3
#define SCREEN_ANIM_DELAY 10
#define WEATHER_OF_OTHER_DAYS 2
lv_obj_t **lv_anim_screen[MAX_SCREEN_NUM] = {
    &ui_scWelcome,
    &ui_scToday,
    &ui_scWeather};
int ncurrentScreen = 0;

lv_obj_t **lv_wearther_obj[WEATHER_OF_OTHER_DAYS] = {
    &ui_cmPanelWeather1,
    &ui_cmPanelWeather2};

const lv_img_dsc_t *wl_icon[40] = {
    &ui_img_white_wl_0_sm_png,
    &ui_img_white_wl_1_sm_png,
    &ui_img_white_wl_2_sm_png,
    &ui_img_white_wl_3_sm_png,
    &ui_img_white_wl_4_sm_png,
    &ui_img_white_wl_5_sm_png,
    &ui_img_white_wl_6_sm_png,
    &ui_img_white_wl_7_sm_png,
    &ui_img_white_wl_8_sm_png,
    &ui_img_white_wl_9_sm_png,

    &ui_img_white_wl_10_sm_png,
    &ui_img_white_wl_11_sm_png,
    &ui_img_white_wl_12_sm_png,
    &ui_img_white_wl_13_sm_png,
    &ui_img_white_wl_14_sm_png,
    &ui_img_white_wl_15_sm_png,
    &ui_img_white_wl_16_sm_png,
    &ui_img_white_wl_17_sm_png,
    &ui_img_white_wl_18_sm_png,
    &ui_img_white_wl_19_sm_png,

    &ui_img_white_wl_20_sm_png,
    &ui_img_white_wl_21_sm_png,
    &ui_img_white_wl_22_sm_png,
    &ui_img_white_wl_23_sm_png,
    &ui_img_white_wl_24_sm_png,
    &ui_img_white_wl_25_sm_png,
    &ui_img_white_wl_26_sm_png,
    &ui_img_white_wl_27_sm_png,
    &ui_img_white_wl_28_sm_png,
    &ui_img_white_wl_29_sm_png,

    &ui_img_white_wl_30_sm_png,
    &ui_img_white_wl_31_sm_png,
    &ui_img_white_wl_32_sm_png,
    &ui_img_white_wl_33_sm_png,
    &ui_img_white_wl_34_sm_png,
    &ui_img_white_wl_35_sm_png,
    &ui_img_white_wl_36_sm_png,
    &ui_img_white_wl_37_sm_png,
    &ui_img_white_wl_38_sm_png,
    &ui_img_white_wl_99_sm_png};

const char *zWeek[7] = {
    "星期日",
    "星期一",
    "星期二",
    "星期三",
    "星期四",
    "星期五",
    "星期六"};

/************************************************
 *   网络时钟获取数据
 ************************************************/
void configTimeL()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

int getNtpTimeL()
{

  // time_t now;
  //   char strftime_buf[64];
  tm timeinfo;

  //   time(&now);
  //   // 将时区设置为中国标准时间
  //   setenv("TZ", "CST-8", 1);
  //   tzset();
  //     localtime_r(&now, &timeinfo);
  //     strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
  //     ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);

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

    if (xSemaphoreTake(xMutex, portMAX_DELAY))
    {

      Clock.setSecond(timeinfo.tm_sec);    // Set the second
      Clock.setMinute(timeinfo.tm_min);    // Set the minute
      Clock.setHour(timeinfo.tm_hour);     // Set the hour
      Clock.setDoW(timeinfo.tm_wday);      // Set the day of the week
      Clock.setDate(timeinfo.tm_mday);     // Set the date of the month
      Clock.setMonth(timeinfo.tm_mon + 1); // Set the month of the year
      Clock.setYear(timeinfo.tm_year);     // Set the year (Last two digits of the year)

      xSemaphoreGive(xMutex);
    }
  }

  Serial.println("获取网络时间结束！");
  return WiFi.status();
}

// 获取天气的函数
void task_reqWeather_Callback(void *arg)
{
  Serial.println("****************reqWeather_Callback**********");
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
  while (1)
  {

    // 更新时间
    getNtpTimeL();
    myWeather.requestsWeather();

    String city = req_Result.locat.city_name;
    heart_Daily daily = req_Result.dailys.at(0);
    String wheather = daily.getWeather();
    String wind = daily.getWind();

    // 更换当天图标
    int code_day = daily.code_day;
    int code_night = daily.code_night;
    code_day = (code_day == 99 ? 39 : code_day);
    code_night = (code_night == 99 ? 39 : code_night);

    Serial.print("根据天气，获得定位城市：");
    Serial.print(city);
    Serial.println(wheather);

    lv_sctoday_update_weather(wheather, wind, wl_icon[code_day]);

    for (int nindex = 1; nindex < req_Result.dailys.size(); nindex++)
    {

      heart_Daily daily = req_Result.dailys.at(nindex);

      code_day = daily.code_day;
      code_night = daily.code_night;
      code_day = (code_day == 99 ? 39 : code_day);
      code_night = (code_night == 99 ? 39 : code_night);
      lv_scWeather_update_otherday_weather(*lv_wearther_obj[nindex - 1], daily, wl_icon[code_day]);
    }

    lv_all_update_location(city);
    // 延迟15分钟一次
    vTaskDelay(840000 / portTICK_PERIOD_MS);
  }
}
// 获取硬件时钟RTC的函数
void timer_get_RTC_Callback(void *arg)
{
  Serial.println("****************RTC_Callback**********");

  byte year, month, date, DoW, hour, minute, second;
  byte temper;

  Clock.getTime(year, month, date, DoW, hour, minute, second);

  month = Clock.getMonth(Century);
  temper = Clock.getTemperature();
  hour = Clock.getHour(h12, PM);

  Serial.print("RTC:");
  Serial.println(hour);
  String hh, mm, ss, sdate, stime;
  hh = intToCharPtr(hour);
  mm = intToCharPtr(minute);
  ss = intToCharPtr(second);
  sdate = String(year + 1900) + "年" + String(month) + "月" + String(date) + "日  " + zWeek[DoW];
  stime = hh + ":" + mm + ":" + ss;

  // 显示时分秒
  lv_sctoday_update_RTC_Time(hh, mm, ss);
  lv_all_update_panelTop_Day(sdate);

  Serial.println(sdate);
  Serial.println(stime);
}

void timer_change_sreen_Callback(void *arg)
{
  int nindex = ncurrentScreen;
  nindex++;
  if (nindex >= MAX_SCREEN_NUM)
  {
    nindex = 1;
  }
  uiChangeScreen(nindex, LV_SCR_LOAD_ANIM_OVER_RIGHT);
}
void initRTCTimer(void)
{

  // 初始化RTC
  Clock.setClockMode(h12);
  esp_timer_create_args_t timerRTC_arg = {
      .callback = &timer_get_RTC_Callback,
      .arg = &gl_time,
      .name = "RTC"};
  esp_timer_create(&timerRTC_arg, &timerRTC);
  esp_timer_start_periodic(timerRTC, 1000 * 1000); // RTC时钟1s执行一次,周期执行
}
void initScreenAnimTimer()
{
  esp_timer_create_args_t timerAnim_arg = {
      .callback = &timer_change_sreen_Callback,
      .arg = NULL,
      .name = "ScreenAnim"};
  esp_timer_create(&timerAnim_arg, &timerScreenAnim);
  esp_timer_start_periodic(timerScreenAnim, SCREEN_ANIM_DELAY * 1000 * 1000);
}
void uiChangeScreen(int nindex, lv_scr_load_anim_t fademode)
{
  if (nindex > -1 && nindex < MAX_SCREEN_NUM)
  {
    lv_obj_t **obj = lv_anim_screen[nindex];
    _ui_screen_change(obj, fademode, 0, 10, NULL);
    ncurrentScreen = nindex;
  }
}
void wifiConnected(wl_status_t wl_status)
{
  if (wifi_status != wl_status && wl_status == WL_CONNECTED)
  {
    wifi_status = wl_status;
    //  保存变量
    String ssid, pass;
    //myWifiConfig.getWifiInfo(ssid, pass);

    //wifiManager
    global_Para.wifi_ssid = ssid;
    global_Para.wifi_pass = pass;
    savemyData(global_Para);
    // 更新Wifi状
    lv_all_update_wifi_status((int)wl_status);
    // 创建互斥锁
    xMutex = xSemaphoreCreateMutex();

    // 创建获取天气的任务，
    xTaskCreatePinnedToCore(task_reqWeather_Callback, "heartWeather", 20480, NULL, configMAX_PRIORITIES, &handleTaskWeather, 0);

    lv_scwelcome_update_tip();

    // 时间同步
    configTimeL();
    // esp_wait_sntp_sync();
    // 一切就绪, 启动LVGL任务
    xTaskNotifyGive(handleTaskWeather);
    Serial.print("xTaskNotifyGive handleTaskWeather done!\n");

    delay(6000);
    // start rtc Timer
    initRTCTimer();
    delay(2000);

    uiChangeScreen(1, LV_SCR_LOAD_ANIM_NONE);

    // start ScreenAnim Timer
    initScreenAnimTimer();
  }
}
 
void changeWifiStatus(uint8_t wl_wifistatus)
{
  if (wl_wifistatus == WL_CONNECTED)
  {
  }
  else
  {
  }
}
char *intToCharPtr(int value)
{
  char *result = new char[20];    // 分配足够的内存来存储整数的字符串形式
  sprintf(result, "%02d", value); // 将整数转换为字符串
  return result;
}
