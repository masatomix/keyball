#ifdef PRECISION_ENABLE

#include QMK_KEYBOARD_H

static uint16_t latest_cpi = 1;
static bool     cpi_state  = false;

// キー押下中だけ切り替え
void precision_switch(bool pressed) {
    if (pressed) {
        if (!cpi_state) {
            latest_cpi = keyball_get_cpi();
        }
        cpi_state = true;
        keyball_set_cpi(PRECISION_CPI);
    } else {
        cpi_state = false;
        keyball_set_cpi(latest_cpi);
    }
}

// レイヤー離脱時のCPI復元ガード (#745)
void precision_restore_cpi(void) {
    if (cpi_state) {
        cpi_state = false;
        keyball_set_cpi(latest_cpi);
    }
}
#endif
