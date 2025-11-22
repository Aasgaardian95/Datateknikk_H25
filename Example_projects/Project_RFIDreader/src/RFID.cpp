#include <SPI.h>     // Inkluderer SPI-biblioteket (Serial Peripheral Interface) for kommunikasjon
#include <MFRC522.h> // Inkluderer RFID-biblioteket for MFRC522-modulen

// Definerer hvilke pinner på Arduino som brukes til RFID-leseren
#define SS_PIN 10 // Slave Select (SDA) koblet til digital pin 10
#define RST_PIN 9 // Reset-pinnen koblet til digital pin 9

// Oppretter et RFID-objekt med de definerte pinnene
MFRC522 rfid(SS_PIN, RST_PIN);

// Definerer LED-pinner
int greenLed = 6; // Grønn LED på pin 6 (for "godkjent")
int redLed = 5;   // Rød LED på pin 5 (for "ikke godkjent")

// -------------------- SETUP --------------------
void setup()
{
  Serial.begin(115200); // Starter seriell kommunikasjon med PC på 115200 baud
  SPI.begin();          // Starter SPI-bussen
  rfid.PCD_Init();      // Initialiserer RFID-leseren
  Serial.println("RFID klar.");

  // Setter LED-pinnene som utganger
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
}

// -------------------- LOOP --------------------
void loop()
{
  // Sjekker om et nytt kort er tilstede
  if (!rfid.PICC_IsNewCardPresent())
    return;
  // Leser kortets UID (unik ID)
  if (!rfid.PICC_ReadCardSerial())
    return;

  // Henter lengden på UID og peker til selve UID-arrayet
  byte uidLen = rfid.uid.size;
  byte *uid = rfid.uid.uidByte;

  // Skriver ut UID til Serial Monitor
  Serial.print("UID: ");
  for (byte i = 0; i < uidLen; i++)
  {
    if (uid[i] < 0x10)
      Serial.print('0');       // Legger til ledende null hvis tallet er under 0x10
    Serial.print(uid[i], HEX); // Skriver ut byte i hex-format
    if (i < uidLen - 1)
      Serial.print(':'); // Setter kolon mellom bytes
  }
  Serial.println();

  // Sjekker om UID finnes i listen over godkjente kort
  if (isAllowed(uid, uidLen))
  {
    Serial.println("Velkommen inn, Marius!");
    digitalWrite(greenLed, HIGH); // Tenn grønn LED
    digitalWrite(redLed, LOW);    // Slukk rød LED
  }
  else
  {
    Serial.println("Prøv igjen!");
    digitalWrite(redLed, HIGH);  // Tenn rød LED
    digitalWrite(greenLed, LOW); // Slukk grønn LED
  }

  // Vent litt med LED på
  delay(1000);
  // Slukk begge LED-ene
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);

  // Stopper kommunikasjon med kortet
  rfid.PICC_HaltA();
  delay(500); // Kort pause før neste lesing
}

// -------------------- GODKJENTE KORT --------------------
// Liste over godkjente UID-er (hver UID er 4 bytes lang)
const byte ALLOWED[][4] = {
    {0x23, 0xB9, 0x47, 0x2D}, // Første godkjente kort
    {0xF0, 0x8B, 0x30, 0x03}  // Andre godkjente kort
};

// Lengden på hver UID (her er begge 4 bytes)
const byte ALLOWED_LEN[] = {4, 4};
const int ALLOWED_COUNT = 2; // Antall godkjente kort i listen

// -------------------- FUNKSJON FOR SJEKK --------------------
bool isAllowed(const byte *uid, byte len)
{
  // Går gjennom alle godkjente kort
  for (int i = 0; i < ALLOWED_COUNT; i++)
  {
    if (len != ALLOWED_LEN[i])
      continue; // Hopper over hvis lengden ikke stemmer
    bool match = true;
    // Sammenligner byte for byte
    for (byte j = 0; j < len; j++)
    {
      if (uid[j] != ALLOWED[i][j])
      {
        match = false;
        break;
      }
    }
    if (match)
      return true; // Returnerer true hvis alle bytes stemmer
  }
  return false; // Returnerer false hvis ingen kort matcher
}
