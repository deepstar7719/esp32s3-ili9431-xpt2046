
#include <Arduino.h>
#include "touch.h"
#include "espWifiConfig.h"
#include <Preferences.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
 

const int reset_Pin = 0; // 设置重置按键引脚,用于删除WiFi信息
const int wifi_LED = 2;  // 设置LED引脚

DNSServer dnsServer;  // 创建dnsServer实例
WebServer server(80); // 开启web服务, 创建TCP SERVER,参数: 端口号,最大连接数

espWifiConfig myWifiConfig(&dnsServer, &server);

Preferences preferences;

struct global_Parameter
{
   String wifi_ssid = "";
   String wifi_pass = "";
   String reqUserKey = "21"; // 私钥
   String city = "12";       // 城市
   String reqUnit = "c";     // 摄氏
};
global_Parameter global_Para;

static lv_disp_draw_buf_t draw_buf;                 // 定义显示器变量
static lv_color_t buf[TFT_WIDTH * TFT_HEIGHT / 10]; // 定义刷新缓存

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
 

void savemyData();
bool readlastdata();

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
   uint32_t w = (area->x2 - area->x1 + 1);
   uint32_t h = (area->y2 - area->y1 + 1);

   tft.startWrite();                                        // 使能写功能
   tft.setAddrWindow(area->x1, area->y1, w, h);             // 设置填充区域
   tft.pushColors((uint16_t *)&color_p->full, w * h, true); // 写入颜色缓存和缓存大小
   tft.endWrite();                                          // 关闭写功能

   lv_disp_flush_ready(disp); // 调用区域填充颜色函数
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
   uint16_t touchX, touchY;

   bool touched = tft.getTouch(&touchX, &touchY, 600);

   if (!touched)
   {
      data->state = LV_INDEV_STATE_REL;
   }
   else
   {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touchX;
      data->point.y = touchY;

      Serial.print("Data x ");
      Serial.println(touchX);

      Serial.print("Data y ");
      Serial.println(touchY);
   }
}
// 显示欢迎页面
void welcome()
{
   Serial.println("显示欢迎页面.");
   static lv_style_t style;
   lv_style_set_text_color(&style, lv_palette_main(LV_PALETTE_RED)); // 设置样式文本字颜色、

   lv_obj_t *label;                       // 创建对象
   label = lv_label_create(lv_scr_act()); // 获取默认屏幕
   lv_obj_set_style_text_font(label, &lv_font_simsun_16_cjk, LV_PART_MAIN | LV_STATE_DEFAULT);
   // lv_obj_add_style(label, &style, 0);                        // 将样式添加到文字对象中
   lv_label_set_text(label, "你好世界!"); // 显示文字
   lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
   delay(3000);
}
void setup()
{
   // put your setup code here, to run once:
   pinMode(wifi_LED, OUTPUT);        // 配置LED口为输出口
   digitalWrite(wifi_LED, LOW);      // 初始灯灭
   pinMode(reset_Pin, INPUT_PULLUP); // 按键上拉输入模式(默认高电平输入,按下时下拉接到低电平)
   Serial.begin(115200);

   tft.init();         // 初始化
   tft.begin();        /* TFT init */
   tft.setRotation(1); // 屏幕旋转方向（横向）
   lv_init();

   /*Set the touchscreen calibration data,
     the actual data for your display can be acquired using
     the Generic -> Touch_calibrate example from the TFT_eSPI library*/
   uint16_t calData[5] = {275, 3620, 264, 3532, 1};
   tft.setTouch(calData);
   lv_disp_draw_buf_init(&draw_buf, buf, NULL, TFT_WIDTH * TFT_HEIGHT / 10);
   /*Initialize the display*/
   static lv_disp_drv_t disp_drv;
   lv_disp_drv_init(&disp_drv);
   /*Change the following line to your display resolution*/
   disp_drv.hor_res = TFT_HEIGHT;
   disp_drv.ver_res = TFT_WIDTH;
   disp_drv.flush_cb = my_disp_flush;
   disp_drv.draw_buf = &draw_buf;
   lv_disp_drv_register(&disp_drv);

   /*Initialize the (dummy) input device driver*/
   static lv_indev_drv_t indev_drv;
   lv_indev_drv_init(&indev_drv);
   indev_drv.type = LV_INDEV_TYPE_POINTER;
   indev_drv.read_cb = my_touchpad_read;
   lv_indev_drv_register(&indev_drv);
   welcome();
   delay(3000);

   /*
   if (readlastdata())
   {
      myWifiConfig.connectToWifi();
   }
   else
   {
      myWifiConfig.wifiConfigured();
      if (WiFi.status() == WL_CONNECTED)
      {
         //定位，获取ctiy

         //保存信息
         savemyData();
         //更新心知天气

      }
   }
   */
}

void loop()
{
   // // 长按5秒(P0)清除网络配置信息
   // if (!digitalRead(reset_Pin))
   // {
   //    delay(5000);
   //    if (!digitalRead(reset_Pin))
   //    {
   //       Serial.println("\n按键已长按5秒,正在清空网络连保存接信息.");
   //       myWifiConfig.restoreWifi(); // 删除保存的wifi信息
   //       ESP.restart();              // 重启复位esp32
   //       Serial.println("已重启设备.");
   //    }
   // }

   // dnsServer.processNextRequest();  // 检查客户端DNS请求
   // server.handleClient();           // 检查客户端(浏览器)http请求
   // myWifiConfig.checkConnect(true); // 检测网络连接状态，参数true表示如果断开重新连接

   // delay(30);
}
// 保存数据
void savemyData()
{
   Serial.println("正在保存信息");
   preferences.begin("wifi", false);
   preferences.putString("ssid", global_Para.wifi_ssid); // 保存WIFI账号密码
   preferences.putString("pasd", global_Para.wifi_pass);
   preferences.putString("reqUserKey", global_Para.reqUserKey);
   preferences.putString("city", global_Para.city);
   preferences.end();
}
bool readlastdata()
{
   Serial.printf("进入readlastdata函数\n");
   preferences.begin("wifi", false);
   if (!preferences.isKey("ssid"))
   {
      Serial.println("未找到ssid..");
      preferences.end();
      return false;
   }
   else
   {
      global_Para.wifi_ssid = preferences.getString("ssid", "none");
      global_Para.wifi_pass = preferences.getString("pasd", "none");
      global_Para.reqUserKey = preferences.getString("reqUserKey", "");
      global_Para.city = preferences.getString("city", ""); // 在EEPROM中找地区信息
      preferences.end();
      Serial.printf("ssid = %s\n", global_Para.wifi_ssid);
      Serial.printf("password = %s\n", global_Para.wifi_pass);
      Serial.printf("reqUserKey = %s\n", global_Para.reqUserKey);
      Serial.printf("city = %s\n", global_Para.city);
      return true;
   }
}