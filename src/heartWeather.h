
#ifndef __HEART_WEATHER_H__
#define __HEART_WEATHER_H__
#include "HTTPClient.h"
 

class heartWeather
{
protected:
  typedef std::function<void(wl_status_t , const char * )> THandlerFunction;
  THandlerFunction _fn=NULL;

  typedef std::function<int( String )> TParseFunction;
public:

    heartWeather(String  reqUserKey);
    virtual ~heartWeather();
    int _icon;
    int _hour;
    int _minute;
    int _sec;

    int _weatherCode;
    const char *city;
    const char *weather1;
    const char *temputer;

    const char *holiday;
 
   // const char* ntpServer = "ntp1.aliyun.com"; // 阿里云NTP网络时间服务器
    const char *_heartHost = "https://api.seniverse.com"; //心知天气APIhost   
    String _holidayUrl = "http://timor.tech/api/holiday/info/";  //节假日接口
 
private:


    String _today;

    String _reqUserKey = "";   // 私钥    
    String _reqUnit = "c";     // 摄氏
    String _reqRes = "";

public:
    void selectIcon(int i);
    int getNtpTime(tm  timeinfo);
    int requestHoliday(TParseFunction fn_parse);
    int requestsWeather(TParseFunction fn_parse);
   
 
};
#endif