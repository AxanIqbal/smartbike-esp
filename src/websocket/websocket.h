#ifndef WebSocket_h
#define WebSocket_h

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

void initWebSocket();
void notifyClients();
void sendSosToWeb();

extern AsyncWebServer server;
extern AsyncWebSocket ws;

#endif