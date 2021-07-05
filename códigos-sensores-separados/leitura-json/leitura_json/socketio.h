#ifndef SOCKETIO_H_
#define SOCKETIO_H_

#include <Arduino.h>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>
#include "usuarios.h"

void inicializa_socketIO();
void verifica_socketIO();
void download_usuarios();
void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length);

#endif
