// Copyright 2025 Solder Party
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "timer.h"
#include "backlight.h"

// -----------------------------------------------------------------------------
// Backlight idle timeout
// -----------------------------------------------------------------------------
static uint32_t backlight_timer        = 0;
static bool     backlight_timed_out    = false;
static uint8_t  saved_backlight_level  = 0;

static void refresh_backlight_activity(void) {
    backlight_timer = timer_read32();  // mark "last activity" time

    // If it timed out, restore the previous brightness
    if (backlight_timed_out) {
        backlight_timed_out = false;
        backlight_set(saved_backlight_level);
    }
}

// -----------------------------------------------------------------------------
// Custom keycodes
// -----------------------------------------------------------------------------
enum custom_keycodes {
    KC_SPC2 = SAFE_RANGE,
    KC_SPC3,
};

// -----------------------------------------------------------------------------
// Keymaps
// -----------------------------------------------------------------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   _______, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_BSPC, KC_MINS, KC_LBRC, KC_ENT,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
        KC_E,    KC_Q,    KC_W,    KC_TAB,  KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RBRC,
        MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT, KC_BSLS, KC_SPC,  KC_SPC2, KC_SPC3, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT, KC_RSFT
    ),

    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  KC_F11,  _______, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP,
        _______, _______, _______, _______, BL_STEP, BL_STEP, BL_STEP, _______, KC_HOME, KC_PGDN, KC_END,  _______
    ),
};

// -----------------------------------------------------------------------------
// Enable debugging + matrix prints on boot (for qmk console)
// -----------------------------------------------------------------------------
void keyboard_post_init_user(void) {
    debug_enable   = true;
    debug_matrix   = true;   // prints matrix changes
    debug_keyboard = true;
    // debug_mouse  = true;  // optional
}

// -----------------------------------------------------------------------------
// Prevent sending multiple space presses if more than one space dome is pressed
// -----------------------------------------------------------------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t space_press_count = 0;

    // Any keypress resets the backlight idle timer
    if (record->event.pressed) {
        refresh_backlight_activity();
    }

    switch (keycode) {
        case KC_SPC:
        case KC_SPC2:
        case KC_SPC3:
            if (record->event.pressed) {
                if (space_press_count == 0) {
                    register_code(KC_SPC);
                }
                space_press_count++;
            } else {
                if (space_press_count > 0) {
                    space_press_count--;
                }
                if (space_press_count == 0) {
                    unregister_code(KC_SPC);
                }
            }
            return false;  // we handled it
    }

    return true;
}

// -----------------------------------------------------------------------------
// Backlight timeout handler
// -----------------------------------------------------------------------------
void housekeeping_task_user(void) {
    // Initialize backlight timer on first run
    if (backlight_timer == 0) {
        backlight_timer = timer_read32();
    }

    // If we haven't already turned backlight off, and it's been idle too long
    if (!backlight_timed_out && timer_elapsed32(backlight_timer) > BACKLIGHT_TIMEOUT) {
        saved_backlight_level = get_backlight_level();  // remember current brightness
        backlight_set(0);                               // turn it off
        backlight_timed_out = true;
    }
}
