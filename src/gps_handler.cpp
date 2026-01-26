#include "gps_handler.h"

TinyGPSPlus gps;
SoftwareSerial ss(RX_PIN, TX_PIN);

double totalDistance = 0.0;
double lastLat = 0.0, lastLon = 0.0;
bool firstFix = true;

void initGPS() {
    ss.begin(GPS_BAUD);
}

void runGPSLoop() {
    while (ss.available() > 0) {
        gps.encode(ss.read());
    }

    if (gps.location.isUpdated() && gps.location.isValid()) {
        double currLat = gps.location.lat();
        double currLon = gps.location.lng();

        if (firstFix) {
            lastLat = currLat;
            lastLon = currLon;
            firstFix = false;
        } else {
            double dist = gps.distanceBetween(lastLat, lastLon, currLat, currLon);
            if (dist > 3.0) { // Filter small noise
                totalDistance += dist;
                lastLat = currLat;
                lastLon = currLon;
            }
        }
    }
}

bool isGPSUpdated() { return gps.location.isUpdated(); }
bool isGPSValid() { return gps.location.isValid(); }

double getLat() { return gps.location.lat(); }
double getLon() { return gps.location.lng(); }
double getSpeed() { return gps.speed.kmph(); }
double getAlt() { return gps.altitude.meters(); }
double getDistance() { return totalDistance; }
void resetDistance() { totalDistance = 0.0; firstFix = true; }
int getSats() { return gps.satellites.value(); }

int getHour() { return (gps.time.hour() + TIME_OFFSET) % 24; }
int getMinute() { return gps.time.minute(); }
int getDay() { return gps.date.day(); }
int getMonth() { return gps.date.month(); }
int getYear() { return gps.date.year(); }
