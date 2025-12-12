# ESP32-2432S032C Counter App - Complete Project Status

## 📋 Project Overview
Creating a counter/timer app for the ESP32-2432S032**C** (ESP32-C3 variant) with 3.2" touchscreen display.

---

## 🔍 Critical Discovery: Device Identification

### What We Thought vs. What It Is
| Aspect | Initial Assumption | **Actual Device** |
|--------|-------------------|-------------------|
| Display Driver | GC9A01 | **ST7789** |
| Resolution | 240x240 (round) | **320x240** (rectangular) |
| Chip | ESP32 (Xtensa) | **ESP32-C3** (RISC-V) |
| Backlight Pin | GPIO 3 | **GPIO 19** ← Discovered via pin scanner! |

### How We Found GPIO 19
- Uploaded pin scanner that tested all possible GPIO pins
- Backlight blinked at 53 seconds into a 57-second cycle
- Calculation: 53s ÷ (57s / 15 pins) ≈ 14th pin = GPIO 19 ✅

---

## ✅ Correct Hardware Configuration

### Display Pins (ST7789 320x240)
```c
TFT_MOSI  = GPIO 13  // SPI Data
TFT_SCLK  = GPIO 14  // SPI Clock
TFT_MISO  = GPIO 12  // SPI MISO
TFT_CS    = GPIO 15  // Chip Select
TFT_DC    = GPIO 2   // Data/Command
TFT_RST   = -1       // Not connected
TFT_BL    = GPIO 19  // ⭐ BACKLIGHT (KEY FINDING)
```

### Touch Controller Pins (CST816D - if present)
```c
TOUCH_SDA = GPIO 4
TOUCH_SCL = GPIO 5
TOUCH_INT = GPIO 0
TOUCH_RST = GPIO 1
```

### Display Specifications
- **Driver**: ST7789
- **Resolution**: 320x240 pixels
- **Orientation**: Landscape (use `rotation = 1`)
- **Color Order**: BGR (not RGB)
- **SPI Speed**: 40MHz (safe), 80MHz (max)

---

## 📁 Current Directory Structure

```
/Users/tob/Programming/HildesTidsDings/
├── 3.2inch_ESP32-2432S032/        # Manufacturer sample code
│   ├── 1-Demo/
│   ├── 2-Specification/
│   ├── 5-Schematic/
│   └── 8-Burn operation/
│       └── Burn files/
│           └── 3.2C-LvglWidgets-C.bin  # Factory firmware for testing
│
├── docs/
│   ├── PROGRESS_SUMMARY.md        # Old summary (outdated paths)
│   └── spec.prd                   # Product requirements
│
├── include/
│   ├── lv_conf.h                  # LVGL configuration
│   ├── timer_fsm.h                # Timer state machine (complete)
│   └── ui_theme.h                 # Neomorphic theme (complete)
│
├── src/
│   └── main.cpp                   # ⚠️ WRONG CONFIG - needs update
│
├── reference/
│   └── 3.2inch_ESP32-2432S032/    # Backup of samples
│       └── counter_app.ino        # Old counter app code
│
├── platformio.ini                 # ⚠️ WRONG CONFIG - needs update
├── Screens.af                     # Affinity Designer UI mockup
├── Screens.png                    # UI design reference
└── README.md
```

---

## ⚠️ Files That Need Updating

### 1. **platformio.ini** - WRONG CONFIGURATION
**Current (Incorrect)**:
```ini
-DGC9A01_DRIVER=1          # ❌ Wrong driver
-DTFT_WIDTH=240             # ❌ Wrong resolution
-DTFT_HEIGHT=240            # ❌ Wrong resolution  
-DTFT_MOSI=7                # ❌ Wrong pin
-DTFT_SCLK=6                # ❌ Wrong pin
-DTFT_CS=10                 # ❌ Wrong pin
-DTFT_BL=3                  # ❌ WRONG BACKLIGHT PIN!
```

**Should Be (Correct)**:
```ini
-DST7789_DRIVER=1           # ✅ Correct driver
-DTFT_WIDTH=240             # ✅ Physical width
-DTFT_HEIGHT=320            # ✅ Physical height
-DTFT_MOSI=13               # ✅ Correct pin
-DTFT_SCLK=14               # ✅ Correct pin
-DTFT_CS=15                 # ✅ Correct pin
-DTFT_BL=19                 # ✅ CORRECT BACKLIGHT!
-DTFT_RGB_ORDER=TFT_BGR     # ✅ Color order
```

### 2. **src/main.cpp** - WRONG BACKLIGHT PIN
Line 9-11: Uses GPIO 3 instead of GPIO 19 ❌

