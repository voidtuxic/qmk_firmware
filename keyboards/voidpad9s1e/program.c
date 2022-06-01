#include QMK_KEYBOARD_H
#include "program.h"
#include "keycodes.h"

void launch_program(const char* program_name)
{
    SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(200));
    send_string(program_name);
    SEND_STRING(SS_DELAY(200) SS_TAP(X_ENTER));
}

void process_record_program(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
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
    }
}
