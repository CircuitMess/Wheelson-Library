#include "BatteryService.h"
#include "Wheelson.h"
#include <Support/ContextTransition.h>
#include <WiFi.h>
#include <SPIFFS.h>

const uint16_t BatteryService::measureInterval = 10; //in seconds

BatteryService::BatteryService(){
}

void BatteryService::loop(uint micros){
	measureMicros += micros;
	if(measureMicros >= measureInterval * 1000000){
		measureMicros = 0;
		voltage = Nuvo.getBatteryVoltage();
		if(getLevel() == 0 && !shutdownDisable){
			Nuvo.shutdown();
			WiFi.mode(WIFI_OFF);
			btStop();
			esp_deep_sleep_start();
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

void BatteryService::disableShutdown(bool _shutdown){
	shutdownDisable = _shutdown;
}

uint8_t BatteryService::getLastDrawnLevel() const{
	return lastDrawn;
}

void BatteryService::drawIcon(Sprite* canvas){
	uint8_t level = getLevel();
	Color* batteryBuffer = nullptr;
	batteryBuffer = static_cast<Color*>(ps_malloc(14 * 6 * 2));
	if(batteryBuffer == nullptr){
		Serial.println("Battery icon, unpack error");
		return;
	}
    char filename[20];
	sprintf(filename,"battery_%d.raw",level);

	fs::File bgFile = SPIFFS.open(filename);
	bgFile.read(reinterpret_cast<uint8_t*>(batteryBuffer), 14 * 6 * 2);
	bgFile.close();
	canvas->drawIcon(batteryBuffer, 140, 5, 14, 6, 1, TFT_TRANSPARENT);

	lastDrawn=level;
	free(batteryBuffer);
}