---

## 📝 Implementation Status

### ✅ Complete Components
- [x] Timer FSM (`timer_fsm.h`) - Full state machine for count up/down
- [x] UI Theme (`ui_theme.h`) - Neomorphic design system
- [x] LVGL Config (`lv_conf.h`) - Display library configuration
- [x] Pin identification - GPIO 19 backlight discovered
- [x] Sample code reference - All manufacturer examples available

### ⚠️ Needs Update
- [ ] **platformio.ini** - Update to ST7789 + correct pins
- [ ] **src/main.cpp** - Update to GPIO 19 backlight + 320x240
- [ ] **Timer FSM implementation (.c file)** - Missing, only .h exists
- [ ] **UI Theme implementation (.c file)** - Missing, only .h exists  
- [ ] **UI Presets** - Countdown preset selector
- [ ] **Full counter app** - Integrate all components

### 📋 TODO List
1. **Fix Configuration** (URGENT)
   - Update `platformio.ini` with ST7789 + GPIO 19
   - Update `main.cpp` with correct pins
   
2. **Test Display**
   - Upload simple color test
   - Verify GPIO 19 backlight works
   - Confirm ST7789 driver works
   
3. **Restore Missing Code**
   - Create `src/timer_fsm.c` (implementation)
   - Create `src/ui_theme.c` (implementation)
   - Create `src/ui_presets.c` (preset selector)
   
4. **Build Counter App**
   - Integrate timer + UI + LVGL
   - Test count up/down modes
   - Add preset timers (1m, 3m, 5m, 10m)

---

## 🚨 Current Blocker

**Cannot upload new code** - Old pin scanner still running on device.

### Solution: Enter Bootloader Mode
```bash
1. Unplug USB cable
2. Wait 10 seconds (full power down)
3. Press and HOLD the BOOT button
4. While holding BOOT, plug USB back in
5. Keep holding BOOT for 5 more seconds
6. Release BOOT
7. Upload immediately:
   cd /Users/tob/Programming/HildesTidsDings
   ~/.platformio/penv/bin/pio run --target upload
```

---

## 🔌 Upload Command
```bash
cd /Users/tob/Programming/HildesTidsDings
~/.platformio/penv/bin/pio run --target upload
```

**Device Port**: `/dev/cu.usbmodem______1` (may change)

---

## 📚 Reference Materials

### Manufacturer Documentation
- **Location**: `3.2inch_ESP32-2432S032/`
- **Specs**: `2-Specification/ESP32-2432S032 Specifications-EN.pdf`
- **Schematics**: `5-Schematic/ESP32-2432S032-MCU-V1.0.jpg`
- **User Manual**: `6-User_Manual/Getting started 3.2.pdf`
- **Factory Firmware**: `8-Burn operation/Burn files/3.2C-LvglWidgets-C.bin`

### Sample Code Location
- **TFT Examples**: `1-Demo/Demo_Arduino/3_3-1_TFT_HelloWorld/`
- **LVGL Examples**: `1-Demo/Demo_Arduino/7_2LvglMusic3.2_gt911/`
- **Libraries**: `1-Demo/Demo_Arduino/Libraries/TFT_eSPI_original/`

### Pin Confirmation Source
File: `1-Demo/Demo_Arduino/Libraries/TFT_eSPI_original/User_Setup.h`
```c
#define TFT_CS   15
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_DC   2
#define TFT_BL   27  // ← Sample says 27, but our C variant uses 19!
```

**Note**: The "C" variant (ESP32-C3 chip) has different pins than the standard ESP32 version!

---

## 🎯 Next Immediate Steps

1. **Fix platformio.ini** - Update all pins to correct values
2. **Fix main.cpp** - Change GPIO 3 → GPIO 19
3. **Enter bootloader mode** - Follow 10-second unplug method
4. **Upload and test** - Verify display shows colors
5. **Build full counter app** - Once hardware confirmed working

---

## 📊 Discovery Timeline

1. ❌ Assumed round display (GC9A01, 240x240)
2. 🔍 Found manufacturer samples (ESP32-2432S032)
3. ✅ Identified ST7789 320x240 display
4. ✅ Identified ESP32-C3 chip (not standard ESP32)
5. 🔬 Created pin scanner to find backlight
6. ✅ **Discovered GPIO 19 backlight** (53s mark in cycle)
7. ⚠️ Upload blocked by running scanner
8. 📋 **Current state**: Ready to upload with correct config

---

**Last Updated**: Nov 30, 2025
**Status**: Configuration identified, ready to fix and upload
**Blocker**: Need bootloader mode to upload new firmware

