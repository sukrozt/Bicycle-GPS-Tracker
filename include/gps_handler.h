#ifndef GPS_HANDLER_H
#define GPS_HANDLER_H

#include "config.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

void initGPS();
void runGPSLoop(); // Call this in main loop to read data,
bool isGPSUpdated();
bool isGPSValid();

// Getters (to access data safely)
double getLat();
double getLon();
double getSpeed();
double getAlt();
double getDistance(); // Returns total distance calculated
void resetDistance();
int getSats();

// Time helpers
int getHour();
int getMinute();
int getDay();
int getMonth();
int getYear();

#endif
