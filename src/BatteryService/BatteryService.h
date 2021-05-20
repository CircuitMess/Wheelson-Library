#ifndef WHEELSON_LIBRARY_BATTERYSERVICE_H
#define WHEELSON_LIBRARY_BATTERYSERVICE_H

#include <Arduino.h>
#include <Loop/LoopListener.h>
#include <Wire.h>
#include <Display/Sprite.h>

#define GET_BATTERY_BYTE 0X50
#define SHUTDOWN_BYTE 0X51

class BatteryService : LoopListener {
public:
	BatteryService();
	void loop(uint micros) override;
	uint16_t getVoltage() const;
	uint8_t getLevel();
	uint8_t getPercentage();

	uint8_t getLastDrawnLevel() const;

	void drawIcon(Sprite* canvas);

private:
	TwoWire& Wire;
	uint16_t voltage = 0; //in mV
	static const uint16_t measureInterval;
	uint measureMicros = 0;
    uint8_t lastDrawn=0;

	void shutdown();
	void warning();

};


#endif //WHEELSON_LIBRARY_BATTERYSERVICE_H
