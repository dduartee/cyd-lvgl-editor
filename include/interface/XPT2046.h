#include <XPT2046_Touchscreen.h>
/*  Install the "TFT_eSPI" library by Bodmer to interface with the TFT Display -
   https://github.com/Bodmer/TFT_eSPI
    *** IMPORTANT: User_Setup.h available on the internet will probably NOT work
   with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE User_Setup.h FILE PROVIDED IN THE LINK BELOW IN ORDER
   TO USE THE EXAMPLES FROM RANDOM NERD TUTORIALS *** FULL INSTRUCTIONS
   AVAILABLE ON HOW CONFIGURE THE LIBRARY:
   https://RandomNerdTutorials.com/cyd-lvgl/ or
   https://RandomNerdTutorials.com/esp32-tft-lvgl/   */
#include <TFT_eSPI.h>

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
SPIClass touchscreenSPI = SPIClass(VSPI);

void startXPT2046() {
  // Start the SPI for the touchscreen and init the touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might
  // need to set the rotation to 0: touchscreen.setRotation(0);
  touchscreen.setRotation(2);
}