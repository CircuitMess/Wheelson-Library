#include "BatteryService.h"
#include "../Wheelson.h"
#include "ShutdownPopup.h"
#include "WarningPopup.h"
#include <Support/ContextTransition.h>

const uint16_t BatteryService::measureInterval = 15; //in seconds

BatteryService::BatteryService() : Wire(Nuvo.getWire()){
}

void BatteryService::loop(uint micros){
	measureMicros += micros;
	if(measureMicros >= measureInterval * 1000000){
		measureMicros = 0;
		voltage = Nuvo.getBatteryVoltage();
		uint8_t percentage = getPercentage();
		if(percentage <= 1){
			if(ContextTransition::isRunning() || Context::getCurrentContext() == shutdownPopup || Context::getCurrentContext() == warningPopup)
				return;
			shutdownPopup = new ShutdownPopup(*Context::getCurrentContext());
			shutdownPopup->push(Context::getCurrentContext());
		}else if((percentage <= 15 || true) && !warningShown){
			if(ContextTransition::isRunning() || Context::getCurrentContext() == shutdownPopup || Context::getCurrentContext() == warningPopup)
				return;
			warningShown = true;
			warningPopup = new WarningPopup(*Context::getCurrentContext());
			warningPopup->push(Context::getCurrentContext());
		}
		measureMicros = 0;
	}
}

uint8_t BatteryService::getLevel(){
	uint8_t percentage = getPercentage();
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
	int16_t percentage = map(voltage, 3600, 4200, 0, 100);
	if(percentage < 0){
		return 0;
	}else if(percentage > 100){
		return 100;
	}else{
		return percentage;
	}
}
