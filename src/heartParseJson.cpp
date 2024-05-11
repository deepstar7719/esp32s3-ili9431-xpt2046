
#include "heartParseJson.h"

 

// 解析now接口数据
  int parseJsonNow(String data)
{

  DynamicJsonDocument doc(500);
  deserializeJson(doc, data);

  const char *date = doc["results"][0]["last_update"];                            // 提取日期
  const char *id = doc["results"][0]["location"]["id"];                           // 提取城市ID
  const char *city_name = doc["results"][0]["location"]["name"];                  // 提取城市名称
  const char *country = doc["results"][0]["location"]["country"];                 // 提取国家
  const char *path = doc["results"][0]["location"]["path"];                       //  国家全地址
  const char *timezone = doc["results"][0]["location"]["timezone"];               // 时区中文
  const char *timezone_offset = doc["results"][0]["location"]["timezone_offset"]; // 时区+08国家

  const char *weather = doc["results"][0]["now"]["text"];    // 天气信息
  int weathercode = doc["results"][0]["now"]["code"];        // 天气代码
  const char *tem = doc["results"][0]["now"]["temperature"]; // 温度

  String today = date;
  req_Result.last_update = today;
  req_Result.today = today.substring(0, 10);
  req_Result.locat.id = id;
  req_Result.locat.city_name = city_name;
  req_Result.locat.country = country;
  req_Result.locat.path = path;
  req_Result.locat.timezone = timezone;
  req_Result.locat.timezone_offset = timezone_offset;


  Serial.print("parseJsonNow!");
  Serial.print("city_name: ");
  Serial.println(city_name);
  Serial.print("weather: ");
  Serial.println(weather);
  Serial.print("weathercode: ");
  Serial.println(weathercode);
  Serial.print("tem: ");
  Serial.println(tem);

  


  return 0;
}

  int parseJsonDaily(String data)
{

  DynamicJsonDocument doc(500);
  deserializeJson(doc, data);

  const char *date = doc["results"][0]["last_update"];                            // 提取日期
  const char *id = doc["results"][0]["location"]["id"];                           // 提取城市ID
  const char *city_name = doc["results"][0]["location"]["name"];                  // 提取城市名称
  const char *country = doc["results"][0]["location"]["country"];                 // 提取国家
  const char *path = doc["results"][0]["location"]["path"];                       //  国家全地址
  const char *timezone = doc["results"][0]["location"]["timezone"];               // 时区中文
  const char *timezone_offset = doc["results"][0]["location"]["timezone_offset"]; // 时区+08国家

  String today = date;
  req_Result.last_update = today;
  req_Result.today = today.substring(0, 10);
  req_Result.locat.id = id;
  req_Result.locat.city_name = city_name;
  req_Result.locat.country = country;
  req_Result.locat.path = path;
  req_Result.locat.timezone = timezone;
  req_Result.locat.timezone_offset = timezone_offset;
  for (int i; i < doc["results"][0]["daily"].size(); i++)
  {
    const char *date = doc["results"][0]["daily"][i]["date"];                           // 天气信息
    const char *text_day = doc["results"][0]["daily"][i]["text_day"];                   // 白天天气现象文字"晴",
    int code_day = doc["results"][0]["daily"][i]["code_day"];                           // 白天天气现象代码"0",
    const char *text_night = doc["results"][0]["daily"][i]["text_night"];               // 晚间天气现象文字"晴",
    int code_night = doc["results"][0]["daily"][i]["code_night"];                       // 晚间天气现象代码"1",
    const char *high = doc["results"][0]["daily"][i]["high"];                           // 当天最高温度  "28",
    const char *low = doc["results"][0]["daily"][i]["low"];                             // 当天最低温度": "15",
    const char *rainfall = doc["results"][0]["daily"][i]["rainfall"];                   // 降水量，单位mm "0.00",
    const char *precip = doc["results"][0]["daily"][i]["precip"];                       //"降水概率，范围0~1，单位百分比（目前仅支持国外城市）"0.00",
    const char *wind_direction = doc["results"][0]["daily"][i]["wind_direction"];       // 风向文字 东南",
    int wind_direction_degree = doc["results"][0]["daily"][i]["wind_direction_degree"]; // 风向角度，范围0~360"135",
    const char *wind_speed = doc["results"][0]["daily"][i]["wind_speed"];               // 风速，单位km/h（当unit=c时）、mph（当unit=f时）"23.4",
    const char *wind_scale = doc["results"][0]["daily"][i]["wind_scale"];               // 风力等级 "4",
    const char *humidity = doc["results"][0]["daily"][i]["humidity"];                   // 相对湿度，0~100，单位为百分比"37"

    heart_Daily daily;

    daily.date = date;
    daily.text_day = text_day;
    daily.code_day = code_day;
    daily.text_night = text_night;
    daily.code_night = code_night;
    daily.high = high;
    daily.low = low;
    daily.rainfall = rainfall;
    daily.precip = precip;
    daily.wind_direction = wind_direction;
    daily.wind_direction_degree = wind_direction_degree;
    daily.wind_speed = wind_speed;
    daily.wind_scale = wind_scale;
    daily.humidity = humidity;
    req_Result.dailys.push_back(daily);
  }

  Serial.print("parseJsonDaily!");

  return 0;
}

  int parseJsonHoliday(String data)
{
  return 0;
}
