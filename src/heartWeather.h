
#ifndef __HEART_WEATHER_H__
#define __HEART_WEATHER_H__
#include "HTTPClient.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <vector>

typedef struct 
{
public:
    String date;
    String text_day;           // 白天天气现象文字"晴",
    int code_day;              // 白天天气现象代码"0",
    String text_night;         // 晚间天气现象文字"晴",
    int code_night;            // 晚间天气现象代码"1",
    String high;               // 当天最高温度  "28",
    String low;                // 当天最低温度": "15",
    String rainfall;           // 降水量，单位mm "0.00",
    String precip;             //"降水概率，范围0~1，单位百分比（目前仅支持国外城市）"0.00",
    String wind_direction;     // 风向文字 东南",
    int wind_direction_degree; // 风向角度，范围0~360"135",
    String wind_speed;         // 风速，单位km/h（当unit=c时）、mph（当unit=f时）"23.4",
    String wind_scale;         // 风力等级 "4",
    String humidity;           // 相对湿度，0~100，单位为百分比"37"
public:

String getWeather()
{
  String wheather = "";
  wheather = text_day;
  wheather = wheather + " " + high;
  wheather = wheather + "/" + low + " 度";
  return String(wheather);
}

String getRain()
{
  String rain = "";
  return String(rain);
}

String getWind()
{
  String wind = "";
  wind = wind_direction;
  wind = wind + " " + wind_direction_degree + " 度";
  wind = wind + "， 风速，" + wind_speed + "km/h";
  wind = wind + "， 风力等级" + wind_scale + " ";
  return String(wind);
}

String getHumidity()
{
    String humidity = "";
  return String(humidity);
}

}heart_Daily;
typedef struct
{
    String id;              // "WX4FBXXFKE4F",
    String city_name;       // "北京",
    String country;         // "CN",
    String path;            // "北京,北京,中国",
    String timezone;        //"Asia/Shanghai",
    String timezone_offset; // "+08:00"
} heartL_Location;
typedef struct
{
    heartL_Location locat;
    std::vector<heart_Daily> dailys;
    String last_update;
    String today;
} request_Result;

class heartWeather
{
protected:
    typedef std::function<void(wl_status_t, const char *)> THandlerFunction;
    THandlerFunction _fn = NULL;

    typedef std::function<int(String)> TParseFunction;

public:
    heartWeather(String reqUserKey);
    virtual ~heartWeather();
    int _icon;
    int _hour;
    int _minute;
    int _sec;

    int _weatherCode;
    String _city;
    // const char *weather1;
    // const char *temputer;

    const char *holiday;

    // const char* ntpServer = "ntp1.aliyun.com"; // 阿里云NTP网络时间服务器
    String _heartHost = "https://api.seniverse.com";       // 心知天气APIhost
    String _holidayUrl = "http://timor.tech/api/holiday/info/"; // 节假日接口

private:
    String _today;

    String _reqUserKey = ""; // 私钥
    String _reqUnit = "c";   // 摄氏
    String _reqRes = "";

public:
    void selectIcon(int i);

    int requestHoliday();
    int requestsWeather();
    int parseJsonNow(String data);
    int parseJsonDaily(String data);
    int parseJsonHoliday(String data);
};
#endif