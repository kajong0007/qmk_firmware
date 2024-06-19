#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum jack_keys {
    JAK_NEXT_IMAGE = SAFE_RANGE,
    JAK_PREV_IMAGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC, KC_ENT, MO(_RAISE), KC_BSPC, KC_RGUI
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  _______, JAK_NEXT_IMAGE, JAK_PREV_IMAGE, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, LGUI(KC_ENT),                   KC_MUTE, KC_VOLU, KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, RGB_MOD, RGB_RMOD,XXXXXXX, LGUI(KC_ENT), XXXXXXX,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL,  XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
//0        1        2        3        4        5        6        7        8        9        10       11       12       13
};


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

/*
 * Idea for transport:
 *  - make send image opcode
 *  - when image is fully sent to left side, shuttle over to right side
 *  - when image is done, buffer swap and display
 *  - would have receive buffers for temp storage until transfer is done
 *  - hidraw would need "op-code", but left-to-right has RPC
 */

enum in_message_opcode {
    LEFT_WRITE_STR = 0,
    RIGHT_WRITE_STR = 1,
    SEND_IMAGE_LEFT = 2,
    FINISH_IMAGE_LEFT = 3,
    SEND_IMAGE_RIGHT = 4,
    FINISH_IMAGE_RIGHT = 5,
};

struct in_message {
    uint8_t opcode;
    uint8_t number;
    uint8_t data[30];
};

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);


static bool show_image = false;
static char left_image[512];
static char left_image_recv_buffer[512];

static char left_lines[4][22];
static bool left_display_lines[4] = {false, false, false, false};

void raw_hid_receive(uint8_t* data, uint8_t length) {
    struct in_message *recv_msg = (struct in_message*) data;
    switch (recv_msg->opcode) {
        case LEFT_WRITE_STR: {
            char* which_line = left_lines[recv_msg->number];
            memset(which_line, '\0', 22);
            memcpy(which_line, recv_msg->data, 21);
            which_line[21] = '\0';
            left_display_lines[recv_msg->number] = true;
            break;
        }
        case SEND_IMAGE_LEFT: {
            size_t offset = recv_msg->number * sizeof(recv_msg->data);
            size_t size = 30;
            size_t buffer_left = sizeof(left_image_recv_buffer) - offset;
            if (buffer_left < 30) {
                size = buffer_left;
            }
            memset(&left_image_recv_buffer[offset], '\0', size);
            memcpy(&left_image_recv_buffer[offset], recv_msg->data, size);
            break;
        }
        case FINISH_IMAGE_LEFT: {
            show_image = false;
            memcpy(left_image, left_image_recv_buffer, sizeof(left_image));
            show_image = true;
            break;
        }
        default: {
            break;
        }
    }
}
static char image0[512] = {
        // test_image.png
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x80, 0x80, 0xc0, 0x38, 0x00,
    0x00, 0x3c, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xf0, 0xb0, 0x28, 0xa8, 0xe4, 0x00, 0x00, 0x78, 0x10, 0x20, 0x7c, 0x02, 0x08, 0xc8, 0x38, 0x10,
    0x10, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x34, 0x74, 0x98, 0x00, 0x00, 0x60, 0xe0,
    0x90, 0xb0, 0xe0, 0x00, 0x00, 0x88, 0x88, 0xa8, 0xf8, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x08, 0x38, 0xf8, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0x01, 0x01, 0x01, 0xc0, 0xc0, 0xc0, 0x00,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc1,
    0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0x60, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x81, 0x01, 0x01, 0x00, 0x00, 0x04, 0x04, 0x06, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x3f, 0x30, 0x20, 0x2f, 0x3f, 0x3f, 0x30, 0x18, 0x1e, 0x0f, 0x07,
    0x03, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x09, 0x08, 0x08, 0x0c, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x04, 0x04, 0x1f,
    0x1f, 0x1f, 0x06, 0x06, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x38,
    0xf9, 0xfb, 0xcf, 0x8e, 0x8c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3c, 0x3e, 0x36, 0x27, 0x3f, 0x3d, 0x38, 0x00, 0x00, 0x38, 0x3c, 0x3c, 0x24,
    0x3c, 0x3c, 0x1c, 0x04, 0x04, 0x04, 0x04, 0x7c, 0x7c, 0x7c, 0x00, 0x07, 0x0f, 0x1f, 0x1f, 0x17, 0x17, 0x10, 0x10, 0x1f, 0x1f, 0x0f, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static uint16_t cat_left_down = 0;
//static uint16_t cat_left_timer = 0;
static uint16_t cat_right_down = 0;
//static uint16_t cat_right_timer = 0;

#include "cat.h"

static bool redraw_left = true;
static bool debug_draw_left = false;

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    if (debug_draw_left && redraw_left) {
        redraw_left = false;
        oled_write_ln(read_keylog(), false);
        return true;
    }
    if (show_image) {
        oled_write_raw_P(left_image, sizeof(left_image));
    } else {
        bool any_displayed = false;

        if (left_display_lines[0]) {
            any_displayed = true;
            oled_write_ln(left_lines[0], false);
        }

        if (left_display_lines[1]) {
            any_displayed = true;
            oled_write_ln(left_lines[1], false);
        }

        if (left_display_lines[2]) {
            any_displayed = true;
            oled_write_ln(left_lines[2], false);
        }

        if (left_display_lines[3]) {
            any_displayed = true;
            oled_write_ln(left_lines[3], false);
        }

        if (!any_displayed && redraw_left) {
            redraw_left = false;
            bool drawn = false;
            // teehee, cat time
            if (cat_left_down > 0 && cat_right_down > 0) {
                drawn = true;
                oled_write_raw_P(cat_both_down, sizeof(cat_both_down));
            }
            if (cat_left_down > 0 && !drawn) {
                drawn = true;
                oled_write_raw_P(cat_f_down, sizeof(cat_f_down));
            } 
            if (cat_right_down > 0 && !drawn) {
                drawn = true;
                oled_write_raw_P(cat_j_down, sizeof(cat_j_down));
            }
            if (!drawn) {
                oled_write_raw_P(cat_all_up, sizeof(cat_all_up));
            }
        }
    }
  } else {
      oled_write_raw_P(image0, sizeof(image0));
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    if (record->event.key.row <= 4) {
        if (cat_left_down == 0) {
            redraw_left = true;
        }
        cat_left_down += 1;
    } else {
        if (cat_right_down == 0) {
            redraw_left = true;
        }
        cat_right_down += 1;
    }
#ifdef OLED_ENABLE
    switch (keycode) {
        case JAK_NEXT_IMAGE: {
          show_image = false;
          for (int i = 0; i < sizeof(left_display_lines); i++) {
              left_display_lines[i] = false;
          }
          oled_clear();
          return false;
        }
        case JAK_PREV_IMAGE: {
          if (debug_draw_left) {
              redraw_left = true;
              debug_draw_left = false;
          } else {
              redraw_left = true;
              debug_draw_left = true;
          }
          oled_clear();
          return false;
        }
    }
    set_keylog(keycode, record);
#endif
    // set_timelog();
  } else {
    if (record->event.key.row <= 4) {
        if (cat_left_down > 0) {
            cat_left_down -= 1;
        }
        if (cat_left_down == 0) {
            redraw_left = true;
        }
    } else {
        if (cat_right_down > 0) {
            cat_right_down -= 1;
        }
        if (cat_right_down == 0) {
            redraw_left = true;
        }
    }
  }
  return true;
}
