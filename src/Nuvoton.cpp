#include "Nuvoton.h"
#include "Wheelson.h"

Nuvoton::Nuvoton(TwoWire& Wire) : Wire(Wire) {

}

bool Nuvoton::begin() {
	pinMode(WSNV_PIN_RESET, OUTPUT);
	reset();
	delay(50);

	Wire.begin(I2C_SDA, I2C_SCL);

	Wire.beginTransmission(WSNV_ADDR);
	if(Wire.endTransmission() != 0) return false;

	return identify();
}

bool Nuvoton::identify() {
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(IDENTIFY_BYTE);
	Wire.endTransmission();

	Wire.requestFrom(WSNV_ADDR, 1);
	return Wire.available() && Wire.read() == WSNV_ADDR;
}

void Nuvoton::reset() {
	digitalWrite(WSNV_PIN_RESET, LOW);
	delay(50);
	digitalWrite(WSNV_PIN_RESET, HIGH);
}

TwoWire &Nuvoton::getWire() {
	return this->Wire;
}
