 #include <Arduino.h>
#include <SD.h>
#define NBCARTE 32
 #define FILENAME "ALAIN.C"
#include "Machine.h"
  char buff[3] = {0,0,0};
  
Machine::Machine()
{

  
}
Machine::~Machine()
{
  
}
bool Machine::Run()
{
  for(unsigned int i = 0 ; i < NBCARTE; i++)
  {
    m_Cartes[i].Execute();
  }
  return true;
}

bool Machine::Initialize()
{
  for(unsigned int i = 0 ; i < NBCARTE; i++)
  {
      String trace;
      trace = "Initializing Card " ;
     
      
     Serial.print(trace); 
     sprintf(buff,"%02d",i+1);
   
     m_Cartes[i].SetNumCarte(i+1);
     String NameFile(buff);
     NameFile = FILENAME + NameFile;
     Serial.println(NameFile);  
      if (SD.exists(NameFile) )
      {
         Serial.println("Le fichier existe");
         m_Cartes[i].LoadFile(NameFile);
      }
    else 
    {
      Serial.println("Le fichier n'existe pas existe");
    }
  }

  return true;
}
  



