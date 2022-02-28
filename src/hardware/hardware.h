#ifndef Hardware_h
#define Hardware_h

#include <ESP8266WiFi.h>

const int analogInPin = A0; // input analog
const int shockSensor = D2; // input
const int sosCancel = D1;   // input
const int chargingPin = D5; // input
const int lockPin = D4;     // output

void sendSos();
void hardwareLoop();

#endif