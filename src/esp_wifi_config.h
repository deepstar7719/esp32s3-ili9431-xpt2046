
#if !defined(_ESP_WIFI_CONFIG_)
#define _ESP_WIFI_CONFIG_

#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <ESPmDNS.h>      //用于设备域名 MDNS.begin("esp32")
#include <esp_wifi.h>     //用于esp_wifi_restore() 删除保存的wifi信息


void handleRoot();
void handleConfigWifi();
void handleNotFound();
void restoreWifi();
void checkConnect(bool reConnect);
void connectToWifi();
void wifiConfigured();

#endif