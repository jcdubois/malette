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

#ifndef MACHINE_H
#define MACHINE_H

#include <Arduino.h>

#include "Board.h"

#define MAXBOARD 32

class Machine {
public:
  Machine();
  ~Machine();

  void Initialize(void (*timer_isr)());

  void Reset();
  void Run();

  void GotoStep(unsigned int Step);
  void ChangeFile(String file);
  void DeleteCache();

  void DisableTimer();
  void EnableTimer();
  bool IsTimerEnabled();

private:
  Board m_board[MAXBOARD];
  String m_nameFile;
  bool m_timerEnable;
};

#endif // MACHINE_H
