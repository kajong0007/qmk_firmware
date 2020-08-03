RGB_MATRIX_EFFECT(jack_test_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS


static uint8_t red_key_idx;
#define JAK_EFFECT_EVERY 15
static uint8_t every = JAK_EFFECT_EVERY;

static void jack_test_effect_init(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    red_key_idx = led_min;
}

static bool jack_test_effect_run(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 0xff, 0xff, 0x00);
    }
    rgb_matrix_set_color(red_key_idx, 0xff, 0x00, 0x00);
    every--;
    if (every == 0) {
        red_key_idx = (red_key_idx + 1) % led_max;
        if (red_key_idx == 0) {
            red_key_idx = led_min;
        }
        every = JAK_EFFECT_EVERY;
    }
    return led_max < DRIVER_LED_TOTAL;
}

static bool jack_test_effect(effect_params_t* params) {
    if (params->init) jack_test_effect_init(params);
    return jack_test_effect_run(params);
}






#endif
