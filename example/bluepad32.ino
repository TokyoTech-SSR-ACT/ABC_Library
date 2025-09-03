#include "abc_function.hpp"

void Sample_Process(ControllerPtr ctl);

void setup() {
    using namespace ABC;
    PIN_SETUP();
    Serial_Begin(115200, 115200, 1000000);
    Debug_Serial.println("Debug Serial Initialized.");
    // Setup the Bluepad32
    BluePad32_Controller_Setup(false);  // Enable touchpad and mouse support
}
void loop() {
    // Check for input from Controller
    bool dataUpdated = BP32.update();

    if (dataUpdated) {
        for (auto myController : myControllers) {
            if (myController && myController->isConnected() &&
                myController->hasData()) {
                if (myController->isGamepad()) {
                    Sample_Process(myController);
                } else {
                    Debug_Serial.println("[WARNIG]:Unsupported controller");
                    PW_Switch_LED(true, false, true);  // Purple LED on
                    delay(1000);
                }
            }
        }
    }

    vTaskDelay(1);
}

void Sample_Process(ControllerPtr ctl) {
    /*https://github.com/maxgerhardt/pio-bluepad32-controllerより引用*/
    if (ctl->a()) {
        static int colorIdx = 0;
        // Some gamepads like DS4 and DualSense support changing the color LED.
        // It is possible to change it by calling:
        switch (colorIdx % 3) {
            case 0:
                // Red
                ctl->setColorLED(255, 0, 0);
                break;
            case 1:
                // Green
                ctl->setColorLED(0, 255, 0);
                break;
            case 2:
                // Blue
                ctl->setColorLED(0, 0, 255);
                break;
        }
        colorIdx++;
    }

    if (ctl->b()) {
        // Turn on the 4 LED. Each bit represents one LED.
        static int led = 0;
        led++;
        // Some gamepads like the DS3, DualSense, Nintendo Wii, Nintendo Switch
        // support changing the "Player LEDs": those 4 LEDs that usually
        // indicate the "gamepad seat". It is possible to change them by
        // calling:
        ctl->setPlayerLEDs(led & 0x0f);
    }

    if (ctl->x()) {
        // Some gamepads like DS3, DS4, DualSense, Switch, Xbox One S, Stadia
        // support rumble. It is possible to set it by calling: Some controllers
        // have two motors: "strong motor", "weak motor". It is possible to
        // control them independently.
        ctl->playDualRumble(0 /* delayedStartMs */, 250 /* durationMs */,
                            0x80 /* weakMagnitude */,
                            0x40 /* strongMagnitude */);
    }
}