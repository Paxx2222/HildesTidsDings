// ESP32-2424S012C Touch Test with CST816D
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <Wire.h>

// CST816D Touch Controller
#define TOUCH_SDA 4
#define TOUCH_SCL 5
#define TOUCH_INT 0
#define TOUCH_RST 1
#define CST816D_ADDR 0x15

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

// CST816D Touch Functions
bool cst816d_init() {
  pinMode(TOUCH_RST, OUTPUT);
  digitalWrite(TOUCH_RST, LOW);
  delay(10);
  digitalWrite(TOUCH_RST, HIGH);
  delay(50);
  
  Wire.begin(TOUCH_SDA, TOUCH_SCL);
  Wire.setClock(400000);
  
  // Check if device responds
  Wire.beginTransmission(CST816D_ADDR);
  byte error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.println("CST816D detected!");
    return true;
  } else {
    Serial.printf("CST816D not found (error: %d)\n", error);
    return false;
  }
}

bool getTouchPoint(int16_t &x, int16_t &y) {
  Wire.beginTransmission(CST816D_ADDR);
  Wire.write(0x00);
  Wire.endTransmission();
  
  Wire.requestFrom(CST816D_ADDR, 7);
  if (Wire.available() >= 7) {
    uint8_t data[7];
    for (int i = 0; i < 7; i++) {
      data[i] = Wire.read();
    }
    
    // CST816S register format:
    // 0x02: number of touch points
    // 0x03: X high byte (bits 3:0)
    // 0x04: X low byte
    // 0x05: Y high byte (bits 3:0)
    // 0x06: Y low byte
    uint8_t touches = data[2];
    
    if (touches > 0 && touches < 10) {
      x = ((data[3] & 0x0F) << 8) | data[4];
      y = ((data[5] & 0x0F) << 8) | data[6];
      return true;
    }
  }
  return false;
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== CST816D Touch Test ===");
  
  // Initialize display
  lcd.init();
  lcd.setBrightness(255);
  lcd.fillScreen(TFT_BLACK);
  
  lcd.setTextColor(TFT_WHITE);
  lcd.setTextSize(2);
  lcd.setCursor(20, 20);
  lcd.println("Touch Test");
  
  // Initialize touch
  if (cst816d_init()) {
    lcd.setCursor(20, 50);
    lcd.setTextColor(TFT_GREEN);
    lcd.println("Touch OK!");
    Serial.println("Touch initialized successfully");
  } else {
    lcd.setCursor(20, 50);
    lcd.setTextColor(TFT_RED);
    lcd.println("Touch ERROR");
    Serial.println("Touch initialization failed");
  }
  
  lcd.setCursor(20, 100);
  lcd.setTextColor(TFT_YELLOW);
  lcd.setTextSize(1);
  lcd.println("Touch screen anywhere");
  
  delay(1000);
}

int lastX = -1;
int lastY = -1;

void loop() {
  int16_t x, y;
  
  if (getTouchPoint(x, y)) {
    
    // Clear previous touch indicator
    if (lastX >= 0 && lastY >= 0) {
      lcd.fillCircle(lastX, lastY, 8, TFT_BLACK);
    }
    
    // Draw new touch indicator
    lcd.fillCircle(x, y, 8, TFT_RED);
    lcd.drawCircle(x, y, 10, TFT_WHITE);
    
    // Display coordinates
    lcd.fillRect(0, 200, 240, 40, TFT_BLACK);
    lcd.setTextColor(TFT_CYAN);
    lcd.setTextSize(2);
    lcd.setCursor(20, 210);
    lcd.printf("X:%3d Y:%3d", x, y);
    
    lastX = x;
    lastY = y;
    
    delay(50);
  } else {
    // No touch detected
    if (lastX >= 0) {
      // Clear touch indicator after release
      delay(500);
      lcd.fillCircle(lastX, lastY, 10, TFT_BLACK);
      lcd.fillRect(0, 200, 240, 40, TFT_BLACK);
      lastX = -1;
      lastY = -1;
    }
  }
  
  delay(10);
}
