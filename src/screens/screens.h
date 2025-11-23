#ifndef SCREENS_H
#define SCREENS_H
#include <lvgl.h>

// Namespace for main screen
namespace SCREENS {  // Enum for screen IDs
enum ScreenIDs {
  SCREEN_MAIN,
  SCREEN_SETTINGS,
};
ScreenIDs current_screen;
namespace MAIN {
lv_obj_t* main_screen;
typedef struct {
  int btn1_count = 0;
} MainConfig;
MainConfig main_config;
void event_handler_main_btn(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    LOG_STR("Back to main screen");
    lv_screen_load(main_screen);
    current_screen = SCREEN_MAIN;
    LOG_VAR(current_screen);
  }
}
}  // namespace main_screen
namespace SETTINGS {
lv_obj_t* settings_screen;
typedef struct {
  int brightness_value;
  bool dark_theme;
  bool sound_enabled;
} SettingsConfig;
SettingsConfig settings_config;
void event_handler_settings_btn(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    LOG_STR("Opening settings screen");
    lv_screen_load(settings_screen);
    current_screen = SCREEN_SETTINGS;
    LOG_VAR(current_screen);
  }
}
}  // namespace settings_screen

}  // namespace screens
#endif  // SCREENS_H
