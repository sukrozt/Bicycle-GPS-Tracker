#ifndef STORAGE_H
#define STORAGE_H

#include "config.h"
#include <SD.h>

bool initStorage();
void logDataToSD(int d, int m, double lat, double lon, double speed);

#endif
