#ifndef WHEELSON_LIBRARY_WHEELSON_H
#define WHEELSON_LIBRARY_WHEELSON_H

#include "Nuvoton/Nuvoton.h"
#include "Nuvoton/WheelsonLED.h"
#include "Nuvoton/WheelsonMotor.h"
#include "BatteryService/BatteryService.h"

#define I2C_SDA 14
#define I2C_SCL 15

#define BTN_UP 3
#define BTN_DOWN 1
#define BTN_LEFT 0
#define BTN_RIGHT 2
#define BTN_MID 4
#define BTN_BACK 5

#define MOTOR_FL 0
#define MOTOR_BL 1
#define MOTOR_FR 2
#define MOTOR_BR 3

extern Nuvoton Nuvo;
extern WheelsonLED LED;
extern WheelsonMotor Motors;
extern BatteryService Battery;

#endif //WHEELSON_LIBRARY_WHEELSON_H
