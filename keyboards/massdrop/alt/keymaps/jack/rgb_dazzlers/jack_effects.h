RGB_MATRIX_EFFECT(jack_test_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include <stdlib.h>

#define JAK_QMK_KB_EFFECT_EVERY 40
//static uint8_t every = JAK_QMK_KB_EFFECT_EVERY;

#define JAK_QMK_KB_MAX_RAND 2147483647ul

static void jack_test_effect_init(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
}

//static uint8_t jak_random_byte(void) {
//    unsigned long l = (unsigned long) lrand48();
//    return l % 0x100;
//}
//
//static RGB jak_random_color(void) {
//    RGB ret = {jak_random_byte(), jak_random_byte(), jak_random_byte()};
//    return ret;
//}

#define JAK_SET_PINK(i) rgb_matrix_set_color(i, 0xff, 100, 100)
#define JAK_SET_BLUE(i) rgb_matrix_set_color(i, 0, 205, 252)
#define JAK_SET_WHITE(i) rgb_matrix_set_color(i, 0xff, 0xff, 0xff)

//static RGB nb_flag[] = {
//    {0xff, 0xf4, 0x30},
//    {0xff, 0xff, 0xff},
//    {0x9c, 0x59, 0xd1},
//    {0x00, 0x00, 0x00}
//};
//
//static RGB lipstick_lesbian[] = {
//    {0xd6, 0x29, 0x00},
//    {0xff, 0x9b, 0x55},
//    {0xff, 0xff, 0xff},
//    {0xd4, 0x61, 0xa6},
//    {0xa5, 0x00, 0x62}
//};
//
//struct {
//    uint8_t row_size;
//} jak_row_handler;
//struct {
//    uint8_t row_size;
//    struct {
//        uint8_t index;
//        RGB color;
//    } swipe;
//    uint8_t active_swipes;
//    struct swipe current_swipes[3];
//} typedef jak_row_holder;

static bool jack_test_effect_run(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    //HSV hsv = rgb_matrix_config.hsv;
    //RGB col = hsv_to_rgb(hsv);
    //uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);

    // call out to the rainbow pinwheel for the underglow if active
    effect_params_t tmp = *params;
    tmp.flags = tmp.flags & LED_FLAG_UNDERGLOW;
    CYCLE_SPIRAL(&tmp);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (!HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            uint8_t row = g_led_config.point[i].y;
            switch(row) {
                case 56:
                    row = 0;
                    rgb_matrix_set_color(i, 0xff, 0xf4, 0x30);
                    break;
                case 44:
                    row = 1;
                    rgb_matrix_set_color(i, 0xff, 0xff, 0xff);
                    break;
                case 32:
                    row = 2;
                    rgb_matrix_set_color(i, 0x9c, 0x59, 0xd1);
                    break;
                case 19:
                    row = 3;
                    rgb_matrix_set_color(i, 0x20, 0x20, 0x20);
                    break;
                case 7:
                    row = 4;
                    rgb_matrix_set_color(i, 0xef, 0xff, 0xff);
                    break;
            }
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}

static bool jack_test_effect(effect_params_t* params) {
    if (params->init) jack_test_effect_init(params);
    return jack_test_effect_run(params);
}






#endif
