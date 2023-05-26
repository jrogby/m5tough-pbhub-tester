#include "main.h"


void drawBackground(void);


void setupDisplay() {
  M5.Lcd.setFont(&fonts::Font2);
  M5.Lcd.setBaseColor(TFT_DARKGRAY);
  M5.Lcd.setTextColor(TFT_GREEN, TFT_DARKGRAY);
  //M5.Display.setBrightness(128);

  int textsize = M5.Display.height() / 160;
  if (textsize == 0) { textsize = 1; }
  M5.Display.setTextSize(textsize);

  M5.Lcd.setTextScroll(true);
  M5.Lcd.startWrite();
  drawBackground();
}



void drawBackground(void)
{
  M5.Lcd.fillScreen(TFT_DARKGRAY);
}

void displayHomeCallback(const void*) {
    uint16_t x = 15;
    uint16_t y = M5.Lcd.height() / 2 - 30;
    M5.Lcd.fillScreen(TFT_WHITE);
    M5.Lcd.setCursor(x, y);
    M5.Lcd.print("0000");
}
void displayHome() {
    M5.Lcd.setRotation(0);
    M5.Lcd.setFont(&FreeMonoBold18pt7b);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(TFT_BLACK);
}
