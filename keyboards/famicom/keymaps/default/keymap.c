/* Copyright 2019 Samuel Carroll
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { QMKBEST = SAFE_RANGE, QMKURL };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
|       | Col 1 |  Col 2 | Col 3 | Col 4 |  Col 5 |  Col 6 | Col 7 | Col 8 |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 1 |   F8  | RETURN |   [   |   ]   |  KANA  | RSHIFT |   ¥   |  STOP |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 2 |   F7  |    @   |   ;   |   :   |    _   |    /   |   -   |   ^   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 3 |   F6  |    O   |   L   |   K   |    <   |    .   |   P   |   0   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 4 |   F5  |    I   |   U   |   J   |    M   |    N   |   9   |   8   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 5 |   F4  |    Y   |   G   |   H   |    B   |    V   |   7   |   6   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 6 |   F3  |    T   |   R   |   D   |    F   |    C   |   5   |   4   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 7 |   F2  |    W   |   S   |   A   |    X   |    Z   |   E   |   3   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 8 |   F1  |   ESC  |   Q   |  CTR  | LSHIFT |  GRPH  |   1   |   2   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 9 |  CLR/ |   UP   | RIGHT |  LEFT |  DOWN  |  SPACE |  DEL  |  INS  |
|       |  HOME |        |       |       |        |        |       |       |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
NOTE: Accourding to https://wiki.nesdev.com/w/index.php/Family_BASIC_Keyboard#Miscellaneous
      The ¥ key is often used to represent the backslash key due to being in the same
      approximate keyboard location

Some keys don't follow the US layout, since I'm in the US I'll repurpose some
keys to be more in line with the US layout (e.g. 2 and @ are the same key but
the Famicom Keyboard has them as separate keys)
*/

    [0] = LAYOUT(/* Base */
/*
We have the following default layout
    F1  F2  F3  F4  F5  F6  F7  F8
     1 2 3 4 5 6 7 8 9 0 - + \ BckSpc          CH* INS DEL
    ESC Q W E R T Y U I O P [ ] RETURN             UP
    CAPS A S D F G H J K L ; " PGUP ALT        LEFT RIGHT
    LSHIFT Z X C V B N M , . / PGDWN SHIFT        DOWN
           RCTL   SPACE 
Might use the KANA key to shift between keyboard settings

       F0      F1      F4       F5      F6       F7      B6      B5
   +-------+--------+-------+-------+--------+--------+-------+-------+
B0 |   F8  | RETURN |   ]   |  PGUP |   ALT  | RSHIFT |   \   | BKSPC |
   +-------+--------+-------+-------+--------+--------+-------+-------+
B1 |   F7  |    [   |   "   |   ;   |  PGDN  |    /   |   -   |   =   |
   +-------+--------+-------+-------+--------+--------+-------+-------+
B2 |   F6  |    O   |   L   |   K   |    ,   |    .   |   P   |   0   |
   +-------+--------+-------+-------+--------+--------+-------+-------+
B3 |   F5  |    I   |   U   |   J   |    M   |    N   |   9   |   8   |
   +-------+--------+-------+-------+--------+--------+-------+-------+
B7 |   F4  |    Y   |   G   |   H   |    B   |    V   |   7   |   6   |
   +-------+--------+-------+-------+--------+--------+-------+-------+
D0 |   F3  |    T   |   R   |   D   |    F   |    C   |   5   |   4   |
   +-------+--------+-------+-------+--------+--------+-------+-------+
D1 |   F2  |    W   |   S   |   A   |    X   |    Z   |   E   |   3   |
   +-------+--------+-------+-------+--------+--------+-------+-------+
D2 |   F1  |   ESC  |   Q   |  CAPS | LSHIFT |  RCTL  |   1   |   2   |
   +-------+--------+-------+-------+--------+--------+-------+-------+
D3 |  CLR/ |   UP   | RIGHT |  LEFT |  DOWN  |  SPACE |  DEL  |  INS  |
   |  HOME |        |       |       |        |        |       |       |
   +-------+--------+-------+-------+--------+--------+-------+-------+
*/

    KC_F8,   KC_ENT,  KC_RBRC, KC_PGUP, KC_ALGR, KC_RSFT, KC_BSLS, KC_BSPC, \
    KC_F7,   KC_LBRC, KC_QUOT, KC_SCLN, KC_PGDN, KC_SLSH, KC_MINS, KC_EQL,  \
    KC_F6,   KC_O,    KC_L,    KC_K,    KC_COMM, KC_DOT,  KC_P,    KC_0,    \
    KC_F5,   KC_I,    KC_U,    KC_J,    KC_M,    KC_N,    KC_9,    KC_8,    \
    KC_F4,   KC_Y,    KC_G,    KC_H,    KC_B,    KC_V,    KC_7,    KC_6,    \
    KC_F3,   KC_T,    KC_R,    KC_D,    KC_F,    KC_C,    KC_5,    KC_4,    \
    KC_F2,   KC_W,    KC_S,    KC_A,    KC_X,    KC_Z,    KC_E,    KC_3,    \
    KC_F1,   KC_ESC,  KC_Q,    KC_CAPS, KC_LSFT, KC_RCTL, KC_1,    KC_2,    \
    KC_HOME, KC_UP,   KC_RGHT, KC_LEFT, KC_DOWN, KC_SPC,  KC_DEL,  KC_INS   \

    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}
