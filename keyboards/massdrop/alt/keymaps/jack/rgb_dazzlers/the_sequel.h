RGB_MATRIX_EFFECT(new_jack_casey_effect)

    //uint8_t theta = atan2_8(y, x);
    //uint8_t r = sqrt16(x*x + y*y);
    //float f_theta = (float) theta;
    //float f_r = (float) r;
    //float f_time = (float) time;
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
static uint8_t do_math_wave_horiz(uint8_t x, uint8_t  y, uint8_t time) {
    float f_val =  0.5 * x + time;
    if(f_val < 0){
        f_val = 255 + f_val;
    }
    if(f_val > 255){
        f_val = f_val - 255;
    }
    if((f_val > 130) && (f_val < 146)){
        f_val = 21;
    }else{
        float difference = abs8(f_val-138);
        if(difference <= 30){
            f_val = f_val - 0.8 * difference;
        }else{
            f_val = 85;
        }
    }
    return (uint8_t) f_val;
}

static bool new_jack_casey_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 16);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (i == 0) {
            if (time < 0x80) {
                rgb_matrix_set_color(i, (time * 2), 0x0, 0x0);
            } else {
                rgb_matrix_set_color(i, 0x0, 0x0, (time - 0x80) * 2);
            }
        } else {
            uint8_t x = g_led_config.point[i].x;
            uint8_t y = g_led_config.point[i].y;
            HSV hsv = rgb_matrix_config.hsv;
            hsv.h += do_math_wave_horiz(x, y, time);
            RGB cur = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, cur.r, cur.g, cur.b);
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}
#endif
