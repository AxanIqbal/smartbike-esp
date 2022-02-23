#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
// #include "firebase/firebase.h"
#include "fingerprint/fingerprint.h"
#include "websocket/websocket.h"

#define WIFI_SSID "ZONG MBB-E5573-79A8"
#define WIFI_PASSWORD "43825940"

unsigned long sendDataPrevMillis = 0;



IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

void setup()
{
  Serial.begin(115200);

  if (!WiFi.config(local_IP,gateway,subnet)) {
    Serial.println("STA Failed to configure");
  }

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

  pinMode(16, OUTPUT); //#D0 Finger lock

  initWebSocket();
  server.begin();
}

void loop()
{
  ws.cleanupClients();
  // ws.textAll();
  // if ( getFingerprintID() == 1)
  // {
  //   Serial.println("Congrats you are the owner");
  //   digitalWrite(16, HIGH);
  // }
}