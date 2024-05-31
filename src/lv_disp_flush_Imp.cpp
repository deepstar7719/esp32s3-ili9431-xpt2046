#include "lv_disp_flush_Imp.h"

#include "nvs_data_handle.h"
#include "esp_timer.h"
#include "heartWeather.h"
// #include <esp_netif.h>
// #include <esp_netif_types.h>
// #include <esp_sntp.h>
#include <DS3231.h>
#include <Wire.h>
#include <mutex>

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
/************************************************
 *   定时函数及设置
 ************************************************/
// esp_timer_handle_t timer0 = 0;
esp_timer_handle_t timerRTC = 0;
// esp_timer_handle_t timer2 = 0;

TaskHandle_t handleTaskWeather;
/************************************************
 *   全局变量声明
 ************************************************/
extern global_Time gl_time;
extern global_Parameter global_Para;
extern request_Result req_Result;
extern uint8_t wifi_status;

extern heartWeather myWeather;
extern espWifiConfig myWifiConfig;

SemaphoreHandle_t xMutex; // 互斥锁句柄
DS3231 Clock;
bool Century = false;
bool h12 = false;
bool PM;
// std::mutex my_mutex;

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

void configTimeL()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  // esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG(ntpServer);
  // esp_netif_sntp_init(&config);
  // if (esp_netif_sntp_sync_wait(pdMS_TO_TICKS(10000)) != ESP_OK)
  // {
  //   printf("Failed to update system time within 10s timeout");
  // }
}

void lvUpdateUIElements()
{
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
 *   网络时钟获取数据
 ************************************************/

int getNtpTimeL(global_Time &gl_time)
{

  /*
  time_t now;
  char strftime_buf[64];
  struct tm timeinfo;

  time(&now);
  // 将时区设置为中国标准时间
  setenv("TZ", "CST-8", 1);
  tzset();

  localtime_r(&now, &timeinfo);
  strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
  ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);
  */

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

    int hh = (timeinfo.tm_hour < 12 ? timeinfo.tm_hour : timeinfo.tm_hour + 6);

    Serial.print("更新RTC时钟的时间。\n");
    Serial.printf("更新RTC时间小时为:%d\n", hh);

    if (xSemaphoreTake(xMutex, portMAX_DELAY))
    {
      Clock.setClockMode(h12);
      Clock.setSecond(timeinfo.tm_sec);      // Set the second
      Clock.setMinute(timeinfo.tm_min);      // Set the minute
      Clock.setHour(hh);                     // Set the hour
      Clock.setDoW(timeinfo.tm_wday);        // Set the day of the week
      Clock.setDate(timeinfo.tm_mday);       // Set the date of the month
      Clock.setMonth(timeinfo.tm_mon + 1);   // Set the month of the year
      Clock.setYear(timeinfo.tm_year - 100); // Set the year (Last two digits of the year)

      xSemaphoreGive(xMutex);
    }
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
    getNtpTimeL(gl_time); // 更新时间

    myWeather.requestsWeather();

    String city = req_Result.locat.city_name;
    heart_Daily daily = req_Result.dailys.at(0);

    String wheather = daily.getWeather();
    String wind = daily.getWind();

    Serial.print("根据天气，获得定位城市：");
    Serial.print(city);
    Serial.println(wheather);
    // 更换定位
    lv_obj_t *_lbdate = ui_comp_get_child(ui_panelTop1, 3);
    if (_lbdate != NULL)
    {
      _ui_label_set_property(_lbdate, 0, city.c_str());
    }
    _lbdate = ui_comp_get_child(ui_panelTop2, 3);
    if (_lbdate != NULL)
    {
      _ui_label_set_property(_lbdate, 0, city.c_str());
    }
    _lbdate = ui_comp_get_child(ui_panelTop3, 3);
    if (_lbdate != NULL)
    {
      _ui_label_set_property(_lbdate, 0, city.c_str());
    }
    // 更换天气说明
    lv_label_set_text(ui_lbtemp, wheather.c_str());
    lv_label_set_text(ui_lbdesc, wind.c_str());

    // 更换当天图标
    int code_day = daily.code_day;
    int code_night = daily.code_night;
    code_day = (code_day == 99 ? 39 : code_day);
    code_night = (code_night == 99 ? 39 : code_night);

    lv_img_set_src(ui_ImgIcon, wl_icon[code_day]);

    // 延迟15分钟一次
    vTaskDelay(840000 / portTICK_PERIOD_MS);
  }
}

// 获取硬件时钟RTC的函数
void timer_get_RTC_Callback(void *arg)
{
  Serial.println("****************RTC_Callback**********");
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

void initTimer(void)
{

  esp_timer_create_args_t timerRTC_arg = {
      .callback = &timer_get_RTC_Callback,
      .arg = &gl_time,
      .name = "RTC"};
  esp_timer_create(&timerRTC_arg, &timerRTC);
  esp_timer_start_periodic(timerRTC, 1000 * 1000); // RTC时钟1s执行一次,周期执行
}

void wificonnected(wl_status_t wl_status)
{
  if (wifi_status != wl_status && wl_status == WL_CONNECTED)
  {
    wifi_status = wl_status;
    //  保存变量
    String ssid, pass;
    myWifiConfig.getWifiInfo(ssid, pass);
    global_Para.wifi_ssid = ssid;
    global_Para.wifi_pass = pass;
    savemyData(global_Para);

    // 创建互斥锁
    xMutex = xSemaphoreCreateMutex();

    // 创建获取天气的任务，

    xTaskCreatePinnedToCore(task_reqWeather_Callback, "heartWeather", 20480, NULL, configMAX_PRIORITIES, &handleTaskWeather, 0);

    // 在welcome页面显示链接成功信息，
    String lsWifi = "成功连接:(将在8秒后关闭此页面。)";
    lsWifi = lsWifi + "\nWIFI:" + WiFi.SSID().c_str();
    lsWifi = lsWifi + "\n闹钟IP:" + WiFi.localIP().toString().c_str();
    _ui_label_set_property(ui_lbwifiInstr, 0, lsWifi.c_str());

    Serial.print(lsWifi.c_str());
    Serial.print('\n');

    // 更换wifi状态icon
    lv_obj_t *wifi_image = ui_comp_get_child(ui_panelTop1, 1);
    if (wifi_image != NULL)
    {
      lv_img_set_src(wifi_image, &ui_img_png_wifi_full_png);
    }

    // 一切就绪, 启动LVGL任务
    configTimeL();
    xTaskNotifyGive(handleTaskWeather);
    Serial.print("xTaskNotifyGive handleTaskWeather done!\n");

    delay(6000);
    initTimer(); // start Timer
    delay(2000);
    _ui_screen_change(&ui_scToday, LV_SCR_LOAD_ANIM_NONE, 0, 0, NULL);
    wifi_image = ui_comp_get_child(ui_panelTop2, 1);
    if (wifi_image != NULL)
    {
      lv_img_set_src(wifi_image, &ui_img_png_wifi_full_png);
    }
  }
}
