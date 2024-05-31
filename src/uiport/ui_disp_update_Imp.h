

#if !defined(_LV_DISP_FLUSH_IMP_)
#define _LV_DISP_FLUSH_IMP_
#include <Arduino.h>
#include "ui/ui.h"
#include "espWifiConfig.h"
 






 
void lvUpdateUIElements();


void lv_all_update_wifi_status(int wf_status);

void lv_all_update_location (String &city);

void lv_all_update_panelTop_Day(String &sdate);


void lv_scwelcome_showMessage(const char *msg);
void lv_scwelcome_update_tip();
void lv_sctoday_update_RTC_Time(  String &hh, String &mm, String &ss);
void lv_sctoday_update_weather( String &wheather, String &wind, const lv_img_dsc_t *wicon);
void lv_scWeather_update_otherday_weather();
#endif // _LV_DISP_FLUSH_IMP_
