
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
  m_BufferPosition = 0;
  //Chargement du buffer à partir du step 0
  LoadBuffer();

  
   WriteData();
  return true;
}


bool Carte::CloseFile()
{
   m_file.close();
 
}


bool Carte::Execute()
{
  m_timeLeft--;

  if( m_timeLeft <= 0)
  {
    // Passage à l'étape suivante
    ///je déplace le curseur Buffer
    m_BufferPosition++;
    m_indexStep++;
    //Utilisation du modulo
    m_indexStep = m_indexStep%m_nbStep;
  

    if(m_indexStep == 0 || m_BufferPosition >= MAX_STEP_LOAD)
    {
      if( m_indexStep == 0)
      {
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
  
  Serial.print("WriteData ");
  Serial.print(m_uiNumCarte);
  Serial.print(" ");
  Serial.print(m_indexStep);
  Serial.print(" ");
  Serial.print(m_dataSteps[m_BufferPosition]);
  Serial.print(" ");
  Serial.println(m_timeSteps[m_BufferPosition]);;
  m_timeLeft = m_timeSteps[m_BufferPosition];
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
  m_BufferPosition = 0;
  
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
      if( i !=7)
      {
        data = data <<1;
      }
    }
    
    m_dataSteps[NStep] = data;
  //Lecture de l'espace entre la data et le timer
    m_file.read();
    String sTimeStep = "";
  do
  {
    ret = m_file.read();
   
  String sTimetpStep(ret);
  sTimeStep += sTimetpStep;
   
  } while(ret != '\n');
    m_timeSteps[NStep] = sTimeStep.toInt();
  
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
  return true;
}

