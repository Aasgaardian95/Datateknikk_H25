# Smart Alarm – Arduino Prosjekt

Dette prosjektet viser et **smart alarmsystem** som bruker:

- **4x4 Keypad** for kodeinntasting
- **Motor/servo** for fysisk lås
- **Grønn LED** → alarm av
- **Rød LED** → feil kode / alarm
- **Buzzer** → alarmlyd
- **Dørbruddsensor** → registrerer uautorisert inngang
- **OLED 128x64** → viser sanntidsstatus
- **Serial Monitor** → debug

---

## Logikk

- Keypad brukes for å taste inn firesifret kode
- Korrekt kode → alarm av, lås åpnes, grønn LED lyser
- Feil kode → rød LED lyser i tidsvindu
- Tidsvindu utløpt → buzzer / alarm aktiveres
- Dørbrudd (sensor) → umiddelbar alarm
- OLED viser sanntidsdata:
  - Tastet kode
  - Alarmstatus
  - Låsstatus
- Serial Monitor brukes for debugging

---

## Oppkobling

### **OLED**
- VCC → 3.3V / 5V  
- GND → GND  
- SDA → A4  
- SCL → A5  

### **Keypad 4x4**
- R1 → 9  
- R2 → 8  
- R3 → 7  
- R4 → 6  
- C1 → 5  
- C2 → 4  
- C3 → 3  
- C4 → 2  
- GND → GND  

### **Motor / Servo (Lås)**
- Signal → 6 (`MOTOR_LOCK`)  
- GND → GND  
- Strøm → ekstern H-bro / ekstern kilde om nødvendig  

### **LED & Buzzer**
- Grønn LED → 3  
- Rød LED → 4  
- Buzzer → 5  
- Bruk motstand på LED (f.eks. 220Ω)  

### **Dørbruddsensor**
- Sensor → 10  
- GND → GND  
- `INPUT_PULLUP` gjør at LOW = dør åpnet  

### **Generelt**
- Hold kabler ryddige  
- Skill sensorer fra aktuatorkretser  
- Del I2C-bus for OLED og andre I2C-enheter  
- Kortest mulig kabler, fargekodede signaler:  
  - Rød = 5V  
  - Svart = GND  
  - Andre farger = signal


---

## Eksamenstips

1. Test én del om gangen:
   - Keypad → test kodeinntasting
   - Lås/LED/Buzzer → test logikk
   - Dør-sensor → test uautorisert åpning
   - OLED → vis sanntidsstatus
2. Bygg iterativt:
   - Input → logikk → output → visuell feedback
3. Kort delay (100–200ms) holder loop responsiv
4. Serial Monitor kan brukes for å se tastetrykk, status og debug
5. Husk alltid å ha kontroll på strøm og kabelføring
6. Husk å nullstille inputCode etter korrekt/feil kode
7. Husk at HIGH/LOW logikk for sensor og motor må stemme med fysisk oppkobling
