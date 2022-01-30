#include "weather.h"
#include "common.h"
#include "creds_accuweather.h"

#include <HTTPClient.h>
#include <ArduinoJson.h>
//#include <Fonts/FreeSerifBold12pt7b.h>

int8_t currentTempMetric = 0;
int8_t currentTempImperial = 0;

// Get color565 directly from 24-bit RGB value
// TODO - replace arrays with color565 values!
uint16_t color565(uint32_t rgb) {
  return (((rgb>>16) & 0xF8) << 8) | 
    (((rgb>>8) & 0xFC) << 3) | 
    ((rgb & 0xFF) >> 3);
};

void displayTodaysTempRange() {
  dma_display->fillRect(TEMPRANGE_X, TEMPRANGE_Y, TEMPRANGE_WIDTH, TEMPRANGE_HEIGHT, 0);
  dma_display->setTextSize(1);     // size 1 == 8 pixels high
  dma_display->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  dma_display->setTextColor(TEMPRANGE_COLOR);

  dma_display->setCursor(TEMPRANGE_X, TEMPRANGE_Y);   
  dma_display->printf("%3dC/%3dF", currentTempMetric, currentTempImperial);
  
  // Draw the degree symbol manually
  //dma_display->fillRect(TEMPRANGE_X + 44, TEMPRANGE_Y, 2, 2, TEMPRANGE_COLOR);
}

void displayWeatherData() {
  displayTodaysTempRange();
}

//Source: https://github.com/witnessmenow/LED-Matrix-Display-Examples/blob/master/LED-Matrix-Mario-Display/LED-Matrix-Mario-Display.ino
void drawBitmap(int startx, int starty, int width, int height, uint32_t *bitmap) {
  int counter = 0;
  for (int yy = 0; yy < height; yy++) {
    for (int xx = 0; xx < width; xx++) {
      dma_display->drawPixel(startx+xx, starty+yy, color565(bitmap[counter]));
      counter++;
    }
  }
}

// Draw the bitmap, with an option to enlarge it by a factor of two
void drawBitmap(int startx, int starty, int width, int height, uint32_t *bitmap, bool enlarged) {
  int counter = 0;
  if (enlarged) {
    for (int yy = 0; yy < height; yy++) {
      for (int xx = 0; xx < width; xx++) {
        dma_display->drawPixel(startx+2*xx, starty+2*yy, color565(bitmap[counter]));
        dma_display->drawPixel(startx+2*xx+1, starty+2*yy, color565(bitmap[counter]));
        dma_display->drawPixel(startx+2*xx, starty+2*yy+1, color565(bitmap[counter]));
        dma_display->drawPixel(startx+2*xx+1, starty+2*yy+1, color565(bitmap[counter]));
        counter++;
      }
    }
  }
  else drawBitmap(startx, starty, width, height, bitmap);
}

void getAccuWeatherData() {
  HTTPClient http;
  char url[256];
  DynamicJsonDocument doc(16384); // Might be overkill, since the Accuweather JSONs are about 3-5K in length - but better safe...

  snprintf( url, 256, "http://dataservice.accuweather.com/currentconditions/v1/%s?apikey=%s", 
      ACCUWEATHER_CITY_CODE, ACCUWEATHER_API_KEY);

  http.begin(url);
  http.GET(); //TODO - check status code!

  DeserializationError error = deserializeJson( doc, http.getStream());

  if (error) {
    Serial.print(F("deserialization failed: "));
    Serial.println(error.f_str());
    logStatusMessage("Weather data error!");
  }

  doc.shrinkToFit();

  //Just in case we need to debug...
  //serializeJsonPretty(doc, Serial);

  //Populate the variables: 
  currentTempMetric = round( double(doc[0]["Temperature"]["Metric"]["Value"]) );
  currentTempImperial = round( double(doc[0]["Temperature"]["Imperial"]["Value"]) );
  
  Serial.println(currentTempMetric);
  Serial.println(currentTempImperial);
}
