#include "data.h"

// Cache all data
static GColor s_foreground, s_background;
static bool s_bool_settings[DataNumBoolKeys];

static void write_defaults() {
  s_bool_settings[DataKeyDate] = false;
  s_bool_settings[DataKeyAnimations] = true;
  s_bool_settings[DataKeyBTIndicator] = true;
  s_bool_settings[DataKeyHourlyVibration] = false;
  s_bool_settings[DataKeySleep] = false;
  s_foreground = GColorWhite;
  s_background = GColorBlack;
  data_deinit();
}

void data_init() {
  // Nuke previus version settings
  if(!persist_exists(V_3_1)) {
    persist_write_bool(V_3_1, true);

    for(int i = 0; i < DataNumBoolKeys; i++) {
      persist_delete(i);
    }
    persist_delete(DataKeyForegroundColor);
    persist_delete(DataKeyBackgroundColor);

    write_defaults();
  } else {
    // Read settings
    for(int i = 0; i < DataNumBoolKeys; i++) {
      s_bool_settings[i] = persist_read_bool(i);
    }
#if defined(PBL_SDK_3)
    s_foreground = (GColor){ .argb = persist_read_int(DataKeyForegroundColor) };
    s_background = (GColor){ .argb = persist_read_int(DataKeyBackgroundColor) };
#elif defined(PBL_SDK_2)
    s_foreground = (persist_read_int(DataKeyForegroundColor) == 1) ? GColorWhite : GColorBlack;
    s_background = (persist_read_int(DataKeyBackgroundColor) == 1) ? GColorWhite : GColorBlack;
#endif
  }
}

void data_deinit() {
  // Store current values
  for(int i = 0; i < DataNumBoolKeys; i++) {
    persist_write_bool(i, s_bool_settings[i]);
  }
#if defined(PBL_SDK_3)
  persist_write_int(DataKeyForegroundColor, s_foreground.argb);
  persist_write_int(DataKeyBackgroundColor, s_background.argb);
#elif defined(PBL_SDK_2)
  persist_write_int(DataKeyForegroundColor, (s_foreground == GColorWhite) ? 1 : 0);
  persist_write_int(DataKeyBackgroundColor, (s_background == GColorWhite) ? 1 : 0);
#endif
}

bool data_get_boolean_setting(int data_key) {
  return (data_key < DataNumBoolKeys && persist_exists(data_key)) ? s_bool_settings[data_key] : false;
}

void data_set_boolean_setting(int data_key, bool value) {
  if(data_key < DataNumBoolKeys) {
    s_bool_settings[data_key] = value;
  }
}

GColor data_get_foreground_color() {
  return s_foreground;
}

GColor data_get_background_color() {
  return s_background;
}

void data_set_foreground_color(GColor color) {
  s_foreground = color;
}

void data_set_background_color(GColor color) {
  s_background = color;
}
