#include "Nuvoton.h"
#include "../Wheelson.h"

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

uint16_t Nuvoton::getBatteryVoltage(){
	uint16_t level;

	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(BATTERY_BYTE);
	Wire.endTransmission();

	Wire.requestFrom(WSNV_ADDR, 2);
	while(!Wire.available()){
		delayMicroseconds(1);
	}
	Wire.readBytes(reinterpret_cast<char*>(&level), 2);

	return level;
}

TwoWire &Nuvoton::getWire() {
	return this->Wire;
}

void Nuvoton::shutdown(){
	for(uint8_t i = 0; i < 4; i++){
		Motors.setMotor(i, 0);
	}
	LED.setBacklight(false);
	LED.setHeadlight(0);
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(SHUTDOWN_BYTE);
	Wire.endTransmission();
}
