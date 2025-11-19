## LCD med visning fra analog read (LDR)

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

- Arduino Uno → LDR (lyssensor):
    - LDR kobles i serie med en motstand (f.eks. 10 kΩ) som spenningsdeler.
    - Én ende av LDR → +5 V
    - Andre ende av LDR → A0 og til motstanden
    - Motstanden → GND