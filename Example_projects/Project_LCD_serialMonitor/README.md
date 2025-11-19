## LCD med visning fra inntasting i serial monitor

## Oppkobling

- Arduino Uno → LCD (16x2, 4‑bit modus):
    - RS → pin 12
    - EN → pin 11
    - D4 → pin 5
    - D5 → pin 4
    - D6 → pin 3
    - D7 → pin 2
    - R/W → GND
    - VSS → GND
    - VCC → +5 V
    - LED+ → +5 V via 220 Ω motstand
    - LED− → GND
    - VO (kontrast) → midtuttak på 10 kΩ potmeter (ender til +5 V og GND)