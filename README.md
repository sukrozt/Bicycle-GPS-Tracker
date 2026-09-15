# WatchLog Biker - High Precision GPS Tracker & Data Logger

> **Status:** Active Development  
> **Target Platform:** Arduino Uno / Embedded C++  
> **Application:** Offline Performance Tracking for Outdoor Sports

## Overview
WatchLog Biker is a standalone, embedded system designed to track, display, and log geospatial data for cycling and hiking without reliance on cellular networks. 

Unlike standard phone apps, this device provides real-time telemetry (Speed, Altitude, Distance) via a dedicated TFT dashboard and logs granular NMEA data to an SD card for scientific analysis or mapping.

## Key Features
* **Real-Time Telemetry:** Displays Speed (km/h), Altitude (m), and Total Distance (km) with <1s latency.
* **Precision Timing:** Integrated chronometer with start/stop/reset logic handled via hardware debouncing.
* **Offline Data Logging:** Writes CSV-formatted logs (`DATE, TIME, LAT, LON, SPD, ALT`) to an SD card for post-processing.
* **Power Management:** Optimized for 18650 Li-Ion battery operation using LM2596 voltage regulation.
* **Modular Architecture:** Codebase separated into distinct handlers (GPS, UI, Storage) for maintainability.

## Hardware Architecture

### Components
| Component | Function | Protocol |
| :--- | :--- | :--- |
| **Microcontroller** | Arduino Uno (ATmega328P) | - |
| **GPS Module** | NEO-M8N (High Precision GNSS) | UART (9600 Baud) |
| **Display** | 2.4" TFT LCD (ILI9341 Driver) | SPI |
| **Storage** | SD Card Module | SPI |
| **Power** | 2x 18650 Batteries + LM2596 Buck Converter (Alternative: 5.0V 3.0A Powerbank)| - |

### Wiring & Pinout
The system utilizes SoftwareSerial for GPS communication to keep the hardware UART open for debugging.

| Device | Pin | Description |
| :--- | :--- | :--- |
| **GPS TX** | D2 | RX SoftwareSerial |
| **GPS RX** | D3 | TX SoftwareSerial |
| **SD CS** | D4 | Chip Select (Storage) |
| **TFT CS** | D10 | Chip Select (Display) |
| **TFT DC** | D9 | Data/Command |
| **Btn 1** | A5 | Chronometer Start/Stop |
| **Btn 2** | A4 | System Reset |



## Software Architecture
The codebase follows a **Service-Oriented** structure.

* `src/gps_handler.cpp`: Encapsulates NMEA parsing logic using `TinyGPS++`. Filters noise and calculates Haversine distance.
* `src/display_ui.cpp`: Manages the SPI-driven ILI9341 display. Uses partial screen refreshing (dirty rectangles) to prevent flickering.
* `src/storage.cpp`: Handles file I/O operations. Includes error checking for SD card presence and write permissions.
* `src/main.cpp`: Acts as the central controller, polling sensors and updating the UI state machine.

## Data Sample
The device generates analysis-ready CSV files. In future, these CSV files will be converted visual map data.
```csv
DATE,TIME,LAT,LON,SPD,ALT,DIST
26/01/2026,14:30:05,48.23412,16.3412,24.5,340,12.4
26/01/2026,14:30:10,48.23415,16.3415,25.1,342,12.5
