/* Copyright 2022 @daliusd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
// Copyright 2023 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
    _QWERTY,
};

enum jak_keys {
    JAK_MORSE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(JAK_MORSE, KC_SPC, KC_BSPC)
};

#define DIT_DEFAULT 100
//#define SHORT_GAP (DIT_DURATION * 3)

uint16_t DIT_DURATION = DIT_DEFAULT;
uint16_t SHORT_GAP = DIT_DEFAULT * 3;

uint16_t timer_started = 0;
uint16_t timer_ended = 0;
uint8_t  code_length = 0;
uint16_t code = 0;
bool visible = true;
bool render = true;

uint8_t modifiers = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case JAK_MORSE: {
            if (record->event.pressed) {
                timer_started = timer_read();
                timer_ended = 0;
            } else {
                timer_ended = timer_read();
                code <<= 1;
                code_length += 1;
                if (timer_elapsed(timer_started) > DIT_DURATION * 2) {
                    if (visible) {
                        tap_code16(KC_MINS);
                    }
                    code += 1;
                } else {
                    if (visible) {
                        tap_code16(KC_DOT);
                    }
                }
                timer_started = 0;
            }

            return false;
        }
    }
    return true;
}

/*
 * Generating code from another file so it'll be easier to parse in
 * python and we can generate a cheat sheet for the version of morse code
 * we're using
 *
 * ultimately, we'll end up with functions that look like:
void process_1(void) {
    switch (code) {
        case 0b0:
            tap_code16(KC_E);
            break;
        case 0b1:
            tap_code16(KC_T);
            break;
    }
}
 *
 */
#define JAK_PROCESS_FUNCTION_OPEN(x) \
void process_##x(void) {\
    switch (code) {\
        do {\
        } while(0)
#define JAK_PROCESS_FUNCTION_CLOSE \
    }\
}
#define JAK_TYPE_KEY(bits, keycode) \
        case bits:\
            tap_code16(keycode);\
            break
#define JAK_DO_OTHER(bits, explain, code) \
        case bits:\
            code\
            break

JAK_PROCESS_FUNCTION_OPEN(1);
JAK_TYPE_KEY(0b0, KC_E);
JAK_TYPE_KEY(0b1, KC_T);
JAK_PROCESS_FUNCTION_CLOSE

JAK_PROCESS_FUNCTION_OPEN(2);
JAK_TYPE_KEY(0b00, KC_I);
JAK_TYPE_KEY(0b01, KC_A);
JAK_TYPE_KEY(0b10, KC_N);
JAK_TYPE_KEY(0b11, KC_M);
JAK_PROCESS_FUNCTION_CLOSE

JAK_PROCESS_FUNCTION_OPEN(3);
JAK_TYPE_KEY(0b000, KC_S);
JAK_TYPE_KEY(0b001, KC_U);
JAK_TYPE_KEY(0b010, KC_R);
JAK_TYPE_KEY(0b011, KC_W);
JAK_TYPE_KEY(0b100, KC_D);
JAK_TYPE_KEY(0b101, KC_K);
JAK_TYPE_KEY(0b110, KC_G);
JAK_TYPE_KEY(0b111, KC_O);
JAK_PROCESS_FUNCTION_CLOSE

JAK_PROCESS_FUNCTION_OPEN(4);
JAK_TYPE_KEY(0b0000, KC_H);
JAK_TYPE_KEY(0b0001, KC_V);
JAK_TYPE_KEY(0b0010, KC_F);
JAK_TYPE_KEY(0b0011, KC_BSPC);
JAK_TYPE_KEY(0b0100, KC_L);
JAK_TYPE_KEY(0b0101, KC_SPC);
JAK_TYPE_KEY(0b0110, KC_P);
JAK_TYPE_KEY(0b0111, KC_J);
JAK_TYPE_KEY(0b1000, KC_B);
JAK_TYPE_KEY(0b1001, KC_X);
JAK_TYPE_KEY(0b1010, KC_C);
JAK_TYPE_KEY(0b1011, KC_Y);
JAK_TYPE_KEY(0b1100, KC_Z);
JAK_TYPE_KEY(0b1101, KC_Q);
JAK_TYPE_KEY(0b1111, KC_ENT);
JAK_PROCESS_FUNCTION_CLOSE

