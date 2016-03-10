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

#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>
#include <SD.h>

class Board {
public:
  // Constructor
  Board();
  // Destructor
  ~Board();

  void Reset();

  void SetNum(unsigned char num);

  // load a file associated to the board
  void SetFile(String path);

  // Called each time the timer is triggered
  void Execute();

  // Position the board to the desired time
  void SetStep(unsigned int time);

  // Close the file in use
  void CloseFile();

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

  void WriteData();

  void ReadHeader();

  void ReadLine();
};

#endif // BOARD_H
