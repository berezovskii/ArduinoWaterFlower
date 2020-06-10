#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

const int groundSensonPin = 0;
const int minGroundSensorValue = 563;
const int maxGroundSensorValue = 295;
const int delayValue = 1000;
const int maxPersentageValue = 268;
const int groundHumidityMinValue = 20;
const int groundHumidityMaxValue = 60;
const int pumpPin = 4;
bool isPumpEnabled = false;
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void DisplayHumidity(String text);
int GetGroundHumidity();
void TurnOnPump();
void TurnOffPump();

void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT);
    pinMode(pumpPin, OUTPUT);
    lcd.init();
    lcd.backlight();
}

void loop() {
    int groundHumidity = GetGroundHumidity();
    DisplayHumidity("hello");

    if(groundHumidity < groundHumidityMinValue)
    {
        TurnOnPump();
    } else if(isPumpEnabled){
        TurnOffPump();
    }
}

int GetGroundHumidity(){
    int currentValue = analogRead(groundSensonPin);
    int percentage = (563 - currentValue) / 2.68;
    Serial.println(percentage);
    delay(delayValue);

    return percentage;
}

void TurnOnPump(){
    isPumpEnabled = true;
    digitalWrite(pumpPin, HIGH);
}

void TurnOffPump(){
    isPumpEnabled = false;
    digitalWrite(pumpPin, LOW);
}

void DisplayHumidity(String text){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println(text);
}
