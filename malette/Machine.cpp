
#include "Machine.h"

#define DEF "DEFAULT"

Machine::Machine() { m_nameFile = DEF; }

Machine::~Machine() {}

bool Machine::Run() {
  for (unsigned int i = 0; i < MAXBOARD; i++) {
    m_board[i].Execute();
  }

  return true;
}

bool Machine::GotoStep(unsigned int Step) {
  for (unsigned int i = 0; i < MAXBOARD; i++) {
    m_board[i].SetStep(Step);
  }

  return true;
}

void Machine::ChangeFile(String file) {
  Serial.println(file);

  m_nameFile = file;
  for (unsigned int i = 0; i < MAXBOARD; i++) {
    m_board[i].SetFile(file);
  }
}

bool Machine::Initialize() {
  // list all files in the card with date and size
  for (unsigned int i = 0; i < MAXBOARD; i++) {
    // Set the board number
    m_board[i].SetNum(i + 1);
    // Set the file associated to the board
    m_board[i].SetFile(m_nameFile);
  }

  return true;
}
