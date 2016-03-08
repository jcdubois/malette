#ifndef CARTE_H
#define CARTE_H

#include <Arduino.h>
#include <SD.h>

class Board {
public:
  // Constructor
  Board();
  // Destructor
  ~Board();

  bool SetNum(unsigned char num);

  // load a file associated to the board
  bool SetFile(String path);

  // Called each time the timer is triggered
  bool Execute();

  // Position the board to the desired time
  bool SetStep(unsigned int time);

  // Close the file in use
  bool CloseFile();

private:
  File m_file;

  // card number (between 1 and 32)
  unsigned char m_num;
  // decoder number (between 0 and 3)
  unsigned char m_decoder;
  // Channel number (between 0 and 7)
  unsigned char m_channel;

  // current value for output
  unsigned char m_value;

  // Current step
  unsigned int m_indexStep;

  // Position of the first data line
  unsigned int m_dataposition;

  // Time left in current step
  int m_timeLeft;

  // Total number of step
  unsigned short m_nbStep;

  bool WriteData();

  bool ReadHeader();

  bool ReadLine();
};

#endif // CARTE_H
