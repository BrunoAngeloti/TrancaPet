#ifndef SOCKETIO_H_
#define SOCKETIO_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>
#include <Hash.h>
#include "rfid.h"
#include "biometria.h"
#include "usuarios.h"

void inicializa_socketIO();
void verifica_socketIO();
void download_usuarios();
void cadastrar_cartao(String cartao, int id);
void cadastrar_biometria(int biometria, int id);
void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length);
boolean passou_5_minutos_desconectado();

#endif
