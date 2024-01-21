# RFID Doorlock System With Datalogging

## Overview
Designed and implemented an RFID-Based door lock system.integrated data logging feature,with data stored and analyzed on Google sheets
It is designed to provide secure access using RFID technology, with the added feature of data logging.

## Hardware Components

- MFRC522 Module
- Esp8266
- Solenoid
- Relay
- RFID tags
- Buzzer
- 12V Battery
- Breadboard

## Software Components

- Arduino IDE for Esp8266
- Google Sheets (for storing data logs)

## Connect the hardware components:
Follow the provided documentation to connect the MFRC522 Module, Esp8266, Solenoid, Relay, RFID tags, Buzzer, and the 12V Battery.

## Install necessary libraries
If using Arduino IDE, install the required libraries for the MFRC522 module and any other dependencies.

## Upload the code:
Upload the Arduino code to the Esp8266 using the Arduino IDE.

## Usage
Users can present RFID tags to gain access through the doorlock.
Access attempts are logged and stored in Google Sheets.

## Configuration
Configure the WiFi settings in the Arduino code for Esp8266.
Adjust any other settings as needed in the code for specific requirements.

## Installation

1. **Clone the repository:**

   ```bash
   git clone https://github.com/ganesh81471/RFID_WITH_DATALOGGING.git
   cd RFID_WITH_DATALOGGING
