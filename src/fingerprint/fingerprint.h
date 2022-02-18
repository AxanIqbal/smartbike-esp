
#ifndef Fingerprint_h
#define Fingerprint_h

#include <Adafruit_Fingerprint.h>

void FingerprintInit();
uint8_t getFingerprintID();
uint8_t getFingerprintEnroll(uint8_t id);

#endif