#ifndef LAYER_WITH_MOD_TAP_H
#define LAYER_WITH_MOD_TAP_H

#include <stdbool.h>
#include "quantum.h"

// Constants ------------------------------------------------------------------
#define PENDING_KEYS_BUFFER_SIZE 8

// If more time goes by between the layer_with_mod_tap press and the the press
// of the first key consider the press a full press even if there were no associated
// up events. This values was determined through statistical analysis of typing patterns.
#define FALSE_ROLLOVER_DELAY 60
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

// Returns true if both key down event and it's associated key up were buffered.
bool complete_press_buffered(void);

// Emit all the buffered key presses.
void flush_pending(bool use_previous_layer);

// Updates the current layer to account for layer changes that take place during a hold.
// Currently nothing is done with the information but to provide correct behavior a buffered
// press of 8 that takes place after a layer 2 activation should return *. 
void layer_with_mod_tap_on_layer_change(uint8_t layer);

// This function has to be called on process_record_user() to know if a layer
// hold got interrupted. Returns true if the press was absorbed and should not
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
