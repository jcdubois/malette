#ifndef CARTE_H
#define CARTE_H

#define MAX_STEP 400
#define MAX_STEP_LOAD 8

#include <Arduino.h>
#include <SD.h>

class Carte {
public:
    Carte();
    ~Carte();

    void SetAdresse(char auiAdresse) { m_uiAdresse = auiAdresse; };
    void SetNumCarte(short auinNumCarte) { m_uiNumCarte = auinNumCarte; };
    bool LoadFile(String path);
    bool Execute();
    bool SetStep(unsigned int Step);
    bool LoadBuffer();
    bool CloseFile();

private:
    File m_file;

    // Numéro de la carte
    short m_uiNumCarte;

    // Adresse de la carte
    char m_uiAdresse;

    // Position du m_BufferPosition dans le buffer)
    short m_BufferPosition;

    // Position du step dans la totalité des etats (pas N°300 sur 400 etat au
    // total)
    unsigned int m_indexStep;

    // Poistion dans la ligne 1 de données
    unsigned int m_dataposition;

    // Temps restant de l'etat
    unsigned int m_timeLeft;

    // Nombre d'etat total
    unsigned int m_nbStep;

    // Données
    short m_dataSteps[MAX_STEP_LOAD];
    // Temps
    unsigned int m_timeSteps[MAX_STEP_LOAD];

    bool WriteData();
    bool ReadHeader();
    bool ReadLine(unsigned int NStep);
};

#endif // CARTE_H
