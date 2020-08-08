RGB_MATRIX_EFFECT(jack_casey_simple_sine)
RGB_MATRIX_EFFECT(jack_simple_atan)
RGB_MATRIX_EFFECT(jack_row_stripes)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

uint8_t do_math_simple_sine(uint8_t x, uint8_t y, uint8_t t) {
    float fx = x/5 + 1.15;
    float fy = (y-1)/5;
    float ratio = 2;
    float val = fx * ((float)sin8(t)/255.0f) + ratio * fy * ((float)cos8(t)/255.0f);
    val += 28.84;
    val = val * 8.84;
    return (uint8_t)val;
}

typedef struct {
    uint8_t min_idx;
    uint8_t max_idx;
} row_bound_t;

typedef struct {
    uint8_t row_idx;
    uint8_t cur_delay;
    uint8_t offset;
    uint8_t prev_offset;
} row_stripe_t;

static row_bound_t jak_row_bounds[6] = {
    { 0, 15},
    {15, 30},
    {30, 44},
    {44, 58},
    {58, 67},
    {67, DRIVER_LED_TOTAL}
};

static row_stripe_t jak_row_stripes[6] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

static uint8_t led_delays[DRIVER_LED_TOTAL] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1,
    2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1,
    4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1,
    1, 1, 1, 9, 1, 2, 1, 1, 1,
    // underglow
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1
};

static bool jak_stripes_init;

static uint8_t jak_stripes_rando_delay;

uint8_t do_math_atan(uint8_t x, uint8_t y, uint8_t t) {
    uint8_t val = sin8(atan2_8(y, x)) + t;
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

static uint8_t led_idx_to_row_idx(uint8_t led_idx) {
    uint8_t led_y = g_led_config.point[led_idx].y;
    uint8_t ret = 0;
    // underglow leds are the last row (6th row, idx 5)
    if (led_idx >= 67) {
        ret = 5;
    } else {
        switch(led_y) {
            case 56:
                ret = 0;
                break;
            case 44:
                ret = 1;
                break;
            case 32:
                ret = 2;
                break;
            case 19:
                ret = 3;
                break;
            case 7:
                ret = 4;
                break;
        }
    }
    return ret;
}

static uint8_t stripe_get_delay(uint8_t idx) {
    uint8_t speed = 0x80 / (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed);
    if (speed == 0) {
        speed = 1;
    }
    return led_delays[idx] * speed;
}

static bool jack_row_stripes(effect_params_t* params) {
    if (params->init) {
        jak_stripes_init = true;
        jak_stripes_rando_delay = random8_max(254) + 1;
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (jak_stripes_init) {
        for (uint8_t i = 0; i < 6; i++) {
            row_stripe_t* rando_stripe = &(jak_row_stripes[i]);
            rando_stripe->row_idx = jak_row_bounds[i].min_idx;
            rando_stripe->cur_delay = stripe_get_delay(rando_stripe->row_idx);
            rando_stripe->offset = random8();
        }
    } else {
        jak_stripes_rando_delay--;
        if (jak_stripes_rando_delay == 0) {
            jak_stripes_rando_delay = random8_max(254) + 1;
            uint8_t idx = random8_max(6);
            row_stripe_t* rando_stripe = &(jak_row_stripes[idx]);
            if (rando_stripe->row_idx == 0 && rando_stripe->cur_delay == 0) {
                rando_stripe->row_idx = jak_row_bounds[idx].min_idx;
                uint8_t speed = 0x80 / (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed);
                if (speed == 0) {
                    speed = 1;
                }
                rando_stripe->cur_delay = stripe_get_delay(rando_stripe->row_idx);
                rando_stripe->offset = random8();
            }
        }
    }

    for (uint8_t i = led_min; i < led_max; i++) {
        if (jak_stripes_init) {
            rgb_matrix_set_color(i, 0, 0, 0);
        } else {
            HSV cur_hsv = rgb_matrix_config.hsv;
            uint8_t row_idx = led_idx_to_row_idx(i);
            row_stripe_t* cur_stripe = &(jak_row_stripes[row_idx]);
            if (! (cur_stripe->row_idx == 0 && cur_stripe->cur_delay == 0) && i == cur_stripe->row_idx) {
                cur_hsv.h += cur_stripe->offset;
                RGB cur_r = hsv_to_rgb(cur_hsv);
                rgb_matrix_set_color(i, cur_r.r, cur_r.g, cur_r.b);
                cur_stripe->cur_delay--;
                if (cur_stripe->cur_delay == 0) {
                    cur_stripe->row_idx++;
                    if (cur_stripe->row_idx == jak_row_bounds[row_idx].max_idx) {
                        cur_stripe->row_idx = 0;
                        cur_stripe->cur_delay = 0;
                        cur_stripe->prev_offset = cur_stripe->offset;
                    } else {
                        cur_stripe->cur_delay = stripe_get_delay(cur_stripe->row_idx);
                    }
                }
            } else {
                if (i >= cur_stripe->row_idx && cur_stripe->prev_offset != 0) {
                    cur_hsv.h += cur_stripe->prev_offset;
                    RGB cur_r = hsv_to_rgb(cur_hsv);
                    rgb_matrix_set_color(i, cur_r.r, cur_r.g, cur_r.b);
                }
            }
        }
    }

    if (led_max == DRIVER_LED_TOTAL) {
        jak_stripes_init = false;
    }

    return led_max < DRIVER_LED_TOTAL;
}

#endif
