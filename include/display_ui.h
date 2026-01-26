#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H

#include "config.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

void initDisplay();
void drawBaseInterface(); // Draws static labels
void updateDashboard(double speed, double dist, double alt, int sats);
void updateClock(int h, int m);
void updateDate(int d, int m, int y);
void updateTimer(unsigned long currentSeconds);
void showSDStatus(bool status);
void blinkRecordIndicator();
void resetUI();

#endif
