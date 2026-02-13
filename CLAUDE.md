# CLAUDE.md

このファイルはClaude Code (claude.ai/code) がこのリポジトリで作業する際のガイダンスを提供します。

## プロジェクト概要

QMK (Quantum Mechanical Keyboard) ファームウェアはAVR・ARMマイコン向けのオープンソースキーボードファームウェア。レイヤーキーマップシステム、マクロ、RGB照明、オーディオ、OLEDディスプレイ、ポインティングデバイスなどの機能をサポートしている。

## ビルドコマンド

ビルド書式: `make keyboard_folder:keymap_folder[:target]`

```bash
# ファームウェアのビルド
make planck/rev6:default

# ビルド＆書き込み
make planck/rev6:default:flash

# QMK CLIでの同等コマンド
qmk compile -kb planck/rev6 -km default
qmk flash -kb planck/rev6 -km default

# ビルド成果物のクリーン
make clean
qmk clean

# 並列ビルド（サブmakeに適用、トップレベルは.NOTPARALLELのため無効）
make planck/rev6:default -j4

# IDE連携用 compile_commands.json の生成
qmk compile -kb planck/rev6 -km default --compiledb
```

## テスト

Google Test / Google Mock を使用（`lib/`配下）。ビルド成果物は`.build/`へ出力。

```bash
# 全テスト実行
make test:all

# 特定テストグループの実行
make test:basic
make test:tap_hold_configurations
make test:combo

# 利用可能なテストグループ（tests/配下）:
# audio, auto_shift, autocorrect, basic, caps_word, combo, leader,
# no_tapping, repeat_key, secure, tap_dance, tap_hold_configurations,
# tri_layer, unicode
```

各テストグループは`tests/`配下のディレクトリで、以下を含む:
- `test_*.cpp` — Google Testテストケース
- `config.h` — テスト用機能設定
- `test.mk` — テスト固有のビルドルール（ソースファイル、機能フラグ）

共通テスト基盤は`tests/test_common/`（TestFixture、KeymapKey、TestDriver）。

## リント＆フォーマット

```bash
# Cコードのフォーマット（.clang-format設定を使用）
clang-format -style=file -i <file.c>

# QMK CLIでのフォーマット
qmk format-c
qmk format-json
qmk format-python

# キーボードのリント
qmk lint -kb <keyboard>
```

LAYOUTマクロはclang-formatで壊れるため、`// clang-format off` / `// clang-format on`で囲むこと。

## アーキテクチャ

### レイヤー構成（下層から上層）

1. **`tmk_core/`** — TMKベースファームウェア層。プロトコル実装（AVR向けLUFA、ARM向けChibiOS）、HIDレポート生成、USBディスクリプタ、ホストドライバインターフェース。

2. **`platforms/`** — MCU/プラットフォーム抽象化層。AVR、ARM（ChibiOS、ATSAM）、テストプラットフォーム間の差異、フラッシュ・ブートローダロジックを担当。

3. **`quantum/`** — QMK拡張層。コアアクション処理（`action.c`, `action_tapping.c`, `action_layer.c`）、キーコード定義（`keycodes.h`）、マトリクススキャン（`matrix.c`）、各機能（オーディオ、RGB、エンコーダ、ポインティングデバイスなど）をサブディレクトリとして配置。

4. **`keyboards/`** — キーボード定義。最大5階層の深さ（`keyboards/メーカー/モデル/リビジョン/`）。各階層の`rules.mk`、`config.h`、`info.json`がカスケード適用される。

5. **`keymaps/`** — 各キーボードディレクトリ配下。`keymap.c`（または`keymap.json`）で各レイヤーの実際のキー配置を定義。

### キーボード定義の構成

キーボードは`keyboards/<パス>/`配下のファイルで定義:
- **`info.json`** — メタデータ: メーカー名、MCU、ピンマトリクス、USB ID、機能フラグ、物理キー座標レイアウト
- **`rules.mk`** — ビルドフラグ: 機能有効化（`RGBLIGHT_ENABLE`、`ENCODER_ENABLE`等）、MCU設定、ドライバ選択
- **`config.h`** — Cプリプロセッサ設定: マトリクスサイズ、ピン割当、タイミング値、機能パラメータ
- **`<keyboard>.c`** — オプションのボードレベルCコード（LEDコールバック、エンコーダハンドラ等）

### ビルドシステムフロー

`make keyboard:keymap` → トップレベルMakefileがルール解析 → `builddefs/build_keyboard.mk`がキーボードパス階層を解決 → 全カスケード`rules.mk`・`config.h`をインクルード → QMK CLIが`info.json`から`info_config.h`・`info_rules.mk`を生成 → quantum + platform + keyboard + keymapソースをコンパイル → ファームウェアバイナリにリンク。

