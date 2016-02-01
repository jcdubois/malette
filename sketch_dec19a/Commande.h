
#ifndef COMMANDE_H
#define COMMANDE_H

#include <Arduino.h>

#include <SD.h>


#define START 'S'
#define STOP  'B'
#define RESET 'R'
#define LOAD 'L'
#define GOTO 'G'

void AnalyseCommande(String inputString);

#endif
