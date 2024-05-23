

#if !defined(_LV_DISP_FLUSH_IMP_)
#define _LV_DISP_FLUSH_IMP_
#include <Arduino.h>
#include "ui/ui.h"
#include "espWifiConfig.h"
//#include <esp_sntp.h>

const uint32_t sty_green = 0x0ACF00;
const uint32_t sty_blue = 0x0A64A4;
const uint32_t sty_orange = 0xFF9000;
const uint32_t sty_red = 0xFD0D06;
const uint32_t sty_deep_blue = 0x03406A;



typedef struct
{
        int hour = 0;
        int minute = 0;
        int second = 0;
        int date=  0;
        int month = 0;
        int year = 0;
        int temperature = 0;
        int wday;
        String syear;
        String smonth;
        String sdate;
        String shour;
        String sminute;
        String ssecond;
        String week;
        String stime;

} global_Time;


void initTimer(void);



extern lv_obj_t * currentScreen;
void showMessage(const char *msg);
int getNtpTimeL(tm &timeinfo);
void configTimeL();
 
void lvUpdateUIElements();

void wificonnected(wl_status_t wl_status);


#endif // _LV_DISP_FLUSH_IMP_
