
#ifndef MACHINE_H
#define MACHINE_H

#include <Arduino.h>

#include "Board.h"

#define MAXBOARD 32

class Machine {
public:
  Machine();
  ~Machine();

  bool Run();
  bool Initialize();

  bool GotoStep(unsigned int Step);
  void ChangeFile(String file);

private:
  Board m_board[MAXBOARD];
  String m_nameFile;
};

#endif // MACHINE_H
