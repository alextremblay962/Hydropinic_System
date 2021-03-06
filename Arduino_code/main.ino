/*
need for arduino plc shield
- RTC
- LDC display



*/

#include <ArduinoJson.h>

#define led 13
#define light1 2
#define light2 3
#define fan 4

void setup()
{
    Serial.begin(115200);
    pinMode(light1, OUTPUT);
    pinMode(light2, OUTPUT);
    pinMode(fan, OUTPUT);
}

void loop()
{
    if (Serial.available()) {
        String str = Serial.readStringUntil('\n');
        delay(50);
       // Serial.println(str);
        
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& root = jsonBuffer.parseObject(str);

        int payload = root["payload"];
        String topic = root["topic"];

        if (topic == "hydro/light1") {
            digitalWrite(light1, payload);
            delay(50);
            Serial.println("light1");

        } else if (topic == "hydro/light2") {
            digitalWrite(light2, payload);
            delay(50);
            Serial.println("light2");
        }

        else if (topic == "hydro/fan") {
            digitalWrite(fan, payload);
            delay(50);
            Serial.println("fan");
        }
        else{
            Serial.println("invalid");
        }
    }
}