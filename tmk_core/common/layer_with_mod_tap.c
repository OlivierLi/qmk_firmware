#include "quantum.h"
#include "quantum/keymap.h"
#include "layer_with_mod_tap.h"

uint16_t last_layer_tap_mod_down_time = 0;
bool layer_tap_mod_in_progress = false;
bool interrupted = false;

struct InteruptingPress pending_keys[PENDING_KEYS_BUFFER_SIZE] = {0};
uint8_t pending_keys_count = 0;
uint8_t current_layer = 0; 
uint8_t previous_layer = 0; 

bool complete_press_buffered(void){
  for(int i=0;i<pending_keys_count;++i){
    if(pending_keys[i].is_down){
      for(int j=i;j<pending_keys_count;++j){
        if(!pending_keys[j].is_down && (pending_keys[j].keycode == pending_keys[i].keycode)){
          return true;
        }
      }
    } 
  }
  return false;
}

void flush_pending(bool use_previous_layer){

  for(int i=0;i<pending_keys_count;++i){

    uint16_t keycode = 0;
    if(use_previous_layer){
      keycode = pending_keys[i].previous_layer_keycode;
    }
    else {
      keycode = pending_keys[i].keycode;
    }

    if(pending_keys[i].is_down)
     register_code16(keycode);
    else
     unregister_code16(keycode);
  } 

  pending_keys_count = 0;
}

void layer_with_mod_tap_on_layer_change(uint8_t layer){
  current_layer = layer;
}

bool layer_with_mod_tap_on_key_press(uint16_t keycode, keyrecord_t *record){
  const bool is_down = record->event.pressed;

  // Any action on the layer tap mod key should be handled in the layer_with_mod_on_hold_key_on_tap().
  if(keycode == LAYER_TAP_MOD){
    return false;
  }

  // Outside of layer tap mod just handle normally.
  if(!layer_tap_mod_in_progress){
    return false;
  }

  const uint16_t elapsed_time = record->event.time - last_layer_tap_mod_down_time;
  if (elapsed_time > TAPPING_TERM) {
      flush_pending(false);
      return false;
  }
  else{
      interrupted = true;
  }

  // If no more place to buffer keycodes. Just drop.
  if(pending_keys_count != PENDING_KEYS_BUFFER_SIZE-1){
    struct InteruptingPress interupting_press = {
      .is_down = is_down, 
      .keycode = keycode,
      .time = record->event.time,
      .previous_layer_keycode = keymap_key_to_keycode(previous_layer, record->event.key)};

    pending_keys[pending_keys_count++] = interupting_press;
  }

  // Swallow the key.
  return true;
}

void layer_with_mod_on_hold_key_on_tap(keyrecord_t *record, uint8_t layer, uint8_t hold_mod, uint8_t tap_keycode) {
  // Key down.
  if (record->event.pressed) {
    last_layer_tap_mod_down_time = record->event.time;

    // Activate the layer and modifier first.
    previous_layer = current_layer;
    layer_on(layer);
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
        layer_off(layer);

        register_code16(tap_keycode);
        unregister_code16(tap_keycode);

        // Key no longer held, no longer in progress.
        layer_tap_mod_in_progress = false;
        return;
      }

      // A full key press happened within the tapping term.
      if(complete_press_buffered()){
        flush_pending(false);

        // Reset state.
        unregister_mods(MOD_BIT(hold_mod));
        layer_off(layer);
      }
      else {

        const uint16_t time_between_mod_tap_and_first_buffer = pending_keys[0].time - last_layer_tap_mod_down_time;

        if(pending_keys_count > 0 && time_between_mod_tap_and_first_buffer > 60){
          struct InteruptingPress interupting_press = pending_keys[0];
          interupting_press.is_down = false;
          pending_keys[pending_keys_count++] = interupting_press;

          flush_pending(false);

          // Reset state.
          unregister_mods(MOD_BIT(hold_mod));
          layer_off(layer);
        }

        else{
          // Reset state.
          unregister_mods(MOD_BIT(hold_mod));
          layer_off(layer);

          register_code16(tap_keycode);
          unregister_code16(tap_keycode);

          flush_pending(true);
        }
      }
    }
    else {
      flush_pending(false);

      // Reset state.
      unregister_mods(MOD_BIT(hold_mod));
      layer_off(layer);
    }

    // Key no longer held, no longer in progress.
    layer_tap_mod_in_progress = false;
  }
}
