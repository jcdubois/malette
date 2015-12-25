


#ifndef CARTE_H
#define CARTE_H



class Carte
{
  public:

    Carte();
    ~Carte();
    void SetAdresse( unsigned int auiAdresse){ m_uiAdresse = auiAdresse;};
    void SetNumCarte(unsigned int auinNumCarte){m_uiNumCarte = auinNumCarte;};
    bool LoadFile(String path);
    bool Execute();
    bool WriteData();
    bool ReadLine();
    bool ReadHeader();

   
  private:
    File m_file;
    unsigned int m_uiNumCarte;
    unsigned int m_uiAdresse;
    unsigned int m_Step;
    unsigned int m_timeLeft;
    unsigned int m_nbStep;
    unsigned int m_dataSteps[32];
    unsigned int m_timeSteps[32];    
    
};
#endif
