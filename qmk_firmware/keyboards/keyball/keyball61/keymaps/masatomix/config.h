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

#ifdef RGBLIGHT_ENABLE
// #    define RGBLIGHT_EFFECT_BREATHING
// #    define RGBLIGHT_EFFECT_RAINBOW_MOOD
// #    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
// //#    define RGBLIGHT_EFFECT_SNAKE
// #    define RGBLIGHT_EFFECT_KNIGHT
// //#    define RGBLIGHT_EFFECT_CHRISTMAS
// #    define RGBLIGHT_EFFECT_STATIC_GRADIENT
// //#    define RGBLIGHT_EFFECT_RGB_TEST
// //#    define RGBLIGHT_EFFECT_ALTERNATING
// //#    define RGBLIGHT_EFFECT_TWINKLE
#endif

#define TAP_CODE_DELAY 5

#define KEYBALL_CPI_DEFAULT 700 // マウス速度 (default: 700)
#define KEYBALL_SCROLL_DIV_DEFAULT 6 // スクロール速度 (default: 6)


#define POINTING_DEVICE_AUTO_MOUSE_ENABLE // 有効化
#define AUTO_MOUSE_DEFAULT_LAYER 3 // 切り替えるマウスレイヤー番号を指定
#define AUTO_MOUSE_TIME 500 // マウスが止まってから元のレイヤーに戻るまでの時間(ms)


#define LAYER_LED_ENABLE

#define PRECISION_ENABLE // 有効化
#define PRECISION_CPI 3  // 下げた時のCPI (1/100の値を指定。左記ならCPI 400)

#define DYNAMIC_KEYMAP_LAYER_COUNT 5

#define KEYBALL_SCROLLSNAP_ENABLE 0


// #define MOUSE_LED_COLOR HSV_TURQUOISE
// #define MOUSE_LED_COLOR HSV_BLUE
#define MOUSE_LED_COLOR HSV_AZURE

