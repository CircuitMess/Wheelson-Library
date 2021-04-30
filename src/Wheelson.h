#ifndef WHEELSON_LIBRARY_WHEELSON_H
#define WHEELSON_LIBRARY_WHEELSON_H

#include "Nuvoton.h"
#include "WheelsonLED.h"
#include "WheelsonMotor.h"

#define I2C_SDA 14
#define I2C_SCL 15

extern Nuvoton Nuvo;
extern WheelsonLED LED;
extern WheelsonMotor Motors;

#endif //WHEELSON_LIBRARY_WHEELSON_H
