#include "layer_with_mod_tap.h"

#include "keymap_canadian_multilingual.h"
#include "print.h"
#include "quantum.h"
#include "math.h"

// Quick hold detection -------------------------------------------------------
struct NormalDistribution {
  float avg;
  float stddev;
};

const struct NormalDistribution rollover_distributions[3] = {
    {.avg = 45.11, .stddev = 19.67},
    {.avg = 30.64, .stddev = 21.16},
    {.avg = 75.74, .stddev = 8.00}};

const struct NormalDistribution hold_distributions[3] = {
    {.avg = 66.72, .stddev = 18.88} ,
    {.avg = 52.64, .stddev = 16.96 },
    {.avg = 119.36,.stddev = 7.69}};

float z_value(float value, struct NormalDistribution dist) {
  return fabs(value - dist.avg) / dist.stddev;
}

float z_values_sum(const int* timings, const struct NormalDistribution* dists){
  float z_values_sum = 0.0;
  for(int i=0;i<3;++i){
    z_values_sum += z_value(timings[i], dists[i]);
  }
  return z_values_sum;
}

bool is_quick_hold(const int timings[3]){
  return z_values_sum(timings, hold_distributions) < z_values_sum(timings, rollover_distributions);
}
// ----------------------------------------------------------------------------


// Variable  ------------------------------------------------------------------
uint16_t last_layer_tap_mod_down_time = 0;
bool layer_tap_mod_in_progress = false;
bool interrupted = false;

struct InteruptingPress pending_keys[PENDING_KEYS_BUFFER_SIZE] = {0};
uint8_t current_layer = 0;
uint8_t previous_layer = 0;
uint8_t pending_keys_count = 0;
// ----------------------------------------------------------------------------

// Algorithm to count the misclassifications.
// Wors for dual functions keys that output characters in both modes so not ESC.
// Buffer the next N keys.
// If in the next N keys there are either: 
// 1) Enough backspaces to backup over the emmited keys.
// 2) A ctrl backspace without having a space in there.

// This needs to be followed by a "retry" meaning for example that 'a is deleted AND
// overwritten by A.
// 
// In those cases you have a miscaculate.

// To verify if this classification extends to the ESC (difference between right and left hands) we can
// start by just looking at the distribution of the timings between the different keys/hands.

// Functions ------------------------------------------------------------------
bool complete_press_buffered(void) {
  for (int i = 0; i < pending_keys_count; ++i) {
    if (pending_keys[i].is_down) {
      for (int j = i; j < pending_keys_count; ++j) {
        if (!pending_keys[j].is_down &&
            (pending_keys[j].keycode == pending_keys[i].keycode)) {
          return true;
        }
      }
    }
  }
  return false;
}

void flush_pending(bool use_previous_layer) {
  for (int i = 0; i < pending_keys_count; ++i) {
    uint16_t keycode = 0;
    if (use_previous_layer) {
      keycode = pending_keys[i].previous_layer_keycode;
    } else {
      keycode = pending_keys[i].keycode;
    }

    if (pending_keys[i].is_down)
      register_code16(keycode);
    else
      unregister_code16(keycode);
  }

  pending_keys_count = 0;
}

void layer_with_mod_tap_on_layer_change(uint8_t layer) {
  current_layer = layer;
}

