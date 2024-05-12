#ifndef __HEART_PARSE_JSON__
#define __HEART_PARSE_JSON__
#include <Arduino.h>
#include <ArduinoJson.h>
#include <vector>

struct heart_Daily
{
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
};
struct heartL_Location
{
        String id;              // "WX4FBXXFKE4F",
        String city_name;       // "北京",
        String country;         // "CN",
        String path;            // "北京,北京,中国",
        String timezone;        //"Asia/Shanghai",
        String timezone_offset; // "+08:00"
};
struct request_Result
{
        heartL_Location locat;
        std::vector<heart_Daily> dailys;
        String last_update;
        String today;
};


int parseJsonNow(String data);
int parseJsonDaily(String data);
int parseJsonHoliday(String data);

#endif
