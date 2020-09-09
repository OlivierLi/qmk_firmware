#ifndef ENUMS_H
#define ENUMS_H

#include "layer_with_mod_tap.h"

enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  CSA_LSPO,
  CSA_RSPC,
  KC_LMT1 = LAYER_TAP_MOD,
};

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _LAYER4,
  _LAYER5,
  _LAYER6,
  _LAYER7,
};

#endif // ENUMS_H
