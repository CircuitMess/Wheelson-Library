#include "Nuvoton.h"
#include "Wheelson.h"

Nuvoton::Nuvoton(TwoWire& Wire) : Wire(Wire) {

}

void Nuvoton::begin() {
	Wire.begin(I2C_SDA, I2C_SCL);
}

bool Nuvoton::identify() {
	Wire.beginTransmission(BYTE_WSNV_ADDR_BYTE);
	Wire.write(IDENTIFY_BYTE);
	Wire.endTransmission();
	Wire.requestFrom(BYTE_WSNV_ADDR_BYTE, 1);
	if(Wire.available()){
		if(Wire.read() == BYTE_WSNV_ADDR_BYTE){
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
