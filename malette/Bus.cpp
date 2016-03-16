/**
 * Copyright (c) 2016 Jean-Christphe Dubois
 * Copyright (c) 2016 Romaric Maillard
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "Bus.h"
#include <Arduino.h>

#define DEBUG 1

#define NB_SEL 4
#define NB_DEMUX_INPUTS 3
#define DEMUX_PIN_OFFSET 5
#define NB_DATA_PINS 8
#define NB_ADDR_PINS 8

static unsigned char addressPins[8] = {22, 24, 26, 28, 30, 32, 34, 36};
static unsigned char dataPins[8] = {37, 35, 33, 31, 29, 27, 25, 23};

Bus::Bus() {}

Bus::~Bus() {}

bool Bus::Initialize() {
  // Initialize all pins as output
  for (unsigned int i = 0; i < NB_ADDR_PINS; i++) {
    pinMode(addressPins[i], OUTPUT);
    digitalWrite(addressPins[i], LOW);
  }

  for (unsigned int i = 0; i < NB_DATA_PINS; i++) {
    pinMode(dataPins[i], OUTPUT);
    digitalWrite(dataPins[i], LOW);
  }
}

void Bus::Write(unsigned char decoder, unsigned char channel,
                unsigned char data) {
#if DEBUG
  Serial.print("WriteData: ");
  for (int i = 7; i >= 0; i--) {
    Serial.print(data & (1 << i) ? '1' : '0');
  }
  Serial.print(" @ (");
  Serial.print(decoder);
  Serial.print(" , ");
  Serial.print(channel);
  Serial.println(')');
#endif

  // Clear the address
  ClearAddress();

  // write the data value to the data bus
  WriteData(data);

  // write the address to the address bus
  WriteAddress(decoder, channel);

  // Write 0 to the data bus
  WriteData(0);
}

void Bus::ClearAddress() {
  for (int i = 0; i < NB_SEL; i++) {
    digitalWrite(addressPins[i], LOW);
  }
}

void Bus::WriteAddress(unsigned char decoder, unsigned char channel) {
  // Set the 3 higher bits = channel
  for (unsigned int i = 0; i < NB_DEMUX_INPUTS; i++) {
    digitalWrite(addressPins[i + DEMUX_PIN_OFFSET],
                 (channel & (1 << i)) ? HIGH : LOW);
  }

  // Select our decoder
  digitalWrite(addressPins[decoder], HIGH);

  // Deselect the decoder
  digitalWrite(addressPins[decoder], LOW);
}

void Bus::WriteData(unsigned char data) {
  // Set the data pins
  for (unsigned int i = 0; i < NB_DATA_PINS; i++) {
    digitalWrite(dataPins[i], data & (1 << i) ? HIGH : LOW);
  }
}
