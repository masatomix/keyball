// US(ANSI) keymap -> JIS host translation.
//
// Based on m47ch4n/qmk-translate-ansi-to-jis (MIT License).
//   https://github.com/m47ch4n/qmk-translate-ansi-to-jis
//   Copyright (c) m47ch4n
// Vendored & extended for this keymap (#1019): internal symbols are made
// static to avoid clashing with QMK's global namespace, and a2j_translate()
// is exported so Tap Dance / LT callbacks can share the one table.

#include QMK_KEYBOARD_H
#include "translate_ansi_to_jis.h"

#define HANDLED false
#define NOT_HANDLED true

// ANSI keycode -> JIS keycode. Keyed on the (shift-embedded) ANSI keycode,
// e.g. KC_AT == S(KC_2), so process_record_user_a2j re-derives the embedded
// keycode from get_mods() before looking it up.
static const uint16_t translate_map[][2] = {
    // clang-format off
    // ANSI    JIS
    {KC_EQL,  S(KC_MINS)},
    {KC_LBRC, KC_RBRC},
    {KC_BSLS, KC_INT3},
    {KC_RBRC, KC_NUHS},
    {KC_QUOT, S(KC_7)},
    {KC_GRV,  S(KC_LBRC)},
    {KC_RPRN, S(KC_9)},
    {KC_AT,   KC_LBRC},
    {KC_CIRC, KC_EQL},
    {KC_AMPR, S(KC_6)},
    {KC_ASTR, S(KC_QUOT)},
    {KC_LPRN, S(KC_8)},
    {KC_PLUS, S(KC_SCLN)},
    {KC_UNDS, S(KC_INT1)},
    {KC_LCBR, S(KC_RBRC)},
    {KC_PIPE, S(KC_INT3)},
    {KC_RCBR, S(KC_NUHS)},
    {KC_COLN, KC_QUOT},
    {KC_DQT,  S(KC_2)},
    {KC_TILD, S(KC_EQL)},
    // clang-format on
};

static const size_t a2j_rows = sizeof(translate_map) / sizeof(translate_map[0]);

// Raw table lookup. Returns 0 when there is no mapping.
static uint16_t a2j_find(uint16_t kc) {
    for (size_t index = 0; index < a2j_rows; index++) {
        if (translate_map[index][0] == kc) return translate_map[index][1];
    }
    return 0;
}

uint16_t a2j_translate(uint16_t kc) {
    uint16_t jis = a2j_find(kc);
    return jis ? jis : kc;
}

#define PUSH_NONE 0
// Assumes that multiple symbolic keys will never be used at the same time.
static uint16_t pushing_shift_embeded_basic_kc = PUSH_NONE;

bool process_record_user_a2j(uint16_t kc, keyrecord_t *record) {
    // Mod-Tap / Layer-Tap (>QK_MODS_MAX) は対象外。これらの mod ニブルを
    // QK_MODS_GET_MODS で読むと埋め込み Shift と誤判定し、例えば RSFT_T(KC_7)
    // のタップが S(KC_7)=& と誤変換される (#1024)。QK_MODS と素のキーのみ扱い、
    // Mod-Tap/Layer-Tap のタップは keymap.c 側(process_record_user)で変換する。
    if (kc > QK_MODS_MAX) return NOT_HANDLED;

    uint8_t mods_kc  = QK_MODS_GET_MODS(kc);
    uint8_t basic_kc = QK_MODS_GET_BASIC_KEYCODE(kc);

    if (record->event.pressed) {
        uint8_t  mod_state                    = get_mods();
        bool     shift_state_or_shift_embeded = (mod_state | mods_kc) & MOD_MASK_SHIFT;
        uint16_t shift_embeded_basic_kc       = shift_state_or_shift_embeded ? S((uint16_t)basic_kc) : basic_kc;
        uint16_t shift_embeded_basic_jis_kc   = a2j_find(shift_embeded_basic_kc);

        if (!shift_embeded_basic_jis_kc) return NOT_HANDLED;

        if (pushing_shift_embeded_basic_kc != PUSH_NONE) {
            uint16_t pushing_basic_kc = QK_MODS_GET_BASIC_KEYCODE(pushing_shift_embeded_basic_kc);
            unregister_code16(pushing_basic_kc);
        }

        if (mod_state & MOD_MASK_SHIFT) {
            del_mods(MOD_MASK_SHIFT);
            register_code16(shift_embeded_basic_jis_kc);
            set_mods(mod_state);
        } else {
            register_code16(shift_embeded_basic_jis_kc);
        }
        pushing_shift_embeded_basic_kc = shift_embeded_basic_kc;
        return HANDLED;
    }

    // if keycode is the same as previous one without mods.
    if (basic_kc == QK_MODS_GET_BASIC_KEYCODE(pushing_shift_embeded_basic_kc)) {
        unregister_code16(a2j_find(pushing_shift_embeded_basic_kc));
        pushing_shift_embeded_basic_kc = PUSH_NONE;
        return HANDLED;
    }

    return NOT_HANDLED;
}
