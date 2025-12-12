# Fixes Needed - Quick Reference

## ⚠️ CRITICAL ISSUES

### Issue #1: platformio.ini has WRONG pins
**File**: `/Users/tob/Programming/HildesTidsDings/platformio.ini`

**Lines 17-29** currently say:
```ini
-DGC9A01_DRIVER=1      # ❌ WRONG - Should be ST7789_DRIVER
-DTFT_HEIGHT=240       # ❌ WRONG - Should be 320
-DTFT_MOSI=7           # ❌ WRONG - Should be 13
-DTFT_SCLK=6           # ❌ WRONG - Should be 14
-DTFT_CS=10            # ❌ WRONG - Should be 15
-DTFT_BL=3             # ❌ WRONG - Should be 19 (CRITICAL!)
```

### Issue #2: main.cpp has WRONG backlight pin
**File**: `/Users/tob/Programming/HildesTidsDings/src/main.cpp`

**Line 9** currently says:
```cpp
pinMode(3, OUTPUT);    # ❌ WRONG - Should be 19
```

**Line 11** currently says:
```cpp
ledcAttachPin(3, 0);   # ❌ WRONG - Should be 19
```

**Line 18** uses wrong rotation:
```cpp
tft.setRotation(0);    # ❌ WRONG - Should be 1 for landscape
```

**Lines 51** uses wrong width:
```cpp
tft.fillRect(0, 200, 240, 40, ...);  # ❌ WRONG - Should be 320
```

---

## ✅ CORRECT Configuration

### platformio.ini (Lines 17-32)
```ini
; TFT_eSPI User Setup for ST7789 (ESP32-2432S032C with ESP32-C3)
-DUSER_SETUP_LOADED=1
-DST7789_DRIVER=1                # ✅ Correct driver
-DTFT_WIDTH=240                  # ✅ Width
-DTFT_HEIGHT=320                 # ✅ Height  
-DTFT_RGB_ORDER=TFT_BGR          # ✅ Color order
-DTFT_MOSI=13                    # ✅ Correct pin
-DTFT_SCLK=14                    # ✅ Correct pin
-DTFT_MISO=12                    # ✅ MISO
-DTFT_CS=15                      # ✅ Correct pin
-DTFT_DC=2                       # ✅ Correct pin
-DTFT_RST=-1                     # ✅ Not used
-DTFT_BL=19                      # ✅ CORRECT BACKLIGHT!
-DTFT_BACKLIGHT_ON=HIGH          # ✅ Active high
-DSPI_FREQUENCY=40000000         # ✅ 40MHz safe speed
-DSPI_READ_FREQUENCY=10000000    # ✅ 10MHz read
```

### main.cpp (Setup function)
```cpp
void setup() {
    // Turn on backlight with PWM on GPIO 19  ✅
    pinMode(19, OUTPUT);
    ledcSetup(0, 2000, 8);
    ledcAttachPin(19, 0);
    ledcWrite(0, 255); // Full brightness
    
    delay(200);
    
    // Initialize display
    tft.init();
    tft.setRotation(1); // ✅ Landscape mode for 320x240
    
    // Rest of code...
}
```

---

## 📦 Missing Implementation Files

These header files exist in `include/` but their `.c` implementations are missing:

1. **timer_fsm.c** - Timer state machine logic
2. **ui_theme.c** - Theme color and button styling
3. **ui_presets.c** - Preset timer selector UI

**These were in the original project_bundle but got deleted.**

---

## 🎯 Action Plan

### Step 1: Fix Configuration (5 min)
- [ ] Update `platformio.ini` with correct ST7789 pins
- [ ] Update `src/main.cpp` with GPIO 19 backlight
- [ ] Change rotation to 1 (landscape)
- [ ] Change width references from 240 to 320

### Step 2: Test Display (2 min)
- [ ] Enter bootloader mode (unplug 10s method)
- [ ] Upload display test
- [ ] Verify RED/GREEN/BLUE colors appear
- [ ] Confirm "HELLO!" text shows

### Step 3: Recreate Missing Files (10 min)
- [ ] Create `src/timer_fsm.c` from saved code
- [ ] Create `src/ui_theme.c` from saved code
- [ ] Create `src/ui_presets.c` from saved code

### Step 4: Build Counter App (15 min)
- [ ] Integrate timer FSM with UI
- [ ] Add LVGL dependencies to platformio.ini
- [ ] Create complete counter app in main.cpp
- [ ] Test all functionality

---

## 🔧 Quick Fix Commands

```bash
# Navigate to project
cd /Users/tob/Programming/HildesTidsDings

# Fix platformio.ini
# (Use search_replace tool to update pins)

# Fix main.cpp  
# (Use search_replace tool to change GPIO 3 → 19)

# Enter bootloader mode
# (Physical: Unplug → wait 10s → hold BOOT → plug in → hold 5s → release)

# Upload
~/.platformio/penv/bin/pio run --target upload
```

---

## 📖 Key Learnings

1. **ESP32-2432S032C ≠ ESP32-2432S032** - The "C" variant uses ESP32-C3 chip with different pins
2. **Sample code pins don't match C variant** - Manufacturer samples show GPIO 27 backlight, but C variant uses GPIO 19
3. **Pin scanning technique works!** - Successfully identified unknown pin via systematic testing
4. **Bootloader mode required** - ESP32-C3 needs BOOT button held during upload when code is running

---

**Summary**: All components exist, just need configuration fixes + enter bootloader mode to upload.

