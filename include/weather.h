#ifndef WEATHER_H
#define WEATHER_H

#include <Arduino.h>

void displayWeatherData();
void displayTodaysTempRange();
void drawBitmap(int startx, int starty, int width, int height, uint32_t *bitmap);
void drawBitmap(int startx, int starty, int width, int height, uint32_t *bitmap, bool enlarged);
void getAccuWeatherData();

#endif