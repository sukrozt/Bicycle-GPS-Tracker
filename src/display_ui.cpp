#include "display_ui.h"

// Initialize the global TFT object here
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, -1);

void drawStat(int x, int y, double val, int dec, uint16_t color) {
  tft.fillRect(x, y, 140, 30, ILI9341_BLACK); 
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(3);
  tft.print(val, dec);
}

void initDisplay() {
    pinMode(TFT_CS, OUTPUT); 
    digitalWrite(TFT_CS, HIGH); 
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(ILI9341_BLACK);
}

void drawBaseInterface() {
    tft.setTextColor(ILI9341_WHITE); tft.setTextSize(2);
    tft.setCursor(10, 10);  tft.print(F("SPD:"));
    tft.setCursor(170, 10); tft.print(F("CLK:")); 
    tft.setCursor(10, 80);  tft.print(F("DST (km):"));
    tft.setCursor(10, 150); tft.print(F("ALT (m):"));
    tft.setCursor(170, 150);tft.print(F("TMR:"));
    tft.setTextSize(1); tft.setCursor(280, 230); tft.print(F("Sat:"));
}

void updateDashboard(double speed, double dist, double alt, int sats) {
    drawStat(10, 35, speed, 1, ILI9341_CYAN);           
    drawStat(10, 105, dist / 1000.0, 2, ILI9341_GREEN);  
    drawStat(10, 175, alt, 0, ILI9341_YELLOW);  

    // Sats
    tft.fillRect(305, 230, 15, 10, ILI9341_BLACK);
    tft.setTextSize(1); tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(305, 230); 
    tft.print(sats);
}

void updateClock(int h, int m) {
    tft.fillRect(170, 35, 140, 30, ILI9341_BLACK);
    tft.setCursor(170, 35);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    if (h < 10) tft.print('0'); tft.print(h); tft.print(':');
    if (m < 10) tft.print('0'); tft.print(m);
}

void updateDate(int d, int month, int y) {
    tft.fillRect(220, 10, 100, 20, ILI9341_BLACK);
    tft.setCursor(220, 12);
    tft.setTextColor(ILI9341_ORANGE);
    tft.setTextSize(1);
    if (d < 10) tft.print('0'); tft.print(d); tft.print('.');
    if (month < 10) tft.print('0'); tft.print(month); tft.print('.');
    tft.print(y);
}

void updateTimer(unsigned long currentSec) {
    static unsigned long lastDrawnSec = 99999; 
    if (currentSec == lastDrawnSec) return;
    lastDrawnSec = currentSec;

    tft.fillRect(170, 175, 140, 30, ILI9341_BLACK); 
    tft.setCursor(170, 175);
    tft.setTextColor(ILI9341_MAGENTA); tft.setTextSize(3);
  
    int m = currentSec / 60;
    int s = currentSec % 60;
  
    if (m < 10) tft.print('0'); tft.print(m); tft.print(':');
    if (s < 10) tft.print('0'); tft.print(s);
}

void showSDStatus(bool status) {
    tft.setCursor(5, 230); tft.setTextSize(1);
    if (!status) {
        tft.setTextColor(ILI9341_RED); tft.print(F("SD: FAIL"));
    } else {
        tft.setTextColor(ILI9341_GREEN); tft.print(F("SD: REC"));
    }
}

void blinkRecordIndicator() {
    tft.fillCircle(310, 230, 4, ILI9341_RED); 
    delay(50); // Kept small delay for visual effect
    tft.fillCircle(310, 230, 4, ILI9341_BLACK);
}

void resetUI() {
    tft.fillScreen(ILI9341_BLACK);
    drawBaseInterface();
}
