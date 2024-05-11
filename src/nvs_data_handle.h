#if !defined(__NVS_DATA_HANLE__)
#define __NVS_DATA_HANLE__

#include <Arduino.h>
#include <Preferences.h>

struct global_Parameter
{
  String wifi_ssid = "";
  String wifi_pass = "";
  String reqUserKey = "STm9u5f27O-X4vrvO"; // 私钥
  String city = "12";                      // 城市
  String reqUnit = "c";                    // 摄氏
};





void savemyData(global_Parameter para);
bool readlastdata(global_Parameter *para);

void eraserData();

#endif