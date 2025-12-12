# ESP32-2424s012c Counter App

A beautiful counter/timer application for the ESP32-2424s012c round display module.

## Hardware

- **Device**: ESP32-2424s012c
- **MCU**: ESP32-C3
- **Display**: GC9A01 240x240 round LCD
- **Interface**: SPI

## Features

- **Count Up Mode**: Stopwatch functionality
- **Count Down Mode**: Timer with presets (1m, 3m, 5m, 10m, custom)
- **Neomorphic UI**: Modern, elegant design with shadows and depth
- **Adjustable Time**: +/- buttons to adjust time on the fly
- **Preset Timer**: Quick access to common timer durations
- **Custom Timer**: Numeric keypad for setting custom times (mm:ss format)

## Project Structure

```
project_bundle/
├── counter_app.ino     # Main Arduino application
├── timer_fsm.c/h       # Timer finite state machine
├── ui_theme.c/h        # Neomorphic theme engine
├── ui_presets.c        # Preset selector UI
├── platformio.ini      # PlatformIO configuration
├── lv_conf.h          # LVGL configuration
└── README.md          # This file
```

## Installation

### Prerequisites

1. Install [PlatformIO](https://platformio.org/) (via VSCode extension or CLI)
2. Connect your ESP32-2424s012c to USB

### Build & Upload

```bash
cd /Users/tob/Downloads/project_bundle
pio run --target upload
```

Or use PlatformIO VSCode extension: Click "Upload" button in the bottom toolbar.

### Monitor Serial Output

```bash
pio device monitor
```

## Pin Configuration (ESP32-2424s012c)

- **TFT_MOSI**: GPIO 7
- **TFT_SCLK**: GPIO 6  
- **TFT_CS**: GPIO 10
- **TFT_DC**: GPIO 2
- **TFT_BL**: GPIO 3 (Backlight)

## Usage

### Buttons

- **START/STOP**: Toggle timer running state
- **RST**: Reset timer to zero
- **MODE**: Toggle between Count Up and Count Down
- **+/-**: Adjust time by 1 second increments
- **...** (dots): Open preset selector

### Preset Selector

- Choose from 1m, 3m, 5m, 10m presets
- Select "Custom" to enter a specific time using numeric keypad
- Format: mm:ss (e.g., "5:30" for 5 minutes 30 seconds)

## Development

The app uses a clean FSM architecture:

1. **timer_fsm**: Core timer logic, mode handling, state transitions
2. **ui_theme**: Reusable neomorphic theme system
3. **ui_presets**: Preset selector with animated bottom sheet
4. **counter_app**: Main application, display driver, UI layout

## Troubleshooting

- **Display not working**: Check pin definitions in platformio.ini
- **Upload fails**: Press and hold BOOT button during upload
- **Serial not detected**: Ensure `ARDUINO_USB_CDC_ON_BOOT=1` is set

## License

Open source - modify as needed for your projects!




