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

const uint32_t PROGMEM unicode_map[] = {};

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
bool shift_lock = false;

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
}\
//
#define JAK_TYPE_KEY(bits, keycode) \
        case bits:\
            tap_code16(keycode);\
            break
#define JAK_DO_OTHER(bits, explain, code) \
        case bits:\
            code\
            break
#define JAK_TYPE_UNICODE(bits, character) \
        case bits:\
            send_unicode_string(character);\
            break
#define JAK_TYPE_CAPSABLE(bits, keycode) \
        case bits:\
            if (shift_lock) { \
                register_code(KC_LSFT); \
            } \
            tap_code16(keycode); \
            if (shift_lock) { \
                unregister_code(KC_LSFT); \
            } \
            break

JAK_PROCESS_FUNCTION_OPEN(1);
JAK_TYPE_CAPSABLE(0b0, KC_E);
JAK_TYPE_CAPSABLE(0b1, KC_T);
JAK_PROCESS_FUNCTION_CLOSE;

JAK_PROCESS_FUNCTION_OPEN(2);
JAK_TYPE_CAPSABLE(0b00, KC_I);
JAK_TYPE_CAPSABLE(0b01, KC_A);
JAK_TYPE_CAPSABLE(0b10, KC_N);
JAK_TYPE_CAPSABLE(0b11, KC_M);
JAK_PROCESS_FUNCTION_CLOSE;

JAK_PROCESS_FUNCTION_OPEN(3);
JAK_TYPE_CAPSABLE(0b000, KC_S);
JAK_TYPE_CAPSABLE(0b001, KC_U);
JAK_TYPE_CAPSABLE(0b010, KC_R);
JAK_TYPE_CAPSABLE(0b011, KC_W);
JAK_TYPE_CAPSABLE(0b100, KC_D);
JAK_TYPE_CAPSABLE(0b101, KC_K);
JAK_TYPE_CAPSABLE(0b110, KC_G);
JAK_TYPE_CAPSABLE(0b111, KC_O);
JAK_PROCESS_FUNCTION_CLOSE;

JAK_PROCESS_FUNCTION_OPEN(4);
JAK_TYPE_CAPSABLE(0b0000, KC_H);
JAK_TYPE_CAPSABLE(0b0001, KC_V);
JAK_TYPE_CAPSABLE(0b0010, KC_F);
JAK_TYPE_KEY(0b0011, KC_BSPC);
JAK_TYPE_CAPSABLE(0b0100, KC_L);
JAK_TYPE_KEY(0b0101, KC_SPC);
JAK_TYPE_CAPSABLE(0b0110, KC_P);
JAK_TYPE_CAPSABLE(0b0111, KC_J);
JAK_TYPE_CAPSABLE(0b1000, KC_B);
JAK_TYPE_CAPSABLE(0b1001, KC_X);
JAK_TYPE_CAPSABLE(0b1010, KC_C);
JAK_TYPE_CAPSABLE(0b1011, KC_Y);
JAK_TYPE_CAPSABLE(0b1100, KC_Z);
JAK_TYPE_CAPSABLE(0b1101, KC_Q);
JAK_TYPE_UNICODE(0b1110, "🫡");
JAK_TYPE_KEY(0b1111, KC_ENT);
JAK_PROCESS_FUNCTION_CLOSE;

//0b00110
//0b01001
//0b01101
//0b01110
//0b10001
//0b10011
//0b10100
//0b10111
//0b11001
JAK_PROCESS_FUNCTION_OPEN(5);
JAK_TYPE_KEY(0b00000, KC_5);
JAK_TYPE_KEY(0b00001, KC_4);
JAK_TYPE_KEY(0b00011, KC_3);
JAK_TYPE_KEY(0b00111, KC_2);
JAK_TYPE_KEY(0b01000, KC_AMPR);
JAK_DO_OTHER(0b01100, "Hold Windows/super key for the next press", \
    modifiers |= 0b0001; \
    );
JAK_TYPE_KEY(0b01111, KC_1);
JAK_TYPE_KEY(0b10000, KC_6);
JAK_TYPE_KEY(0b10010, KC_SLSH);
JAK_DO_OTHER(0b10101, "Hold control for the next press", \
    modifiers |= 0b0010; \
    );
JAK_TYPE_KEY(0b10110, KC_LPRN);
JAK_TYPE_KEY(0b11000, KC_7);
JAK_TYPE_KEY(0b11100, KC_8);
JAK_TYPE_KEY(0b11110, KC_9);
JAK_TYPE_KEY(0b11111, KC_0);
JAK_TYPE_KEY(0b11101, KC_ESC);
JAK_TYPE_KEY(0b11010, KC_LBRC);
JAK_TYPE_KEY(0b11011, KC_RBRC);
JAK_TYPE_KEY(0b01010, KC_LCBR);
JAK_TYPE_KEY(0b01011, KC_RCBR);
JAK_TYPE_KEY(0b00100, KC_GRV);
JAK_TYPE_KEY(0b00101, KC_TILD);
JAK_TYPE_KEY(0b00010, KC_TAB);
JAK_PROCESS_FUNCTION_CLOSE;


