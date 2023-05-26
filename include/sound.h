#pragma once

#include "main.h"

#ifndef M5TOOLS_I2S_COMM_FORMAT
#define M5TOOLS_I2S_COMM_FORMAT I2S_COMM_FORMAT_I2S
#endif

#define CONFIG_I2S_BCK_PIN 12
#define CONFIG_I2S_LRCK_PIN 0
#define CONFIG_I2S_DATA_PIN 2
#define CONFIG_I2S_DATA_IN_PIN 34

#define Speak_I2S_NUMBER I2S_NUM_0
#define MODE_MIC 0
#define MODE_SPK 1
#define I2S_DATA_LEN 60

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


struct sound_param_t
{
  xTaskHandle handle = nullptr;
  const uint8_t* data = nullptr;
  size_t len = 0;
  size_t rate = 0;
};
sound_param_t soundParam;


extern const unsigned char gWav_Click[];
extern const unsigned char gWav_Error[];


void setSpeaker(int sampleRate = 16000)
{
  i2s_driver_uninstall(Speak_I2S_NUMBER);

  i2s_config_t i2s_config = {
    .mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate          = sampleRate,
    .bits_per_sample      = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format       = I2S_CHANNEL_FMT_ALL_RIGHT,
    .communication_format = M5TOOLS_I2S_COMM_FORMAT,
    .intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count        = 2,
    .dma_buf_len          = I2S_DATA_LEN,
    .use_apll             = false,
    .tx_desc_auto_clear   = true,
    .fixed_mclk           = 0
  };

  auto res = i2s_driver_install(Speak_I2S_NUMBER, &i2s_config, 0, nullptr);
  ESP_LOGI("main", "i2s_driver_install:%d", res);

  i2s_pin_config_t tx_pin_config = {
    .bck_io_num     = CONFIG_I2S_BCK_PIN,
    .ws_io_num      = CONFIG_I2S_LRCK_PIN,
    .data_out_num   = CONFIG_I2S_DATA_PIN,
    .data_in_num    = CONFIG_I2S_DATA_IN_PIN,
  };
  res = i2s_set_pin(Speak_I2S_NUMBER, &tx_pin_config);
  ESP_LOGI("main", "i2s_set_pin:%d", res);
  res = i2s_set_clk(Speak_I2S_NUMBER, sampleRate, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
  ESP_LOGI("main", "i2s_set_clk:%d", res);
  res = i2s_zero_dma_buffer(Speak_I2S_NUMBER);
  ESP_LOGI("main", "i2s_zero_dma_buffer:%d", res);
}

static void IRAM_ATTR soundTask(void* sound_param)
{
  auto param = (sound_param_t*)sound_param;
  param->rate = 16000;
  int prevSampleRate = 0;
  // I2S
  int16_t data[I2S_DATA_LEN];
  for (;;)
  {
    sound_param_t p = *param;
//    play(param->data, param->len, param->rate);

    if (prevSampleRate != p.rate)
    {
      prevSampleRate = p.rate;
      setSpeaker(p.rate);
      M5.Power.Axp192.bitOn(0x94, 0x04); // speaker on
    }

    // Write Speaker
    size_t bytes_written = 0;

    int index = 0;

  //  i2s_zero_dma_buffer(Speak_I2S_NUMBER);
    memset(data, 0, I2S_DATA_LEN << 1);
    for (int i = 0; i < 2; ++i)
    {
      i2s_write(Speak_I2S_NUMBER, data, I2S_DATA_LEN*2, &bytes_written, portMAX_DELAY);
    }
    for (int i = 0; i < p.len; i++)
    {
      int16_t val = p.data[i];
      data[index] = (val - 128) * 64;
      index += 1;
      if (I2S_DATA_LEN <= index)
      {
        index = 0;
        i2s_write(Speak_I2S_NUMBER, data, I2S_DATA_LEN*2, &bytes_written, portMAX_DELAY);
      }
    }
    memset(&data[index], 0, (I2S_DATA_LEN - index) * 2);
    i2s_write(Speak_I2S_NUMBER, data, I2S_DATA_LEN * 2, &bytes_written, portMAX_DELAY);
    if (index <= I2S_DATA_LEN)
    {
      memset(data, 0, index * 2);
    }

    for (int i = 0; i < 4; ++i)
    {
      i2s_write(Speak_I2S_NUMBER, data, I2S_DATA_LEN*2, &bytes_written, portMAX_DELAY);
    }
    ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
  }
}

void clickSound(void)
{
  soundParam.data = gWav_Click;
  soundParam.len  = 112;
  soundParam.rate = 16000;
  xTaskNotifyGive(soundParam.handle);
}

void errorSound(void)
{
  soundParam.data = gWav_Error;
  soundParam.len  = 3584;
  soundParam.rate = 16000;
  xTaskNotifyGive(soundParam.handle);
}
