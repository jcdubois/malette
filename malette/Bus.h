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
