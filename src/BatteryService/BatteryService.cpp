#include <WiFi.h>
#include "BatteryService.h"
#include "../Wheelson.h"

const uint16_t BatteryService::measureInterval = 30; //in seconds

BatteryService::BatteryService() : Wire(Nuvo.getWire()){
}

void BatteryService::loop(uint micros){
	measureMicros += micros;
	if(measureMicros >= measureInterval * 1000000){
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
	WiFi.mode(WIFI_OFF);
	btStop();
	ESP.deepSleep(0);
}

void BatteryService::warning(){

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

	if(level == 1){
		fs::File bgFile = SPIFFS.open("/battery_1.raw");
		bgFile.read(reinterpret_cast<uint8_t*>(batteryBuffer), 14 * 6 * 2);
		bgFile.close();
		canvas->drawIcon(batteryBuffer,140,5,14,6,1,TFT_TRANSPARENT);
	}
	else if(level == 2){
		fs::File bgFile = SPIFFS.open("/battery_2.raw");
		bgFile.read(reinterpret_cast<uint8_t*>(batteryBuffer), 14 * 6 * 2);
		bgFile.close();
		canvas->drawIcon(batteryBuffer,140,5,14,6,1,TFT_TRANSPARENT);
	}
	else if(level == 3){
		fs::File bgFile = SPIFFS.open("/battery_3.raw");
		bgFile.read(reinterpret_cast<uint8_t*>(batteryBuffer), 14 * 6 * 2);
		bgFile.close();
		canvas->drawIcon(batteryBuffer,140,5,14,6,1,TFT_TRANSPARENT);
	}
	else if(level == 4){
		fs::File bgFile = SPIFFS.open("/battery_4.raw");
		bgFile.read(reinterpret_cast<uint8_t*>(batteryBuffer), 14 * 6 * 2);
		bgFile.close();
		canvas->drawIcon(batteryBuffer,140,5,14,6,1,TFT_TRANSPARENT);
	}
	lastDrawn=level;
}
