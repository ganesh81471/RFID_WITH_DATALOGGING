// Install all Libraries Mentioned here
#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>

ESP8266WiFiMulti wifiMulti;
const uint32_t connectTimeoutMs = 5000;
const uint8_t fingerprint[20] = {0x5D, 0x3A, 0xD9, 0x47, 0x14, 0xB0, 0x78, 0x30, 0xA1, 0xBF, 0xB4, 0x45, 0xF6, 0xF5, 0x81, 0xAD, 0x0A, 0xC7, 0x76, 0x89};//Replace with your Fingerprint
String data2;
char data;
const String data1 = "https://script.google.com/macros/s/AKfycbzmyNCrtxgSsKWdLLtfY_7eYb1ZZrD0n7K5sf1BM5hxksNiVRTJnSBjYzBgAhVCMguI/exec?name=";
int solenoid = D0;
int buzzer = D8;
const int RST_PIN = D3;
const int SS_PIN = D4;
String storedtag1 = "67163111148";// it Changes According  tags
String storedtag2 = "9920327144";
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
String tag, dataRFID = "";

void setup() {
  //Setup the wifi Connection
  WiFi.persistent(false);
  Serial.begin(115200);
  Serial.println("\nESP8266 Multi WiFi example");
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP("iot", "project1234");// Replace with Your SSID and Password

  if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED) {
    Serial.print("WiFi connected: ");
    Serial.print(WiFi.SSID());
    Serial.print(" ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi not connected!");
  }

  pinMode(solenoid, OUTPUT);
  digitalWrite(solenoid, HIGH);
  pinMode(buzzer, OUTPUT);
  digitalWrite(solenoid, LOW);
  SPI.begin();
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("RFID module initialized");
}

void loop() {
  // Read data from Serial if available
  if (Serial.available()) {
    data = Serial.read();
  }

  // Check if a new RFID card is present
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Read RFID card serial and process it
  if (rfid.PICC_ReadCardSerial()) {
    tag = "";

    // Concatenate UID bytes to form a string
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }

    // Check if the RFID tag matches a stored tag
    if (tag == storedtag1) {
      dataRFID = "Ganesh_EC012";
      Serial.println("ganesh");
      digitalWrite(solenoid, LOW);
      delay(3500);
      digitalWrite(solenoid, HIGH);
    } else {
      Serial.println("card not recognized");
      dataRFID = "invalid_card";
      //when the Rfid dectects invalid card ,Buzzer will be on
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
    }
   // Halt the card and stop crypto to save power
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  // Check if WiFi is connected
  if ((wifiMulti.run() == WL_CONNECTED)) {
    // Set up a secure WiFi client with a fingerprint
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setFingerprint(fingerprint);

    // Prepare data for HTTP request
    data2 = data1 + dataRFID;
    Serial.println(data2);

    // Make an HTTPS request
    HTTPClient https;
    Serial.print(F("[HTTPS] begin...\n"));
    if (https.begin(*client, (String)data2)) {
      Serial.print(F("[HTTPS] GET...\n"));
      int httpCode = https.GET();
      if (httpCode > 0) {
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  // Print RFID data and a message to Serial
  Serial.println(dataRFID);
  Serial.println("works!");
}
