#include "Nuvoton.h"
#include "Wheelson.h"

Nuvoton::Nuvoton(TwoWire& Wire) : Wire(Wire) {

}

void Nuvoton::begin() {
	Wire.begin(I2C_SDA, I2C_SCL);
}

bool Nuvoton::identify() {
	Wire.beginTransmission(JDNV_ADDR);
	Wire.write(BYTE_IDENTIFY);
	Wire.endTransmission();
	Wire.requestFrom(JDNV_ADDR, 1);
	if(Wire.available()){
		if(Wire.read() == JDNV_ADDR){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

void Nuvoton::reset() {
	digitalWrite(JDNV_PIN_RESET, LOW);
	delay(5);
	digitalWrite(JDNV_PIN_RESET, HIGH);
}

TwoWire &Nuvoton::getWire() {
	return this->Wire;
}
