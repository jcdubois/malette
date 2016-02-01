
#ifndef MACHINE_H
#define MACHINE_H
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#define NBCARTE 32
#define DOT '.'
#define EXT 'C'
#define DEF "DEFAULT"
#define CSPIN 53


// set up variables using the SD utility library functions:


#include "Carte.h"

class Machine
{
   
  public:
  
    Machine();
    ~Machine();
    bool Run();
    bool Initialize();
  
    void ChangeFile(String file);

    
  private:
  
    Carte m_Cartes[32];
    String m_nameFile;
  
};
#endif



