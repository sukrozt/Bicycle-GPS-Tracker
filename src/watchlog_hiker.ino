#include "config.h"
#include "gps_handler.h"
#include "display_ui.h"
#include "storage.h"

// Chronometer Variables
bool chronoRunning = false;
unsigned long chronoStartTime = 0;
unsigned long chronoElapsed = 0;
unsigned long lastChronoPress = 0;
unsigned long lastResetPress = 0;
unsigned long lastLog = 0;

void setup() {
    // 1. Init System
    pinMode(RESET_PIN, INPUT_PULLUP); 
    pinMode(CHRONO_BTN, INPUT_PULLUP);
    
    // 2. Init Modules
    initGPS();
    initDisplay();
    drawBaseInterface();
    
    // 3. Init SD and show status
    bool sdStatus = initStorage();
    showSDStatus(sdStatus);
}

void loop() {
    // A. Run GPS Logic
    runGPSLoop();

    // B. Update Screen if GPS Changed
    if (isGPSUpdated() && isGPSValid()) {
        updateDashboard(getSpeed(), getDistance(), getAlt(), getSats());
        updateClock(getHour(), getMinute());
        
        // Update date only if changed (handled inside display_ui for visual, 
        // but we pass data here to keep logic separated)
        static int lastDay = 0;
        if(getDay() != lastDay) {
            updateDate(getDay(), getMonth(), getYear());
            lastDay = getDay();
        }
    }

    // C. Logging Logic
    if (millis() - lastLog > LOG_INTERVAL) {
        if (isGPSValid()) {
             logDataToSD(getDay(), getMonth(), getLat(), getLon(), getSpeed());
             blinkRecordIndicator();
        }
        lastLog = millis();
    }

    // D. Button & Timer Logic
    handleButtons();
    
    // Calculate timer seconds for display
    unsigned long now = chronoRunning ? chronoElapsed + (millis() - chronoStartTime) : chronoElapsed;
    updateTimer(now / 1000);
}

void handleButtons() {
    // Chrono Button
    if (digitalRead(CHRONO_BTN) == LOW) {
        if (millis() - lastChronoPress > 500) {
            if (chronoRunning) {
                chronoElapsed += (millis() - chronoStartTime);
                chronoRunning = false;
            } else {
                chronoStartTime = millis();
                chronoRunning = true;
            }
            lastChronoPress = millis();
        }
    }

    // Reset Button
    if (digitalRead(RESET_PIN) == LOW) {
        if (millis() - lastResetPress > 2000) { 
            resetDistance();
            chronoElapsed = 0; 
            chronoRunning = false;
            
            resetUI(); // Clears screen and redraws labels
            showSDStatus(true); // Re-show SD status
            
            lastResetPress = millis();
        }
    }
}
