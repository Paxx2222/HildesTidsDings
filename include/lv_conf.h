/**
 * LVGL Configuration for ESP32-2424s012c
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

/* Color depth: 16bit (RGB565) */
#define LV_COLOR_DEPTH 16

/* Memory settings */
#define LV_MEM_CUSTOM 0
#define LV_MEM_SIZE (48 * 1024U)

/* Display settings */
#define LV_HOR_RES_MAX 240
#define LV_VER_RES_MAX 240
#define LV_DPI_DEF 130

/* Rendering */
#define LV_DISP_DEF_REFR_PERIOD 30
#define LV_INDEV_DEF_READ_PERIOD 30

/* Features */
#define LV_USE_ANIMATION 1
#define LV_USE_SHADOW 1
#define LV_SHADOW_CACHE_SIZE 0

/* Font support */
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_20 1
#define LV_FONT_MONTSERRAT_24 1
#define LV_FONT_MONTSERRAT_28 1
#define LV_FONT_MONTSERRAT_32 1
#define LV_FONT_MONTSERRAT_48 1

/* Logging */
#define LV_USE_LOG 1
#define LV_LOG_LEVEL LV_LOG_LEVEL_WARN
#define LV_LOG_PRINTF 1

/* Widgets */
#define LV_USE_BTN 1
#define LV_USE_LABEL 1
#define LV_USE_ARC 1
#define LV_USE_ANIMIMG 0
#define LV_USE_BAR 0
#define LV_USE_CALENDAR 0
#define LV_USE_CHART 0
#define LV_USE_CHECKBOX 0
#define LV_USE_DROPDOWN 0
#define LV_USE_IMG 1
#define LV_USE_KEYBOARD 0
#define LV_USE_LED 0
#define LV_USE_LINE 0
#define LV_USE_LIST 0
#define LV_USE_METER 0
#define LV_USE_MSGBOX 0
#define LV_USE_ROLLER 0
#define LV_USE_SLIDER 0
#define LV_USE_SPAN 0
#define LV_USE_SPINBOX 0
#define LV_USE_SPINNER 0
#define LV_USE_SWITCH 0
#define LV_USE_TABLE 0
#define LV_USE_TABVIEW 0
#define LV_USE_TEXTAREA 0
#define LV_USE_TILEVIEW 0
#define LV_USE_WIN 0

/* Themes */
#define LV_USE_THEME_DEFAULT 1
#define LV_USE_THEME_BASIC 1

#endif /* LV_CONF_H */

