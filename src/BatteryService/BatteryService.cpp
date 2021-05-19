#include "BatteryService.h"
#include "../Wheelson.h"

const uint16_t BatteryService::measureInterval = 30; //in seconds

BatteryService::BatteryService() : Wire(Nuvo.getWire()){
}

void BatteryService::loop(uint micros){
	measureMicros+=micros;
	if(measureMicros >= measureInterval*1000000){
		measureMicros = 0;
		voltage = Nuvo.getBatteryVoltage();
		uint8_t percentage = getPercentage();
		if(percentage <= 1){
			shutdown();
		}else if(percentage <= 15){
			warning();
		}
	}
}

void BatteryService::shutdown(){
	Nuvo.shutdown();
	ESP.deepSleep(0);
}

void BatteryService::warning(){

}

uint8_t BatteryService::getLevel(){
	uint8_t percentage = map(voltage, 3600, 4200, 0, 100);
	if(percentage > 80){
		return 4;
	}else if(percentage <= 80 && percentage > 40){
		return 3;
	}else if(percentage <= 40 && percentage > 15){
		return 2;
	}else if(percentage <= 15 && percentage > 0){
		return 1;
	}else if(percentage == 0){
		return 0;
	}
}

uint16_t BatteryService::getVoltage() const{
	return voltage;
}

uint8_t BatteryService::getPercentage(){
	return map(voltage, 3600, 4200, 0, 100);
}
