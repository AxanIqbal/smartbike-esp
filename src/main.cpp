#include "firebase/firebase.h"
#include "fingerprint/fingerprint.h"
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#define WIFI_SSID "WIFI_AP"
#define WIFI_PASSWORD "WIFI_PASSWORD"

unsigned long sendDataPrevMillis = 0;

void setup()
{
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  firebaseInit();
  FingerprintInit();
}

void loop()
{
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    Serial.print("Set int async... ");
    auth.token.uid.c_str();
        // for (size_t i = 0; i < 10; i++)
        // {

        // The purpose for this async function is to set, push and update data instantly but...

        //The async function is implemented by the library and not supported by Firebase.

        // When use this async function, the response will be ignored, then sometimes server may reject the subsequence requests or
        // full of receive buffer can be interrupted the async continuous operation.

        // You do not need to use these async functions in general usage.

        // Use library in Test Mode (see examples/Authentication/TestMode) or legacy database secret authentication,
        // the speed of data transfer will be increased.

        // Firebase.RTDB.setIntAsync(&fbdo, "/test/int", count);
        // count++;
        // }
        Serial.println("ok");
  }
}