# Smart Ventilasjon – Arduino Prosjekt

Dette prosjektet viser en **smart ventilasjon / vifte** som bruker:

- **BME280** (temperatur og fuktighet)
- **ENS160** (luftkvalitet: TVOC og eCO2)
- **PWM-motor** med retning
- **Toggle-knapp** for sommer/vinter-modus
- **OLED 128x64** for visning av sensorverdier og motorstatus
- **Serial Monitor** for debug

---

## Logikk

- BME280 måler temperatur og fuktighet
- ENS160 måler luftkvalitet (TVOC / eCO2), kompensert med temperatur og fuktighet
- PWM-motor styrer viftehastighet basert på temperatur og luftkvalitet
- Retning settes via toggle-knapp:
  - **Sommermodus** → motor i én retning
  - **Vintermodus** → motsatt retning
- OLED viser sanntidsdata:
  - Temperatur
  - Fuktighet
  - TVOC
  - eCO2
  - Motorhastighet
  - Retning
- Serial Monitor brukes for debugging

---

## Oppkobling

1. **I2C-sensorer og OLED kan dele samme SDA/SCL bus**
   - Koble BME280, ENS160 og OLED til A4/A5 eller direkte til SDA/SCL
2. **PWM-motor med retning**
   - PWM pin 9 → motor hastighet  
   - DIR pin 8 → motor retning (HIGH/LOW)
   - Bruk H-bro / L298N for ekstern strømstyring
3. **Toggle-knapp**
   - Koble til pin 7 og GND
   - `INPUT_PULLUP` gjør at LOW = trykket
4. **Strøm**
   - BME280 / ENS160 / OLED → Arduino 3.3V
   - Motor → ekstern strøm via H-bro
5. **Ryddig oppsett**
   - Sensorer samlet på én side, motor / H-bro på annen side
   - Kortest mulig kabler, fargekodede ledninger:
     - Rød = 5V
     - Svart = GND
     - Gul / Blå = signal

---

## Eksamenstips

1. Test én sensor om gangen  
2. Mate ENS160 med temp/hum før måling  
3. PWM motor: hastighet 0–255, retning HIGH/LOW  
4. Toggle knapp: kantdeteksjon HIGH→LOW, bruk `summerMode = !summerMode`  
5. OLED: oppdater hvert loop, ikke la delay blokkere kritisk logikk  
6. Serial Monitor: print alle sensorverdier for debugging  
7. Bygg iterativt: sensor → logikk → motor → OLED → knapp  
8. Korte delay (100–500ms) holder loop rask og responsiv  