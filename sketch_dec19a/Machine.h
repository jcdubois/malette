
#ifndef MACHINE_H
#define MACHINE_H
#include "Carte.h"

class Machine
{
   
  public:
  
    Machine();
    ~Machine();
    bool Run();
    bool Initialize();
  
  private:
  
    Carte m_Cartes[32];
  
};
#endif



