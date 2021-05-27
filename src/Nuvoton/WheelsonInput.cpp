#include "WheelsonInput.h"
#include "Nuvoton.h"
#include "../Wheelson.h"

WheelsonInput::WheelsonInput() : Input(NUM_BUTTONS), Wire(Nuvo.getWire()), mutex(Nuvo.getMutex()){

}

uint8_t WheelsonInput::getNumEvents(){
	mutex.lock();
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(GET_NUM_EVENTS_BYTE);
	Wire.endTransmission();

	Wire.requestFrom(WSNV_ADDR, 1);
	if(!Wire.available()){
		mutex.unlock();
		return 0;
	}
	uint8_t value = Wire.read();
	mutex.unlock();

	return value;
}

void WheelsonInput::scanButtons(){
	uint8_t numberOfEvents = getNumEvents();
	if(numberOfEvents == 0) return;
	handleEvents(numberOfEvents);
}

void WheelsonInput::handleEvents(uint8_t numEvents){
	if(numEvents == 0) return;

	mutex.lock();
	Wire.beginTransmission(WSNV_ADDR);
	Wire.write(GETEVENTS_BYTE);
	Wire.write(numEvents);
	Wire.endTransmission();

	std::vector<InputEvent> events;
	Wire.requestFrom((uint8_t) WSNV_ADDR, numEvents);
	while(!Wire.available()){
		delayMicroseconds(1);
	}
	for(int i = 0; i < numEvents; i++){
		uint8_t data = Wire.read();
		uint8_t id = data & 0x7F;
		bool state = data >> 7;
		events.push_back({ id, state });
	}
	mutex.unlock();

	for(const InputEvent& event : events){
		handleSingleEvent(event);
	}
}

void WheelsonInput::handleSingleEvent(const WheelsonInput::InputEvent& event){
	if(event.state){
		btnPress(event.id);
	}else{
		btnRelease(event.id);
	}
}




