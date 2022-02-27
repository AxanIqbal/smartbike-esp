#include "websocket.h"
#include "hardware/hardware.h"

void commandInstructions(char *data)
{
  ws.textAll(String(data));
}

void sendMessageToAll(bool sos = false) {
  const uint8_t size = JSON_OBJECT_SIZE(3);

  StaticJsonDocument<size> doc;

  doc["battery"] = analogRead(analogInPin);
  doc["charging"] = digitalRead(chargingPin);
  doc["sos"] = sos;

  char data[128];
  size_t len = serializeJson(doc, data);

  ws.textAll(data, len);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
  {
    data[len] = 0;
    commandInstructions((char *)data);
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
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

void sendSosToWeb()
{
  sendMessageToAll(true);
}

void initWebSocket()
{
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

unsigned long prevtime = 0;

void notifyClients()
{
  if (millis() - prevtime > 1000 || prevtime == 0)
  {
    prevtime = millis();

    sendMessageToAll();
  }
}