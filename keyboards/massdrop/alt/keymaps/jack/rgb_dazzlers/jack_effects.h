RGB_MATRIX_EFFECT(jack_casey_simple_sine)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

uint8_t do_math(uint8_t x, uint8_t y, uint8_t t) {
	float fx = x/5;
	float fy = (y-1)/5;
	float ratio = 4;
	float val = fx * ((float)sin8(t)/255.0f) + ratio * fy * ((float)cos8(t)/255.0f);
	val += 40;
	val = val * 6.375;
	return (uint8_t)val;
}

static bool jack_casey_simple_sine(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 16);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
	uint8_t x = g_led_config.point[i].x;
	uint8_t y = g_led_config.point[i].y;
	HSV hsv = rgb_matrix_config.hsv;
	hsv.h += do_math(x, y, time);
	RGB cur = hsv_to_rgb(hsv);
	rgb_matrix_set_color(i, cur.r, cur.g, cur.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif
