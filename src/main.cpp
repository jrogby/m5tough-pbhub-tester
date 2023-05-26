#include "main.h"
#include "sound.h"
#include "PbHub.h"

PbHub pbHub;
uint8_t hub_ports[6] = {PBHUB_PORT0_ADDR, PBHUB_PORT1_ADDR, PBHUB_PORT2_ADDR, PBHUB_PORT3_ADDR, PBHUB_PORT4_ADDR, PBHUB_PORT5_ADDR};
#define X_OFFSET 10
#define Y_OFFSET 18

uint32_t loopCount = 0;
bool drawReady;

void setup(void)
{
  auto cfg = M5.config();
  cfg.serial_baudrate = 9600; // default=115200
  cfg.clear_display = true;   // default=true. clear the screen when begin.
  cfg.output_power = true;    // default=true. use external port 5V output.
  cfg.internal_rtc = true;    // default=true. use internal RTC.
  cfg.internal_spk = true;    // default=true. use internal speaker.
  cfg.external_rtc = true;    // default=false. use Unit RTC.
  cfg.led_brightness = 255;
  M5.begin(cfg);

  xTaskCreatePinnedToCore(soundTask, "soundTask", 4096, &soundParam, 0, &soundParam.handle, 0);

  setupDisplay();

  pbHub.begin();
}

// BtnPWR hold: Show/hide console
// BtnPWR click: Toggle status screens (analog, digital, specific sensor, ..)

void loop(void)
{
  vTaskDelay(1);
  M5.update();
  ++loopCount;
  TestBtnPWR();

  M5.Lcd.beginTransaction();
  M5.Lcd.clear(TFT_DARKGRAY);
  for (int i = 0; i < 6; i++)
  {
    M5.Lcd.setCursor(0, (i * 2) * Y_OFFSET);
    M5.Lcd.printf("PortB%d:A=%d", i, pbHub.b_analog(hub_ports[i]));

    M5.Lcd.setCursor(X_OFFSET + 120, (i * 2) * Y_OFFSET);
    M5.Lcd.printf("D=%d", pbHub.b_digital(hub_ports[i]));
  }
  M5.Lcd.endTransaction();
}
