#ifndef SOCKETIO_H_
#define SOCKETIO_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>
#include <Hash.h>
#include "sensor_rfid.h"

void inicializa_socketIO();
void verifica_socketIO();
void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length);

#endif
