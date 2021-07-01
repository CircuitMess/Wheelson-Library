#include "Nuvoton.h"
#include "../Wheelson.h"

Nuvoton::Nuvoton(TwoWire& Wire) : Wire(Wire) {

}

bool Nuvoton::begin() {
	pinMode(WSNV_PIN_RESET, OUTPUT);
	reset();
	delay(50);

	mutex.lock();
	Wire.begin(I2C_SDA, I2C_SCL);

	Wire.beginTransmission(WSNV_ADDR);
	if(Wire.endTransmission() != 0){
		mutex.unlock();
		return false;
	}
	mutex.unlock();

	return identify();
}

bool Nuvoton::identify() {
	mutex.lock();
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(IDENTIFY_BYTE);
	Wire.endTransmission();

	Wire.requestFrom(WSNV_ADDR, 1);
	bool value = Wire.available() && Wire.read() == WSNV_ADDR;
	mutex.unlock();

	return value;
}

void Nuvoton::reset() {
	digitalWrite(WSNV_PIN_RESET, LOW);
	delay(50);
	digitalWrite(WSNV_PIN_RESET, HIGH);
}

uint16_t Nuvoton::getBatteryVoltage(){
	uint16_t level;

	mutex.lock();
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(BATTERY_BYTE);
	Wire.endTransmission();

	Wire.requestFrom(WSNV_ADDR, 2);
	while(!Wire.available()){
		delayMicroseconds(1);
	}
	Wire.readBytes(reinterpret_cast<char*>(&level), 2);
	mutex.unlock();

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
	LED.setRGB(OFF);

	mutex.lock();
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(SHUTDOWN_BYTE);
	Wire.endTransmission();
	mutex.unlock();
}

Mutex& Nuvoton::getMutex(){
	return mutex;
}
