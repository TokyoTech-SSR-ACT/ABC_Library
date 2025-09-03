#include "abc_function.hpp"

void setup() {
    using namespace ABC;
    PIN_SETUP();
    Serial_Begin(115200, 115200, 1000000);
    Debug_Serial.println("Debug Serial Initialized.");
}
void loop() {
    Debug_Serial.println("PW_Switch_LED: Red");
    PW_Switch_LED(true, false, false);  // Red LED on
    delay(1000);
    Debug_Serial.println("PW_Switch_LED: Green");
    PW_Switch_LED(false, true, false);  // Green LED on
    delay(1000);
    Debug_Serial.println("PW_Switch_LED: Blue");
    PW_Switch_LED(false, false, true);  // Blue LED on
    delay(1000);
}