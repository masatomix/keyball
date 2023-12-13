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

#ifdef LAYER_LED_ENABLE
#include "layer_led.c"
#endif


#ifdef PRECISION_ENABLE
#include "precision.c"
#endif

enum my_keyball_keycodes {
    LAY_TOG = KEYBALL_SAFE_RANGE,
    PRC_SW,                       // Precision モードスイッチ
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    // _______  , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , LT(3,KC_EQL)   ,
    LCTL_T(KC_ESC) ,KC_A, KC_S     , KC_D     , LT(4,KC_F) , KC_G   ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , RCTL_T(KC_QUOT) ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , _______ ,             _______ ,  KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , RSFT_T(KC_BSLS)  ,
    _______  , _______  , KC_LGUI  , KC_LALT  , LT(4,KC_LNG1),LT(1,KC_SPC),LT(2,KC_LNG2),LT(1,KC_BSPC),LT(2,KC_ENT), LT(1,KC_LNG2),KC_RGUI , _______  ,LT(4,KC_GRAVE)   , LT(4,KC_GRAVE)
  ),

  [1] = LAYOUT_universal(
    // _______  , _______    , KC_F2         , KC_F3    , KC_F4   , KC_F5 ,                              KC_F6  , KC_F7    , KC_F8     , KC_F9    , KC_F10    , KC_F11  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                _______ , _______  , _______   , _______  , _______   , _______ ,
    KC_F11   , LCTL(KC_UP ), LCTL(KC_DOWN), KC_PGUP  , KC_UP   , _______ ,                           _______ , _______  , KC_PSCR   , KC_PGUP  , KC_UP     , _______ ,
   S(KC_LCTL), KC_VOLD    , KC_VOLU       , KC_DEL   , KC_RGHT , LGUI(KC_ESC)       ,                KC_BSPC , KC_DOWN  , KC_UP     , KC_RGHT  , _______   , _______ ,
    _______  , KC_BTN4    , KC_BTN5       , KC_PGDN  , KC_DOWN , KC_LEFT , _______  ,     _______  , KC_DOWN , KC_LEFT  , _______   , KC_PGDN  , _______   , _______ ,
    _______  , _______    , S(KC_LGUI)    , S(KC_LALT), _______, _______ , _______  ,      KC_DEL ,  _______ , _______  , S(KC_RGUI), _______  , S(KC_RALT), _______
  ),

  [2] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______ ,
    RGB_VAD  , RGB_VAI  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______ ,
    RGB_SAD  , RGB_SAI  , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10  , KC_F11  ,
    RGB_HUD  , RGB_HUI  , _______  , _______  , LAY_TOG  , RGB_TOG  , _______  ,            _______ ,  CPI_D100 , CPI_I100 , SCRL_DVD , SCRL_DVI , KBC_SAVE, KC_F12  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______ ,  _______  , _______  , _______  , _______  , KBC_RST , _______
  ),

  [3] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______ ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______ ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , KC_BTN1  , KC_BTN3  , KC_BTN2  , _______ , _______ ,
    _______  , KC_BTN4  , KC_BTN5  , _______  , _______  , _______  , _______  ,            _______ ,  _______  , KC_BTN4  , _______  , KC_BTN5  , _______ , _______ ,
    _______  , _______  , _______  , _______  , _______  , KC_BTN1  , PRC_SW  ,            _______ ,  _______  , _______  , _______  , _______  , _______ , _______
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                   _______   , _______ , _______  , _______  , _______  , _______ ,
    _______  , S(KC_1)  , S(KC_2)  , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                                   S(KC_6)   , S(KC_7) , S(KC_8)  , S(KC_9)  , S(KC_0)  , S(KC_MINS),
    KC_LCTL  , KC_1     , KC_2     , KC_3     , KC_4     , KC_5 ,                                        KC_6     ,   KC_7  , KC_8     , KC_9     , KC_0     , KC_MINS,
    _______  , _______  , _______  , _______  , S(KC_LBRC), KC_LBRC    , _______  ,           _______ , KC_RBRC  ,S(KC_RBRC), _______  , _______  , _______  , _______ ,
    _______  , _______  , _______  , _______  , _______  , _______     , _______  ,           _______ ,  _______  , _______ , _______  , _______  , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 4
    keyball_set_scroll_mode(get_highest_layer(state) == 4);


    #ifdef LAYER_LED_ENABLE
    change_layer_led_color(state);
    #endif

    #ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case 1:
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            break;
        default:
            set_auto_mouse_enable(true);
            break;
    }
    #endif

    return state;
}

// 切り替え処理
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        #ifdef LAYER_LED_ENABLE
        case LAY_TOG: toggle_layer_led(record->event.pressed); return true;
        #endif
        #ifdef PRECISION_ENABLE
        case PRC_SW:  precision_switch(record->event.pressed); return false;
        #endif

        default: break;
    }
    return true;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}
#endif
