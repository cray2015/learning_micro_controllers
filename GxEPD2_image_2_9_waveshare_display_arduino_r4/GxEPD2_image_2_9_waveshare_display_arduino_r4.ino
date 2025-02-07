// uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX
//#include <GFX.h>

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_4C.h>
#include <GxEPD2_7C.h>
#include <avr/pgmspace.h>
#include "profile_img.h"

GxEPD2_3C<GxEPD2_290c, GxEPD2_290c::HEIGHT> display(GxEPD2_290c(D10, D9, D8, D7));
// image2cpp config
// "image rotation matters before converting - change to horizontal for better compatibility"
// canvas size - 296x128
// scaling - to fit or strech
// rotate 90 degree
// code rotation off

void setup() {
  display.init(115200, true, 2, false);
  showImage();
  display.hibernate();
  // // To clean display 
  // display.clearScreen();
}

void showImage() {
  // display.setRotation(1);
  for (uint16_t i = 0; i < sizeof(epd_bitmap_allArray) / sizeof(char*); i++) {
    display.firstPage();
    do {
      display.fillScreen(GxEPD_WHITE);
      display.drawInvertedBitmap(0, 0, epd_bitmap_allArray[i], 128, 296, GxEPD_BLACK);
    } 
    while (display.nextPage());
    delay(2000);
  }
  display.mirror(true);
}

void loop(){
};
