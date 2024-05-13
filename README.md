# esp32-TFT_eSPI-ILI9431-XPT2046-Touch

#### 软硬介绍
 **   本程序是ESP32-S3+ILI9431(带xpt2046触摸)屏幕，**
- 硬件环境及驱动：
1. 选用esp32-s3-DevKitC-1开发板形，配置开启PSRAM，16Mflash
2. 使用DS3231-RTC时钟模块（带温度）
3. 屏幕为ILI9431芯片。（dev分支为TFT_eSPI驱动，A-gfx分支为GFX驱动）
4. 屏幕带Touch的xpt2046芯片，采用XPT2046_Touchscreen驱动。
 
- 开发环境：
1. vscode + platformio


#### 使用到的组件

- UI界面： 
1. LVGL v8.3.11
2. LVGL界面UI使用SquareLine 1.4.0设计生成
 - 引用的组件：
1. lvgl/lvgl@8.3.11
2. paulstoffregen/XPT2046_Touchscreen@1.4.0
3. bblanchon/ArduinoJson@6.21.5
4. moononournation/GFX Library for Arduino@^1.4.6 	

#### 更新说明：
2024-5-13
1.  A-gfx分支将作为主要开发分支持续开发
2.  增加DS3231-RTC时钟模块的读取 


