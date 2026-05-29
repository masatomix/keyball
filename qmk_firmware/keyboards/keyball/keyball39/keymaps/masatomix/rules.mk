RGBLIGHT_ENABLE = no

OLED_ENABLE = yes

# VIA は GUI ツール不使用方針 (#1019) のため無効化。
# os_detection / Key Override 等は VIA(Vial 含む) では扱えず、
# dynamic keymap を切ってフラッシュ容量を確保する。
VIA_ENABLE = no

EXTRAKEY_ENABLE = yes

# CONSOLE_ENABLE = yes

TAP_DANCE_ENABLE = yes

COMBO_ENABLE = yes

# OS 自動判別 (Windows=JIS / Mac=US 素通し) (#1019)
OS_DETECTION_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

# US(ANSI) -> JIS host 変換テーブル
SRC += translate_ansi_to_jis.c
