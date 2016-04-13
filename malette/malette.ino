/**
 * Copyright (c) 2016 Julien Viaud
 * Copyright (c) 2016 Jean-Christphe Dubois
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

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "Machine.h"
#include "Commande.h"
#include "Bus.h"

#define DEBUG 0

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;
Machine Malette;
Bus Bus1;

#define CSPIN 53

static boolean stringComplete = false; // whether the string is complete

static String inputString = "";

static void timer_isr() { Malette.Run(); }

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //(1 char(data) + 1 char (Time) )*8 +1 \n
  inputString.reserve(17);

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_FULL_SPEED, CSPIN)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match "
                   "your shield or module?");
    return;
  } else {
#if DEBUG
    Serial.println("Wiring is correct and a card is present.");
#endif
  }

#if DEBUG
  // print the type of card
  Serial.print("\nCard type: ");
  switch (card.type()) {
  case SD_CARD_TYPE_SD1:
    Serial.println("SD1");
    break;
  case SD_CARD_TYPE_SD2:
    Serial.println("SD2");
    break;
  case SD_CARD_TYPE_SDHC:
    Serial.println("SDHC");
    break;
  default:
    Serial.println("Unknown");
    break;
  }
#endif

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or
  // FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\n"
                   "Make sure you've formatted the card");
    return;
  }


#if DEBUG
  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize = volume.blocksPerCluster(); // clusters are collections of blocks
  volumesize *= volume.clusterCount();    // we'll have a lot of clusters
  volumesize *= 512;                      // SD card blocks are always 512 bytes
  Serial.print("Volume size (bytes): ");
  Serial.println(volumesize);
  Serial.print("Volume size (Kbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);

  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
#endif

  root.openRoot(volume);

#if DEBUG
  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
#endif

  SD.begin(CSPIN);

  Bus1.Initialize();

  Serial.println("Initializing the Malette");

  Malette.Initialize(timer_isr);

  Serial.println("Malette is ready to run");

  Malette.EnableTimer();

  Serial.println("Malette is running");

}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    AnalyseCommande(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
 * SerialEvent occurs whenever a new data comes in the
 * hardware serial RX.  This routine is run between each
 * time loop() runs, so using delay inside loop can delay
 * response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();

    // add it to the inputString:
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      inputString += inChar;
    }
  }
}
