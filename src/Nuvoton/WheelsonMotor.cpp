#include "WheelsonMotor.h"
#include "../Wheelson.h"
#include "../Settings.h"

WheelsonMotor::WheelsonMotor() : Wire(Nuvo.getWire()){
}

void WheelsonMotor::setMotor(uint8_t id, int8_t intensity){
	if(id > 3) return;
	if(state[id] == intensity) return;
	if(intensity <= -128){
		intensity = -127;
	}
	state[id] = intensity;
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(MOTOR_SET_BYTE);
	Wire.write(id);
	Wire.write((uint8_t) intensity * (Settings.get().speedMultiplier / 255));
	Wire.endTransmission();
}

int8_t WheelsonMotor::getMotor(uint8_t id){
	if(id > 3) return 0;

	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(MOTOR_GET_BYTE);
	Wire.write(id);
	Wire.endTransmission();
	Wire.requestFrom(WSNV_ADDR, 1);
	if(Wire.available()){
		state[id] = Wire.read() & 0xFF;
	}
	return (state[id] * (255 / Settings.get().speedMultiplier));
}

