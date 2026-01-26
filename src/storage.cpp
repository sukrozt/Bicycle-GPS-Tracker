#include "storage.h"

File logFile;

bool initStorage() {
    if (!SD.begin(SD_CS)) return false;
    
      if (!SD.exists("log.txt")) {
      logFile = SD.open("log.txt", FILE_WRITE);
      if (logFile) {
        logFile.println(F("DATE,TIME,LAT,LON,SPD,ALT,DIST"));
        logFile.close();
      }
    }
    return true;
}

void logDataToSD(int d, int m, double lat, double lon, double speed) {
    logFile = SD.open("log.txt", FILE_WRITE);
    if (logFile) {
        logFile.print(d); logFile.print('/');
        logFile.print(m); logFile.print(',');
        logFile.print(lat, 6); logFile.print(',');
        logFile.print(lon, 6); logFile.print(',');
        logFile.print(speed); logFile.println(); 
        logFile.close();
    }
}
