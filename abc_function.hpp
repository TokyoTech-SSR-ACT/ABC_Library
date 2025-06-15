#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <HardwareSerial.h>

#include "abc_config.hpp"
#include "abc_pin_assign.hpp"

#define EEPROM_ADDR 0

extern HardwareSerial Debug_Serial;  // Use USB
extern HardwareSerial RS485_Serial;  // Use IO32, & IO33
extern HardwareSerial Servo_Serial;  // Use IO16, & IO17

namespace ABC {
void PIN_SETUP(void);
void PW_Switch_LED(bool R, bool G, bool B);
void Battery_Voltage_Calibration(double R10, double R11);
bool Check_Battery_Voltage(double R10, double R11);
void Serial_Begin(uint32_t DS_rate, uint32_t RS_rate, uint32_t SS_rate);

static constexpr uint8_t pwmch_Speaker = 0;
extern double battery_voltage;
extern double Battery_Voltage_ScaleFactor;  // Scale factor for battery voltage
extern const double max_battery_boltage;
extern const double min_battery_voltage;
};