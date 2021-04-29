#include "WheelsonInput.h"
#include "Nuvoton.h"
#include "Wheelson.h"

WheelsonInput::WheelsonInput() : Input(NUM_BUTTONS), Wire(Nuvo.getWire()){

}

uint8_t WheelsonInput::getNumEvents(){
	Wire.beginTransmission(JDNV_ADDR);
	Wire.write(GET_NUM_EVENTS);
	Wire.endTransmission();
	Wire.requestFrom(JDNV_ADDR, 2);
	if(Wire.available()){
		Wire.read();
	}
	if(Wire.available()){
		uint8_t numEventsData = Wire.read();
		return numEventsData;
	}

}

void WheelsonInput::scanButtons(){
	if(getNumEvents() == 0) return;
	else{
		handleEvents(getNumEvents());
	}
}

void WheelsonInput::handleEvents(uint8_t numEvents){
	if(numEvents == 0) return;
	Wire.beginTransmission(JDNV_ADDR);
	Wire.write(BYTE_GETEVENTS);
	Wire.write(numEvents);
	Wire.endTransmission();
	Wire.requestFrom(JDNV_ADDR, numEvents + 1);
	if(Wire.available()){
		Wire.read();
	}
	std::vector<InputEvent> events;
	uint8_t idState;
	for(int i = numEvents; i > 0; i--){
		if(Wire.available()){
			idState = Wire.read();
		}
		uint8_t id = idState & 0x7F;
		bool state = idState >> 7;

		events.push_back({id,state});
	}
	for(const InputEvent& event : events){
		handleSingleEvent(event);
	}
}

void WheelsonInput::handleSingleEvent(const WheelsonInput::InputEvent& event){
if (event.state){
	btnPress(event.id);
}else{
	btnRelease(event.id);
}
}




