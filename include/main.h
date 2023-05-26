#pragma once

#include <M5Unified.h>
#include <M5GFX.h>
#include <StreamString.h>
#include <esp_log.h>


#if __has_include (<esp_idf_version.h>)
 #include <esp_idf_version.h>
 #if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 0, 0)
  #define M5TOOLS_I2S_COMM_FORMAT I2S_COMM_FORMAT_STAND_I2S
 #endif
#endif


extern void setupDisplay();
extern void TestBtnPWR();
extern void canairioInitSensors();
extern void canairioReadSensors();
extern void setupTSL2591();
extern void advancedReadTSL2591();