bool layer_with_mod_tap_on_key_press(uint16_t keycode, keyrecord_t *record) {
  const bool is_down = record->event.pressed;

  // ************************************************************************
  // Some codes won't register if paired with shift.
  // Dirty hack to try and avoid weird issues on macos before the actual fix.
  switch (keycode) {
    case CSA_LESS:
    case CSA_GRTR:
    case CSA_PIPE:
      return false;
  }
  // ************************************************************************

  // Any action on the layer tap mod key should be handled in the
  // layer_with_mod_on_hold_key_on_tap().
  if (keycode >= LAYER_TAP_MOD && keycode <= LAYER_TAP_MOD_MAX) {
    return false;
  }

  // Outside of layer tap mod just handle normally.
  if (!layer_tap_mod_in_progress) {
    return false;
  }

  // Never buffer KC_NO
  if (keycode == KC_NO){
    return false;
  }

  const uint16_t elapsed_time =
      record->event.time - last_layer_tap_mod_down_time;
  if (elapsed_time > TAPPING_TERM) {
    flush_pending(false);
    return false;
  } else {
    interrupted = true;
  }

  // If no more place to buffer keycodes. Just drop.
  if (pending_keys_count != PENDING_KEYS_BUFFER_SIZE - 1) {
    struct InteruptingPress interupting_press = {
        .is_down = is_down,
        .keycode = keycode,
        .time = record->event.time,
        .previous_layer_keycode =
            keymap_key_to_keycode(previous_layer, record->event.key)};

    pending_keys[pending_keys_count++] = interupting_press;
  }

  // Swallow the key.
  return true;
}

void tap_key(uint8_t tap_keycode, uint8_t tap_mod){
  if(tap_mod != KC_NO){
    add_oneshot_mods(MOD_BIT(tap_mod));
  }

  register_code16(tap_keycode);
  unregister_code16(tap_keycode);
}

void deactivate(uint8_t layer, uint8_t hold_mod){
  // Reset state.
  if(hold_mod != KC_NO){ 
    unregister_mods(MOD_BIT(hold_mod));
  }

  layer_off(layer);
}

void layer_with_mod_on_hold_key_on_tap(keyrecord_t *record, uint8_t layer,
                                       uint8_t hold_mod, uint8_t tap_keycode, uint8_t tap_mod) {

  // Key down.
  if (record->event.pressed) {
    last_layer_tap_mod_down_time = record->event.time;

    // Activate the layer and modifier first.
    previous_layer = current_layer;
    layer_on(layer);
    if(hold_mod != KC_NO){ 
      register_mods(MOD_BIT(hold_mod));
    }

    layer_tap_mod_in_progress = true;
    interrupted = false;
  }
  // Key up.
  else {

    // Layer was changed while key pressed. Never activated means nothing to deactivate.
    if(!layer_tap_mod_in_progress){
      return;
    }

    const uint16_t elapsed_time =
        record->event.time - last_layer_tap_mod_down_time;
    if (elapsed_time <= TAPPING_TERM) {
      // Normal tap.
      if (!interrupted) {
        deactivate(layer, hold_mod);

        tap_key(tap_keycode, tap_mod);

        // Key no longer held, no longer in progress.
        layer_tap_mod_in_progress = false;
        return;
      }

      // A full key press happened within the tapping term.
      if (complete_press_buffered()) {
        flush_pending(false);

        deactivate(layer, hold_mod);
      } else {
        const int hold_down_to_letter_down =
            pending_keys[0].time - last_layer_tap_mod_down_time;
        const int letter_down_to_hold_up =
            record->event.time - pending_keys[0].time;
        const int hold_down_to_hold_up =
            record->event.time - last_layer_tap_mod_down_time;
        const int timings[3] = {hold_down_to_letter_down, letter_down_to_hold_up, hold_down_to_hold_up};

        /*uprintf("%d, %d, %d \n", hold_down_to_letter_down,*/
                /*letter_down_to_hold_up, hold_down_to_hold_up);*/

        if (pending_keys_count > 0 && is_quick_hold(timings)) {
          // A "false rollover" is detected. Emit a synthetic "up" event so that
          // the key registers fully. This is now considered a fully buffered
          // press so there is no tap.
          struct InteruptingPress interupting_press = pending_keys[0];
          interupting_press.is_down = false;
          pending_keys[pending_keys_count++] = interupting_press;

          flush_pending(false);

          deactivate(layer, hold_mod);
        } else {
          deactivate(layer, hold_mod);

          tap_key(tap_keycode, tap_mod);

          flush_pending(true);
        }
      }
    } else {
      flush_pending(false);

      deactivate(layer, hold_mod);
    }

    // Key no longer held, no longer in progress.
    layer_tap_mod_in_progress = false;
  }
}
