#include "hardware/hardware.h"
#include "websocket/websocket.h"
#include "fingerprint/fingerprint.h"

const char *ssid = "ZONG MBB-E5573-79A8";
const char *password = "43825940";

DynamicJsonDocument doc(1024);

int fingerLock = 0;

// Set your Static IP address
IPAddress local_IP(192, 168, 8, 110);
// Set your Gateway IP address
IPAddress gateway(192, 168, 8, 1);

IPAddress subnet(255, 255, 255, 0);
// IPAddress primaryDNS(8, 8, 8, 8);   //optional
// IPAddress secondaryDNS(8, 8, 4, 4); //optiona

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void setup()
{
  Serial.begin(115200);

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  // Connect to Wi-Fi

  // Hardware Configs
  pinMode(shockSensor, INPUT);
  pinMode(sosCancel, INPUT);
  pinMode(chargingPin, INPUT);
  pinMode(lockPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Start server
  server.begin();

  FingerprintInit();
}

void loop()
{
  ws.cleanupClients();
  notifyClients();
  hardwareLoop();
  if (getFingerprintID() == 1)
  {
    if (fingerLock == 0)
    {
      digitalWrite(lockPin, HIGH);
      fingerLock = 1;
    }
    else
    {
      digitalWrite(lockPin, LOW);
      fingerLock = 0;
    }
  }
}