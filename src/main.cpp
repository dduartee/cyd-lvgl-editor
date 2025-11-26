#include <Arduino.h>
#include <lvgl.h>
#include "ui/ui.h"
#include "interface/Display.h"
#include "interface/Touchscreen.h"

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

  // Parameter to editor_project_init() is the asset path.
  // Provide the base directory where LVGL should look for asset files (fonts & images).
  // If you are not loading assets from a filesystem, pass an empty string "".
  //
  // Example folder structure:
  //   /editor_project/fonts/font.ttf
  //   /editor_project/images/image.bin
  //
  // LVGL uses a drive letter prefix based on what you configure (e.g. "C", "D", etc.).
  // If you configure the drive letter as "C", the path would be:
  //   C:/editor_project/
  //
  // Example:
  // editor_project_init("C:/editor_project/");
  ui_init();
}

void loop() {
  lv_timer_handler(); // Handle LVGL tasks
  lv_tick_inc(5);
  ui_tick();
  delay(5);
}