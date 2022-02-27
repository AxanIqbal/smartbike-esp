#include "hardware.h"
#include "websocket/websocket.h"

int present_condition = 1;

void sendSos()
{
    const unsigned long prevtime = millis();
    while (millis() - prevtime <= 10000)
    {
        if (digitalRead(sosCancel) == HIGH)
        {
            Serial.println("Canceled");
            return;
        }
        delay(200);
    }
    Serial.println("Sent");
    sendSosToWeb();
}

void hardwareLoop()
{
    present_condition = digitalRead(shockSensor);
    if (present_condition != HIGH)
    {
        Serial.println("Accident Detected... Sending sos notification in 10 sec");
        sendSos();
    }
}