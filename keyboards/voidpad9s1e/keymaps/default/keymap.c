#include QMK_KEYBOARD_H

#include "keycodes.h"
#include "program.h"
#include "code.h"
#include "oled.h"
#include "encoder.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_default(
        KC_NO,            KC_NO,     ENCODER_PUSH,
        V_TERM,           V_OBS,     V_TASKMAN,
        V_VSCODE,         V_RIDER,   V_SNIP,
        V_CUT,            V_COPY,    V_PASTE
    ),
    [1] = LAYOUT_default(
        KC_NO,   KC_NO,   KC_NUM_LOCK,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3
    ),
    [2] = LAYOUT_default(
        KC_NO,           KC_NO,          ENCODER_PUSH,
        KC_F5,           KC_F10,         V_RIDER_REFORMAT,
        V_VSCODE_OPEN,   V_VSCODE_CMD,   V_RIDER_REFACTOR,
        V_CUT,           V_COPY,         V_PASTE
    ),
    [3] = LAYOUT_default(
        KC_NO,            KC_NO,   QK_BOOTLOADER,
        KC_NO,            KC_NO,   KC_NO,
        KC_NO,            KC_NO,   KC_NO,
        KC_RIGHT_CTRL,    KC_NO,   KC_NO
    )
};

static bool pressing_encoder = false;
static uint16_t encoder_press_time = 0;
static bool oled_is_on = true;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
    case ENCODER_PUSH:
        if (record->event.pressed) {
            if (pressing_encoder == false)
            {
                pressing_encoder = true;
                encoder_press_time = timer_read();
            }
        }
        else {
            pressing_encoder = false;
        }
        break;

    case V_CUT:
        if (record->event.pressed)
        {
            SEND_STRING(SS_LCTL("x"));
        }
        break;
    case V_COPY:
        if (record->event.pressed)
        {
            SEND_STRING(SS_LCTL("c"));
        }
        break;
    case V_PASTE:
        if (record->event.pressed)
        {
            SEND_STRING(SS_LCTL("v"));
        }
        break;

    case V_TERM:
    case V_VSCODE:
    case V_RIDER:
    case V_OBS:
    case V_SNIP:
    case V_TASKMAN:
        process_record_program(keycode, record);
        break;

    case V_VSCODE_OPEN:
    case V_VSCODE_CMD:
    case V_RIDER_REFACTOR:
    case V_RIDER_REFORMAT:
        process_record_vscode(keycode, record);
        break;
    }
    return true;
};

void matrix_scan_user(void) {
    if (pressing_encoder && timer_elapsed(encoder_press_time) > 500) {
        oled_is_on = !oled_is_on;
        pressing_encoder = false;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_update_voidpad(index, clockwise);
    return false;
}

bool oled_task_kb(void) {
    oled_clear();

    if (oled_is_on) {
        switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Macros\n"), true);
            draw_layer_keys(
                PSTR("Scr Tgl"),
                PSTR("Term"), PSTR("OBS"), PSTR("Tasks"),
                PSTR("VsCode"), PSTR("Rider"), PSTR("Snip"),
                PSTR("Cut"), PSTR("Copy"), PSTR("Paste")
            );
            break;
        case 1:
            oled_write_P(PSTR("Numpad\n"), true);
            draw_layer_keys(
                PSTR("Num Lck"),
                PSTR("7"), PSTR("8"), PSTR("9"),
                PSTR("4"), PSTR("5"), PSTR("6"),
                PSTR("1"), PSTR("2"), PSTR("3")
            );
            break;
        case 2:
            oled_write_P(PSTR("Code\n"), true);
            draw_layer_keys(
                PSTR("Scr Tgl"),
                PSTR("F5"), PSTR("F10"), PSTR("Format"),
                PSTR("Open"), PSTR("Cmd"), PSTR("Refacto"),
                PSTR("Cut"), PSTR("Copy"), PSTR("Paste")
            );
            break;
        case 3:
            oled_write_P(PSTR("Nerd"), true);
            draw_layer_keys(
                PSTR("Boot"),
                PSTR("CPU %"), PSTR("GPU %"), PSTR(""),
                PSTR("CPU \0x06"), PSTR("GPU \0x06"), PSTR(""),
                PSTR("Bright"), PSTR(""), PSTR("")
            );
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), true);
        }
    }

    return false;
}
