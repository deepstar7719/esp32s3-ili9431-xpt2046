#ifndef __ESP_WIFI_CONFIG__
#define __ESP_WIFI_CONFIG__

#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <ESPmDNS.h>  //用于设备域名 MDNS.begin("esp32")
#include <esp_wifi.h> //用于esp_wifi_restore() 删除保存的wifi信息

// const char* AP_PASS  = "";               //设置AP热点密码

// 定义根目录首页网页HTML源代码
#define ROOT_HTML "<!DOCTYPE html><html lang=\"zh\"><head><meta charset=\"UTF-8\"><title>WIFI Config by Lotware</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>\
<style type=\"text/css\">.input{display: block; margin-top: 10px;}.input span{width: 100px; float: left; float: left; height: 36px; line-height: 36px;}.input input{height: 30px;width: 200px;}.btn{width: 120px; height: 35px; background-color: #000000; border:0px; color:#ffffff; margin-top:15px; margin-left:100px;}</style>\
<body><form method=\"POST\" action=\"configwifi\">\
<label class=\"input\"><span>WiFi SSID</span><input type=\"text\" name=\"ssid\" value=\"\"></label>\
<label class=\"input\"><span>WiFi PASS</span><input type=\"text\"  name=\"pass\"></label>\
<input class=\"btn\" type=\"submit\" name=\"submit\" value=\"保存\"> <p><span>附近的WiFi:</P></form>"
// 定义成功页面HTML源代码
#define SUCCESS_HTML "<html lang=\"zh\"><head><meta charset=\"UTF-8\"><body><font size=\"10\">WIFI链接成功！<br />请手动关闭本页面</font></body></html>"

typedef struct ui_callback_handler
{
  //std::function<void(wl_status_t, const char *)> THandlerFunction;
  void(* tip_message)(const char *msg);
  void(* ui_handelr)(wl_status_t wl_status);
}ui_handler_cb;

class espWifiConfig
{

protected:
//typedef std::function<void(wl_status_t, const char *)> THandlerFunction;
 


  ui_handler_cb *uihandler = NULL;

protected:
  String _scanNetworksID = ""; // 用于储存扫描到的WiFi ID
  int _timeOut_s = 15;         // WiFi连接超时时间，单位秒
  String _wifi_ssid = "";      // 暂时存储wifi账号密码
  String _wifi_pass = "";      // 暂时存储wifi账号密码

  const int _led_PIN = 2;
  String _ap_SSID = "ESP32_"; // 设置AP热点名称
  IPAddress _apIP;            // 设置AP的IP地址

  DNSServer *_dnsServer = nullptr; // 创建dnsServer实例
  WebServer *_server = nullptr;    // 开启web服务, 创建TCP SERVER,参数: 端口号,最大连接数

public:
  espWifiConfig(DNSServer *dnsServer, WebServer *server);
  
  virtual ~espWifiConfig();

  void setApssid(String ssid)
  {
    _ap_SSID = _ap_SSID + ssid;
  };
  void ui_handler_register(ui_handler_cb *handler);

  void setWifiInfo(String &ssid, String &pass)
  {
    _wifi_ssid = ssid;
    _wifi_pass = pass;
  };
  void getWifiInfo(String &ssid, String &pass)
  {
    ssid = _wifi_ssid;
    pass = _wifi_pass;
  };
  void wifiConfigured();
  void connectToWifi();
  void restoreWifi();
  void checkConnect(bool reConnect);
  bool scanWifi();
  void readlastdata();
  void initSoftAP();
  void initDNS();
  void initWebServer();

private:
  void handleRoot();
  void handleConfigWifi();
  void handleNotFound();
};

#endif