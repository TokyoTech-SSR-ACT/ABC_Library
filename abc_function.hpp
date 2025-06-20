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

const uint8_t pwmch_Speaker = 0;
const double max_battery_boltage = 4.2 * BATTERY_S_NO;
const double min_battery_voltage = 3.5 * BATTERY_S_NO;
};