### Quantum主要コンセプト

- **キーコード**（`quantum/keycodes.h`）: `QK_*`プレフィックスの範囲。キーマップでカスタムキーコードを定義する場合は`SAFE_RANGE`（= `QK_USER`）を開始値に使う。
- **レイヤー操作**: `MO(layer)` モメンタリ、`TO(layer)` 遷移、`TG(layer)` トグル、`LT(layer, kc)` レイヤータップ、`DF(layer)` デフォルトレイヤー変更。
- **Mod-Tap**: `MT(mod, kc)` — タップでキーコード、ホールドでモディファイア。`LCTL_T(kc)`、`LSFT_T(kc)`等の便利マクロあり。
- **ワンショット**: `OSM(mod)` ワンショットモディファイア、`OSL(layer)` ワンショットレイヤー。
- **機能プロセッサ**: `quantum/process_keycode/` — 各機能（auto-shift、caps word、combo等）が`process_*()`関数でキーコード処理にフック、`quantum.c`から呼ばれる。

## masatomix 自作データ

### ビルドコマンド

```bash
# Keyball61 masatomixキーマップ
make keyball/keyball61:masatomix

# Keyball44 masatomixキーマップ
make keyball/keyball44:masatomix

# Keyball61 my_via キーマップ
make keyball/keyball61:my_via

# mugen（自作分割キーボード）
make mugen:default
make mugen:via
```

### 自作キーボード: mugen

パス: `keyboards/mugen/`

ATmega32u4ベースの自作分割キーボード。左右各4行x6列のマトリクス。

| ファイル | 内容 |
|---|---|
| `info.json` | MCU: atmega32u4、COL2ROW、USB VID/PID: 0xFEED/0x0000 |
| `config.h` | マトリクスピン定義（ROW: C6,D7,E6,B4 / COL: F4,F5,F6,F7,B1,B3）、SOFT_SERIAL_PIN: D2、WS2812: D3（LED 48個=左右24個ずつ）、5レイヤー |
| `rules.mk` | SPLIT_KEYBOARD=yes、VIA_ENABLE=yes、RGBLIGHT_ENABLE=yes、LTO_ENABLE=yes |
| `keymaps/via/info.json` | VIA用のキーボード定義JSON（8行x6列マトリクス） |

defaultキーマップの特徴:
- レイヤーごとにRGB色を切り替え（0:ターコイズ、1:青、2:緑、3:白、4:赤）
- Tri Layer対応（Layer1 + Layer2 → Layer3）
- CONSOLE_ENABLEでキー押下のデバッグログ出力

### Keyballキーマップ: masatomix

Keyball（トラックボール付き分割キーボード）用のカスタムキーマップ。keyball61とkeyball44の2モデルで展開。

#### ファイル構成（keyball61/keyball44共通パターン）

```
keyboards/keyball/keyball{61,44}/keymaps/masatomix/
├── keymap.c       — メインキーマップ定義
├── config.h       — 設定パラメータ
├── rules.mk       — RGBLIGHT, OLED, VIA, EXTRAKEY有効化
├── layer_led.c    — レイヤーLED色変更機能
└── precision.c    — Precisionモード（CPI低下）機能
```

#### 独自機能モジュール

**layer_led.c** — マウスレイヤー検知でLED色を自動変更
- マウスレイヤー(Layer 3)に入ると`MOUSE_LED_COLOR`（デフォルト: HSV_AZURE）でLEDを点灯
- それ以外のレイヤーではLEDを消灯（val=0）
- `LAY_TOG`キーで機能のON/OFFを切り替え
- `config.h`で`#define LAYER_LED_ENABLE`で有効化
- `#define MOUSE_LED_COLOR HSV_AZURE`で色を変更可能

**precision.c** — キー押下中にトラックボールのCPIを一時的に下げる
- `PRC_SW`キーを押している間だけCPIが`PRECISION_CPI`の値に低下
- キーを離すと元のCPIに復帰
- `config.h`で`#define PRECISION_ENABLE`で有効化
- `#define PRECISION_CPI 3`で低速時CPI設定（値は1/100単位、3 = CPI 300）

#### カスタムキーコード

`keymap.c`内で`KEYBALL_SAFE_RANGE`を起点に定義:
- `LAY_TOG` — Layer LED機能のトグル
- `PRC_SW` — Precisionモードスイッチ（押下中のみ有効）

