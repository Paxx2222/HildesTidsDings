// ESP32-2424S012C with LovyanGFX
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_GC9A01 _panel_instance;
  lgfx::Bus_SPI _bus_instance;
  lgfx::Light_PWM _light_instance;

public:
  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();
      cfg.spi_host = SPI2_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 40000000;
      cfg.freq_read = 16000000;
      cfg.spi_3wire = false;
      cfg.use_lock = true;
      cfg.dma_channel = SPI_DMA_CH_AUTO;
      cfg.pin_sclk = 6;
      cfg.pin_mosi = 7;
      cfg.pin_miso = -1;
      cfg.pin_dc = 2;
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs = 10;
      cfg.pin_rst = -1;
      cfg.pin_busy = -1;
      cfg.panel_width = 240;
      cfg.panel_height = 240;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = false;
      cfg.invert = true;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = false;
      _panel_instance.config(cfg);
    }

    {
      auto cfg = _light_instance.config();
      cfg.pin_bl = 3;
      cfg.invert = false;
      cfg.freq = 2000;
      cfg.pwm_channel = 0;
      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);
    }

    setPanel(&_panel_instance);
  }
};

LGFX lcd;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== ESP32-2424S012C LovyanGFX ===");
  
  lcd.init();
  lcd.setBrightness(255);
  
  Serial.println("Display initialized!");
  
  lcd.fillScreen(TFT_WHITE);
  Serial.println("WHITE");
  delay(1000);
  
  lcd.fillScreen(TFT_RED);
  Serial.println("RED");
  delay(1000);
  
  lcd.fillScreen(TFT_GREEN);
  Serial.println("GREEN");
  delay(1000);
  
  lcd.fillScreen(TFT_BLUE);
  Serial.println("BLUE");
  delay(1000);
  
  lcd.fillScreen(TFT_BLACK);
  
  // Draw circles
  lcd.fillCircle(120, 120, 100, TFT_RED);
  lcd.fillCircle(120, 120, 60, TFT_GREEN);
  lcd.fillCircle(120, 120, 30, TFT_BLUE);
  
  // Text
  lcd.setTextColor(TFT_WHITE);
  lcd.setTextSize(3);
  lcd.setCursor(50, 100);
  lcd.println("HELLO!");
  
  lcd.setTextSize(2);
  lcd.setCursor(30, 140);
  lcd.setTextColor(TFT_YELLOW);
  lcd.println("LovyanGFX!");
  
  Serial.println("Complete!");
}

void loop() {
  delay(1000);
}
