

#if !defined(_LV_DISP_FLUSH_IMP_)
#define _LV_DISP_FLUSH_IMP_
#include <Arduino.h>
#include "ui/ui.h"

const uint32_t sty_green = 0x0ACF00;
const uint32_t sty_blue = 0x0A64A4;
const uint32_t sty_orange = 0xFF9000;
const uint32_t sty_red = 0xFD0D06;
const uint32_t sty_deep_blue = 0x03406A;

extern lv_obj_t * currentScreen;
void initTimer(void);
void showMessage(const char *msg);


















#endif // _LV_DISP_FLUSH_IMP_
