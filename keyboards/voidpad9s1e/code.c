#include QMK_KEYBOARD_H
#include "code.h"
#include "keycodes.h"

void process_record_vscode(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
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
    }
}
