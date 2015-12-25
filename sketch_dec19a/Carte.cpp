#include <Arduino.h>
#include <SD.h>

#include "Carte.h"

#include "Machine.h"

bool Carte::LoadFile(String path)
{
 
  m_file = SD.open(path, FILE_READ);
  ReadHeader();
  for(unsigned int i = 0;i < 32 ;i++)
  {
    ReadLine();
  }
  return true;
}
bool Carte::Execute()
{
  m_timeLeft--;
  if( m_timeLeft <=0)
  {
    // Passage à l'étape suivante
    m_Step++;
    //Utilisation du modulo
    m_Step = m_Step%m_nbStep;
    WriteData();
  }
  return true;
}
bool Carte::WriteData()
{
  ///Ecriture data sur le bus de données
  //././/.

  ///Activation sur l'adresse

  //D'asactivation de l'adresse

  ///Effacement des données présentes sur le bus d'adresse
  return true;
}
bool Carte::ReadLine()
{
  ///Sauvegarde d'une ligne de data et du temps du step

    char ret;
   for (unsigned int NumStep = 0 ; NumStep < m_nbStep; NumStep++)
   {
        unsigned int data = 0;
       ////Lecture des binaires
      for (unsigned int i = 0; i < 8; i++)
      {
        ret = m_file.read();
        if(ret == '1')
        {
          data |= 0x1;
          data = data <<1;
        }
      }
      m_dataSteps[NumStep] = data;
    
      
      String sTimeStep = "";
      do
      {
        ret = m_file.read();
        sTimeStep += ret; 
      } while(ret != '\n');
      m_timeSteps[NumStep] = sTimeStep.toInt();
   }
      
  return true;
}

bool Carte::ReadHeader()
{
  ////Sauvegarde du nb de step
  String snbStep = "";
  
    char ret;
  do
  {
    ret = m_file.read();
    snbStep += ret; 
  } while(ret != '\n');
  m_nbStep = snbStep.toInt();
  return true;
}
