#include QMK_KEYBOARD_H
#include "oled.h"

void draw_layer_keys(
    const char* encoder,
    const char* n7, const char* n8, const char* n9,
    const char* n4, const char* n5, const char* n6,
    const char* n1, const char* n2, const char* n3
) {
    oled_set_cursor(14, 1);
    oled_write_P(encoder, false);

    oled_set_cursor(0, 3);
    oled_write_P(n7, false);
    oled_set_cursor(7, 3);
    oled_write_P(n8, false);
    oled_set_cursor(14, 3);
    oled_write_P(n9, false);

    oled_set_cursor(0, 5);
    oled_write_P(n4, false);
    oled_set_cursor(7, 5);
    oled_write_P(n5, false);
    oled_set_cursor(14, 5);
    oled_write_P(n6, false);

    oled_set_cursor(0, 7);
    oled_write_P(n1, false);
    oled_set_cursor(7, 7);
    oled_write_P(n2, false);
    oled_set_cursor(14, 7);
    oled_write_P(n3, false);

    for (uint8_t i = 1; i < 8; i++)
    {
        if (i > 1) {
            oled_set_cursor(6, i);
            oled_write_char((char)28, false);
        }
        oled_set_cursor(13, i);
        oled_write_char((char)28, false);
    }

    for (uint8_t i = 0; i < 21; i++)
    {
        char symbol = (char)30;
        if (i != 20 && i % 7 == 6) {
            symbol = (char)26;
        }
        oled_set_cursor(i, 2);
        oled_write_char(symbol, false);
        oled_set_cursor(i, 4);
        oled_write_char(symbol, false);
        oled_set_cursor(i, 6);
        oled_write_char(symbol, false);
    }
}
