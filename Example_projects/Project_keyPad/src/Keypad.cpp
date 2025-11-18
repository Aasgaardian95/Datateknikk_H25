#include <Arduino.h>
#include "Keypad.h"
#include <Wire.h>

// Kommer fungerende keypad kode her senere
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
 
}

void loop() {
  
  char mapKey(int a, int b) {
  int minP = min(a, b);
  int maxP = max(a, b);
  if (minP == 6 && maxP == 7) return '1';
  if (minP == 7 && maxP == 8) return '2';
  if (minP == 4 && maxP == 7) return '3';
  if (minP == 2 && maxP == 6) return '4';
  if (minP == 2 && maxP == 8) return '5';
  if (minP == 2 && maxP == 4) return '6';
  if (minP == 3 && maxP == 6) return '7';
  if (minP == 3 && maxP == 8) return '8';
  if (minP == 3 && maxP == 4) return '9';
  if (minP == 5 && maxP == 8) return '0';
  if (minP == 5 && maxP == 6) return '*';
  if (minP == 4 && maxP == 5) return '#';
  return '?';
}

}

