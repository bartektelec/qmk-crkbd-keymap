/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H
#include <stdio.h>
enum layers { _QWERTY = 0, _LOWER, _RAISE, _ADJUST, _MOUSE };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_LGUI,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   MO(1),  KC_SPC,     KC_ENT,   MO(2),  KC_BSPC
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F1,   KC_F2,   KC_F3,  KC_F4,   KC_F5,   KC_F6,                         KC_F7,    KC_F8,   KC_F9,   KC_F10,   KC_F11, KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_GRV,  KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                         KC_CIRC,   KC_AMPR, KC_ASTR,KC_LPRN, KC_RPRN, KC_TILD,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______,     _______,   _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV, KC_1,   KC_2,    KC_3,     KC_4,    KC_5,                         KC_6,     KC_7,    KC_8,    KC_9,   KC_0,    XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT,  KC_DOWN, KC_UP, KC_RGHT, XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PLUS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,   _______,  _______,     _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CG_TOGG, AG_TOGG,             KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MEDIA_PLAY_PAUSE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_AUDIO_MUTE, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______,   _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}



#ifdef OLED_ENABLE

char wpm_str[10];


static void render_mod_keys(uint8_t const modifiers, uint8_t const col, uint8_t const line) {
    static const char PROGMEM mod_status[5][3] = {
        {0x88, 0x89, 0},
        {0x84, 0x85, 0},
        {0x86, 0x87, 0},
        {0x8A, 0x8B, 0},
        {0x8C, 0x8D, 0}};
    oled_set_cursor(col, line);

    oled_write_P(mod_status[0], (modifiers & MOD_MASK_SHIFT));
    oled_write_P(mod_status[!keymap_config.swap_lalt_lgui ? 3 : 4], (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR(" "), false);
    oled_write_P(mod_status[2], (modifiers & MOD_MASK_ALT));
    oled_write_P(mod_status[1], (modifiers & MOD_MASK_CTRL));
}



void render_bootmagic_status(uint8_t col, uint8_t line) {
    /* Show Ctrl-Gui Swap options */
    oled_set_cursor(col, line);

    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xAD, 0xAE, 0}},
        {{0x95, 0x96, 0}, {0xAB, 0xAC, 0}},
    };
    if (keymap_config.swap_lalt_lgui) {
        oled_write_P(logo[1][0], false);
        oled_set_cursor(col, line + 1);
        oled_write_P(logo[1][1], false);
    } else {
        oled_write_P(logo[0][0], false);
        oled_set_cursor(col, line + 1);
        oled_write_P(logo[0][1], false);
    }
}

/**
 * @brief Renders the active layers to the OLED
 *
 */
void render_layer_state(uint8_t col, uint8_t line) {
    // clang-format off
    static const char PROGMEM tri_layer_image[][3][24] = {
        // base
        {
            {
                0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
                0x40, 0x20, 0x20, 0x10, 0x10, 0x08,
                0x08, 0x10, 0x10, 0x20, 0x20, 0x40,
                0x40, 0x80, 0x80, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x88, 0x88, 0x5D,
                0x5D, 0x3E, 0x3E, 0x7C, 0x7C, 0xF8,
                0xF8, 0x7C, 0x7C, 0x3E, 0x3E, 0x5D,
                0x5D, 0x88, 0x88, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                0x01, 0x02, 0x02, 0x04, 0x04, 0x08,
                0x08, 0x04, 0x04, 0x02, 0x02, 0x01,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        },
        // raise
        {
            {
                0x00, 0x00, 0x00, 0x80, 0x80, 0xC0,
                0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF8,
                0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0,
                0xC0, 0x80, 0x80, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x88, 0x88, 0x55,
                0x55, 0x23, 0x23, 0x47, 0x47, 0x8F,
                0x8F, 0x47, 0x47, 0x23, 0x23, 0x55,
                0x55, 0x88, 0x88, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                0x01, 0x02, 0x02, 0x04, 0x04, 0x08,
                0x08, 0x04, 0x04, 0x02, 0x02, 0x01,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        },
        // lower
        {
            {
                0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
                0x40, 0x20, 0x20, 0x10, 0x10, 0x08,
                0x08, 0x10, 0x10, 0x20, 0x20, 0x40,
                0x40, 0x80, 0x80, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x88, 0x88, 0xD5,
                0xD5, 0xE2, 0xE2, 0xC4, 0xC4, 0x88,
                0x88, 0xC4, 0xC4, 0xE2, 0xE2, 0xD5,
                0xD5, 0x88, 0x88, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                0x01, 0x03, 0x03, 0x07, 0x07, 0x0F,
                0x0F, 0x07, 0x07, 0x03, 0x03, 0x01,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        },
        // adjust
        {
            {
                0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
                0xC0, 0x60, 0xA0, 0x50, 0xB0, 0x58,
                0xA8, 0x50, 0xB0, 0x60, 0xA0, 0x40,
                0xC0, 0x80, 0x80, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x88, 0x88, 0x5D,
                0xD5, 0x6B, 0xB6, 0x6D, 0xD6, 0xAD,
                0xDA, 0x6D, 0xD6, 0x6B, 0xB6, 0x5D,
                0xD5, 0x88, 0x88, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                0x01, 0x03, 0x02, 0x05, 0x06, 0x0D,
                0x0A, 0x05, 0x06, 0x03, 0x02, 0x01,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        },
        // blank
        {
            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
        },
        // mouse
        {
            { 0,  0,  0,  0,  0,  0,  0,  0,192, 32, 32, 32,160, 32, 32, 32,192,  0,  0,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  0,  0,240, 15,  0,  0,  0,  3,  0,  0,  0, 15,240,  0,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  0,  0,  3,  6,  4,  4,  4,  4,  4,  4,  4,  6,  3,  0,  0,  0,  0,  0,  0 }
        }
    };

  #define L_BASE 0
  #define L_RAISE 1
  #define L_LOWER 2
  #define L_ADJUST 3
  #define L_BLANK 4
  #define L_MOUSE 5

    // clang-format on
    uint8_t layer_is[4] = {L_BASE, L_BLANK};
    if (layer_state_is(_ADJUST)) {
        layer_is[0] = L_ADJUST;
    } else if (layer_state_is(_RAISE)) {
        layer_is[0] = L_RAISE;
    } else if (layer_state_is(_LOWER)) {
        layer_is[0] = L_LOWER;
    }

    if (layer_state_is(_MOUSE)) {
        layer_is[1] = L_MOUSE;
    }

    oled_set_cursor(col, line);
    oled_write_raw_P(tri_layer_image[layer_is[0]][0], sizeof(tri_layer_image[0][0]));

    oled_set_cursor(col, line + 1);
    oled_write_raw_P(tri_layer_image[layer_is[0]][1], sizeof(tri_layer_image[0][0]));

    oled_set_cursor(col, line + 2);
    oled_write_raw_P(tri_layer_image[layer_is[0]][2], sizeof(tri_layer_image[0][0]));

}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_270;
    }
}

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(crkbd_logo, false);
}


void render_status_main(void) {
    /* Show Keyboard Layout  */
    uint8_t mods = get_mods();
    oled_set_cursor(1,0);
    oled_write_P(PSTR(" "), false);
    oled_write_ln(wpm_str, false);
    render_bootmagic_status(2, 3);
    render_layer_state(1, 6);
    // render_os();

    render_mod_keys(mods, 1, 12);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        sprintf(wpm_str, "%03d", get_current_wpm());
        render_status_main(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        // render_crkbd_logo();
    }
    return false;
}

#endif
