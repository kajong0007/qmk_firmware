RGB_MATRIX_EFFECT(jack_casey_simple_sine)
RGB_MATRIX_EFFECT(jack_simple_atan)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/*
 *=============================================
 * SINE EFFECT
 *=============================================
 */
    //ratio = 4
    //val += 40;
    //val = val * 6.375;
uint8_t do_math_simple_sine(uint8_t x, uint8_t y, uint8_t t) {
    float fx = x/5 + 1.15;
    float fy = (y-1)/5;
    float ratio = 2;
    float val = fx * ((float)sin8(t)/255.0f) + ratio * fy * ((float)cos8(t)/255.0f);
    val += 28.84;
    val = val * 8.84;
    return (uint8_t)val;
}

uint8_t do_math_atan(uint8_t x, uint8_t y, uint8_t t) {
    uint8_t val = atan2_8(y, x) + t;
    return val;
}

static bool jack_casey_simple_sine(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 16);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        uint8_t x = g_led_config.point[i].x;
        uint8_t y = g_led_config.point[i].y;
        HSV hsv = rgb_matrix_config.hsv;
        hsv.h += do_math_simple_sine(x, y, time);
        RGB cur = hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, cur.r, cur.g, cur.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

static bool jack_simple_atan(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 16);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        uint8_t x = g_led_config.point[i].x;
        uint8_t y = g_led_config.point[i].y;
        HSV hsv = rgb_matrix_config.hsv;
        hsv.h += do_math_atan(x, y, time);
        RGB cur = hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, cur.r, cur.g, cur.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif
