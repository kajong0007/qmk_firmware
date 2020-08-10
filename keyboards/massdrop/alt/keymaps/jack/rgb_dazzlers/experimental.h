RGB_MATRIX_EFFECT(another_jack_casey_effect)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

//static uint8_t do_math(uint8_t x, uint8_t  y, uint8_t t) {
//    x = x + 112;
//    y = y + 32;
//    uint8_t theta = atan2_8(y,x);
//    uint16_t x2 = (uint16_t)x;
//    uint16_t y2 = (uint16_t)y;
//    uint8_t r = sqrt16(x2 * x2 + y2 * y2);
//    uint8_t val = r * theta - sin8(t);
//    return val;
//}
static uint8_t do_math(uint8_t x, uint8_t  y, uint8_t t) {
    x = x + 12;
    y = y + 10;
    uint8_t val = x + y + t;
    return val;
}

static bool another_jack_casey_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 16);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (i == 0) {
            if (time < 0x80) {
                rgb_matrix_set_color(i, 0x0, (time * 2), 0x0);
            } else {
                rgb_matrix_set_color(i, 0x0, 0x0, (time - 0x80) * 2);
            }
        } else {
            uint8_t x = g_led_config.point[i].x;
            uint8_t y = g_led_config.point[i].y;
            HSV hsv = rgb_matrix_config.hsv;
            hsv.h += do_math(x, y, time);
            RGB cur = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, cur.r, cur.g, cur.b);
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}
#endif
