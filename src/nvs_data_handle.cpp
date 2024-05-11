
#include "nvs_data_handle.h"

// 保存数据
void savemyData(global_Parameter para)
{
        Preferences preferences;
        Serial.println("正在保存信息");
        preferences.begin("wifi", false, "nvs");
        preferences.putString("ssid", para.wifi_ssid); // 保存WIFI账号密码
        preferences.putString("pasd", para.wifi_pass);
        preferences.putString("reqUserKey", para.reqUserKey);
        preferences.putString("city", para.city);
        preferences.end();
}
bool readlastdata(global_Parameter *para)
{
        Preferences preferences;
        Serial.printf("进入readlastdata函数\n");
        preferences.begin("wifi", false, "nvs");
        if (!preferences.isKey("ssid"))
        {
                Serial.println("未找到ssid..");
                preferences.end();
                return false;
        }
        else
        {
                para->wifi_ssid = preferences.getString("ssid", "none");
                para->wifi_pass = preferences.getString("pasd", "none");
                para->reqUserKey = preferences.getString("reqUserKey", "");
                para->city = preferences.getString("city", ""); // 在EEPROM中找地区信息
                preferences.end();
                Serial.printf("ssid = %s\n", para->wifi_ssid);
                Serial.printf("password = %s\n", para->wifi_pass);
                Serial.printf("reqUserKey = %s\n", para->reqUserKey);
                Serial.printf("city = %s\n", para->city);
                return true;
        }
}
// 清楚数据
void eraserData()
{
        Preferences preferences;
        preferences.begin("wifi", false, "nvs");
        preferences.clear();
        preferences.end();
}