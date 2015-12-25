 #include <Arduino.h>
#include <SD.h>

  
#include "Machine.h"
  
  
Machine::Machine()
{

  
}
Machine::~Machine()
{
  
}
bool Machine::Run()
{
  for(unsigned int i = 0 ; i < 32; i++)
  {
    m_Cartes[i].Execute();
  }
  return true;
}

bool Machine::Initialize()
{
  return true;
}
  
