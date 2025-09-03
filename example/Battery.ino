#include "abc_function.hpp"

double R10 = 1006;   // 抵抗R10の値（単位：オーム）
double R11 = 154.6;  // 抵抗R11の値

void setup() {
    using namespace ABC;

    PIN_SETUP();
    Serial_Begin(115200, 115200, 1000000);
    Battery_Voltage_Calibration(R10, R11);
}

void loop() {
    using namespace ABC;

    if (Check_Battery_Voltage(R10, R11)) {
        battery_voltage_count++;
        if (battery_voltage_count > 10) {
            PW_Switch_LED(true, false, false);  // Red LED on
            Debug_Serial.println("[FATAL]:Battery voltage out of range!");
            while (1) {
                PW_Switch_LED(true, false, false);  // Red LED on
                delay(1000);
                PW_Switch_LED(false, false, false);  // All LEDs off
                delay(1000);
            };
        }
    } else {
        battery_voltage_count = 0;  // Reset battery voltage count
    }
}