#include "lvgldisplayImp.h"
/*
// 定时器1中断函数
void tickerIsr()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(wifi_LED, !(digitalRead(wifi_LED)));
  }
  else
  {
    digitalWrite(wifi_LED, 1);
  }
  timeClient.update(); // 更新时间
  hour = timeClient.getHours();
  minute = timeClient.getMinutes();
  sec = timeClient.getSeconds();
  count++;
  count1++;
  if (count1 > 0 && count1 <= 5)
  {
    mode = 1;
  }
  else if (count1 > 5 && count1 <= 10)
  {
    mode = 2;
  }
  else if (count1 > 10 && count1 <= 15)
  {
    mode = 3;
  }
  else
  {
    count1 = 0;
  }
  if (count > 300)
  { // 每5分钟复位一次，重新获取时间、天气
    Serial.println("重新获取时间、天气....");
    count = 0;
    requestsWeatherTime = true;
  }
}
*/