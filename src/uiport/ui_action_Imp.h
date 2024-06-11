#if !defined(__UI_ACTION_IMP__)
#define __UI_ACTION_IMP__
#include "ui_disp_update_Imp.h"




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

 

void initRTCTimer(void);

void uiChangeScreen(int nindex, lv_scr_load_anim_t fademode);

void changeWifiStatus(uint8_t wl_wifistatus);

char *intToCharPtr(int value);
int getNtpTimeL( );


void configTimeL(); 

void wifiConnected(wl_status_t wl_status);
 
#endif //__UI_ACTION_IMP__
