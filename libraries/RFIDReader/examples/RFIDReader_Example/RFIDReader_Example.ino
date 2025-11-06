#include <Arduino.h>
#include <SPI.h>
#include <RFIDReader.h>

constexpr uint8_t SS_PIN = 10;   // SDA til pinne 10 på Arduino UNO
constexpr uint8_t RST_PIN = 9;   // RST til pinne 9

// Eksempel på autorisert UID (4 byte). Verdiene må oppgis i heks.
byte autorisertKort[4] = {0xDE, 0xAD, 0xBE, 0xEF};

RFIDReader leser(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  leser.begin();
  Serial.println("Legg et kort på leseren for å teste.");
}

void loop() {
  leser.read();

  if (leser.cardDetected()) {
    String uid = leser.getUID();
    Serial.print("Kontrollerer UID ");
    Serial.println(uid);

    byte uidBuffer[10];
    byte uidLength = 0;
    if (leser.getUIDBytes(uidBuffer, sizeof(uidBuffer), uidLength)) {
      if (uidLength == sizeof(autorisertKort) && memcmp(uidBuffer, autorisertKort, uidLength) == 0) {
        Serial.println("Tilgang gitt – kortet er autorisert.");
      } else {
        Serial.println("Tilgang avslått – ukjent kort.");
      }
    }
  }

  delay(500);
}
