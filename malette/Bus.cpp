
#include "Bus.h"
#include <Arduino.h>

static int addressPins[8] = {22, 24, 26, 28, 30, 32, 34, 36};
static int dataPins[8] = {23, 25, 27, 29, 31, 33, 35, 37};

Bus::Bus() {}

Bus::~Bus() {}

bool Bus::Initialize() {
  // Initialize all pins as output
  for (int i = 0; i < 8; i++) {
    pinMode(addressPins[i], OUTPUT);
    pinMode(dataPins[i], OUTPUT);
  }
}

void Bus::Write(unsigned char decoder, unsigned char channel,
                unsigned char data) {

  Serial.print("WriteData: ");
  for (int i = 7; i >= 0; i--) {
    Serial.print(data & (1 << i) ? '1' : '0');
  }
  Serial.print(" @ (");
  Serial.print(decoder);
  Serial.print(" , ");
  Serial.print(channel);
  Serial.println(')');

  // write the data to the data bus
  WriteData(data);

  // write the address to the address bus
  WriteAddress(decoder, channel);

  WriteData(0);
}

void Bus::WriteAddress(unsigned char decoder, unsigned char channel) {
  // Set the 3 higher bits = channel
  for (int i = 0; i < 4; i++) {
    if (channel & (1 < i)) {
      digitalWrite(addressPins[i + 5], HIGH);
    }
  }

  // Select our decoder
  digitalWrite(addressPins[decoder], HIGH);

  // Deselect the decoder
  digitalWrite(addressPins[decoder], LOW);

  // Clear the 3 higher bits = channel
  for (int i = 0; i < 4; i++) {
    digitalWrite(addressPins[i + 5], LOW);
  }
}

void Bus::WriteData(unsigned char data) {
  // Set the data pins
  for (int i = 0; i < 8; i++) {
    digitalWrite(dataPins[i], data & (1 << i) ? HIGH : LOW);
  }
}
