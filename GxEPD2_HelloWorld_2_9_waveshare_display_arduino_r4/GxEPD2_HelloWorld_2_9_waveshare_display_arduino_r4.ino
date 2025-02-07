// uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX
//#include <GFX.h>

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_4C.h>
#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <DHT22.h>

#define pinDATA SDA

DHT22 dht22(pinDATA);

GxEPD2_3C<GxEPD2_290c, GxEPD2_290c::HEIGHT> display(GxEPD2_290c(D10, D9, D8, D7));

void setup() {
  display.init(115200, true, 2, false);
  // // To save power use hibernate
  // display.hibernate();
  // // reset the screen to white to prevent screen burn
  // display.clearScreen();
}

void TextToShow(char textData[]) {
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(2);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(textData, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, y);
    display.print(textData);
  } while (display.nextPage());
}

void loop() {
  // full refresh interval 15 sec, update data every 15 sec
  float t = dht22.getTemperature();
  float h = dht22.getHumidity();
  
  String x_val = "T: " + String(t) + "'C\nH: " + String(h) + "%";

  // Prepare the character array (the buffer)
  char char_array[x_val.length() + 1];

  // Copy it over
  x_val.toCharArray(char_array, x_val.length() + 1);
  TextToShow(char_array);

  delay(20000);
};