#### keyball61 キーマップ レイヤー構成（5レイヤー）

| Layer | 役割 | 主な内容 |
|---|---|---|
| 0 | ベース | QWERTY配列。`LCTL_T(KC_ESC)`でCtrl/Esc兼用。`LT(3,KC_D)`,`LT(4,KC_F)`でレイヤー切替兼用キー |
| 1 | ナビゲーション | 矢印キー、PgUp/PgDn、音量、`LGUI(KC_ESC)`でタスク切替 |
| 2 | 設定 | RGB制御、CPI調整（`CPI_D100`/`CPI_I100`）、スクロール設定、`KBC_SAVE`/`KBC_RST` |
| 3 | マウス（自動切替） | `KC_BTN1`〜`KC_BTN5`配置。`PRC_SW`でPrecisionモード。AUTO_MOUSEで自動遷移 |
| 4 | 記号・数字 | Shiftキー記号（`S(KC_1)`〜`S(KC_0)`）、数字行、括弧類。Layer4でスクロールモード有効化 |

#### keyball44 キーマップ レイヤー構成（7レイヤー設定、実装は0,1,2,3,6）

| Layer | 役割 | 主な内容 |
|---|---|---|
| 0 | ベース | QWERTY配列。keyball61と類似だが行数が少ないためコンパクト構成 |
| 1 | ナビゲーション | keyball61 Layer1と同様 |
| 2 | 設定 | RGB制御、Fキー、CPI/スクロール調整。`LGUI(KC_E)`、`LALT(KC_PSCR)` 追加 |
| 3 | マウス（自動切替） | keyball61 Layer3と同様 |
| 6 | 記号・数字 | keyball61 Layer4に相当。Layer6でスクロールモード有効化 |

#### keyball61 と keyball44 の主な差異

| 項目 | keyball61 | keyball44 |
|---|---|---|
| レイアウト | 5行（数字行あり） | 3行（数字行なし） |
| レイヤー数 | 5 (`DYNAMIC_KEYMAP_LAYER_COUNT 5`) | 7 (`DYNAMIC_KEYMAP_LAYER_COUNT 7`) |
| 記号・数字レイヤー | Layer 4 | Layer 6 |
| スクロールモード有効化レイヤー | Layer 4 | Layer 6 |
| AUTO_MOUSE_TIME | 500ms | 400ms |
| Precision CPI コメント記載値 | CPI 400 | CPI 300 |
| Layer1でのauto mouse無効化 | あり | あり |

#### config.h 共通設定パラメータ

```c
#define TAP_CODE_DELAY 5
#define KEYBALL_CPI_DEFAULT 700      // マウス速度
#define KEYBALL_SCROLL_DIV_DEFAULT 6 // スクロール速度
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 3   // 自動マウスレイヤー
#define KEYBALL_SCROLLSNAP_ENABLE 0  // スクロールスナップ無効
#define MOUSE_LED_COLOR HSV_AZURE    // マウスレイヤーLED色
```

### Keyball ライブラリ参照

Keyball共通ライブラリは `keyboards/keyball/lib/` にある:
- `keyball/keyball.h` — Keyball設定定数、カスタムキーコード定義（`KBC_RST`, `KBC_SAVE`, `CPI_I100`, `CPI_D100`, `SCRL_DVD`, `SCRL_DVI`等）、`KEYBALL_SAFE_RANGE`（ユーザー定義キーコードの起点）
- `oledkit/oledkit.c` — OLED表示ヘルパー（`keyball_oled_render_keyinfo()`, `keyball_oled_render_ballinfo()`, `keyball_oled_render_layerinfo()`）
- `duplexmatrix/` — デュプレックスマトリクス実装
- `drivers/pmw3360/` — トラックボールセンサードライバ

### テスト・サンプルキーボード

以下はテスト・学習目的で作成されたもの（本番利用ではない）:
- `keyboards/testtest/` — テスト用
- `keyboards/sample_hoge/` — サンプル
- `keyboards/sample/` — サンプル

## Cコーディング規約

- 4スペースインデント（ソフトタブ）。Makefileのみ実タブ使用。
- 修正版One True Brace Style: 開き波括弧は行末、オプションの波括弧も常に含める。
- ヘッダガードには`#pragma once`を使用（`#ifndef`方式は使わない）。
- ドキュメントにはCスタイルコメント（`/* */`）を推奨。
- `#ifdef X`と`#if defined(X)`の両方を受け入れるが、新規コードでは`#if defined()`を推奨。
- 既存コードのスタイルを変更しない。周囲のコードスタイルに合わせること。
