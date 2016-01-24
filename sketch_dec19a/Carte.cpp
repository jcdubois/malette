#include <Arduino.h>
#include <SD.h>

#include "Carte.h"

#include "Machine.h"
Carte::Carte()
{

}
Carte::~Carte()
{

}

bool Carte::LoadFile(String path)
{
  m_file = SD.open(path, FILE_READ);
  ReadHeader();

  //Sauvegarde de la positon de données
  m_dataposition = m_file.position();
  m_indexStep = 0;

  //Chargement du buffer à partir du step 0
  LoadBuffer();
  return true;
}
bool Carte::Execute()
{
  m_timeLeft--;
  if( m_timeLeft <= 0)
  {
    // Passage à l'étape suivante
    m_Step++;
    //Utilisation du modulo
    m_Step = m_Step%m_nbStep;
    
    if(m_Step == 0 || m_Step > m_indexStep)
    {
      if( m_Step == 0)
      {
        m_indexStep = 0;
        m_file.seek(m_dataposition);
      }
     LoadBuffer();
    }
    
    WriteData();
  }
  return true;
}
bool Carte::WriteData()
{
  ///Ecriture data sur le bus de données
  //././/.donnéesv portA pin 22 a 29

  ///Activation sur l'adresse adresse portc 30 -37

  //D'asactivation de l'adresse

  ///Effacement des données présentes sur le bus d'adresse
  return true;
}


bool Carte::SetStep(unsigned int  Step)
{
  //m_Step = (Step - 1)%m_nbStep;
  //m_timeLeft = 0;

  return true;
    
}

bool Carte::LoadBuffer()
{
  int index;
  for( index = 0; (index < MAX_STEP_LOAD)  && (m_nbStep > (m_indexStep  + index) ); index++)
  {
    ReadLine(index);
  }
  
  m_indexStep += index;
  
  return true;
}

bool Carte::ReadLine(unsigned int NStep)
{
  ///Sauvegarde d'une ligne de data et du temps du step

    char ret;

      unsigned int data = 0;
     ////Lecture des binaires
    for (unsigned int i = 0; i < 8; i++)
    {
      ret = m_file.read();

      
      if(ret == '1')
      {
        data |= 0x1;

        
      } 
      data = data <<1;
    }

      Serial.print(data);
    m_dataSteps[NStep] = data;
  //Lecture de l'espace entre la data et le timer
    m_file.read();
    
      Serial.print(' ');
    String sTimeStep = "";
  do
  {
    ret = m_file.read();
   
  String sTimetpStep(ret);
  sTimeStep += sTimetpStep;
   
  } while(ret != '\n');
    m_timeSteps[NStep] = sTimeStep.toInt();
  
      Serial.println(m_timeSteps[NStep]);
  return true;
}

bool Carte::ReadHeader()
{
  
    char ret;
    
  String snbStep= "";;
  do
  {
    ret = m_file.read();
   
  String snbtpStep(ret);
  snbStep += snbtpStep;
   
  } while(ret != '\n');

  ////Sauvegarde du nb de step
  
  m_nbStep = snbStep.toInt();
  Serial.println(m_nbStep);
  return true;
}

