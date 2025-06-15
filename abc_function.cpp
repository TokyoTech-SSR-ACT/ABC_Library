#include "abc_function.hpp"

HardwareSerial Debug_Serial(0);  // Use USB
HardwareSerial RS485_Serial(1);  // Use IO32, & IO33
HardwareSerial Servo_Serial(2);  // Use IO16, & IO17

namespace ABC {

double battery_voltage = 0.0;
double Battery_Voltage_ScaleFactor = 1.0;
const double max_battery_boltage = 4.2 * BATTERY_S_NO;
const double min_battery_voltage = 3.5 * BATTERY_S_NO;

void PIN_SETUP(void) {
    pinMode(BATTERY_VOLTAGE_PIN, INPUT);
    pinMode(SWITCH_LED_R_PIN, OUTPUT);
    pinMode(SWITCH_LED_G_PIN, OUTPUT);
    pinMode(SWITCH_LED_B_PIN, OUTPUT);
    ledcSetup(pwmch_Speaker, 1000, 8);  // 1kHz frequency, 8-bit resolution
    ledcAttachPin(SPEAKER_PIN,
                  pwmch_Speaker);  // Attach the speaker pin to the PWM channel
    ledcWrite(pwmch_Speaker, 0);   // Initialize the speaker to off

    // Initialize ADC
    analogSetWidth(12);
    analogSetAttenuation(ADC_11db);

    // Initialize EEPROM
    EEPROM.begin(64);  // allocate 64 bytes

    // Load previous scaleFactor if available
    EEPROM.get(EEPROM_ADDR, Battery_Voltage_ScaleFactor);
    if (isnan(Battery_Voltage_ScaleFactor) ||
        Battery_Voltage_ScaleFactor < 0.5 ||
        Battery_Voltage_ScaleFactor > 2.0) {
        Battery_Voltage_ScaleFactor = 1.0;  // fallback
    }
}

void PW_Switch_LED(bool R, bool G, bool B) {
    digitalWrite(SWITCH_LED_R_PIN, R ? HIGH : LOW);
    digitalWrite(SWITCH_LED_G_PIN, G ? HIGH : LOW);
    digitalWrite(SWITCH_LED_B_PIN, B ? HIGH : LOW);
}

void Battery_Voltage_Calibration(double R10, double R11) {
    // EEPROMから設定値を読み込む
    Debug_Serial.println("=== Welcome to Batery Voltage Calibration Mode ===");
    Debug_Serial.println(
        "Please input the actual battery voltage (in volts, e.g., 7.40):");

    while (!Debug_Serial.available()) {
        delay(100);
    }

    String input = Debug_Serial.readStringUntil('\n');
    float actualVoltage = input.toFloat();

    int adc_raw = analogRead(BATTERY_VOLTAGE_PIN);
    float measuredVoltage = (adc_raw / 4095.0) * 3.3 * (R10 + R11) / R11;

    Battery_Voltage_ScaleFactor = actualVoltage / measuredVoltage;

    // Save to EEPROM
    EEPROM.put(EEPROM_ADDR, Battery_Voltage_ScaleFactor);
    EEPROM.commit();

    Debug_Serial.printf(
        "Battery Voltage Calibration complete! Scale factor: %.4f\n",
        Battery_Voltage_ScaleFactor);
}

bool Check_Battery_Voltage(double R10, double R11) {
    battery_voltage = Battery_Voltage_ScaleFactor *
                      (3.3 * analogRead(BATTERY_VOLTAGE_PIN) / 4095) *
                      (R10 + R11) / R11;
    // Debug_Serial.printf("Raw ADC Value: %d\n",
    // analogRead(BATTERY_VOLTAGE_PIN)); Debug_Serial.printf("Battery Voltage:
    // %.2f V\n", battery_voltage);
    if (max_battery_boltage < battery_voltage ||
        battery_voltage < min_battery_voltage) {
        return 1;
    } else {
        return 0;
    }
}

void Serial_Begin(uint32_t DS_rate, uint32_t RS_rate, uint32_t SS_rate) {
    // Debug Serial
    Debug_Serial.begin(DS_rate);
    Debug_Serial.setTimeout(1000);  // タイムアウトを1秒に設定
    Debug_Serial.println("Debug Serial initialized.");
    RS485_Serial.begin(RS_rate, SERIAL_8N1, U1RXD_PIN, U1TXD_PIN);
    RS485_Serial.setTimeout(1000);  // タイムアウトを1秒に設定
    Debug_Serial.println("RS485 Serial initialized.");
    Servo_Serial.begin(SS_rate);
    Servo_Serial.setTimeout(1000);  // タイムアウトを1秒に設定
    Debug_Serial.println("Servo Serial initialized.");
}
}  // namespace ABC