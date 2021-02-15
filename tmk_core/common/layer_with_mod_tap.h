#ifndef LAYER_WITH_MOD_TAP_H
#define LAYER_WITH_MOD_TAP_H

#include <stdbool.h>
#include "quantum.h"

// Constants ------------------------------------------------------------------
#define PENDING_KEYS_BUFFER_SIZE 8
// ----------------------------------------------------------------------------

// Custom codes ---------------------------------------------------------------
// One code must be defined per use of layer_with_mod_tap. Using the same code
// for two or more uses will result in broken behavior.
#define LAYER_TAP_MOD 100
#define LAYER_TAP_MOD2 101
// ----------------------------------------------------------------------------

// Structs --------------------------------------------------------------------
struct InteruptingPress {
  bool is_down;
  uint16_t keycode;
  uint16_t previous_layer_keycode;
  uint16_t time;
};
// ----------------------------------------------------------------------------

// Variables ------------------------------------------------------------------
extern uint16_t last_layer_tap_mod_down_time;
extern bool layer_tap_mod_in_progress;
extern bool interrupted;

extern struct InteruptingPress pending_keys[PENDING_KEYS_BUFFER_SIZE];
extern uint8_t pending_keys_count;
extern uint8_t current_layer;
extern uint8_t previous_layer;
// ----------------------------------------------------------------------------

uint16_t GetKeyFromMatrix(uint8_t layer, keyrecord_t *record);

bool complete_press_buffered(void);

void flush_pending(bool use_previous_layer);

void layer_with_mod_tap_on_layer_change(uint8_t layer);

// This function has to be called on process_record_user() to know if a layer
// hold got interrupted.  Returns true if the press was absorbed and should not
// buble up.
bool layer_with_mod_tap_on_key_press(uint16_t keycode, keyrecord_t *record);

// Call this function to get a layer activation on hold with |hold_mod| active
// and |tap_keycode| on tap.
//
// TODO: There should be a |layer_tap_mod_in_progress| variable for each key
// that is bound to this function. otherwise the tapping will be reactivated
// because another call to this function set it to true. This is only a real
// problem if we start cording with keys that use this function.
//
// TODO: Support a tap modifier so we can use this with quotes
void layer_with_mod_on_hold_key_on_tap(keyrecord_t *record, uint8_t layer,
                                       uint8_t hold_mod, uint8_t tap_keycode);

#endif  // LAYER_WITH_MOD_TAP_H
