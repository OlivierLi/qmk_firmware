#pragma once

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(PLANCK_SOUND)
#endif

#define MIDI_BASIC

#define ENCODER_RESOLUTION 4

#undef IGNORE_MOD_TAP_INTERRUPT

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define FIRMWARE_VERSION u8"JwnlO/yB9Vo"

#ifndef TAPPING_TERM
#define TAPPING_TERM 200
#endif
