#ifndef WHEELSON_LIBRARY_BATTERYMEASURESERVICE_H
#define WHEELSON_LIBRARY_BATTERYMEASURESERVICE_H

#include <Arduino.h>
#include <Loop/LoopListener.h>

class BatteryMeasureService : public LoopListener {
public:
	BatteryMeasureService();
	void loop(uint micros) override;
	uint16_t getVoltage() const;
	uint8_t getLevel();
	uint8_t getPercentage();
	void disableShutdown(bool _shutdown);

private:
	uint16_t voltage = 0; //in mV
	static const uint16_t measureInterval;
	uint measureMicros = 0;
	bool shutdownDisable = false;
};


#endif //WHEELSON_LIBRARY_BATTERYMEASURESERVICE_H
