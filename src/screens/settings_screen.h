#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H
#include <lvgl.h>

#include "Logger.h"
#include "screens/screens.h"
using namespace SCREENS::SETTINGS;
// Callback for brightness slider in settings
static void brightness_slider_callback(lv_event_t* e) {
  lv_obj_t* slider = (lv_obj_t*)lv_event_get_target(e);
  settings_config.brightness_value = (int)lv_slider_get_value(slider);
  LOG_VAR(settings_config.brightness_value);
}

// Callback for theme toggle in settings
static void theme_toggle_callback(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t* obj = (lv_obj_t*)lv_event_get_target(e);
  if (code == LV_EVENT_VALUE_CHANGED) {
    settings_config.dark_theme = lv_obj_has_state(obj, LV_STATE_CHECKED);
    LOG_VAR(settings_config.dark_theme);
  }
}

// Callback for sound toggle in settings
static void sound_toggle_callback(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t* obj = (lv_obj_t*)lv_event_get_target(e);
  if (code == LV_EVENT_VALUE_CHANGED) {
    settings_config.sound_enabled = lv_obj_has_state(obj, LV_STATE_CHECKED);
    LOG_VAR(settings_config.sound_enabled);
  }
}
void init_settings_screen(void) {
  settings_screen = lv_obj_create(NULL);
  LOG_STR("Settings screen created");
}

void lv_create_settings_gui(void) {
  LOG_STR("Creating settings GUI");
  // Create settings screen title
  lv_obj_t* title_label = lv_label_create(lv_screen_active());
  lv_label_set_text(title_label, "Configurações");
  lv_obj_set_style_text_align(title_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 20);

  // Create back button
  lv_obj_t* back_btn = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(back_btn, SCREENS::MAIN::call_main, LV_EVENT_ALL, NULL);
  lv_obj_align(back_btn, LV_ALIGN_TOP_LEFT, 10, 10);
  lv_obj_set_size(back_btn, 50, 40);

  lv_obj_t* btn_label = lv_label_create(back_btn);
  lv_label_set_text(btn_label, LV_SYMBOL_LEFT);
  lv_obj_center(btn_label);

  // Brightness setting
  lv_obj_t* brightness_label = lv_label_create(lv_screen_active());
  lv_label_set_text(brightness_label, "Brilho");
  lv_obj_align(brightness_label, LV_ALIGN_CENTER, 0, -80);

  lv_obj_t* brightness_slider = lv_slider_create(lv_screen_active());
  lv_obj_align(brightness_slider, LV_ALIGN_CENTER, 0, -50);
  lv_obj_add_event_cb(brightness_slider, brightness_slider_callback,
                      LV_EVENT_VALUE_CHANGED, NULL);
  lv_slider_set_range(brightness_slider, 10, 100);
  lv_slider_set_value(brightness_slider, settings_config.brightness_value,
                      LV_ANIM_OFF);

  // Theme setting
  lv_obj_t* theme_label = lv_label_create(lv_screen_active());
  lv_label_set_text(theme_label, "Tema Escuro");
  lv_obj_align(theme_label, LV_ALIGN_CENTER, 0, -10);

  lv_obj_t* theme_toggle = lv_switch_create(lv_screen_active());
  lv_obj_align(theme_toggle, LV_ALIGN_CENTER, 0, 20);
  lv_obj_add_event_cb(theme_toggle, theme_toggle_callback,
                      LV_EVENT_VALUE_CHANGED, NULL);
  if (settings_config.dark_theme) {
    lv_obj_add_state(theme_toggle, LV_STATE_CHECKED);
  }

  // Sound setting
  lv_obj_t* sound_label = lv_label_create(lv_screen_active());
  lv_label_set_text(sound_label, "Som");
  lv_obj_align(sound_label, LV_ALIGN_CENTER, 0, 60);

  lv_obj_t* sound_toggle = lv_switch_create(lv_screen_active());
  lv_obj_align(sound_toggle, LV_ALIGN_CENTER, 0, 90);
  lv_obj_add_event_cb(sound_toggle, sound_toggle_callback,
                      LV_EVENT_VALUE_CHANGED, NULL);
  if (settings_config.sound_enabled) {
    lv_obj_add_state(sound_toggle, LV_STATE_CHECKED);
  }

  LOG_STR("Settings GUI created successfully");
}
void load_settings_screen(void) {
  LOG_STR("Pre-loading settings GUI");
  lv_screen_load(settings_screen);
  lv_create_settings_gui();
}
#endif  // SETTINGS_SCREEN_H
