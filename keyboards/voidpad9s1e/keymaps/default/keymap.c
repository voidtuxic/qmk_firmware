#include QMK_KEYBOARD_H

enum custom_keycodes {
    ENCODER_PUSH = SAFE_RANGE,
    V_CUT,
    V_COPY,
    V_PASTE,
    V_VSCODE,
    V_VSCODE_OPEN,
    V_VSCODE_CMD,
    V_RIDER_REFACTOR,
    V_RIDER_REFORMAT,
    V_RIDER,
    V_OBS,
    V_SNIP,
    V_TASKMAN,
    V_TERM,
};

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
        KC_NO,   KC_NO,   ENCODER_PUSH,
        KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO
    ),
    [4] = LAYOUT_default(
        KC_NO,            KC_NO,   QK_BOOTLOADER,
        KC_NO,            KC_NO,   KC_NO,
        KC_NO,            KC_NO,   KC_NO,
        KC_RIGHT_CTRL,   KC_RIGHT_SHIFT,   KC_NO
    )
};

static bool pressing_encoder = false;
static uint16_t encoder_press_time = 0;
static bool oled_is_on = true;
static uint8_t encoder_selection = 0;

void launch_program(const char* program_name)
{
    SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(200));
    send_string(program_name);
    SEND_STRING(SS_DELAY(200) SS_TAP(X_ENTER));
}

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
        if (record->event.pressed)
        {
            launch_program("term");
        }
        break;
    case V_VSCODE:
        if (record->event.pressed)
        {
            launch_program("code");
            layer_move(2);
        }
        break;
    case V_RIDER:
        if (record->event.pressed)
        {
            launch_program("rid");
            layer_move(2);
        }
        break;
    case V_OBS:
        if (record->event.pressed)
        {
            launch_program("obs");
        }
        break;
    case V_SNIP:
        if (record->event.pressed)
        {
            launch_program("snip");
        }
        break;
    case V_TASKMAN:
        if (record->event.pressed)
        {
            launch_program("task");
        }
        break;
    case V_VSCODE_OPEN:
        if (record->event.pressed)
        {
            SEND_STRING(SS_LCTL("p"));
        }
        break;
    case V_VSCODE_CMD:
        if (record->event.pressed)
        {
            SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) "p" SS_UP(X_LCTRL) SS_UP(X_LSHIFT));
        }
        break;
    case V_RIDER_REFACTOR:
        if (record->event.pressed)
        {
            SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) "r" SS_UP(X_LCTRL) SS_UP(X_LSHIFT));
        }
        break;
    case V_RIDER_REFORMAT:
        if (record->event.pressed)
        {
            SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LSHIFT) "f" SS_UP(X_LALT) SS_UP(X_LSHIFT));
        }
        break;
    case KC_RIGHT_SHIFT:
        if (!record->event.pressed)
        {
            encoder_selection = 0;
        }
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
#define LAYER_COUNT 5
    static uint8_t layer = 0;
    if (index == 0) {
        if (layer == LAYER_COUNT - 1 && get_mods() & MOD_BIT(KC_RIGHT_CTRL)) {
            if (clockwise) oled_set_brightness(oled_get_brightness() + 20);
            else oled_set_brightness(oled_get_brightness() - 20);
        }
        else if (layer == LAYER_COUNT - 1 && get_mods() & MOD_BIT(KC_RIGHT_SHIFT)) {
            if (clockwise) encoder_selection++;
            else encoder_selection--;
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
    return false;
}

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
            oled_write_P(PSTR("N/A\n"), true);
            break;
        case 4:
            oled_write_P(PSTR("Nerd"), true);
            draw_layer_keys(
                PSTR("Boot"),
                PSTR("CPU %"), PSTR("GPU %"), PSTR(""),
                PSTR("CPU \0x06"), PSTR("GPU \0x06"), PSTR(""),
                PSTR("Bright"), PSTR("Select"), PSTR("")
            );
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), true);
        }
    }

    return false;
}
