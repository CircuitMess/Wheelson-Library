#ifndef WHEELSON_LIBRARY_NUVOTON_H
#define WHEELSON_LIBRARY_NUVOTON_H

#include <Wire.h>

#define BYTE_IDENTIFY 0x00
#define JDNV_ADDR 0x38
#define JDNV_PIN_RESET 33

class Nuvoton {
public:
	Nuvoton(TwoWire& Wire);
	void begin();
	bool identify();
	void reset();
	TwoWire& getWire();

private:
	TwoWire& Wire;
};

#endif //WHEELSON_LIBRARY_NUVOTON_H
