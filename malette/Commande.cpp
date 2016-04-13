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

#include "Commande.h"
#include "Machine.h"

extern Machine Malette;

void AnalyseCommande(String inputString) {
  switch (inputString[0]) {
  case 's':
  case 'S': {
    if (!Malette.IsTimerEnabled()) {
      Serial.println("Start Malette");
      Malette.EnableTimer();
    } else {
      Serial.println("Timer is running");
    }
  } break;
  case 'p':
  case 'P': {
    if (Malette.IsTimerEnabled()) {
      Malette.DisableTimer();
      Serial.println("Pause Malette");
    } else {
      Serial.println("Timer is not running");
    }
  } break;
  case 'r':
  case 'R': {
    if (Malette.IsTimerEnabled()) {
      Malette.DisableTimer();
      Serial.println("Reset Malette");
      Malette.Reset();
    } else {
      Serial.println("Timer is not running");
    }
  } break;
  case 'n':
  case 'N': {
    if (!Malette.IsTimerEnabled()) {
      Serial.println("Next step Malette");
      Malette.Run();
    } else {
      Serial.println("Timer is running");
    }
  } break;
  case 'l':
  case 'L': {
    if (Malette.IsTimerEnabled()) {
      Malette.DisableTimer();
    }
    // Remove first char (L).
    inputString.remove(0, 1);
    Serial.println("Change file Malette ");
    Malette.ChangeFile(inputString);
  } break;
  case 'g':
  case 'G': {
    if (!Malette.IsTimerEnabled()) {
      // Remove first char (G)
      Malette.DisableTimer();
      inputString.remove(0, 1);
      Serial.print("Goto Step ");
      Serial.println(inputString);
      Malette.Reset();
      Malette.GotoStep(inputString.toInt());
    } else {
      Serial.println("Timer is running");
    }
  } break;
  case 'c':
  case 'C': {
    if (!Malette.IsTimerEnabled()) {
      Serial.println("Remove Cache files");
      Malette.DeleteCache();
    } else {
      Serial.println("Timer is running");
    }
  } break;
  case 'h':
  case 'H': {
    Serial.println("L[FileName]: use [Filename.CXX] files as data file");
    Serial.println("S          : Start (running the timer)");
    Serial.println("P          : Pause");
    Serial.println("N          : Next");
    Serial.println("G[Time]    : Goto [Time]");
    Serial.println("R          : Reset");
    Serial.println("C          : Remove all cache files");
    Serial.println("H          : Help");
  }
  default:
    Serial.println("Unknown comand");
    break;
  }
}
