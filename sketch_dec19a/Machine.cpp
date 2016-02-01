
#include "Machine.h"
  char buff[3] = {0,0,0};
  
Machine::Machine()
{
  m_nameFile = DEF;
  
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

bool Machine::GotoStep(unsigned int Step)
{
  for(unsigned int i = 0 ; i < NBCARTE; i++)
  {
    m_Cartes[i].SetStep(Step);
  }
  return true;
}

void Machine::ChangeFile(String file)
{
  
     Serial.println(file);  
  m_nameFile = file;
    for(unsigned int i = 0 ; i < NBCARTE; i++)
  {
     m_Cartes[i].CloseFile(); 
  }
}


bool Machine::Initialize()
{
    // list all files in the card with date and size

  for(unsigned int i = 0 ; i < NBCARTE; i++)
  {
     sprintf(buff,"%02d",i+1);
   
     m_Cartes[i].SetNumCarte(i+1);
     String NumFile(buff);
     String file = m_nameFile + DOT + EXT + NumFile;
          
     Serial.println(file);  
      if (SD.exists(file) )
      {
         Serial.println("Le fichier existe");
         m_Cartes[i].LoadFile(file);
      }
    else 
    {
      Serial.println("Le fichier n'existe pas");
      return false;
    }
  }

  return true;
}
  



