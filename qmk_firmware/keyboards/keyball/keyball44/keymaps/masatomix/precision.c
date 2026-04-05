#ifdef PRECISION_ENABLE

#include QMK_KEYBOARD_H

static uint16_t latest_cpi = 1;

// キー押下中だけ切り替え
void precision_switch(bool pressed) {
    if (pressed) {
        latest_cpi = keyball_get_cpi();
        keyball_set_cpi(PRECISION_CPI);
    } else {
        keyball_set_cpi(latest_cpi);
    }
}
#endif