JAK_PROCESS_FUNCTION_OPEN(7);
JAK_DO_OTHER(0b0000000, "Set dit duration to 100ms", \
        DIT_DURATION = 100;\
        );
JAK_DO_OTHER(0b0000001, "Set dit duration to 50ms", \
        DIT_DURATION = 50;\
        );
JAK_PROCESS_FUNCTION_CLOSE

#undef JAK_PROCESS_FUNCTION_OPEN
#undef JAK_PROCESS_FUNCTION_CLOSE
#undef JAK_TYPE_KEY
#undef JAK_DO_OTHER
//void process_1(void) {
//    switch (code) {
//        case 0b0:
//            tap_code16(KC_E);
//            break;
//        case 0b1:
//            tap_code16(KC_T);
//            break;
//    }
//}
//void process_7(void) {
//    switch (code) {
//        case 0b0000000:
//            DIT_DURATION = 100;
//            break;
//        case 0b0000001:
//            DIT_DURATION = 50;
//            break;
//    }
//    SHORT_GAP = 3 * DIT_DURATION;
//}

//void process_2(void) {
//    switch (code) {
//        case 0b00:
//            tap_code16(KC_I);
//            break;
//        case 0b01:
//            tap_code16(KC_A);
//            break;
//        case 0b10:
//            tap_code16(KC_N);
//            break;
//        case 0b11:
//            tap_code16(KC_M);
//            break;
//    }
//}

//void process_3(void) {
//    switch (code) {
//        case 0b000:
//            tap_code16(KC_S);
//            break;
//        case 0b001:
//            tap_code16(KC_U);
//            break;
//        case 0b010:
//            tap_code16(KC_R);
//            break;
//        case 0b011:
//            tap_code16(KC_W);
//            break;
//        case 0b100:
//            tap_code16(KC_D);
//            break;
//        case 0b101:
//            tap_code16(KC_K);
//            break;
//        case 0b110:
//            tap_code16(KC_G);
//            break;
//        case 0b111:
//            tap_code16(KC_O);
//            break;
//    }
//}

//void process_4(void) {
//    switch (code) {
//        case 0b0000:
//            tap_code16(KC_H);
//            break;
//        case 0b0001:
//            tap_code16(KC_V);
//            break;
//        case 0b0010:
//            tap_code16(KC_F);
//            break;
//        case 0b0011:
//            tap_code16(KC_BSPC);
//            break;
//        case 0b0100:
//            tap_code16(KC_L);
//            break;
//        case 0b0101:
//            tap_code16(KC_SPC);
//            break;
//        case 0b0110:
//            tap_code16(KC_P);
//            break;
//        case 0b0111:
//            tap_code16(KC_J);
//            break;
//        case 0b1000:
//            tap_code16(KC_B);
//            break;
//        case 0b1001:
//            tap_code16(KC_X);
//            break;
//        case 0b1010:
//            tap_code16(KC_C);
//            break;
//        case 0b1011:
//            tap_code16(KC_Y);
//            break;
//        case 0b1100:
//            tap_code16(KC_Z);
//            break;
//        case 0b1101:
//            tap_code16(KC_Q);
//            break;
//        case 0b1111:
//            tap_code16(KC_ENT);
//            break;
//    }
//}

