


#ifndef CARTE_H
#define CARTE_H
#define MAX_STEP      400
#define MAX_STEP_LOAD 16 


class Carte
{
  public:

    Carte();
    ~Carte();
    void SetAdresse(char auiAdresse){ m_uiAdresse = auiAdresse;};
    void SetNumCarte(short auinNumCarte){m_uiNumCarte = auinNumCarte;};
    bool LoadFile(String path);
    bool Execute();
    bool SetStep(unsigned int  Step);

    bool LoadBuffer();
   
  private:
    File m_file;
    short m_uiNumCarte;
    char m_uiAdresse;
    short m_Step;

    unsigned int m_dataposition;
    unsigned int m_timeLeft;
    unsigned int m_nbStep;
    
    char m_dataSteps[MAX_STEP_LOAD];
    unsigned int m_timeSteps[MAX_STEP_LOAD]; 

       
    unsigned int m_indexStep;
    bool WriteData();
    bool ReadHeader();
    bool ReadLine(unsigned int NStep);
    
};
#endif



