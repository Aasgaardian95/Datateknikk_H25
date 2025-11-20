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

### **OLED 128x64**
- VCC → 3.3V / 5V  
- GND → GND  
- SDA → A4  
- SCL → A5  

### **PWM-Motor / Retning**
- PWM pin → 9 (`MOTOR_PWM`)  
- DIR pin → 8 (`MOTOR_DIR`)  
- GND → GND  
- Strøm → ekstern kilde / H-bro om nødvendig  

### **Toggle-knapp (sommer/vinter)**
- Knapp → 7 (`TOGGLE_BUTTON`)  
- GND → GND  
- Bruk `INPUT_PULLUP` i koden  

### **Generelt**
- I2C-bus deles av OLED og andre I2C-sensorer (her kun BME280 og ENS160 hvis koblet)  
- Kortest mulig kabler, fargekodede signaler:  
  - Rød = 5V  
  - Svart = GND  
  - Andre farger = signal  
- Hold sensorer på én side, motor og ekstern strøm på annen side for ryddig layout  

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