/* Copyright 2021 Woze Parrot
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
#include QMK_KEYBOARD_H
#include <stdio.h>

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _FN,
    _MOUSE
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    FN,
    MOUSE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
                 KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LPRN,    KC_RPRN,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,                 \
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,    KC_RBRC,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_BSPC,    \
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_TAB,     FN,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT,     \
                          KC_ESC,  KC_LGUI, LOWER,   KC_SPC,  MOUSE,      KC_LEAD,  KC_SPC,  RAISE,   KC_RGUI, KC_LALT                        \
    ),
    [_LOWER] = LAYOUT(
                 KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS,    KC_TRNS,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                 \
        KC_TRNS, KC_GRV,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS, KC_QUOT, KC_MINS, KC_EQL,   KC_TRNS,    \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_BSLS,    \
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_LEAD,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS                        \
    ),
    [_RAISE] = LAYOUT(
                 KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS,    KC_TRNS,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                 \
        KC_TRNS, KC_GRV,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS, KC_QUOT, KC_MINS, KC_EQL,   KC_TRNS,    \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_BSLS,    \
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_LEAD,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS                        \
    ),
    [_FN] = LAYOUT(
                 KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,               \
        KC_TRNS, KC_MPLY, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS,    KC_HOME,  KC_PGUP, KC_END,  KC_UP,   KC_TRNS, KC_TRNS,  KC_PSCR,    \
        KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,  KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT,KC_TRNS,  KC_DEL,     \
                          KC_LALT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_LEAD,  KC_TRNS, KC_TRNS, KC_TRNS, KC_RALT                        \
    ),
    [_MOUSE] = LAYOUT(
                 KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,  KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS,  KC_TRNS,    \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,  KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,  KC_TRNS,    \
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_LEAD,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS                        \
    ) 
};

uint8_t current_kps = 0;
uint16_t kps_timer = 0;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (kps_timer > 0) {
        uint8_t latest_kps = 1000 / timer_elapsed(kps_timer);
        current_kps = (latest_kps - current_kps) * 0.0487 + current_kps;
    }
    kps_timer = timer_read();

    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _FN);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _FN);
            }
            return false;
        break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _FN);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _FN);
            }
            return false;
        break;
        case FN:
            if (record->event.pressed) {
                layer_on(_FN);
            } else {
                layer_off(_FN);
            }
            return false;
        break;
        case MOUSE:
            if (record->event.pressed) {
                layer_on(_MOUSE);
            } else {
                layer_off(_MOUSE);
            }
            return false;
        break;
    }

    return true;
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_T) {
            SEND_STRING("The quick brown fox jumps over the lazy dog");
        }
        SEQ_ONE_KEY(KC_C) {
            SEND_STRING("--- Contact ---\nDiscord: wozeparrot#6403\nEmail: wozeparrot@gmail.com\nGithub: wozeparrot\n--- ------- ---\n");
        }
        
        SEQ_TWO_KEYS(KC_S, KC_G) {
            SEND_STRING(SS_LCTL("t") "github.com\n");
        }
        SEQ_TWO_KEYS(KC_S, KC_R) {
            SEND_STRING(SS_LCTL("t") "reddit.com\n");
        }
        SEQ_TWO_KEYS(KC_S, KC_H) {
            SEND_STRING(SS_LCTL("t") "news.ycombinator.com\n");
        }
        SEQ_TWO_KEYS(KC_S, KC_C) {
            SEND_STRING(SS_LCTL("t") "4chan.org\n");
        }
        SEQ_TWO_KEYS(KC_S, KC_Y) {
            SEND_STRING(SS_LCTL("t") "youtube.com\n");
        }
        
        SEQ_ONE_KEY(KC_L) {
            SEND_STRING(SS_LGUI(SS_TAP(X_ENT)) SS_DELAY(1000) "waylock0\n");
        }
    }
}

void render_dd(void) {
    static const char PROGMEM logo[] = {
        // 'qmktest1dd', 32x32px
        0x00, 0xfe, 0x02, 0x02, 0xf2, 0xf2, 0xf2, 0xf2, 0x02, 0x02, 0x02, 0xf2, 0xf2, 0xf2, 0xf2, 0x02,
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0xf2, 0xf2, 0xf2, 0xf2, 0x02, 0x02, 0xfe, 0x00,
        0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00,
        0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00,
        0x00, 0x7f, 0x40, 0x40, 0x4f, 0x4f, 0x4f, 0x4f, 0x40, 0x40, 0x40, 0x4f, 0x4f, 0x4f, 0x4f, 0x40,
        0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x4f, 0x4f, 0x4f, 0x4f, 0x40, 0x40, 0x7f, 0x00
    };

    oled_write_raw_P(logo, sizeof(logo));
}

void render_rr(void) {
    static const char PROGMEM logo[] = {
        // 'qmktest1rr', 32x32px
        0x00, 0xfe, 0x02, 0x02, 0xf2, 0xf2, 0xf2, 0xf2, 0x02, 0x02, 0x02, 0xf2, 0xf2, 0xf2, 0xf2, 0x02,
        0x02, 0xf2, 0xf2, 0xf2, 0xf2, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0xfe, 0x00,
        0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
        0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
        0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
        0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
        0x00, 0x7f, 0x40, 0x40, 0x4f, 0x4f, 0x4f, 0x4f, 0x40, 0x40, 0x40, 0x4f, 0x4f, 0x4f, 0x4f, 0x40,
        0x40, 0x4f, 0x4f, 0x4f, 0x4f, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7f, 0x00
    };

    oled_write_raw_P(logo, sizeof(logo));
}

void render_ll(void) {
    static const char PROGMEM logo[] = {
        // 'qmktest1ll', 32x32px
        0x00, 0xfe, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0xf2, 0xf2, 0xf2, 0xf2, 0x02,
        0x02, 0xf2, 0xf2, 0xf2, 0xf2, 0x02, 0x02, 0x02, 0xf2, 0xf2, 0xf2, 0xf2, 0x02, 0x02, 0xfe, 0x00,
        0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
        0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00,
        0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
        0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00,
        0x00, 0x7f, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x4f, 0x4f, 0x4f, 0x4f, 0x40,
        0x40, 0x4f, 0x4f, 0x4f, 0x4f, 0x40, 0x40, 0x40, 0x4f, 0x4f, 0x4f, 0x4f, 0x40, 0x40, 0x7f, 0x00
    };

    oled_write_raw_P(logo, sizeof(logo));
}

void render_fn(void) {
    static const char PROGMEM logo[] = {
        // 'qmktest1fn', 32x32px
        0x00, 0xfe, 0x02, 0x02, 0xf2, 0xf2, 0xf2, 0xf2, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
        0x02, 0xf2, 0xf2, 0xf2, 0xf2, 0x02, 0x02, 0x02, 0xf2, 0xf2, 0xf2, 0xf2, 0x02, 0x02, 0xfe, 0x00,
        0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00,
        0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00,
        0x00, 0x7f, 0x40, 0x40, 0x4f, 0x4f, 0x4f, 0x4f, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
        0x40, 0x4f, 0x4f, 0x4f, 0x4f, 0x40, 0x40, 0x40, 0x4f, 0x4f, 0x4f, 0x4f, 0x40, 0x40, 0x7f, 0x00
    };

    oled_write_raw_P(logo, sizeof(logo));
}

void oled_next_line(void) {
    oled_advance_char();
    oled_advance_char();
    oled_advance_char();
    oled_advance_char();
    oled_advance_char();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

char kps_str[6];
char wpm_str[6];
void oled_task_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        render_dd();
        break;
        case _FN:
        render_fn();
        break;
        case _RAISE:
        render_rr();
        break;
        case _LOWER:
        render_ll();
        break;
        case _MOUSE:
        render_dd();
        oled_set_cursor(0, 0);
        render_fn();
        oled_render();
        break;
    }

    oled_set_cursor(0, 5);

    sprintf(kps_str, "|%03d|", current_kps);
    oled_write(kps_str, false);

    if (timer_elapsed(kps_timer) > 1000) {
        current_kps = (0 - current_kps) * 0.0487 + current_kps;
        kps_timer = timer_read();
    }

    oled_next_line();

    sprintf(wpm_str, "|%03d|", get_current_wpm());
    oled_write(wpm_str, false);
}
