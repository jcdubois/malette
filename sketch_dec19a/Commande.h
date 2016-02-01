
#ifndef COMMANDE_H
#define COMMANDE_H

#include <Arduino.h>

#include <SD.h>


#define START 'S'
#define STOP  'P'
#define RESET 'R'

#define LOAD 'L'


void AnalyseCommande(String inputString);

#endif
