# ESP32-2432S032C Counter App - Progress Summary

## CRITICAL DISCOVERY ✅
**Your backlight is on GPIO 19** (identified via pin scanner at 53s into 57s cycle)

## Device Configuration
- **Model**: ESP32-2432S032C (C variant with ESP32-C3 chip, NOT standard ESP32)
- **Display**: ST7789 (not GC9A01)
- **Resolution**: 320x240 pixels (not 240x240 round)
- **Chip**: ESP32-C3 (RISC-V architecture)

## Correct Pin Configuration
Based on sample code + pin scanner results:

```
Display (ST7789):
- MOSI: GPIO 13
- SCLK: GPIO 14
- MISO: GPIO 12
- CS: GPIO 15
- DC: GPIO 2
- RST: -1 (not used)
- **BACKLIGHT: GPIO 19** ← KEY FINDING!

PlatformIO Board: esp32-c3-devkitm-1
SPI Frequency: 40MHz
RGB Order: TFT_BGR
```

## Current Status
- ✅ Pin scanner successfully identified backlight (GPIO 19)
- ✅ Code compiles and builds successfully
- ✅ Display test code ready with correct pins
- ❌ **Upload blocked** - old scanner code still running, preventing new uploads

## Next Steps
1. **Get into bootloader mode** to upload display test:
   - Method: Unplug → Wait 10s → Hold BOOT → Plug in → Hold BOOT 5s more → Release
   
2. **Upload display test** (`src/main.cpp` is ready):
   - Will show RED → GREEN → BLUE → "HELLO!" with yellow "ESP32-C3 WORKS!"
   - Uses GPIO 19 for backlight with PWM control
   
3. **Once display works**, build full counter app with:
   - Timer FSM (already written)
   - UI theme (neomorphic design)
   - Preset selector
   - All adapted for 320x240 ST7789 display

## Files Ready
- `/Users/tob/Downloads/project_bundle/platformio.ini` - Configured for ESP32-C3 + ST7789 + GPIO 19
- `/Users/tob/Downloads/project_bundle/src/main.cpp` - Display test with correct pins
- Timer/UI code exists in project history, needs to be restored

## Upload Command
```bash
cd /Users/tob/Downloads/project_bundle
~/.platformio/penv/bin/pio run --target upload
```

## Troubleshooting Notes
- Device appears as `/dev/cu.usbmodem______1` (port name changes)
- BOOT button must be held during upload to enter bootloader mode
- Old code prevents uploads if running - needs hard reset

## Sample Code Location
Original manufacturer samples: `/Users/tob/Downloads/3.2inch_ESP32-2432S032/`
- Contains factory firmware for testing (3.2C-LvglWidgets-C.bin)
- User manual and schematics available

---
**RESUME HERE**: Try bootloader mode method to upload display test, then verify colors appear on screen.



