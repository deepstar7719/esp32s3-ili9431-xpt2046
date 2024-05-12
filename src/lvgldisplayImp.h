

#if !defined(__LV_DISP_IMP__)
#define __LV_DISP_IMP__
#include <Arduino.h>
#include "ui/ui.h"
#include "espWifiConfig.h"
#include "nvs_data_handle.h"

const uint32_t sty_green = 0x0ACF00;
const uint32_t sty_blue = 0x0A64A4;
const uint32_t sty_orange = 0xFF9000;
const uint32_t sty_red = 0xFD0D06;
const uint32_t sty_deep_blue = 0x03406A;





void showMessage(const char *msg);



#endif // __LV_DISP_IMP__
