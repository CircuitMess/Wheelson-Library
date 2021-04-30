#include "Nuvoton.h"
#include "Wheelson.h"

Nuvoton::Nuvoton(TwoWire& Wire) : Wire(Wire) {

}

void Nuvoton::begin() {
	Wire.begin(I2C_SDA, I2C_SCL);
}

bool Nuvoton::identify() {
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(BYTE_IDENTIFY);
	Wire.endTransmission();
	Wire.requestFrom(WSNV_ADDR, 1);
	if(Wire.available()){
		if(Wire.read() == WSNV_ADDR){
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
	digitalWrite(WSNV_PIN_RESET, LOW);
	delay(5);
	digitalWrite(WSNV_PIN_RESET, HIGH);
}

TwoWire &Nuvoton::getWire() {
	return this->Wire;
}
