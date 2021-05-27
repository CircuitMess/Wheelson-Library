#include "WheelsonLED.h"
#include "Nuvoton.h"
#include "../Wheelson.h"

WheelsonLED::WheelsonLED() : Wire(Nuvo.getWire()), mutex(Nuvo.getMutex()) {

}

void WheelsonLED::setBacklight(bool backlight) {
	mutex.lock();
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(BACKLIGHT_SET_BYTE);
	Wire.write(backlight);
	Wire.endTransmission();
	mutex.unlock();
}

bool WheelsonLED::getBacklight() {
	mutex.lock();
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(BACKLIGHT_GET_BYTE);
	Wire.endTransmission();

	Wire.requestFrom(WSNV_ADDR, 1);
	bool value =  Wire.available() && Wire.read();
	mutex.unlock();

	return value;
}

void WheelsonLED::setHeadlight(uint8_t headlight) {
	mutex.lock();
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(HEADLIGHT_SET_BYTE);
	Wire.write(headlight);
	Wire.endTransmission();
	mutex.unlock();
}

uint8_t WheelsonLED::getHeadlight() {
	mutex.lock();
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(HEADLIGHT_GET_BYTE);
	Wire.endTransmission();

	Wire.requestFrom(WSNV_ADDR, 1);
	if(!Wire.available()){
		mutex.unlock();
		return 0;
	}
	uint8_t value = Wire.read() & 0xFF;
	mutex.unlock();

	return value;
}

void WheelsonLED::setRGB(WLEDColor colour){
	mutex.lock();
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(RGB_SET_BYTE);
	Wire.write(colour);
	Wire.endTransmission();
	mutex.unlock();
}

WLEDColor WheelsonLED::getRGB(){
	mutex.lock();
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(RGB_GET_BYTE);
	Wire.endTransmission();

	Wire.requestFrom(WSNV_ADDR, 1);
	if(!Wire.available()){
		mutex.unlock();
		return OFF;
	}

	uint8_t bitColour = Wire.read() & 0xFF;
	mutex.unlock();
	return (WLEDColor)bitColour;
}
