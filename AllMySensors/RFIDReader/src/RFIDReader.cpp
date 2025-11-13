#include "RFIDReader.h"

RFIDReader::RFIDReader(uint8_t ssPin, uint8_t rstPin)
  : BaseSensor("RFID"), _mfrc522(ssPin, rstPin), _cardPresent(false), _uidBuffer{0}, _uidLength(0) {}

void RFIDReader::begin() {
  SPI.begin();
  _mfrc522.PCD_Init();
  Serial.println("RFID-leser initialisert. Klar for kort.");
}

void RFIDReader::read() {
  if (!_mfrc522.PICC_IsNewCardPresent() || !_mfrc522.PICC_ReadCardSerial()) {
    if (_cardPresent) {
      Serial.println("[RFID] Kort fjernet.");
    }
    _cardPresent = false;
    _uidLength = 0;
    return;
  }

  _cardPresent = true;
  _uidLength = _mfrc522.uid.size;
  memcpy(_uidBuffer, _mfrc522.uid.uidByte, _uidLength);
  _lastRead = millis();

  Serial.print("[RFID] Kort oppdaget. UID: ");
  Serial.println(getUID());

  _mfrc522.PICC_HaltA();
  _mfrc522.PCD_StopCrypto1();
}

String RFIDReader::getUID() const {
  if (!_cardPresent || _uidLength == 0) {
    return String("Ingen UID tilgjengelig");
  }

  String uidString;
  for (byte i = 0; i < _uidLength; ++i) {
    if (i > 0) {
      uidString += ":";
    }
    if (_uidBuffer[i] < 0x10) {
      uidString += "0";
    }
    uidString += String(_uidBuffer[i], HEX);
  }
  uidString.toUpperCase();
  return uidString;
}

bool RFIDReader::getUIDBytes(byte* destination, byte maxLength, byte& outLength) const {
  if (!_cardPresent || _uidLength == 0 || destination == nullptr || maxLength < _uidLength) {
    outLength = 0;
    return false;
  }
  memcpy(destination, _uidBuffer, _uidLength);
  outLength = _uidLength;
  return true;
}
