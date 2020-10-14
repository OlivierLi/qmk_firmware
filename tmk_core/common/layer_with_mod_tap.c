#include "quantum.h"
#include "quantum/keymap.h"
#include "layer_with_mod_tap.h"
#include <string.h>
#include <print.h>

uint16_t last_layer_tap_mod_down_time = 0;
bool layer_tap_mod_in_progress = false;
bool interrupted = false;

struct InteruptingPress pending_keys[PENDING_KEYS_BUFFER_SIZE] = {0};
uint8_t pending_keys_count = 0;

struct SwappedRelease swapped_releases[SWAPPED_KEYS_BUFFER_SIZE] = {0};

uint8_t target_layer = 0; 

// Returns true if there is an up event within the buffered keys for |keycode|
// starting at |pos|. Otherwise returns false. Use this to know if a full keypress
// was buffered.
bool press_completed(uint16_t keycode, int pos){
  for(int i=pos;i<pending_keys_count;++i){
    if(!pending_keys[i].is_down && (pending_keys[i].keycode == keycode)){
      return true;
    }
  }
  return false;
}

// Returns true if both the down and up events were buffered for the same
// key. Otherwise returns false.
bool complete_press_buffered(void){
  for(int i=0;i<pending_keys_count;++i){
    if(pending_keys[i].is_down){
      if(press_completed(pending_keys[i].keycode, i)){
        return true;
      }
    } 
  }
  return false;
}

// Replay all the keys that were buffered. If up events for a key on the target
// layer is replayed without a matching up event then ammend swapped_releases to
// know to do the translation later on when the up event takes place.
void flush_pending(bool use_target_layer){

  for(int i=0;i<pending_keys_count;++i){

    const uint16_t target_layer_keycode = pending_keys[i].target_layer_keycode;
    const uint16_t keycode = pending_keys[i].keycode;

    uint16_t replay_keycode;
    if(use_target_layer && target_layer_keycode != KC_TRANSPARENT){
      replay_keycode = target_layer_keycode;
    }
    else {
      replay_keycode = keycode;
    }

    if(pending_keys[i].is_down){
      register_code16(replay_keycode);

      if(use_target_layer && !press_completed(pending_keys[i].keycode, i)){

        for(int i=0;i<SWAPPED_KEYS_BUFFER_SIZE;++i){
          if(!swapped_releases[i].keycode){
            struct SwappedRelease swapped_release = {
              .keycode = keycode,
              .target_layer_keycode = target_layer_keycode};
            swapped_releases[i] = swapped_release;
            break;
          }

        }
      }

    }
    else {
      unregister_code16(replay_keycode);
    }
  } 

  pending_keys_count = 0;
}

// Save a keypress to played back later.
bool buffer_key(uint16_t keycode, keyrecord_t *record){
  const bool is_down = record->event.pressed;

  // If no more place to buffer keycodes. Just drop.
  if(pending_keys_count != PENDING_KEYS_BUFFER_SIZE-1){
    struct InteruptingPress interupting_press = {
      .is_down = is_down, 
      .keycode = keycode,
      .time = record->event.time,
      .target_layer_keycode = keymap_key_to_keycode(target_layer, record->event.key)};

    pending_keys[pending_keys_count++] = interupting_press;

    return true;
  }
  else {
    return false;
  }
}

// See layer_with_mod_tap.h for comment.
bool layer_with_mod_tap_on_key_press(uint16_t keycode, keyrecord_t *record){
  const bool is_down = record->event.pressed;

  // Any action on the layer tap mod key should be handled in the layer_with_mod_on_hold_key_on_tap().
  if(keycode == LAYER_TAP_MOD){
    return false;
  }

  // Outside of layer tap mod just handle normally.
  if(!layer_tap_mod_in_progress){
    for(int i=0;i<SWAPPED_KEYS_BUFFER_SIZE;++i){
      if(swapped_releases[i].keycode && !is_down){
        unregister_code16(swapped_releases[i].target_layer_keycode);
        memset(&swapped_releases[i], 0, sizeof(struct SwappedRelease));
        return true;
      }
    }
    return false;
  }

  buffer_key(keycode, record);

  const uint16_t elapsed_time = record->event.time - last_layer_tap_mod_down_time;
  if (elapsed_time > TAPPING_TERM) {
      flush_pending(true);
      return true;
  }
  else{
      interrupted = true;
  }

  // Swallow the key.
  return true;
}

// See layer_with_mod_tap.h for comment.
void layer_with_mod_on_hold_key_on_tap(keyrecord_t *record, uint8_t layer, uint8_t hold_mod, uint8_t tap_keycode) {
  // Key down.
  if (record->event.pressed) {
    last_layer_tap_mod_down_time = record->event.time;

    // Save the target layer.
    target_layer = layer;

    // Activate modifier first.
    register_mods(MOD_BIT(hold_mod));

    // Reset state.
    layer_tap_mod_in_progress = true;
    interrupted = false;
  }
  // Key up.
  else{
    const uint16_t elapsed_time = record->event.time - last_layer_tap_mod_down_time;
    if (elapsed_time <= TAPPING_TERM) {
      // Normal tap.
      if(!interrupted){
        // Reset state.
        unregister_mods(MOD_BIT(hold_mod));

        register_code16(tap_keycode);
        unregister_code16(tap_keycode);

        // Key no longer held, no longer in progress.
        layer_tap_mod_in_progress = false;
        return;
      }

      // A full key press happened within the tapping term.
      if(complete_press_buffered()){
        flush_pending(true);

        // Reset state.
        unregister_mods(MOD_BIT(hold_mod));
      }
      else {

        const uint16_t time_between_mod_tap_and_first_buffer = pending_keys[0].time - last_layer_tap_mod_down_time;

        if(pending_keys_count > 0 && time_between_mod_tap_and_first_buffer > 60){

          flush_pending(true);

          // Reset state.
          unregister_mods(MOD_BIT(hold_mod));
        }

        else{
          // Reset state.
          unregister_mods(MOD_BIT(hold_mod));

          register_code16(tap_keycode);
          unregister_code16(tap_keycode);

          flush_pending(false);
        }
      }
    }
    else {
      flush_pending(true);

      // Reset state.
      unregister_mods(MOD_BIT(hold_mod));
    }

    // Key no longer held, no longer in progress.
    layer_tap_mod_in_progress = false;
  }
}
