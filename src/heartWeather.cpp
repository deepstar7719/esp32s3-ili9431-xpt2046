#include "heartWeather.h"

heartWeather::heartWeather(String reqUserKey)
{
  _reqUserKey = reqUserKey;
}

heartWeather::~heartWeather()
{
}

// 选择天气图标
void heartWeather::selectIcon(int i)
{
  switch (i)
  {
  case 0: // 白天晴天
  case 2:
    _icon = 1;
    break;

  case 1: // 晚上晴天
  case 3:
    _icon = 12;
    break;
  case 6: // 晚上多云
  case 8:
    _icon = 2;
  case 4: // 白天多云
  case 5:
  case 7:
  case 9:
    _icon = 3;
    break;

  case 10: // 阵雨(太阳雨)
    _icon = 4;
    break;

  case 11: // 雷阵雨
  case 12:
    _icon = 5;
    break;

  case 13: // 小雨
    _icon = 6;
    break;

  case 14: // 大到暴雨
  case 15:
  case 16:
  case 17:
  case 18:
    _icon = 7;
    break;

  case 20: // 雪
  case 21:
  case 22:
  case 23:
  case 24:
  case 25:
    _icon = 8;
    break;

  case 31: // 霾
    _icon = 9;
    break;

  case 32: // 风
  case 33:
    _icon = 10;
    break;

  default:
    _icon = 99;
    break;
  }
}

// 获取网络时间
int heartWeather::getNtpTime(tm timeinfo)
{

  Serial.println("获取网络时间...");

  if (!getLocalTime(&timeinfo))
  {
    delay(2000);
    if (WiFi.status() != WL_CONNECTED)
    {
      if (_fn != NULL)
      {
        _fn(WiFi.status(), "网络时间超时!......");
      }
      Serial.println("网络时间超时!...");
       return WiFi.status();
    }
  }
  else
  {
    _hour = timeinfo.tm_hour;  // 更新小时
    _minute = timeinfo.tm_min; // 更新分钟
    _sec = timeinfo.tm_sec;    // 获取秒钟
    Serial.println(&timeinfo, "%A, %Y-%m-%d %H:%M:%S");
  }
  return WiFi.status();
}

// 请求节假日信息（判断今天是否是节假日）
int heartWeather::requestHoliday(TParseFunction fn_parse)
{

  String req, res;
  HTTPClient httpclient;
  req = _holidayUrl + _today;
  // req = url+"2021-10-01";
  if (httpclient.begin(req))
  {
    Serial.println("HTTPclient setUp done!");
  }
  int http_code = httpclient.GET();
  if (http_code > 0)
  {
    Serial.printf("HTTP get code: %d\n", http_code);
    if (http_code == HTTP_CODE_OK)
    {
      res = httpclient.getString();
      httpclient.end();
      fn_parse(res);
    }
    else
    {
      httpclient.end();
      Serial.printf("fail to get getHoliday,code:%d\n", http_code);
       
    }
  }
  return http_code;
}

// 请求天气
int heartWeather::requestsWeather(TParseFunction fn_parse)
{

  Serial.println("获取天气信息...");

  if (city == "")
  {

    _reqRes = "/v3/weather/now.json?key=" + _reqUserKey + +"&location=" + "ip" + "&language=zh-Hans&unit=" + _reqUnit;
  }
  else
  {
    _reqRes = "/v3/weather/now.json?key=" + _reqUserKey + +"&location=" + city + "&language=zh-Hans&unit=" + _reqUnit;
  }
  String req, res;
  HTTPClient httpclient;
  req = (String)_heartHost + _reqRes;

  if (httpclient.begin(req))
  {
    Serial.println("HTTPclient setUp done!");
  }
  int http_code = httpclient.GET();
  if (http_code > 0)
  {
    Serial.printf("HTTP get code: %d\n", http_code);
    if (http_code == HTTP_CODE_OK)
    {
      res = httpclient.getString();
      httpclient.end();
      fn_parse(res);
    }
    else
    {
      httpclient.end();
      city = "E";
      weather1 = "E";
      temputer = "-";
      Serial.printf("fail to get cityWeather,code:%d\n", http_code);
    }
  }
  return http_code;
}
 