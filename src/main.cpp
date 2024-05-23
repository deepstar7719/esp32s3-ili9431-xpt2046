#include <Arduino.h>
#include "ui/ui.h"
#include "uiport/lv_port_gfx_disp.h"
#include <Wire.h>

#include "nvs_data_handle.h"
#include "lv_disp_flush_Imp.h"

#include "espWifiConfig.h"
#include "heartWeather.h"


#define DIRECT_MODE

/*******************
 *   全局变量、结构体声明
 ********************/
const int reset_Pin = 0; // 设置重置按键引脚,用于删除WiFi信息
const int wifi_LED = 2;  // 设置LED引脚
uint8_t wifi_status = WL_IDLE_STATUS;

global_Time gl_time;
global_Parameter global_Para;
request_Result req_Result;

/*******************
 *   全局类的声明
 ********************/

DNSServer dnsServer;  // 创建dnsServer实例
WebServer server(80); // 开启web服务, 创建TCP SERVER,参数: 端口号,最大连接数
espWifiConfig myWifiConfig(&dnsServer, &server);
heartWeather myWeather("STm9u5f27O-X4vrvO");
ui_handler_cb ui_wifi_hdl;

/*******************
 *   需前置声明的函数
 ********************/


/*******************
 *   setup开始
 ********************/
void setup()
{
  Serial.println("begin setup!");

  // 初始化WIf功能
  myWifiConfig.setApssid("A");
  ui_wifi_hdl.tip_message = &showMessage;
  ui_wifi_hdl.ui_handelr = &wificonnected;
  myWifiConfig.ui_handler_register(&ui_wifi_hdl);

  // put your setup code here, to run once:
  pinMode(wifi_LED, OUTPUT);        // 配置LED口为输出口
  digitalWrite(wifi_LED, LOW);      // 初始灯灭
  pinMode(reset_Pin, INPUT_PULLUP); // 按键上拉输入模式(默认高电平输入,按下时下拉接到低电平)

  // 启动i2c串口

  Wire.begin();
  Wire.setPins(8, 9);
  Serial.begin(115200); // Set to a high rate for fast image transfer to a PC

  lv_port_gfx_Init();
  Serial.print("init gfxdrv done!\n");

  
  ui_init();
  Serial.print("ui_init  done!\n");
  // 一切就绪, 启动LVGL任务
  xTaskNotifyGive(handleTaskLvgl);
  Serial.print("xTaskNotifyGive handleTaskLvgl done!\n");


  delay(1000);

  if (readlastdata(&global_Para))
  {
    String lstr = "正在尝试连接WIFI" + global_Para.wifi_ssid;
    _ui_label_set_property(ui_lbMessage, 0, lstr.c_str());

    Serial.print(lstr.c_str());
    Serial.print("\n");
    delay(900);
    myWifiConfig.connectToWifi();
  }
  else
  {
    delay(1000);
    String lstr = "请按以上说说配网，尝试连接您家的WIFI！";
    _ui_label_set_property(ui_lbMessage, 0, lstr.c_str());

    Serial.println(lstr.c_str());
    Serial.print("\n");
    myWifiConfig.wifiConfigured();
  }
}

void loop()
{

  //  长按5秒(P0)清除网络配置信息
  if (!digitalRead(reset_Pin))
  {
    delay(5000);
    if (!digitalRead(reset_Pin))
    {
      Serial.print("\n按键已长按5秒,正在清空网络连保存接信息.\n");
      myWifiConfig.restoreWifi(); // 删除保存的wifi信息
      eraserData();
      ESP.restart(); // 重启复位esp32
      Serial.print("已重启设备.\n");
    }
  }

  // dnsServer.processNextRequest();  // 检查客户端DNS请求
  // server.handleClient();           // 检查客户端(浏览器)http请求
  // myWifiConfig.checkConnect(true); // 检测网络连接状态，参数true表示如果断开重新连接

  delay(30);
}
