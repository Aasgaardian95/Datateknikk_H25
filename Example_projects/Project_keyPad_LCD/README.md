## Keypad (membrane switch module) med inntasting av kode for autentisering og visning på LCD-skjerm

## Oppkobling

- Arduino UNO -> LCD (16x2, 4-bit modus):
    - RS → 7
    - EN → 6
    - D4 → 5
    - D5 → 4
    - D6 → 3
    - D7 → 2
    - VSS → GND
    - VDD → 5V
    - VO → potensiometer (midtben, med 5V og GND på sidene)
    - A (baklys +) → 5V via 220Ω motstand
    - K (baklys –) → GND
    - RW -> GND

- Keypad:
    - Rader → 11, 10, 9, 8
    - Kolonner → A0, A1, A2, A3

- LED (rød):
    - Katode -> 220/1k ohm -> GND
    - Anode → 13

- LED (grønn):
    - Katode -> 220/1k ohm -> GND
    - Anode → 12

- Strøm:
    - Arduino 5V → LCD + potmeter + LED-er
    - Arduino GND → LCD + potmeter + LED-er + felles jord

## Datablad
- Link til keypad datablad: https://cdn.sparkfun.com/assets/f/f/a/5/0/DS-16038.pdf

## Demonstrasjonsvideo

[![Demo Video](https://img.youtube.com/vi/YSRPX55sHbY/0.jpg)](https://www.youtube.com/shorts/YSRPX55sHbY)