#include QMK_KEYBOARD_H
#include "encoder.h"

void encoder_update_voidpad(uint8_t index, bool clockwise) {
#define LAYER_COUNT 4
    static uint8_t layer = 0;
    if (index == 0) {
        if (layer == LAYER_COUNT - 1 && get_mods() & MOD_BIT(KC_RIGHT_CTRL)) {
            if (clockwise) oled_set_brightness(oled_get_brightness() + 20);
            else oled_set_brightness(oled_get_brightness() - 20);
        }
        else {
            if (clockwise) {
                layer++;
                if (layer >= LAYER_COUNT) layer = LAYER_COUNT - 1;
            }
            else {
                layer--;
                if (layer < 0) layer = 0;
            }
            layer_move(layer);
        }
    }
}
