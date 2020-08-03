RGB_MATRIX_EFFECT(jack_test_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include <stdlib.h>

static uint8_t red_key_idx;
#define JAK_QMK_KB_EFFECT_EVERY 15
static uint8_t every = JAK_QMK_KB_EFFECT_EVERY;

#define JAK_QMK_KB_MAX_RAND 2147483647ul

static void jack_test_effect_init(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    red_key_idx = led_min;
}

static uint8_t jak_random_byte(void) {
    unsigned long l = (unsigned long) lrand48();
    return l % 0x100;
}

static bool jack_test_effect_run(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        int am_not_red = ((int) red_key_idx != i);
        rgb_matrix_set_color(i,
                0xff,
                0xff * am_not_red,
                jak_random_byte() * am_not_red);
    }
    every--;
    if (every == 0) {
        red_key_idx = (red_key_idx + 1) % led_max;
        if (red_key_idx == 0) {
            red_key_idx = led_min;
        }
        every = JAK_QMK_KB_EFFECT_EVERY;
    }
    return led_max < DRIVER_LED_TOTAL;
}

static bool jack_test_effect(effect_params_t* params) {
    if (params->init) jack_test_effect_init(params);
    return jack_test_effect_run(params);
}






#endif
