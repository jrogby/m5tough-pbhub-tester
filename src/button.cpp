#include "main.h"


static constexpr const char* const names[] = { "none", "wasHold", "wasClicked", "wasPressed", "wasReleased" };

// M5Tough BtgPWR test
void TestBtnPWR(){

  int state = M5.BtnPWR.wasHold() ? 1
            : M5.BtnPWR.wasClicked() ? 2
            : M5.BtnPWR.wasPressed() ? 3
            : M5.BtnPWR.wasReleased() ? 4
            : 0;

  if (state)
  {
    M5.Speaker.tone(391.995, 100);
    ESP_LOGI("loop", "BtnPWR:%s", names[state]);
    M5.Lcd.printf("BtnPWR:%s\n", names[state]);
  }
}