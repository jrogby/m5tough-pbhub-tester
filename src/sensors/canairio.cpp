#include "main.h"
#include <Sensors.hpp>

void printSensorsDetected() {
    uint16_t numSensors =  sensors.getSensorsRegisteredCount();
    uint16_t numUnits   =  sensors.getUnitsRegisteredCount();
    M5.Lcd.println("Detected sensors: " + String(numSensors) + "    units= " + String(numUnits));
    Serial.println("Detected\tsensors: " + String(numSensors) + "\tunits=" + String(numUnits));

    Serial.print("Sensors\t[ ");
    M5.Lcd.print("Sensors [ ");
    int i = 0;
    while (sensors.getSensorsRegistered()[i++] != 0) {

        M5.Lcd.print(sensors.getSensorName((SENSORS)sensors.getSensorsRegistered()[i - 1]));
        M5.Lcd.print(" ");

        Serial.print(sensors.getSensorName((SENSORS)sensors.getSensorsRegistered()[i - 1]));
        Serial.print(" ");
    }
    Serial.print("]\n");
    M5.Lcd.print("]\n");
}

void printSensorsValues() {
    UNIT unit = sensors.getNextUnit();
    while(unit != UNIT::NUNIT) {
        String uName = sensors.getUnitName(unit);
        float uValue = sensors.getUnitValue(unit);
        String uSymb = sensors.getUnitSymbol(unit);
        Serial.println(" " + uName + "  \t:  " + String(uValue) + " " + uSymb);
        M5.Lcd.println(" " + uName + "  \t:  " + String(uValue) + " " + uSymb);
        unit = sensors.getNextUnit();
    }
}

void onSensorDataOk() {
    M5.Speaker.tone(691.995, 5);
    M5.Lcd.startWrite();
    //M5.Lcd.println("--Sensor data read--");
    printSensorsValues();
    M5.Lcd.endWrite();
}

void onSensorDataError(const char * msg){
    M5.Lcd.setTextColor(TFT_RED);
    Serial.println(msg);
    M5.Lcd.println(msg);
    M5.Lcd.setTextColor(TFT_GREEN);
}

void canairioInitSensors() {
    M5.Lcd.println("Detecting sensors..");
    Serial.println("Detecting sensors..");
    sensors.setSampleTime(5);
    sensors.setOnDataCallBack(&onSensorDataOk);
    sensors.setOnErrorCallBack(&onSensorDataError);
    sensors.setDebugMode(false);
    sensors.detectI2COnly(true);
    sensors.init(); // Auto detection to UART and i2c sensors
    printSensorsDetected();
}


void canairioReadSensors() {
    sensors.loop();  // read sensor data and showed it
}
