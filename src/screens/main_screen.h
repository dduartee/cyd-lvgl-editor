#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H
#include <lvgl.h>
#include "Logger.h"
#include "screens/screens.h"
using namespace SCREENS::MAIN;
static lv_obj_t * slider_label;


// Callback que imprime o valor do slider na tela e no Serial Monitor
static void slider_event_callback(lv_event_t * e) {
  lv_obj_t * slider = (lv_obj_t*) lv_event_get_target(e);
  char buf[8];
  lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
  lv_label_set_text(slider_label, buf);
  lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  LOG_STR("Slider changed");
  LOG_VAR(lv_slider_get_value(slider));
}

// Callback que é chamado quando btn1 é clicado
static void event_handler_btn1(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    main_config.btn1_count++;
    LOG_STR("Button clicked");
    LOG_VAR(main_config.btn1_count);
  }
}
// Callback que é chamado quando btn2 é clicado/toggle
static void event_handler_btn2(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = (lv_obj_t*) lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
    bool toggled = lv_obj_has_state(obj, LV_STATE_CHECKED);
    LOG_STR(toggled ? "Toggled on" : "Toggled off");
  }
}

void lv_create_main_gui(void) {
  LOG_STR("Creating main GUI");
  // Create a text label aligned center on top ("Hello, world!")
  lv_obj_t * text_label = lv_label_create(lv_screen_active());
  lv_label_set_long_mode(text_label, LV_LABEL_LONG_WRAP);    // Breaks the long lines
  lv_label_set_text(text_label, "Hello, world!");
  lv_obj_set_width(text_label, 150);    // Set smaller width to make the lines wrap
  lv_obj_set_style_text_align(text_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(text_label, LV_ALIGN_CENTER, 0, -90);

  lv_obj_t * btn_label;
  // Create a Button (btn1)
  lv_obj_t * btn1 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn1, event_handler_btn1, LV_EVENT_ALL, NULL);
  lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -50);
  lv_obj_remove_flag(btn1, LV_OBJ_FLAG_PRESS_LOCK);

  btn_label = lv_label_create(btn1);
  lv_label_set_text(btn_label, "Button");
  lv_obj_center(btn_label);

  // Create a Toggle button (btn2)
  lv_obj_t * btn2 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn2, event_handler_btn2, LV_EVENT_ALL, NULL);
  lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 10);
  lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_set_height(btn2, LV_SIZE_CONTENT);

  btn_label = lv_label_create(btn2);
  lv_label_set_text(btn_label, "Toggle");
  lv_obj_center(btn_label);
  
  // Create a slider aligned in the center bottom of the TFT display
  lv_obj_t * slider = lv_slider_create(lv_screen_active());
  lv_obj_align(slider, LV_ALIGN_CENTER, 0, 60);
  lv_obj_add_event_cb(slider, slider_event_callback, LV_EVENT_VALUE_CHANGED, NULL);
  lv_slider_set_range(slider, 0, 100);
  lv_obj_set_style_anim_duration(slider, 2000, 0);

  // Create a label below the slider to display the current slider value
  slider_label = lv_label_create(lv_screen_active());
  lv_label_set_text(slider_label, "0%");
  lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

  // Create Settings button
  lv_obj_t * settings_btn = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(settings_btn, SCREENS::SETTINGS::event_handler_settings_btn, LV_EVENT_ALL, NULL);
  lv_obj_align(settings_btn, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
  lv_obj_set_size(settings_btn, 60, 40);

  btn_label = lv_label_create(settings_btn);
  lv_label_set_text(btn_label, LV_SYMBOL_SETTINGS);
  lv_obj_center(btn_label);
  
  LOG_STR("Main GUI created successfully");
}
void init_main_screen(void) {
   // Create main screen
  main_screen = lv_obj_create(NULL);
  LOG_STR("Main screen created");
}
void load_main_screen(void) {
    // Load main screen initially and create its GUI
  LOG_STR("Loading main screen and creating GUI");
  lv_screen_load(main_screen);
  lv_create_main_gui();
}

#endif // MAIN_SCREEN_H