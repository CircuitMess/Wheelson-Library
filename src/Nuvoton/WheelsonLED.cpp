#include "WheelsonLED.h"
#include "Nuvoton.h"
#include "../Wheelson.h"

WheelsonLED::WheelsonLED() : Wire(Nuvo.getWire()) {

}

void WheelsonLED::setBacklight(bool backlight) {
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(BACKLIGHT_SET_BYTE);
	Wire.write(backlight);
	Wire.endTransmission();
}

bool WheelsonLED::getBacklight() {
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(BACKLIGHT_GET_BYTE);
	Wire.endTransmission();

	Wire.requestFrom(WSNV_ADDR, 1);
	return Wire.available() && Wire.read();
}

void WheelsonLED::setHeadlight(uint8_t headlight) {
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(HEADLIGHT_SET_BYTE);
	Wire.write(headlight);
	Wire.endTransmission();
}

uint8_t WheelsonLED::getHeadlight() {
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(HEADLIGHT_GET_BYTE);
	Wire.endTransmission();

	Wire.requestFrom(WSNV_ADDR, 1);
	if(!Wire.available()) return 0;
	return Wire.read() & 0xFF;
}
