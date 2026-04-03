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

// Layer number definitions
// Base layers (must be lower than shared/momentary layers)
#define L_MAC_BASE  0
#define L_WIN_BASE  1
// Shared momentary layers
#define L_NAV       2  // Navigation (Mac/Win shared)
#define L_FKEYS     3  // F-keys (Mac/Win shared)
#define L_MOUSE     4
#define L_SYM       5  // Symbols/Numbers (Mac/Win shared)

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

// Tap Dance definitions
enum {
    TD_SS1 = 0,  // 1タップ=Mac スクショ(Cmd+Shift+4), ダブルタップ=Win スクショ(Alt+PrtSc)
    TD_SS2,      // 1タップ=Mac スクショ(Cmd+Shift+5), ダブルタップ=Win スクショ(PrtSc)
    TD_PRN,      // 1タップ=( ダブルタップ=)
    TD_CBR,      // 1タップ={ ダブルタップ=}
    TD_BRC,      // 1タップ=[ ダブルタップ=]
};

// Tap Dance スクショ用コールバック
void td_ss1_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(SGUI(KC_4));        // Mac: Cmd+Shift+4
    } else if (state->count == 2) {
        tap_code16(LALT(KC_PSCR));     // Win: Alt+PrintScreen
    }
}

void td_ss2_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(SGUI(KC_5));        // Mac: Cmd+Shift+5
    } else if (state->count == 2) {
        tap_code16(KC_PSCR);           // Win: PrintScreen
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SS1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ss1_finished, NULL),
    [TD_SS2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ss2_finished, NULL),
    [TD_PRN] = ACTION_TAP_DANCE_DOUBLE(S(KC_9), S(KC_0)),         // ( )
    [TD_CBR] = ACTION_TAP_DANCE_DOUBLE(S(KC_LBRC), S(KC_RBRC)),   // { }
    [TD_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),         // [ ]
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Layer 0: Base QWERTY (Mac)
  [L_MAC_BASE] = LAYOUT_universal(
    KC_TAB         , KC_Q       , KC_W     , KC_E     , KC_R      , KC_T ,                       KC_Y     , KC_U     , KC_I     , KC_O     , KC_P            , KC_EQL,
    KC_ESC         , LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), LT(L_MOUSE,KC_G) ,  KC_H     , RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN) , KC_QUOT,
    KC_NO          , KC_Z       , KC_X     , KC_C     , KC_V      , KC_B ,                       KC_N     , KC_M     , KC_COMM  , KC_DOT   , LT(L_MOUSE,KC_SLSH), KC_BSLS,
                    KC_TAB      ,KC_LNG2   , MO(L_SYM)    ,LT(L_NAV,KC_SPC),MO(L_FKEYS)       ,      KC_BSPC,LT(L_NAV,KC_ENT), _______  ,  _______ , LT(L_SYM,KC_GRAVE)
  ),

  // Layer 1: Base QWERTY (Win) - Alt/Gui swap, RCTL_T(;), layer refs to Win layers
  [L_WIN_BASE] = LAYOUT_universal(
    KC_TAB         , KC_Q       , KC_W     , KC_E     , KC_R      , KC_T ,                       KC_Y     , KC_U     , KC_I     , KC_O     , KC_P            , KC_EQL,
    LCTL_T(KC_ESC) , LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), LT(L_MOUSE,KC_G) ,  KC_H     , RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN) , RCTL_T(KC_QUOT),
    KC_LSFT        , KC_Z       , KC_X     , KC_C     , KC_V      , KC_B ,                       KC_N     , KC_M     , KC_COMM  , KC_DOT   , LT(L_MOUSE,KC_SLSH), RSFT_T(KC_BSLS),
                    KC_LGUI     , KC_LALT  , MO(L_SYM)    ,LT(L_NAV,KC_SPC),LT(L_FKEYS,KC_LNG2),      KC_BSPC,LT(L_NAV,KC_ENT), _______  ,  _______ , LT(L_SYM,KC_GRAVE)
  ),

  // Layer 2: Navigation (Mac/Win shared)
  [L_NAV] = LAYOUT_universal(
    KC_F11   , LCTL(KC_UP ), LCTL(KC_DOWN), KC_PGUP  , KC_UP   , _______ ,                        _______ , _______  , _______   , KC_PGUP  , KC_UP     , _______ ,
   S(KC_LCTL), LGUI_T(KC_VOLD), LALT_T(KC_VOLU), LCTL_T(KC_DEL), LSFT_T(KC_RGHT), LALT(KC_ESC), KC_LEFT, RSFT_T(KC_DOWN), RCTL_T(KC_UP), RALT_T(KC_RGHT), _______, _______,
    _______  , KC_BTN4     , KC_BTN5      , KC_PGDN  , KC_DOWN , KC_LEFT ,                        KC_DOWN , KC_LEFT  , _______   , KC_PGDN  , _______   , _______ ,
               _______     , _______      , _______  , _______ , _______ ,                        KC_DEL  , _______  , _______   , _______  , _______
  ),

  // Layer 3: F-keys (Mac/Win shared) + DF switch
  [L_FKEYS] = LAYOUT_universal(
    RGB_VAD  , RGB_VAI  , _______  , _______      , _______  , _______  ,                             _______  , TD(TD_SS1)   , TD(TD_SS2)   , _______  , DF(L_MAC_BASE)   , DF(L_WIN_BASE)   ,
    RGB_SAD  , RGB_SAI  , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                             KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10  , KC_F11  ,
    RGB_HUD  , RGB_HUI  , KC_F1    , _______  , LAY_TOG  , RGB_TOG  ,                             CPI_D100 , CPI_I100 , SCRL_DVD , SCRL_DVI , KBC_SAVE, KC_F12  ,
               _______  , _______  , _______  , _______  , _______  ,                             _______  , _______  , _______  , _______  , KBC_RST
  ),

  // Layer 4: Mouse (shared)
  [L_MOUSE] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                             _______  , _______  , _______  , _______  , _______ , _______ ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                             _______  , _______  , _______  , _______  , _______ , _______ ,
    _______  , KC_BTN4  , KC_BTN5  , _______  , _______  , PRC_SW   ,                             _______  , KC_BTN1  , KC_BTN3  , KC_BTN2  , _______  , _______ ,
               _______  , _______  , _______  , KC_BTN1  , _______  ,                             _______  , _______  , _______  , _______  , _______
  ),

  // Layer 5: Symbols/Numbers (Mac/Win shared)
  [L_SYM] = LAYOUT_universal(
    S(KC_GRAVE)         , S(KC_1)  , S(KC_2)  , S(KC_3)   , S(KC_4) , S(KC_5) ,                   S(KC_6)  , S(KC_7)   , S(KC_8) , S(KC_9)  , S(KC_0)  , S(KC_MINS),
    LCTL_T(KC_GRAVE)    , LGUI_T(KC_1), LALT_T(KC_2), LCTL_T(KC_3), LSFT_T(KC_4), KC_5,          KC_6     , RSFT_T(KC_7), RCTL_T(KC_8), RALT_T(KC_9), RGUI_T(KC_0) , RCTL_T(KC_MINS),
    KC_LNG1  , KC_BTN4  , KC_BTN5  , TD(TD_PRN), TD(TD_CBR), TD(TD_BRC),                           KC_RBRC  , S(KC_RBRC), _______ , _______  , _______  , _______ ,
               _______  , _______  , _______  ,  _______  , _______ ,                             _______  , _______   , _______ , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is Symbols
    keyball_set_scroll_mode(get_highest_layer(state) == L_SYM);

    #ifdef LAYER_LED_ENABLE
    change_layer_led_color(state);
    #endif

    #ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case L_NAV:  // Navigation (shared)
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


// OS判定ヘルパー
static inline bool is_win_mode(void) {
    return get_highest_layer(default_layer_state) == L_WIN_BASE;
}

// DF永続化: DF()キーコード押下時にEEPROMへ保存
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // DF(layer) キーコードを検出して永続化
    if (keycode >= QK_DEF_LAYER && keycode <= QK_DEF_LAYER_MAX) {
        if (record->event.pressed) {
            uint8_t layer = keycode & 0x1F;
            eeconfig_update_default_layer((layer_state_t)1 << layer);
        }
    }

    switch (keycode) {
        #ifdef LAYER_LED_ENABLE
        case LAY_TOG: toggle_layer_led(record->event.pressed); return true;
        #endif
        #ifdef PRECISION_ENABLE
        case PRC_SW:  precision_switch(record->event.pressed); return false;
        #endif

        // Mod-Morph: Shift+LNG2 → LNG1
        case KC_LNG2: {
            static bool lng1_registered = false;
            if (record->event.pressed) {
                uint8_t mods = get_mods();
                if (mods & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_LNG1);
                    lng1_registered = true;
                    set_mods(mods);
                    return false;
                }
            } else {
                if (lng1_registered) {
                    unregister_code(KC_LNG1);
                    lng1_registered = false;
                    return false;
                }
            }
            return true;
        }

        // Mod-Morph: Shift+Backspace → Delete
        case KC_BSPC: {
            static bool del_registered = false;
            if (record->event.pressed) {
                uint8_t mods = get_mods();
                if (mods & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    del_registered = true;
                    set_mods(mods);
                    return false;
                }
            } else {
                if (del_registered) {
                    unregister_code(KC_DEL);
                    del_registered = false;
                    return false;
                }
            }
            return true;
        }

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

// Per-key tapping term: GUI キーは誤爆しやすいため長めに設定 (#736)
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
        case RGUI_T(KC_SCLN):
            return 300;
        default:
            return TAPPING_TERM;
    }
}

// DF永続化: 起動時にEEPROMからデフォルトレイヤーを復元
void keyboard_post_init_user(void) {
    if (eeconfig_is_enabled()) {
        layer_state_t dl = eeconfig_read_default_layer();
        if (dl) {
            default_layer_set(dl);
        }
    }
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    set_auto_mouse_enable(true);
#endif
}
