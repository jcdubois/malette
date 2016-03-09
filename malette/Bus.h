/**
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

#ifndef BUS_H
#define BUS_H

class Bus {
public:
  // Constructor
  Bus();
  // Destructor
  ~Bus();

  // Initialize
  bool Initialize();

  // Write a data to an address
  void Write(unsigned char decoder, unsigned char channel, unsigned char data);

private:
  // Set the address on the bus
  void WriteAddress(unsigned char decoder, unsigned char channel);

  // Set the data to the bus
  void WriteData(unsigned char data);
};

#endif // BUS_H
