#ifndef WHEELSON_LIBRARY_WHEELSONLED_H
#define WHEELSON_LIBRARY_WHEELSONLED_H

#include <Wire.h>
#define BACKLIGHT_SET_BYTE 0x20
#define BACKLIGHT_GET_BYTE 0x21
#define HEADLIGHT_SET_BYTE 0x22
#define HEADLIGHT_GET_BYTE 0x23

class WheelsonLED {
public:
	WheelsonLED();
	void setBacklight(bool backlight);
	bool getBacklight();
	void setHeadlight(uint8_t intensity);
	uint8_t getHeadlight();

private:
	TwoWire& Wire;
};


#endif //WHEELSON_LIBRARY_WHEELSONLED_H
