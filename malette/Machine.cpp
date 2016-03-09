/**
 * Copyright (c) 2016 Julien Viaud
 * Copyright (c) 2016 Jean-Christphe Dubois
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

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
