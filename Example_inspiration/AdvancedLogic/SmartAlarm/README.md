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

1. **OLED**
   - SDA → A4, SCL → A5 eller direkte til SDA/SCL på Arduino Uno
2. **Keypad**
   - Rader og kolonner kobles til definert pinneoppsett
3. **Motor / Servo**
   - Kobles til MOTOR_LOCK pinne
   - Sørg for ekstern strømforsyning hvis nødvendig
4. **LED & Buzzer**
   - Kortest mulig ledninger
   - Rød = 5V, svart = GND
5. **Dørbruddsensor**
   - Koblet mellom pin og GND
   - `INPUT_PULLUP` gjør at LOW = dør åpnet
6. **Generelt**
   - Hold kabler ryddige
   - Skill strømforbrukende komponenter fra logiske signaler

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
