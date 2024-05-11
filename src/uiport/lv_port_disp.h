#ifndef LV_PORT_DISP_H_
#define LV_PORT_DISP_H_

#include "TFT_eSPI.h"
#include "lvgl.h"

#define DISP_HOR_RES TFT_HEIGHT
#define DISP_VER_RES TFT_WIDTH
#define DISP_BUF_SIZE (DISP_HOR_RES * DISP_VER_RES/4)

extern TaskHandle_t handleTaskLvgl;
void lv_port_tftespi_Init();
void lv_port_disp_init(TFT_eSPI* scr);

#endif
 