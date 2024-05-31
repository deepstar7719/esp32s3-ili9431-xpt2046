

#if !defined(_LV_DISP_FLUSH_IMP_)
#define _LV_DISP_FLUSH_IMP_
#include <Arduino.h>
#include "ui/ui.h"
#include "espWifiConfig.h"
//#include <esp_sntp.h>




void showMessage(const char *msg);

 
void lvUpdateUIElements();



void lv_scwelcome_update_tip();

void lv_update_wifi_status(int wf_status);

void lv_sctoday_update_weather(String &city, String &wheather, String &wind, const lv_img_dsc_t *wicon);

void lv_update_RTC_Time(String &sdate, String &hh, String &mm, String &ss);

#endif // _LV_DISP_FLUSH_IMP_
