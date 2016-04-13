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

#include "Board.h"
#include "Bus.h"

#define DEBUG 0

extern Bus Bus1;

#define DOT '.'
#define EXT1 'C'
#define EXT2 'X'

/*
 * Board constructor
 */
Board::Board() {
  m_num = 0;
  m_decoder = 0;
  m_channel = 0;
  m_steps = 0;
}

Board::~Board() {}

void Board::SetNum(unsigned char num) {
  m_num = num;
  m_decoder = (m_num - 1) / 8;
  m_channel = (m_num - 1) & 0x7;
  m_value = 0;

  WriteData();
}

void Board::SetFile(String path) {
  // Close the file if it is open
  CloseFile();

  m_file_name = path;

  MakeCache(path);

  char buff[3] = {0, 0, 0};
  sprintf(buff, "%02d", m_num);
  String file = path + DOT + EXT2 + buff;

  if (!SD.exists(file)) {
    Serial.print("file ");
    Serial.print(file);
    Serial.println(" does not exist");
    return;
  }

  // open the file related to this board
  m_file = SD.open(file, FILE_READ);

  if (!m_file) {
    Serial.print("Can't open file ");
    Serial.println(file);
    return;
  }

  m_value = 0;

  m_steps = m_file.available() / 3;

  // Write the initial data (0) to the board
  WriteData();
}

void Board::MakeCache(String path) {
  String file_name;
  char buff[3] = {0, 0, 0};
  char ret;

  sprintf(buff, "%02d", m_num);

  file_name = path + DOT + EXT1 + buff;

  if (!SD.exists(file_name)) {
    Serial.print("file ");
    Serial.print(file_name);
    Serial.println(" does not exist");
    return;
  }

  file_name = path + DOT + EXT2 + buff;

  if (SD.exists(file_name)) {
#if DEBUG
    Serial.print("file ");
    Serial.print(file_name);
    Serial.println(" is present");
#endif
    return;
  }

  File cache_file = SD.open(file_name, FILE_WRITE);

  if (!cache_file) {
    Serial.print("Can't open file ");
    Serial.println(file_name);
    return;
  }
  
#if DEBUG
  Serial.print("Output file is ");
  Serial.println(cache_file.name());
#endif

  file_name = path + DOT + EXT1 + buff;

  // open the file related to this board
  File input_file = SD.open(file_name, FILE_READ);

  if (!input_file) {
    Serial.print("Can't open file ");
    Serial.println(file_name);
    cache_file.close();
    return;
  }

#if DEBUG
  Serial.print("Input file is ");
  Serial.println(input_file.name());
#endif

  // Read the number of steps in the input file
  String snbStep;

  do {
    ret = input_file.read();
    if (ret == -1) {
      Serial.print("Board::MakeCache: Failed to read #steps in file ");
      Serial.println(input_file.name());
      goto fail;
    } else if (ret != ' ') {
      snbStep += String(ret);
    }
  } while (ret != '\n');

  unsigned char value;

  for (int j=0; j<snbStep.toInt(); j++) {
    value = 0;

    // Read the binary value
    for (int i = 0; i < 8; i++) {
      value = value << 1;
      ret = input_file.read();
      if (ret == -1) {
        Serial.print("Board::MakeCache: Failed to read value on file ");
        Serial.println(input_file.name());
        goto fail;
      } else if (ret == '1') {
        value |= 0x1;
      } else if (ret != '0') {
        Serial.print("Board::MakeCache: value is not a binary value");
        Serial.println(input_file.name());
        goto fail;
      }
    }

    m_value = value;

    WriteData();
    
    String time_value;

    // read time associated to value
    do {
      ret = input_file.read();
      if (ret == -1) {
        Serial.print("Board::MakeCache: Failed to read time on file ");
        Serial.println(input_file.name());
        goto fail;
      } else if (ret != ' ') {
        time_value += String(ret);
      }
    } while (ret != '\n');

    int time = time_value.toInt();

    /* We wrtie the value */
    if (cache_file.write(value) == 0) {
        Serial.print("Board::MakeCache: Failed to write to file ");
        Serial.println(cache_file.name());
    }
    /* We write the upper time value */
    value = (time >> 8) & 0xff;
    if (cache_file.write(value) == 0) {
        Serial.print("Board::MakeCache: Failed to write to file ");
        Serial.println(cache_file.name());
    }
    /* We write the lower time value */
    value = time & 0xff;
    if (cache_file.write(value) == 0) {
        Serial.print("Board::MakeCache: Failed to write to file ");
        Serial.println(cache_file.name());
    }
  }

fail:
  input_file.close();
  cache_file.close();
}

void Board::DeleteCache() {
  char buff[3] = {0, 0, 0};
  sprintf(buff, "%02d", m_num);
  String file = m_file_name + DOT + EXT2 + buff;

  if (!SD.exists(file)) {
    Serial.print("file ");
    Serial.print(file);
    Serial.println(" does not exist");
    return;
  }

  if (!SD.remove(file)) {
    Serial.print("Cannot remove file ");
    Serial.println(file);
    return;
  }
}

void Board::CloseFile() {
  if (!m_file) {
    return;
  }

  m_file.close();
}

void Board::Execute() {
  if (!m_file) {
    Serial.print("Board::Execute: No file configured for board ");
    Serial.println(m_num);
    return;
  }

  if (m_steps == 0) {
    return;
  }

  m_timeLeft--;

  if (m_timeLeft <= 0) {
    ReadData();
    WriteData();
  }
}

void Board::WriteData() {
  // Write the data to the board address.
  Bus1.Write(m_decoder, m_channel, m_value);
}

void Board::SetStep(unsigned int time) {
  if (!m_file) {
    Serial.print("Board::SetStep: No file configured for board ");
    Serial.println(m_num);
    return;
  }

  if (m_steps == 0) {
    return;
  }

  // We should seek the correct line
  do {
    // Got to first data line
    m_file.seek(0);
    m_timeLeft = 0;

    do {
      time -= m_timeLeft;
      ReadData();
    } while (time > m_timeLeft);

  } while (time > m_timeLeft);

  m_timeLeft -= time;

  WriteData();
}

void Board::ReadData() {
  int ret;
  // Read one data line made of a binary value and a time value
  ret = m_file.read();
  if (ret == -1) {
    Serial.print("Board::ReadData: Failed to read from file ");
    Serial.println(m_file.name());
  }
  m_value = (unsigned char)ret;
  ret = m_file.read();
  if (ret == -1) {
    Serial.print("Board::ReadData: Failed to read from file ");
    Serial.println(m_file.name());
  }
  m_timeLeft = (unsigned char)ret;
  m_timeLeft <<= 8;
  ret = m_file.read();
  if (ret == -1) {
    Serial.print("Board::ReadData: Failed to read from file ");
    Serial.println(m_file.name());
  }
  m_timeLeft |= (unsigned char)ret;

  // If we rolled over then seek the initial data position
  if (m_file.available() < 3) {
    if (m_file.available() != 0) {
      Serial.print("Board::ReadData: ");
      Serial.print(m_file.available());
      Serial.print(" bytes left in file ");
      Serial.println(m_file.name());
    }
    if (!m_file.seek(0)) {
      Serial.print("Board::ReadData: Failed to seek start of file ");
      Serial.println(m_file.name());
    }
  }
}

void Board::Reset() {
  if (m_file) {
    if (!m_file.seek(0)) {
      Serial.print("Board::Reset: Failed to seek start of file ");
      Serial.println(m_file.name());
    }
  }

  // Init to 0
  m_timeLeft = 0;
  m_value = 0;

  // Write the initial data (0) to the board
  WriteData();
}
