#include "BatteryMeasureService.h"
#include "../Wheelson.h"
#include <Support/ContextTransition.h>
#include "../Nuvoton/WheelsonLED.h"
#include <WiFi.h>

const uint16_t BatteryMeasureService::measureInterval = 10; //in seconds

BatteryMeasureService::BatteryMeasureService(){
}

void BatteryMeasureService::loop(uint micros){
	measureMicros += micros;
	if(measureMicros >= measureInterval * 1000000){
		measureMicros = 0;
		voltage = Nuvo.getBatteryVoltage();
		uint8_t batLvl = getLevel();
		if(batLvl == 4){
			LED.setRGB(GREEN);
		}else if(batLvl == 3 || batLvl == 2){
			LED.setRGB(YELLOW);
		}else if(batLvl == 1){
			LED.setRGB(RED);
		}else if(batLvl == 0 && !shutdownDisable){
			Nuvo.shutdown();
			WiFi.mode(WIFI_OFF);
			btStop();
			esp_deep_sleep_start();
		}
		measureMicros = 0;
	}
}

uint8_t BatteryMeasureService::getLevel(){
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

uint16_t BatteryMeasureService::getVoltage() const{
	return voltage;
}

uint8_t BatteryMeasureService::getPercentage(){
	int16_t percentage = map(voltage, 3600, 4200, 0, 100);
	if(percentage < 0){
		return 0;
	}else if(percentage > 100){
		return 100;
	}else{
		return percentage;
	}
}

void BatteryMeasureService::disableShutdown(bool _shutdown){
	shutdownDisable = _shutdown;
}
