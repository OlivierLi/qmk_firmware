#include QMK_KEYBOARD_H

#include "version.h"
#include "keymap_canadian_multilingual.h"

#include "layer_with_mod_tap.h"
#include "enums.h"
#include "rgblight.h"

// This layout provides the experience of a standard US-EN keyboard for programming with quick access to French characters in their traditional CSA placement. 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Base layer.
  [0] = LAYOUT_ergodox_pretty(
    KC_ESCAPE,      KC_1,                   KC_2,                   KC_3,           KC_4,           KC_5,           ST_MACRO_0,         ST_MACRO_5,       KC_6,             KC_7,             KC_8,           KC_9,           KC_0,           KC_DELETE,
    KC_TAB,         KC_Q,                   KC_W,                   KC_E,           KC_R,           KC_T,           LALT(LCTL(KC_H)),   LALT(LCTL(KC_L)), KC_Y,             KC_U,             KC_I,           KC_O,           KC_P,           CSA_BSLS,
    KC_LMT1,        KC_A,                   KC_S,                   KC_D,           KC_F,           KC_G,                                                 KC_H,             KC_J,             KC_K,           KC_L,           KC_SCOLON,      KC_LMT2,
    KC_LMT1,        KC_Z,                   KC_X,                   KC_C,           KC_V,           KC_B,           ST_MACRO_1,         ST_MACRO_6,       KC_N,             KC_M,             KC_COMMA,       KC_DOT,         CSA_SLASH,      KC_RSHIFT,
                    KC_LCTRL,               KC_LGUI,                KC_LALT,        CSA_LCBR,       LEFT_SC_CONTROL,                                      RIGHT_SC_CONTROL, CSA_RCBR,         KC_RALT,        KC_RGUI,        KC_RCTRL,
                                                                                                    KC_TRANSPARENT, ST_MACRO_2,         KC_TRANSPARENT,   KC_TRANSPARENT,
                                                                                                                    ST_MACRO_3,         KC_TRANSPARENT,
                                                                                    LT(2,KC_SPACE),   MO(4),        ST_MACRO_4,         KC_TRANSPARENT, LT(5,KC_BSPACE),  LT(3,KC_ENTER)
  ),
  // "Shifted" layer. Activating this layer activates the shifted equivalent codes from the base layer. Needed to use CSA codes in the same positions as a US keyboard.
  [1] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT,         KC_TRANSPARENT,          KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT,   KC_TRANSPARENT, KC_QUES,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,         KC_TRANSPARENT,          KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT,   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, CSA_PIPE,
    KC_TRANSPARENT, KC_TRANSPARENT,         KC_TRANSPARENT,          KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT,                                   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_COLN,        CSA_DQOT,
    KC_TRANSPARENT, KC_TRANSPARENT,         KC_TRANSPARENT,          KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT,   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, CSA_LESS,       CSA_GRTR,       CSA_QEST,       KC_RSHIFT,
                    KC_TRANSPARENT,         KC_TRANSPARENT,          KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT,                                   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                      KC_TRANSPARENT, KC_TRANSPARENT,   KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                      KC_TRANSPARENT,   KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT,   KC_TRANSPARENT, KC_TRANSPARENT,   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  // Numbers layer.
  [2] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_TRANSPARENT,
    KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_UNDS,        KC_PLUS,        KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,
    KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                    KC_TRANSPARENT, KC_EQUAL,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  // Symbols layer.
  [3] = LAYOUT_ergodox_pretty(
    CSA_DTLD,       KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,
    KC_TRANSPARENT, KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,        KC_F12,
    KC_NO,          CSA_LBRC,       CSA_RBRC,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_HASH,        KC_MINUS,       KC_EQUAL,       KC_ASTR,        KC_TRANSPARENT, KC_NO,
    KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LSFT(KC_INSERT),KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                    KC_TRANSPARENT, WEBUSB_PAIR,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RESET,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  // Move layer. Use keys reminiscent of vim for larger movements (ie u for Up).
  [4] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_END,         KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_HOME,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_END,         KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_PGUP,        KC_TRANSPARENT, KC_TRANSPARENT, KC_HOME,        KC_TRANSPARENT,
    KC_LSHIFT,      KC_TRANSPARENT, KC_TRANSPARENT, KC_PGDOWN,      KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT, KC_RSHIFT,
    KC_LSHIFT,      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_RSHIFT,
                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  // French and Media layer.
  [5] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_VOL_UP,    KC_TRANSPARENT, CSA_DCRC,       CSA_CCED,
    KC_LSHIFT,      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_PSCREEN,     KC_SCROLLLOCK,  KC_AUDIO_MUTE,      KC_PAUSE,       CSA_DGRV,       KC_RSHIFT,
    KC_LSHIFT,      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,  KC_TRANSPARENT, CSA_ECUT,       KC_RSHIFT,
                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
};

