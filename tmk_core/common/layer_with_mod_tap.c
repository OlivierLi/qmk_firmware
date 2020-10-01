#include "quantum.h"
#include "quantum/keymap.h"
#include "layer_with_mod_tap.h"

uint16_t last_layer_tap_mod_down_time = 0;
bool layer_tap_mod_in_progress = false;
bool interrupted = false;

struct InteruptingPress pending_keys[PENDING_KEYS_BUFFER_SIZE] = {0};
uint8_t pending_keys_count = 0;
uint8_t current_layer = 0; 
uint8_t target_layer = 0; 

bool press_completed(uint16_t keycode, int pos){
  for(int i=pos;i<pending_keys_count;++i){
    if(!pending_keys[i].is_down && (pending_keys[i].keycode == keycode)){
      return true;
    }
  }

  return false;
}

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

void flush_pending(bool use_target_layer){

  for(int i=0;i<pending_keys_count;++i){

    uint16_t keycode = 0;
    if(use_target_layer){
      keycode = pending_keys[i].target_layer_keycode;
    }
    else {
      keycode = pending_keys[i].keycode;
    }

    if(pending_keys[i].is_down){
     register_code16(keycode);

     // We're dealing in synthetic presses here. We need to check if the
     // real layer press completed and not the target one.
     if(use_target_layer && !press_completed(pending_keys[i].keycode, i)){
       // TODO: Maybe this should be simulated on deactivation?
       // Otherwhise we might mess with some chords if this is not a final
       // flush.
       unregister_code16(keycode);
     }

    }
    else {
     unregister_code16(keycode);
    }
  } 

  pending_keys_count = 0;
}

void layer_with_mod_tap_on_layer_change(uint8_t layer){
  current_layer = layer;
}

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

bool layer_with_mod_tap_on_key_press(uint16_t keycode, keyrecord_t *record){

  // Any action on the layer tap mod key should be handled in the layer_with_mod_on_hold_key_on_tap().
  if(keycode == LAYER_TAP_MOD){
    return false;
  }

  // Outside of layer tap mod just handle normally.
  if(!layer_tap_mod_in_progress){
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

void layer_with_mod_on_hold_key_on_tap(keyrecord_t *record, uint8_t layer, uint8_t hold_mod, uint8_t tap_keycode) {
  // Key down.
  if (record->event.pressed) {
    last_layer_tap_mod_down_time = record->event.time;

    // Save the target layer.
    target_layer = layer;

    // Activate modifier first.
    register_mods(MOD_BIT(hold_mod));

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

          // TODO: Still needed?
          /*struct InteruptingPress interupting_press = pending_keys[0];*/
          /*interupting_press.is_down = false;*/
          /*pending_keys[pending_keys_count++] = interupting_press;*/

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
