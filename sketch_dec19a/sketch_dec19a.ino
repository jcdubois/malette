#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "Machine.h"

Machine Malette;
void setup() {
    // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    Malette.Initialize();
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
   }
 
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  while(1)
  {
    Malette.Run()
    delay(1);
  }

}
