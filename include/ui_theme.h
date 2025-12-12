#pragma once
#include "lvgl.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    THEME_NEO_DARK = 0,
    THEME_NEO_CAT  = 1
} theme_variant_t;

typedef struct {
    lv_color_t deep1;
    lv_color_t deep2;
    lv_color_t mid1;
    lv_color_t mid2;
    lv_color_t accent;
    lv_color_t ink;
    lv_color_t alert;
} theme_colors_t;

void theme_init_default(void);
void theme_set_variant(theme_variant_t v);
void theme_set_colors(const theme_colors_t* c);

lv_color_t theme_color_deep1(void);
lv_color_t theme_color_deep2(void);
lv_color_t theme_color_mid1(void);
lv_color_t theme_color_mid2(void);
lv_color_t theme_color_accent(void);
lv_color_t theme_color_ink(void);
lv_color_t theme_color_alert(void);

void neo_apply(lv_obj_t* o, lv_color_t base, bool raised);
lv_obj_t* neo_button(lv_obj_t* parent, const char* txt, bool raised,
                     lv_color_t base, lv_color_t txtc, int w, int h);

#ifdef __cplusplus
}
#endif