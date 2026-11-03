/*
This is the c configuration file for the keymap

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

#pragma once

#define TAP_CODE_DELAY 5

// ---- Home Row Mods (GACS) 関連設定 ----
//
// TAPPING_TERM: Mod-Tap/Layer-Tap の「タップ」と「ホールド」を判別する閾値(ms)。
//   この時間未満で離す → タップ（例: A）、以上押し続ける → ホールド（例: GUI）。
//   QMK デフォルト: 200ms。Miryoku もデフォルトのまま。
//   短すぎ → ホールド誤発動、長すぎ → モディファイア反応が遅い。
#define TAPPING_TERM 250
#define TAPPING_TERM_PER_KEY       // get_tapping_term() 有効化 (#736 GUI 300ms, #780 F/J 170ms)
#define PERMISSIVE_HOLD_PER_KEY    // get_permissive_hold() 有効化 (#744 F/J のみ)
//
// Achordion (task#1194): 同手ロール (ji / fa 等) での HRM 誤爆対策。keymap.c の
//   achordion_chord() で「次キーが反対手なら hold、同手なら tap」を判定する。
//   対象は home row の Mod-Tap のみ (Layer-Tap / 親指 Mod-Tap は achordion_timeout()=0 で対象外)。
//   ホールド確定後 (反対手キー 1 つ、または 1000ms 経過) は同手キーにも修飾が効く。
//   既知の制限: GUI 単独の 300ms 長押し→離し (Start メニュー) は Achordion では直らない。
//
// PERMISSIVE_HOLD: Mod-Tap キーを押している間に別キーを「押して離した」場合、
//   TAPPING_TERM を待たず即座にホールド（Mod）扱いにする。
//   有効 → Cmd+C 等のショートカットが素早く効く。
//   無効 → 高速タイピング時の誤Mod発動が減る。
//   まずは無効で始めて、ショートカットの反応が遅ければ有効化を検討。
// #define PERMISSIVE_HOLD
//
// QUICK_TAP_TERM: 同じキーを連続タップした時の保護(ms)。
//   前回タップから この時間以内に再度押す → 無条件でタップ扱い（ホールドにならない）。
//   aaa... のキーリピートで GUI 等が暴発するのを防ぐ。
//   0 にすると無効。
#define QUICK_TAP_TERM 120

#define KEYBALL_CPI_DEFAULT 600 // マウス速度 (Keyball default: 700 → 600 に変更、task#1194)
#define KEYBALL_SCROLL_DIV_DEFAULT 6 // スクロール速度 (default: 6)


#define POINTING_DEVICE_AUTO_MOUSE_ENABLE // 有効化
#define AUTO_MOUSE_DEFAULT_LAYER 3 // 切り替えるマウスレイヤー番号を指定 (L_MOUSE)
#define AUTO_MOUSE_TIME 400 // マウスが止まってから元のレイヤーに戻るまでの時間(ms)


#define PRECISION_ENABLE // 有効化
#define PRECISION_CPI 3  // 下げた時のCPI (1/100の値を指定。左記ならCPI 300)

#undef LAYER_STATE_8BIT
#define LAYER_STATE_16BIT
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

#define KEYBALL_SCROLLSNAP_ENABLE 2




