/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Layer 0. Home-row mods, and - holds layer 2, / holds layer 3.
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , LSFT_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F), LCTL_T(KC_G),                RCTL_T(KC_H), RGUI_T(KC_J), RALT_T(KC_K), KC_L  , LT(2,KC_MINS),
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , LT(3,KC_SLSH),
    KC_LCTL  , KC_ESC   , KC_LALT  , LT(1,KC_GRV), LT(2,KC_SPC), LT(3,KC_TAB), KC_LSFT, KC_BSPC, _______  , _______  , _______  , KC_ENT
  ),

  // Layer 1: function keys and JIS symbols. Thumbs fall through.
  [1] = LAYOUT_universal(
    KC_F2    , KC_F3    , KC_F4    , KC_F5    , KC_F6    ,                            KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    S(KC_1)  , S(KC_2)  , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                            S(KC_6)  , S(KC_7)  , S(KC_8)  , S(KC_9)  , S(KC_EQL),
    KC_F1    , KC_SCLN  , KC_QUOT  , S(KC_INT1), KC_ESC  ,                            KC_RBRC  , KC_BSLS  , KC_INT3  , KC_LBRC  , KC_F12   ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  // Layer 2: numbers and mouse. M0 is Remap macro 0.
  [2] = LAYOUT_universal(
    KC_DEL   , KC_7     , KC_8     , KC_9     , S(KC_SCLN),                           KC_PGUP  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_BTN3  ,
    QK_MACRO_0, KC_4    , KC_5     , KC_6     , KC_MINS  ,                            KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_PSCR  ,
    KC_0     , KC_1     , KC_2     , KC_3     , S(KC_QUOT),                           KC_COMM  , C(KC_C)  , C(KC_V)  , KC_BTN4  , KC_BTN5  ,
    _______  , KC_SLSH  , KC_DOT   , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  // Layer 3: lighting and trackball settings.
  // Left thumbs: snap modes, Boot, Reset; 6th falls through to LT(3) hold.
  [3] = LAYOUT_universal(
    RGB_TOG  , RGB_MOD  , RGB_RMOD , KC_MUTE  , AML_TO   ,                            RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN ,
    RGB_HUI  , RGB_SAI  , RGB_VAI  , KC_VOLU  , SCRL_DVD ,                            RGB_M_K  , RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW ,
    RGB_HUD  , RGB_SAD  , RGB_VAD  , KC_VOLD  , SCRL_DVI ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    SSNP_VRT , SSNP_FRE , SSNP_HOR , QK_BOOT  , KBC_RST  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
