

#if !defined(__LV_DISP_IMP__)
#define __LV_DISP_IMP__
#include <Arduino.h>
#include "ui/ui.h"
uint32_t green = 0x0ACF00;
uint32_t blue = 0x0A64A4;
uint32_t orange = 0xFF9000;
uint32_t red = 0xFD0D06;
uint32_t deep_blue = 0x03406A;

lv_img_dsc_t wl_icon[] = {ui_img_black_wl_0_icon_png,
                          ui_img_black_wl_1_icon_png,
                          ui_img_black_wl_2_icon_png,
                          ui_img_black_wl_3_icon_png,
                          ui_img_black_wl_4_icon_png,
                          ui_img_black_wl_5_icon_png,
                          ui_img_black_wl_6_icon_png,
                          ui_img_black_wl_7_icon_png,
                          ui_img_black_wl_8_icon_png
};

#endif // __LV_DISP_IMP__
