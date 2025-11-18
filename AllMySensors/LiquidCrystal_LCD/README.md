## LiquidCrystal LCD
:repository-owner: arduino-libraries
:repository-name: LiquidCrystal

= {repository-name} Library for Arduino =

image:https://github.com/{repository-owner}/{repository-name}/actions/workflows/check-arduino.yml/badge.svg["Check Arduino status", link="https://github.com/{repository-owner}/{repository-name}/actions/workflows/check-arduino.yml"]
image:https://github.com/{repository-owner}/{repository-name}/actions/workflows/compile-examples.yml/badge.svg["Compile Examples status", link="https://github.com/{repository-owner}/{repository-name}/actions/workflows/compile-examples.yml"]
image:https://github.com/{repository-owner}/{repository-name}/actions/workflows/spell-check.yml/badge.svg["Spell Check status", link="https://github.com/{repository-owner}/{repository-name}/actions/workflows/spell-check.yml"]

## GitHub

- Link to GitHub library: https://github.com/arduino-libraries/LiquidCrystal

## Oppkobling

- LCD RS pin to digital pin 12
- LCD Enable pin to digital pin 11
- LCD D4 pin to digital pin 5
- LCD D5 pin to digital pin 4
- LCD D6 pin to digital pin 3
- LCD D7 pin to digital pin 2
- LCD R/W pin to GND
- LCD VSS pin to GND
- LCD VCC pin to 5V
- LCD LED+ to 5V through a 220 ohm resistor
- LCD LED- to GND
- Additionally, wire a 10k potentiometer to +5V and GND, with it's wiper (output) to LCD screens VO pin (pin3).

This library allows an Arduino board to control liquid crystal displays (LCDs) based on the Hitachi HD44780 (or a compatible) chipset, which is found on most text-based LCDs.

For more information about this library please visit us at

https://www.arduino.cc/en/Reference/{repository-name}

== License ==

Copyright (C) 2006-2008 Hans-Christoph Steiner. All rights reserved.
Copyright (c) 2010 Arduino LLC. All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
