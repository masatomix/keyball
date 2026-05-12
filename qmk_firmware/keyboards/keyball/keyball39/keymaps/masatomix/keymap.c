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

// Layer number definitions
#define L_BASE      0  // Base QWERTY (Mac/Win 共通)
#define L_NAV       1  // Navigation
#define L_FKEYS     2  // F-keys
#define L_MOUSE     3
#define L_SYM       4  // Symbols/Numbers

#ifdef LAYER_LED_ENABLE
#include "layer_led.c"
#endif


#ifdef PRECISION_ENABLE
#include "precision.c"
#endif

// Combo: J+K → Esc (#738), D+F → Tab (#749) 5列移行準備
const uint16_t PROGMEM jk_combo[] = {RSFT_T(KC_J), RCTL_T(KC_K), COMBO_END};
const uint16_t PROGMEM df_combo[] = {LCTL_T(KC_D), LSFT_T(KC_F), COMBO_END};
combo_t key_combos[] = {
    COMBO(jk_combo, KC_ESC),
    COMBO(df_combo, KC_TAB),
};

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
    TD_QUO,      // 1タップ=' ダブルタップ=" (#738 5列移行準備)
    TD_EXLM,     // 1タップ=! ダブルタップ=~ (#937)
    TD_AT,       // 1タップ=@ ダブルタップ=` (#937)
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
    [TD_QUO] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, S(KC_QUOT)),     // ' "
    [TD_EXLM] = ACTION_TAP_DANCE_DOUBLE(S(KC_1), S(KC_GRV)),     // ! ~
    [TD_AT]   = ACTION_TAP_DANCE_DOUBLE(S(KC_2), KC_GRV),        // @ `
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Keyball39 LAYOUT_universal:
  //   Row 0-2: 5+5 (外側列なし)
  //   Row 3:   6+6 (親指行、L30/R30 は KC_NO)

  // Layer 0: Base QWERTY (Mac/Win 共通)
  [L_BASE] = LAYOUT_universal(
    KC_Q       , KC_W     , KC_E     , KC_R      , KC_T ,                       KC_Y     , KC_U     , KC_I     , KC_O     , KC_P            ,
    LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), LT(L_MOUSE,KC_G) ,  KC_H     , RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN) ,
    KC_Z       , KC_X     , KC_C     , KC_V      , KC_B ,                       KC_N     , KC_M     , KC_COMM  , KC_DOT   , LT(L_MOUSE,KC_SLSH),
    KC_LSFT    , LALT_T(KC_TAB), LGUI_T(KC_LNG1), MO(L_SYM) ,LT(L_NAV,KC_SPC),LT(L_FKEYS,KC_LNG2),      KC_BSPC,LT(L_NAV,KC_ENT), _______  ,  _______ , _______           , LT(L_SYM,KC_GRAVE)
  ),

  // Layer 1: Navigation
  [L_NAV] = LAYOUT_universal(
    LCTL(KC_UP ), LCTL(KC_DOWN), KC_PGUP  , KC_UP   , KC_F11  ,                        _______ , _______  , _______   , KC_PGUP  , KC_UP     ,
    LGUI_T(KC_VOLD), LALT_T(KC_VOLU), LCTL_T(KC_DEL), LSFT_T(KC_RGHT), LALT(KC_ESC), KC_LEFT, RSFT_T(KC_DOWN), RCTL_T(KC_UP), RALT_T(KC_RGHT), _______,
    KC_BTN4     , KC_BTN5      , KC_PGDN  , KC_DOWN , KC_LEFT ,                        KC_DOWN , _______  , _______   , KC_PGDN  , _______   ,
    _______     , _______      , _______  , _______ , _______ , _______,                        KC_DEL  , _______  , _______   , _______  , _______, _______
  ),

  // Layer 2: F-keys
  [L_FKEYS] = LAYOUT_universal(
    KC_F11   , KC_F12   , _______      , _______  , _______  ,                             _______  , TD(TD_SS1)   , TD(TD_SS2)   , _______  , _______          ,
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                             KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10  ,
    _______  , _______  , _______  , LAY_TOG  , _______  ,                             CPI_D100 , CPI_I100 , SCRL_DVD , SCRL_DVI , KBC_SAVE,
    _______  , _______  , _______  , _______  , _______  , _______,                             _______  , _______  , _______  , _______  , _______, KBC_RST
  ),

  // Layer 3: Mouse
  [L_MOUSE] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                             _______  , _______  , _______  , _______  , _______ ,
    _______  , _______  , _______  , _______  , _______  ,                             _______  , _______  , _______  , _______  , _______ ,
    KC_BTN4  , KC_BTN5  , _______  , _______  , PRC_SW   ,                             _______  , KC_BTN1  , KC_BTN3  , KC_BTN2  , _______  ,
    _______  , _______  , _______  , _______  , KC_BTN1  , _______,                             _______  , _______  , _______  , _______  , _______, _______
  ),

  // Layer 4: Symbols/Numbers
  [L_SYM] = LAYOUT_universal(
    TD(TD_EXLM), TD(TD_AT), S(KC_3) , S(KC_4) , S(KC_5) ,                   S(KC_6)  , S(KC_7)   , S(KC_8) , S(KC_9)  , S(KC_0)  ,
    LGUI_T(KC_1), LALT_T(KC_2), LCTL_T(KC_3), LSFT_T(KC_4), KC_5,          KC_6     , RSFT_T(KC_7), RCTL_T(KC_8), RALT_T(KC_9), RGUI_T(KC_0) ,
    KC_BSLS  ,TD(TD_QUO), TD(TD_PRN), TD(TD_CBR), TD(TD_BRC),                           KC_EQL   , KC_MINS   , _______ , _______  , _______  ,
    _______  , _______  , _______  ,  _______  , _______ , _______,                             _______  , _______   , _______ , _______  , _______, _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is Symbols
    keyball_set_scroll_mode(get_highest_layer(state) == L_SYM);

    // Precision CPI復元ガード: L_MOUSEを抜けたらCPIを戻す (#745)
    #ifdef PRECISION_ENABLE
    if (!layer_state_cmp(state, L_MOUSE)) {
        precision_restore_cpi();
    }
    #endif

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

// Per-key tapping term (#736, #780, #857)
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
        case RGUI_T(KC_SCLN):
        case LGUI_T(KC_LNG1):  // #857 LNG1 IME 切替の GUI 誤爆防止
            return 300;
        case LSFT_T(KC_F):  // #780 Shift判定高速化
        case RSFT_T(KC_J):
            return 170;
        default:
            return TAPPING_TERM;
    }
}

// Per-key PERMISSIVE_HOLD: Shift のみ即ホールド判定で大文字入力を高速化 (#744)
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_F):
        case RSFT_T(KC_J):
            return true;
        default:
            return false;
    }
}

void keyboard_post_init_user(void) {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    set_auto_mouse_enable(true);
#endif
    // スクロールスナップのデフォルトを FREE に設定（縦横両方動くように） (#761)
    keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_FREE);
}
