#include "abc_function.hpp"

void setup() {
    using namespace ABC;
    PIN_SETUP();
    Serial_Begin(115200, 115200, 1000000);
    Debug_Serial.println("Debug Serial Initialized.");
}
void loop() {
    Debug_Serial.println("Hello, ABC!");
    delay(1000);
}