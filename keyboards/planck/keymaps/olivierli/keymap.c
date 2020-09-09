#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif

#include "enums.h"
#include "eeprom.h"
#include "keymap_canadian_multilingual.h"
#include "layer_with_mod_tap.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSPACE,KC_LMT1, KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCOLON,KC_ENTER,MO(7),KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMMA,KC_DOT,CSA_SLASH,CSA_BSLS,KC_LCTRL,KC_LALT,KC_TRANSPARENT,KC_LGUI,LOWER,LT(4,KC_SPACE),KC_NO,RAISE,MO(6),KC_TRANSPARENT,WEBUSB_PAIR,CSA_APOS),

  [_LOWER] = LAYOUT_planck_grid(KC_GRAVE,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_UNDS,KC_PLUS,CSA_LCBR,CSA_RCBR,CSA_PIPE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_RAISE] = LAYOUT_planck_grid(CSA_DTLD,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DELETE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MINUS,KC_EQUAL,CSA_LBRC,CSA_RBRC,CSA_BSLS,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LSFT(KC_INSERT),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_ADJUST] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_DELETE,KC_TRANSPARENT,AU_ON,AU_OFF,AU_TOG,KC_TRANSPARENT,KC_TRANSPARENT,RGB_TOG,RGB_VAI,RGB_VAD,KC_TRANSPARENT,KC_F12,KC_TRANSPARENT,KC_TRANSPARENT,MU_ON,MU_OFF,MU_TOG,KC_TRANSPARENT,KC_TRANSPARENT,RGB_MOD,RGB_HUI,RGB_HUD,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,RESET),

  [_LAYER4] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_PSCREEN,KC_SCROLLLOCK,KC_SCROLLLOCK,KC_PAUSE,KC_TRANSPARENT,KC_DELETE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_LSHIFT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,MO(5),KC_TRANSPARENT,KC_NO,MO(5),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER5] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_HOME,KC_PGDOWN,KC_PGUP,KC_END,KC_TRANSPARENT,KC_TRANSPARENT,KC_LSHIFT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER6] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,CSA_DCRC,CSA_CCED,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,CSA_DGRV,KC_TRANSPARENT,KC_LSHIFT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,CSA_ECUT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER7] = LAYOUT_planck_grid(LSFT(KC_TAB),LSFT(KC_Q),LSFT(KC_W),LSFT(KC_E),LSFT(KC_R),LSFT(KC_T),LSFT(KC_Y),LSFT(KC_U),LSFT(KC_I),LSFT(KC_O),LSFT(KC_P),LSFT(KC_BSPACE),LSFT(KC_ESCAPE),LSFT(KC_A),LSFT(KC_S),LSFT(KC_D),LSFT(KC_F),LSFT(KC_G),LSFT(KC_H),LSFT(KC_J),LSFT(KC_K),LSFT(KC_L),LSFT(KC_SCOLON),LSFT(KC_ENTER),KC_TRANSPARENT,LSFT(KC_Z),LSFT(KC_X),LSFT(KC_C),LSFT(KC_V),LSFT(KC_B),LSFT(KC_N),LSFT(KC_M),CSA_LESS,CSA_GRTR,LSFT(CSA_QEST),LSFT(KC_BSLASH),LSFT(KC_LCTRL),KC_TRANSPARENT,LSFT(KC_LALT),LSFT(KC_LGUI),KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LSFT(CSA_DQOT)),

};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248} },

    [1] = { {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255}, {48,255,255} },

    [2] = { {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255}, {126,249,255} },

    [4] = { {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255} },

    [6] = { {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255}, {0,0,255}, {0,0,255}, {165,255,255}, {0,0,255}, {165,255,255} },

    [7] = { {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248}, {199,228,248} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 4:
      set_layer_color(4);
      break;
    case 6:
      set_layer_color(6);
      break;
    case 7:
      set_layer_color(7);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Hook user define functionality here. -------------------------------------
  if(layer_with_mod_tap_on_key_press(keycode, record)){
    return false;
  }
  // --------------------------------------------------------------------------

  switch (keycode) {
    case KC_LMT1:
      layer_with_mod_on_hold_key_on_tap(record, 1, KC_LSFT, KC_1);
      return false;
    case CSA_LSPO:
      perform_space_cadet(record, keycode,  KC_LSFT, KC_LSFT, KC_9);
      return false;
    case CSA_RSPC:
      perform_space_cadet(record, keycode, KC_LSFT, KC_LSFT, KC_0);
      return false;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
        #else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
        #else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        #endif
        }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
#endif

uint32_t layer_state_set_user(uint32_t state) {
    const uint8_t layer = get_highest_layer(state);
    layer_with_mod_tap_on_layer_change(layer);
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
