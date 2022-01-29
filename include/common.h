#ifndef COMMON_H
#define COMMON_H

#include "config.h"
#include "rgb_display.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <ESPNtpClient.h>

extern WiFiClient wifiClient;

extern int status;

//Time of last status update
extern unsigned long lastStatusSend;
extern unsigned long lastLightRead;
extern unsigned long lastLedBlink;

//Log message persistence
//Is a log message currently displayed?
extern bool logMessageActive;
//When was the message shown?
extern unsigned long messageDisplayMillis;

// NTP
extern bool wifiFirstConnected;

extern bool syncEventTriggered; // True if a time event has been triggered

//RGB display
extern MatrixPanel_I2S_DMA *dma_display;

//Current time and date
extern struct tm timeinfo;

//Flags to trigger display section updates
extern bool clockStartingUp;

//Just a heartbeat for the watchdog...
extern bool heartBeat;

//Weather data
extern int8_t minTempToday;
extern int8_t maxTempToday;

#endif

