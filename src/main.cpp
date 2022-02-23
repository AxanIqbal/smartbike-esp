// #include "firebase/firebase.h"
#include "fingerprint/fingerprint.h"
#if defined(ESP32)
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

#define WIFI_SSID "ZONG MBB-E5573-79A8"
#define WIFI_PASSWORD "43825940"

unsigned long sendDataPrevMillis = 0;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void notifyClients() {
  // ws.textAll(String(ledState));
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    // if (strcmp((char*)data, "toggle") == 0) {
    //   ledState = !ledState;
    //   notifyClients();
    // }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

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

  pinMode(16, OUTPUT); //#D0 Finger lock

  initWebSocket();
  server.begin();
  // wifiServer.begin();
  // firebaseInit();
  // FingerprintInit();
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
  

  // WiFiClient client = wifiServer.available();
  // String command;
  
  // if (client)
  // {
  //   while (client.connected())
  //   {
  // //     command = client.readStringUntil('\n');
  //     while (client.available() > 0)
  //     {
        
  //       char c = client.read();

  //       if (c == '\n' || int(c) == 13)
  //       {
  //         break;
  //       }

  //       // if (c == '')
  //       // {
  //       //   Serial.println("You hace entered space");
  //       // }
        
        
  //       command += c;
  //       Serial.print(c);
  //     }
  //     client.flush();
  //     delay(10);
  //     if (command.compareTo(String("AHSAN")) == 0)
  //     {
  //       Serial.println("doing the test");
  //       client.write("doing the test");
  //     }else if (command != "")
  //     {
  //       Serial.println();
  //       Serial.println(command);
  //       Serial.println(command.compareTo(String("TAHA")));
  //       Serial.println(command.equals("TAHA"));
  //     }
  // //     getFingerprintID();
  //     command = "";
  //   }
  //   client.stop();
  //   Serial.println("Client disconnected");
  // }

  // if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  // {
  //   sendDataPrevMillis = millis();

  //   Serial.print("Set int async... ");
  //   auth.token.uid.c_str();
  // for (size_t i = 0; i < 10; i++)
  // {

  // The purpose for this async function is to set, push and update data instantly but...

  // The async function is implemented by the library and not supported by Firebase.

  // When use this async function, the response will be ignored, then sometimes server may reject the subsequence requests or
  // full of receive buffer can be interrupted the async continuous operation.

  // You do not need to use these async functions in general usage.

  // Use library in Test Mode (see examples/Authentication/TestMode) or legacy database secret authentication,
  // the speed of data transfer will be increased.

  // Firebase.RTDB.setIntAsync(&fbdo, "/test/int", count);
  // count++;
  // }
  //       Serial.println("ok");
  // }
}