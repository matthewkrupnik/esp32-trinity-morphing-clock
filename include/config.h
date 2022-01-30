#ifndef CONFIG_H
#define CONFIG_H

//#define USE_ANDROID_AP 1

// How often we refresh the time from the NTP server
#define NTP_REFRESH_INTERVAL_SEC 3600

// Timezone difference from GMT, expressed in seconds
#define TIMEZONE_DELTA_SEC -18000
// DST delta to apply
#define TIMEZONE_DST_SEC -14400

// How long are informational messages kept on screen
#define LOG_MESSAGE_PERSISTENCE_MSEC 30000

// Screen positioning settings
// Panel size
#define PANEL_WIDTH 64
#define PANEL_HEIGHT 32

// Clock
#define CLOCK_X 2
#define CLOCK_Y 9
#define CLOCK_SEGMENT_HEIGHT 6
#define CLOCK_SEGMENT_WIDTH 6
#define CLOCK_SEGMENT_SPACING 3
#define CLOCK_WIDTH 6*(CLOCK_SEGMENT_WIDTH+CLOCK_SEGMENT_SPACING)+4
#define CLOCK_HEIGHT 2*CLOCK_SEGMENT_HEIGHT+3
//color565 == ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3)
#define CLOCK_DIGIT_COLOR  ((0x00 & 0xF8) << 8) | ((0xFF & 0xFC) << 3) | (0xFF >> 3)
//Delay in ms for clock animation - should be below 30ms for a segment size of 8
#define CLOCK_ANIMATION_DELAY_MSEC 20

// Day of week
#define DOW_X 2
#define DOW_Y 0
#define DOW_COLOR ((0x00 & 0xF8) << 8) | ((0x40 & 0xFC) << 3) | (0xFF >> 3)
//Width and height are for both DATE and DOW
#define DATE_WIDTH 54
#define DATE_HEIGHT 7

// Log messages at the bottom
#define LOG_MESSAGE_COLOR ((0xFF & 0xF8) << 8) | ((0x00 & 0xFC) << 3) | (0x00 >> 3)

// Watchdog settings
#define WDT_TIMEOUT 60   // If the WDT is not reset within X seconds, reboot the unit
        // Do NOT set this too low, or the WDT will prevent OTA updates from completing!!

//Temperature range for today
#define TEMPRANGE_X 5
#define TEMPRANGE_Y 25
#define TEMPRANGE_WIDTH 60
#define TEMPRANGE_HEIGHT 6
//#define TEMPRANGE_COLOR ((0x00 & 0xF8) << 8) | ((0xFF & 0xFC) << 3) | (0xFF >> 3)
#define TEMPRANGE_COLOR ((0x00 & 0xF8) << 8) | ((0x40 & 0xFC) << 3) | (0xFF >> 3)

// How often to refresh weather forecast data
// (limited by API throttling)
#define WEATHER_REFRESH_INTERVAL_SEC 14400

#endif