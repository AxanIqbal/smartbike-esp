
#ifndef Websocket_h
#define Websocket_h

#if defined(ESP32)
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

void initWebSocket();
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

#endif