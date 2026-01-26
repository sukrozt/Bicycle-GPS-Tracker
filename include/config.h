#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// --- PINS ---
#define SD_CS      4
#define TFT_MOSI   6
#define TFT_CLK    7
#define TFT_RST    8
#define TFT_DC     9
#define TFT_CS     10
#define RESET_PIN  A4 
#define CHRONO_BTN A5 

// GPS PINS
#define RX_PIN     2
#define TX_PIN     3

// --- SETTINGS ---
#define GPS_BAUD    9600
#define TIME_OFFSET 3   // UTC+3 for Turkey
#define LOG_INTERVAL 5000 // 5 seconds

#endif
