
#ifndef MACHINE_H
#define MACHINE_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#include "Carte.h"

#define NBCARTE 32
#define DOT '.'
#define EXT 'C'
#define DEF "DEFAULT"

// set up variables using the SD utility library functions:

class Machine {
public:
    Machine();
    ~Machine();

    bool Run();
    bool Initialize();

    bool GotoStep(unsigned int Step);
    void ChangeFile(String file);

private:
    Carte m_Cartes[NBCARTE];
    String m_nameFile;
};

#endif // MACHINE_H
