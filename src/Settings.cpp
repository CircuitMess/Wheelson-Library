#include "Settings.h"
#include <Util/Settings.h>

SettingsImpl Settings;

bool SettingsImpl::begin(){

}

SettingsData& SettingsImpl::get(){
	return data;
}

void SettingsImpl::store(){
	Settings::store();
}

void SettingsImpl::reset(){
	memset(&data, 0, sizeof(SettingsData));
}
