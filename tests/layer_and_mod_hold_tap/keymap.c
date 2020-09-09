#include "quantum.h"
#include "layer_with_mod_tap.h"

#define COMBO1 RSFT(LCTL(KC_O))

const uint16_t PROGMEM
               keymaps[][MATRIX_ROWS][MATRIX_COLS] =
        {
            [0] =
                {
                    // 0    1      2      3        4        5        6       7            8      9
                    {KC_Q, KC_B, KC_NO, KC_LSFT, KC_RSFT, KC_LCTL, COMBO1, LAYER_TAP_MOD, M(0), KC_NO},
                    {KC_EQL, KC_PLUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
                    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
                    {KC_C, KC_D, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
                },
            [1] =
                {
                    // 0    1      2      3        4        5        6       7            8      9
                    {KC_1, KC_2, KC_NO, KC_LSFT, KC_RSFT, KC_LCTL, COMBO1, LAYER_TAP_MOD, M(0), KC_NO},
                    {KC_EQL, KC_PLUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
                    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
                    {KC_C, KC_D, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
                },
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Hook user defined functionality here. -------------------------------------
  if(layer_with_mod_tap_on_key_press(keycode, record)){
    return false;
  }
  // --------------------------------------------------------------------------

  switch (keycode) {
    case LAYER_TAP_MOD:
      layer_with_mod_on_hold_key_on_tap(record, 1, KC_LSFT, KC_ESC);
      return false;
  }

  return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    const uint8_t layer = get_highest_layer(state);
    layer_with_mod_tap_on_layer_change(layer);
    return state;
}

