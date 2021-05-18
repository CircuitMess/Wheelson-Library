#ifndef WHEELSON_LIBRARY_SETTINGS_H
#define WHEELSON_LIBRARY_SETTINGS_H

#include <Arduino.h>

struct SettingsData {
	uint8_t shutdownTime = 1;
	uint speed = 255;
	bool inputTested = false;
};

class SettingsImpl {
public:
	bool begin();

	void store();

	SettingsData& get();

	void reset();

private:
	SettingsData data;
};

extern SettingsImpl Settings;

#endif //WHEELSON_LIBRARY_SETTINGS_H
