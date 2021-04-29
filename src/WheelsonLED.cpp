#include "WheelsonLED.h"
#include "Nuvoton.h"

WheelsonLED::WheelsonLED(TwoWire &wire) : Wire(wire) {

}

void WheelsonLED::setBacklight(bool backlight) {
	if(this->backlight == backlight) return;

	this->backlight = backlight;
	Wire.beginTransmission(JDNV_ADDR);
	Wire.write(BACKLIGHT_SET_BYTE);
	Wire.write(backlight);
	Wire.endTransmission();
}

bool WheelsonLED::getBacklight() {
	Wire.beginTransmission(JDNV_ADDR);
	Wire.write(BACKLIGHT_GET_BYTE);
	Wire.endTransmission();
	Wire.requestFrom(JDNV_ADDR, 1);
	if(Wire.available()){
		backlight = Wire.read() & 1;
	}
	return backlight;
}

void WheelsonLED::setHeadlight(uint8_t headlight) {
	if(this->headlight == headlight) return;

	this->headlight = headlight;
	Wire.beginTransmission(JDNV_ADDR);
	Wire.write(HEADLIGHT_SET_BYTE);
	Wire.write(headlight);
	Wire.endTransmission();
}

uint8_t WheelsonLED::getHeadlight() {
	Wire.beginTransmission(JDNV_ADDR);
	Wire.write(HEADLIGHT_GET_BYTE);
	Wire.endTransmission();
	Wire.requestFrom(JDNV_ADDR, 1);
	if(Wire.available()){
		headlight = Wire.read() & 0xFF;
	}
	return headlight;
}
