// US(ANSI) keymap -> JIS host translation.
//
// Based on m47ch4n/qmk-translate-ansi-to-jis (MIT License).
//   https://github.com/m47ch4n/qmk-translate-ansi-to-jis
// Vendored into this keymap and extended with a2j_translate() so that the
// same translation table can also be reused from Tap Dance / Layer-Tap
// callbacks (which bypass process_record_user). (#1019)

#pragma once

#include "quantum.h"

// Route a key event through the ANSI->JIS translation table.
// Returns false (HANDLED) if the key was translated & emitted here,
// true (NOT_HANDLED) otherwise (caller should keep processing).
// Call this only when the connected host uses a JIS layout (Windows).
bool process_record_user_a2j(uint16_t keycode, keyrecord_t *record);

// Translate a single (possibly shift-embedded) keycode to its JIS
// equivalent. Returns the JIS keycode if the table has a mapping,
// otherwise returns kc unchanged. For use from Tap Dance / LT tap
// callbacks that emit via tap_code16() and never reach a2j above.
uint16_t a2j_translate(uint16_t kc);
