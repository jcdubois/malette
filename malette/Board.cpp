
#include "Board.h"
#include "Bus.h"

extern Bus Bus1;

#define DOT '.'
#define EXT 'C'

/*
 * Board constructor
 */
Board::Board() {
  m_num = 0;
  m_decoder = 0;
  m_channel = 0;
}

Board::~Board() {}

bool Board::SetNum(unsigned char num) {
  m_num = num;
  m_decoder = (m_num - 1) / 8;
  m_channel = (m_num - 1) & 0x7;

  return true;
}

bool Board::SetFile(String path) {
  // Close the file if it is open
  CloseFile();

  char buff[3] = {0, 0, 0};
  sprintf(buff, "%02d", m_num);
  String file = path + DOT + EXT + buff;

  if (!SD.exists(file)) {
    Serial.print("file ");
    Serial.print(file);
    Serial.println(" does not exist");
    return false;
  }

  // open the file related to this board
  m_file = SD.open(file, FILE_READ);

  if (!m_file) {
    Serial.print("Can't opne file ");
    Serial.println(file);
    return false;
  }

  // Read the "header", i.e the number of steps in the file.
  ReadHeader();

  // Write the initial data (0) to the board
  WriteData();

  return true;
}

bool Board::CloseFile() {
  if (!m_file) {
    return false;
  }

  m_file.close();

  return true;
}

bool Board::Execute() {
  if (!m_file) {
    Serial.print("No file configured for board ");
    Serial.println(m_num);
    return false;
  }

  m_timeLeft--;

  if (m_timeLeft <= 0) {
    ReadLine();
    WriteData();
  }

  return true;
}

bool Board::WriteData() {
  // Write the data to the board address.
  Bus1.Write(m_decoder, m_channel, m_value);

  return true;
}

bool Board::SetStep(unsigned int time) {
  if (!m_file) {
    Serial.print("No file configured for board ");
    Serial.println(m_num);
    return false;
  }

  // We should seek the correct line
  do {
    // Got to first data line
    m_file.seek(m_dataposition);
    m_timeLeft = 0;

    do {
      time -= m_timeLeft;
      ReadLine();
    } while (time > m_timeLeft);

  } while (time > m_timeLeft);

  m_timeLeft -= time;

  WriteData();

  return true;
}

bool Board::ReadLine() {
  // Read one data line made of a binary value and a time value
  char ret;

  m_value = 0;
  // Read the binary value
  for (unsigned int i = 0; i < 8; i++) {
    m_value = m_value << 1;
    ret = m_file.read();
    if (ret == '1') {
      m_value |= 0x1;
    }
  }

  // Skip the space
  ret = m_file.read();

  String sTimeStep;
  do {
    ret = m_file.read();
    sTimeStep += String(ret);
  } while (ret != '\n');

  m_timeLeft = sTimeStep.toInt();

  m_indexStep++;
  m_indexStep %= m_nbStep;

  // If we rolled over then seek the initial data position
  if (!m_indexStep) {
    m_file.seek(m_dataposition);
  }

  return true;
}

bool Board::ReadHeader() {
  char ret;

  // Read the number of steps in the file
  String snbStep;
  do {
    ret = m_file.read();
    if (ret != ' ') {
      snbStep += String(ret);
    }
  } while (ret != '\n');

  // Save the value
  m_nbStep = snbStep.toInt();

  // Save the beginning of the "data" part.
  m_dataposition = m_file.position();

  // Init to 0
  m_indexStep = 0;
  m_timeLeft = 0;
  m_value = 0;

  // m_nbStep should not be null
  if (m_nbStep) {
    return true;
  } else {
    return false;
  }
}