bool disable_layer_color = 0;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Hook user defined functionality here. -------------------------------------
  if(layer_with_mod_tap_on_key_press(keycode, record)){
    return false;
  }
  // --------------------------------------------------------------------------

  switch (keycode) {
    // Some codes won't register if paired with shift. Ommit it. --------------
    case CSA_LESS:
    case CSA_GRTR:
    case CSA_PIPE:
    if (!record->event.pressed) {
        if(get_mods() & MOD_BIT(KC_LSFT)){
          unregister_mods(MOD_BIT(KC_LSFT));
          tap_code16(keycode);
          register_mods(MOD_BIT(KC_LSFT));
        }
    }
    return false;
    // -------------------------------------------------------------------------

    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_TAP(X_A)) SS_DELAY(SHORT_MACRO_DELAY) SS_LCTL(SS_TAP(X_H)));
    }
    return false;

    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_TAP(X_A)) SS_DELAY(SHORT_MACRO_DELAY) SS_TAP(X_H));

    }
    return false;

    case ST_MACRO_2:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_GRV)) SS_DELAY(MEDIUM_MACRO_DELAY) SS_TAP(X_X) SS_DELAY(MEDIUM_MACRO_DELAY) SS_TAP(X_C));
    }
    return false;

    case ST_MACRO_3:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_GRV)) SS_DELAY(MEDIUM_MACRO_DELAY) SS_TAP(X_X) SS_DELAY(MEDIUM_MACRO_DELAY) SS_TAP(X_L));
    }
    return false;

    case ST_MACRO_4:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_GRV)) SS_DELAY(MEDIUM_MACRO_DELAY) SS_TAP(X_X) SS_DELAY(MEDIUM_MACRO_DELAY) SS_TAP(X_X));
    }
    return false;

    case ST_MACRO_5:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_TAP(X_A)) SS_DELAY(SHORT_MACRO_DELAY) SS_LCTL(SS_TAP(X_L)));
    }
    return false;

    case ST_MACRO_6:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_TAP(X_A)) SS_DELAY(SHORT_MACRO_DELAY) SS_TAP(X_L));
    }
    return false;

    case LEFT_SC_CONTROL:
      perform_space_cadet(record, keycode, KC_LCTRL, KC_LSFT, KC_9);
      return false;
    case RIGHT_SC_CONTROL:
      perform_space_cadet(record, keycode, KC_LCTRL, KC_LSFT, KC_0);
      return false;
    case KC_LMT1:
      layer_with_mod_on_hold_key_on_tap(record, 1, KC_LSFT, KC_ESC);
      return false;
    case KC_LMT2:
      layer_with_mod_on_hold_key_on_tap(record, 1, KC_LSFT, CA_COMM);
      return false;
  }
  return true;
}

rgblight_config_t rgblight_config;
uint32_t layer_state_set_user(uint32_t state) {

    const uint8_t layer = biton32(state);
    layer_with_mod_tap_on_layer_change(current_layer);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    switch (layer) {
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }

    // Always display the same color no matter the layer.
    switch (layer) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(198,227,168);
        }
        break;
      default:
        if(!disable_layer_color) {
          rgblight_config.raw = eeconfig_read_rgblight();
          if(rgblight_config.enable == true) {
            rgblight_enable();
            rgblight_mode(rgblight_config.mode);
            rgblight_sethsv(rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
          }
          else {
            rgblight_disable();
          }
        }
        break;
    }

    return state;
};

void keyboard_post_init_user(void) {
  layer_state_set_user(layer_state);
}
