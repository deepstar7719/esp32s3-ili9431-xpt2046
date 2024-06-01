// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: sq_esp32_320_240_tft

#include "../ui.h"


// COMPONENT cmPanelWeather

lv_obj_t * ui_cmPanelWeather_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_cmPanelWeather;
    cui_cmPanelWeather = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_cmPanelWeather, 155);
    lv_obj_set_height(cui_cmPanelWeather, 206);
    lv_obj_set_x(cui_cmPanelWeather, -80);
    lv_obj_set_y(cui_cmPanelWeather, 16);
    lv_obj_set_align(cui_cmPanelWeather, LV_ALIGN_CENTER);
    lv_obj_clear_flag(cui_cmPanelWeather, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * cui_ImgIcon;
    cui_ImgIcon = lv_img_create(cui_cmPanelWeather);
    lv_img_set_src(cui_ImgIcon, &ui_img_white_wl_16_sm_png);
    lv_obj_set_width(cui_ImgIcon, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_ImgIcon, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(cui_ImgIcon, -40);
    lv_obj_set_y(cui_ImgIcon, -21);
    lv_obj_set_align(cui_ImgIcon, LV_ALIGN_CENTER);
    lv_obj_add_flag(cui_ImgIcon, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(cui_ImgIcon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * cui_lbtemp;
    cui_lbtemp = lv_label_create(cui_cmPanelWeather);
    lv_obj_set_width(cui_lbtemp, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_lbtemp, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(cui_lbtemp, 33);
    lv_obj_set_y(cui_lbtemp, -26);
    lv_obj_set_align(cui_lbtemp, LV_ALIGN_CENTER);
    lv_label_set_text(cui_lbtemp, "中雨\n12~20℃");
    lv_obj_set_style_text_font(cui_lbtemp, &ui_font_syHeiTi16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_lbDate;
    cui_lbDate = lv_label_create(cui_cmPanelWeather);
    lv_obj_set_width(cui_lbDate, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_lbDate, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(cui_lbDate, -8);
    lv_obj_set_y(cui_lbDate, -73);
    lv_obj_set_align(cui_lbDate, LV_ALIGN_CENTER);
    lv_label_set_text(cui_lbDate, "明天");
    lv_obj_set_style_text_color(cui_lbDate, lv_color_hex(0x0ACF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_lbDate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_lbDate, &ui_font_syHeiTi28, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_lbDesc;
    cui_lbDesc = lv_label_create(cui_cmPanelWeather);
    lv_obj_set_width(cui_lbDesc, 146);
    lv_obj_set_height(cui_lbDesc, 70);
    lv_obj_set_x(cui_lbDesc, 1);
    lv_obj_set_y(cui_lbDesc, 58);
    lv_obj_set_align(cui_lbDesc, LV_ALIGN_CENTER);
    lv_label_set_text(cui_lbDesc, "东北风4~6级，\n降雨量23ml");
    lv_obj_set_style_text_color(cui_lbDesc, lv_color_hex(0x0A64A4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_lbDesc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(cui_lbDesc, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_lbDesc, &ui_font_syHeiTi16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_CMPANELWEATHER_NUM);
    children[UI_COMP_CMPANELWEATHER_CMPANELWEATHER] = cui_cmPanelWeather;
    children[UI_COMP_CMPANELWEATHER_IMGICON] = cui_ImgIcon;
    children[UI_COMP_CMPANELWEATHER_LBTEMP] = cui_lbtemp;
    children[UI_COMP_CMPANELWEATHER_LBDATE] = cui_lbDate;
    children[UI_COMP_CMPANELWEATHER_LBDESC] = cui_lbDesc;
    lv_obj_add_event_cb(cui_cmPanelWeather, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_cmPanelWeather, del_component_child_event_cb, LV_EVENT_DELETE, children);
    ui_comp_cmPanelWeather_create_hook(cui_cmPanelWeather);
    return cui_cmPanelWeather;
}

