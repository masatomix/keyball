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

#define KEYBALL_CPI_DEFAULT 700 // マウス速度 (default: 700)
#define KEYBALL_SCROLL_DIV_DEFAULT 6 // スクロール速度 (default: 6)


#define POINTING_DEVICE_AUTO_MOUSE_ENABLE // 有効化
#define AUTO_MOUSE_DEFAULT_LAYER 4 // 切り替えるマウスレイヤー番号を指定 (L_MOUSE)
#define AUTO_MOUSE_TIME 400 // マウスが止まってから元のレイヤーに戻るまでの時間(ms)


#define PRECISION_ENABLE // 有効化
#define PRECISION_CPI 3  // 下げた時のCPI (1/100の値を指定。左記ならCPI 300)

#undef LAYER_STATE_8BIT
#define LAYER_STATE_16BIT
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

#define KEYBALL_SCROLLSNAP_ENABLE 2