void process_5(void) {
    switch (code) {
        case 0b00000:
            tap_code16(KC_5);
            break;
        case 0b00001:
            tap_code16(KC_4);
            break;
        case 0b00011:
            tap_code16(KC_3);
            break;
        case 0b00111:
            tap_code16(KC_2);
            break;
        case 0b01000:
            tap_code16(KC_AMPR);
            break;
        case 0b01100:
            // WI - win key
            modifiers |= 0b0001;
            break;
        case 0b01111:
            tap_code16(KC_1);
            break;
        case 0b10000:
            tap_code16(KC_6);
            break;
        case 0b10010:
            tap_code16(KC_SLSH);
            break;
        case 0b10101:
            // CT - ctrl
            modifiers |= 0b0010;
            break;
        case 0b10110:
            tap_code16(KC_LPRN);
            break;
        case 0b11000:
            tap_code16(KC_7);
            break;
        case 0b11100:
            tap_code16(KC_8);
            break;
        case 0b11110:
            tap_code16(KC_9);
            break;
        case 0b11111:
            tap_code16(KC_0);
            break;
    }
}

void process_6(void) {
    switch (code) {
        case 0b000001:
            // SIT - Shift
            modifiers |= 0b1000;
            break;
        case 0b001100:
            tap_code16(KC_QUES);
            break;
        case 0b010000:
            tap_code16(KC_HASH); // reset does not trigger alone. So I have added hash here.
            reset_keyboard();
            break;
        case 0b010010:
            tap_code16(KC_DQT);
            break;
        case 0b010100:
            // AL - Alt
            modifiers |= 0b0100;
            break;
        case 0b010101:
            tap_code16(KC_DOT);
            break;
        case 0b011110:
            tap_code16(KC_QUOT);
            break;
        case 0b101010:
            tap_code16(KC_SCLN);
            break;
        case 0b101011:
            tap_code16(KC_EXLM);
            break;
        case 0b101101:
            tap_code16(KC_RPRN);
            break;
        case 0b110011:
            tap_code16(KC_COMM);
            break;
        case 0b111000:
            tap_code16(S(KC_SCLN));
            break;

    }
}


void process_9(void) {
    switch (code) {
        case 0b000111000:
            if (visible) {
                visible = false;
            } else {
                visible = true;
            }
            break;
        case 0b111000111:
            if (render) {
                render = false;
            } else {
                render = true;
            }
            break;
    }
}

void matrix_scan_user(void) {
    if (timer_started == 0 && timer_ended != 0 && timer_elapsed(timer_ended) > DIT_DURATION * 3) {

        // handle modifiers (register)
        uint8_t old_modifiers = modifiers;
        if ((modifiers & 0b0001) == 0b0001) {
            register_code(KC_LGUI);
        }
        if ((modifiers & 0b0010) == 0b0010) {
            register_code(KC_LCTL);
        }
        if ((modifiers & 0b0100) == 0b0100) {
            register_code(KC_LALT);
        }
        if ((modifiers & 0b1000) == 0b1000) {
            register_code(KC_LSFT);
        }

        if (visible && render) {
            int del_bits;
            for (del_bits = 0; del_bits < code_length; del_bits++) {
                tap_code16(KC_BSPC);
            }
        }
#define BUT_RENDER(x) do {\
    if (render) {\
        x();\
    }\
} while(0)
        // pressed key
        switch (code_length) {
            case 1:
                BUT_RENDER(process_1);
                break;
            case 2:
                BUT_RENDER(process_2);
                break;
            case 3:
                BUT_RENDER(process_3);
                break;
            case 4:
                BUT_RENDER(process_4);
                break;
            case 5:
                BUT_RENDER(process_5);
                break;
            case 6:
                BUT_RENDER(process_6);
                break;
            case 7:
                process_7();
                break;
            case 9:
                process_9();
                break;
        }

        // handle modifiers (unregister). Unregister all modifiers if non modifier key is pressed
        if (old_modifiers == modifiers) {
            if ((modifiers & 0b0001) == 0b0001) {
                unregister_code(KC_LGUI);
            }
            if ((modifiers & 0b0010) == 0b0010) {
                unregister_code(KC_LCTL);
            }
            if ((modifiers & 0b0100) == 0b0100) {
                unregister_code(KC_LALT);
            }
            if ((modifiers & 0b1000) == 0b1000) {
                unregister_code(KC_LSFT);
            }
            modifiers = 0;
        }

        timer_ended = 0;
        code_length = 0;
        code = 0;
    }
}
