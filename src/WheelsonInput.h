#ifndef WHEELSON_LIBRARY_WHEELSONINPUT_H
#define WHEELSON_LIBRARY_WHEELSONINPUT_H

#include <Input/Input.h>
#include <Wire.h>

#define GET_NUM_EVENTS 0x40
#define BYTE_GETEVENTS 0x41
#define NUM_BUTTONS 6

class WheelsonInput : public Input {
public:
	WheelsonInput();

private:

	struct InputEvent {
		uint8_t id;
		bool state;
	};

	uint8_t getNumEvents();

	void handleEvents(uint8_t numEvents);

	void handleSingleEvent(const InputEvent& event);

	TwoWire& Wire;
protected:
	void scanButtons() override;
};

#endif //WHEELSON_LIBRARY_WHEELSONINPUT_H
