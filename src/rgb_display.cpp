
#include "rgb_display.h"

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#include "common.h"

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// From: https://gist.github.com/davidegironi/3144efdc6d67e5df55438cc3cba613c8
uint16_t colorWheel(uint8_t pos) {
  if(pos < 85) {
    return dma_display->color565(pos * 3, 255 - pos * 3, 0);
  } else if(pos < 170) {
    pos -= 85;
    return dma_display->color565(255 - pos * 3, 0, pos * 3);
  } else {
    pos -= 170;
    return dma_display->color565(0, pos * 3, 255 - pos * 3);
  }
}

void display_init() {
  HUB75_I2S_CFG::i2s_pins _pins={R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};
  HUB75_I2S_CFG mxconfig(
	64, // Module width
	32, // Module height
	1, // chain length
	_pins // pin mapping
  );
  // mxconfig.gpio.e = E_PIN;
  mxconfig.driver = HUB75_I2S_CFG::FM6124;
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);

	// MUST DO THIS FIRST!
	dma_display->begin(); // Use default values for matrix dimentions and pins supplied within ESP32-HUB75-MatrixPanel-I2S-DMA.h
  //dma_display->setPanelBrightness(110);
}

void logStatusMessage(const char *message) {
  Serial.println(message);
  // Clear the last line first!
  dma_display->fillRect(0, 56, 64, 8, 0);

  dma_display->setTextSize(1);     // size 1 == 8 pixels high
  dma_display->setTextWrap(false); // Don't wrap at end of line - will do ourselves

  dma_display->setCursor(0, 56);   // Write on last line

  dma_display->setTextColor(LOG_MESSAGE_COLOR);
  dma_display->print(message);

  messageDisplayMillis = millis();
  logMessageActive = true;
}


void logStatusMessage(String message) {
  Serial.println(message);
  // Clear the last line first!
  dma_display->fillRect(0, 56, 64, 8, 0);

  dma_display->setTextSize(1);     // size 1 == 8 pixels high
  dma_display->setTextWrap(false); // Don't wrap at end of line - will do ourselves

  dma_display->setCursor(0, 56);   // Write on last line

  dma_display->setTextColor(dma_display->color444(255,0,0));
  dma_display->print(message);

  messageDisplayMillis = millis();
  logMessageActive = true;
}

void clearStatusMessage() {
   dma_display->fillRect(0, 56, 64, 8, 0); 
   logMessageActive = false;
}

// Simple R/G/B screen fill, for testing displays
void displayTest(int delayMs) {
  dma_display->fillRect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, dma_display->color565(255, 0, 0));
  delay(delayMs);
  dma_display->fillRect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, dma_display->color565(0, 255, 0));
  delay(delayMs);
  dma_display->fillRect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, dma_display->color565(0, 0, 255));
  delay(delayMs);
  dma_display->fillRect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, dma_display->color565(0, 0, 0));
}