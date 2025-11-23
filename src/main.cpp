/*  Install the "lvgl" library version 9.2 by kisvegabor to interface with the
   TFT Display - https://lvgl.io/
    *** IMPORTANT: lv_conf.h available on the internet will probably NOT work
   with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE lv_conf.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO
   USE THE EXAMPLES FROM RANDOM NERD TUTORIALS *** FULL INSTRUCTIONS AVAILABLE
   ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd-lvgl/ or
   https://RandomNerdTutorials.com/esp32-tft-lvgl/   */
#include <lvgl.h>

#include "interface/Touchscreen.h"

// Include the Logger
#include "Logger.h"
#include "screens/main_screen.h"
#include "screens/settings_screen.h"

// If logging is enabled, it will inform the user about what is happening in the
// library
void log_print(lv_log_level_t level, const char* buf) {
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}

void setup() {
  String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() +
                        "." + lv_version_minor() + "." + lv_version_patch();
  Serial.begin(115200);
  Serial.println(LVGL_Arduino);

  // Start LVGL
  lv_init();
  // Register print function for debugging
  lv_log_register_print_cb(log_print);

  createDisplay();

  initInputDevice();

  LOG_STR("Creating screens...");

  init_settings_screen();
  init_main_screen();

  load_main_screen();
  load_settings_screen();

  // Return to main screen
  LOG_STR("Returning to main screen");
  lv_screen_load(main_screen);

  LOG_STR("Setup completed successfully");
}

void loop() {
  lv_task_handler();  // let the GUI do its work
  lv_tick_inc(5);     // tell LVGL how much time has passed
  delay(5);           // let this time pass
}