// so many 6 keycodes unused
//0b001000
//0b001001
//0b001010
//0b001101
//0b001110
//0b001111
//0b010001
//0b010011
//0b010100
//0b010110
//0b010111
//0b011000
//0b011001
//0b011010
//0b011011
//0b011100
//0b011101
//0b011111
//0b100001
//0b100010
//0b100011
//0b100100
//0b100101
//0b100110
//0b100111
//0b101000
//0b101001
//0b101011
//0b101100
//0b101101
//0b101110
//0b101111
//0b110000
//0b110001
//0b110010
//0b110011
//0b110101
//0b110110
//0b110111
//0b111001
//0b111010
//0b111011
//0b111100
//0b111101
//0b111110
//0b111111
JAK_PROCESS_FUNCTION_OPEN(6);
JAK_DO_OTHER(0b000001, "Hold shift for the next press", \
    modifiers |= 0b1000; \
    );
JAK_TYPE_KEY(0b001100, KC_QUES);
JAK_DO_OTHER(0b010000, "Type # and reset keyboard", \
    tap_code16(KC_HASH); \
    reset_keyboard(); \
    );
JAK_TYPE_KEY(0b010010, KC_DQT);
JAK_DO_OTHER(0b010100, "Hold alt for the next press", \
    modifiers |= 0b0100; \
    );
JAK_TYPE_KEY(0b000010, KC_MINS);
JAK_TYPE_UNICODE(0b000110, "😎");
JAK_TYPE_UNICODE(0b000111, "😏");
JAK_TYPE_UNICODE(0b000011, "✨");
JAK_TYPE_UNICODE(0b001011, "🔥");
JAK_TYPE_UNICODE(0b000000, "🗾");
JAK_TYPE_UNICODE(0b110100, "🚠");
JAK_TYPE_UNICODE(0b000100, "👀");
JAK_TYPE_UNICODE(0b000101, "😳");
JAK_TYPE_UNICODE(0b100000, "👍");
JAK_TYPE_KEY(0b010101, KC_DOT);
JAK_TYPE_KEY(0b011110, KC_QUOT);
JAK_TYPE_KEY(0b101010, KC_SCLN);
JAK_TYPE_KEY(0b101011, KC_EXLM);
JAK_TYPE_KEY(0b101101, KC_RPRN);
JAK_TYPE_KEY(0b110011, KC_COMM);
JAK_TYPE_KEY(0b111000, S(KC_SCLN));
JAK_PROCESS_FUNCTION_CLOSE;

JAK_PROCESS_FUNCTION_OPEN(7);
JAK_DO_OTHER(0b0000000, "Set dit duration to 100ms", \
        DIT_DURATION = 100;\
        );
JAK_DO_OTHER(0b0000001, "Set dit duration to 50ms", \
        DIT_DURATION = 50;\
        );
JAK_DO_OTHER(0b0000011, "Toggle locking the shift key", \
        shift_lock = !shift_lock; \
        );
JAK_DO_OTHER(0b1100001, "Switch to next unicode mode", \
        unicode_input_mode_step();\
        );
JAK_DO_OTHER(0b1100000, "Type current unicode input mode", \
        switch(get_unicode_input_mode()) { \
            case UNICODE_MODE_MACOS: \
                SEND_STRING("MacOS"); \
                break; \
            case UNICODE_MODE_WINDOWS: \
                SEND_STRING("Windows"); \
                break; \
            case UNICODE_MODE_LINUX: \
                SEND_STRING("Linux"); \
                break; \
        } \
        );
JAK_PROCESS_FUNCTION_CLOSE;

JAK_PROCESS_FUNCTION_OPEN(9);
JAK_DO_OTHER(0b000111000, "Toggle display of dots and dashes before resolving morse code", \
            if (visible) { \
                visible = false; \
            } else { \
                visible = true; \
            } \
        );
JAK_DO_OTHER(0b111000111, "Toggle turning dots and dashes into the characters they represent in morse code", \
            if (render) { \
                render = false; \
            } else { \
                render = true; \
            } \
        );
JAK_PROCESS_FUNCTION_CLOSE;


#undef JAK_PROCESS_FUNCTION_OPEN
#undef JAK_PROCESS_FUNCTION_CLOSE
#undef JAK_TYPE_KEY
#undef JAK_DO_OTHER

void matrix_scan_user(void) {
    if (timer_started == 0 && timer_ended != 0 && timer_elapsed(timer_ended) > DIT_DURATION * 3) {
        if (visible && render) {
            int del_bits;
            for (del_bits = 0; del_bits < code_length; del_bits++) {
                SEND_STRING(SS_TAP(X_BSPC) SS_DELAY(1));
            }
            SEND_STRING(SS_DELAY(5));
        }

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
                BUT_RENDER(process_7);
                break;
            case 9:
                BUT_RENDER(process_9);
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

        // shift lock is like caps lock for just this keyboard and also does shift a lot
        //if (shift_lock) {
        //    modifiers |= 0b1000;
        //}

        timer_ended = 0;
        code_length = 0;
        code = 0;
    }
}

bool process_detected_host_os_user(os_variant_t detected_os) {
        switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            set_unicode_input_mode(UNICODE_MODE_MACOS);
            break;
        case OS_WINDOWS:
            set_unicode_input_mode(UNICODE_MODE_WINDOWS);
            break;
        case OS_LINUX:
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            break;
        case OS_UNSURE:
            set_unicode_input_mode(UNICODE_MODE_WINDOWS);
            break;
    }

    return true;
}
