#pragma once
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { TIMER_MODE_COUNTUP=0, TIMER_MODE_COUNTDOWN=1 } timer_mode_t;
typedef enum { TIMER_ST_IDLE=0, TIMER_ST_RUNNING, TIMER_ST_PAUSED, TIMER_ST_FINISHED } timer_state_t;

typedef struct {
    timer_mode_t  mode;
    timer_state_t state;
    int32_t       target_ms;
    int32_t       elapsed_ms;
    int32_t       step_ms;
    int32_t       last_tick_ms;
} timer_ctx_t;

typedef void (*timer_on_render_cb)(const timer_ctx_t* ctx,int32_t shown_ms,int32_t total_ms);
typedef void (*timer_on_state_cb)(timer_state_t prev,timer_state_t now);
typedef void (*timer_on_finished_cb)(void);

typedef struct {
    timer_on_render_cb   on_render;
    timer_on_state_cb    on_state;
    timer_on_finished_cb on_finished;
} timer_callbacks_t;

void timer_init(const timer_callbacks_t* cb,int32_t step_ms);
void timer_set_mode(timer_mode_t m);
void timer_set_target_ms(int32_t ms);
void timer_set_elapsed_ms(int32_t ms);
void timer_set_step_ms(int32_t step_ms);
void timer_toggle_start_pause(void);
void timer_start(void);
void timer_pause(void);
void timer_reset(bool keep_target);
void timer_repeat(void);
void timer_continue(void);
void timer_adjust_ms(int32_t delta_ms);
void timer_tick_10ms(void);
const timer_ctx_t* timer_get(void);

#include "lvgl.h"
void apply_preset_ms(lv_event_t* e);
void fsm_ev_start_stop(lv_event_t* e);
void fsm_ev_reset(lv_event_t* e);
void fsm_ev_repeat_or_continue(lv_event_t* e);
void fsm_ev_adjust_plus(lv_event_t* e);
void fsm_ev_adjust_minus(lv_event_t* e);

#ifdef __cplusplus
}
#endif