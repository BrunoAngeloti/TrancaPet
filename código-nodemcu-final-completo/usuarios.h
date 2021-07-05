#ifndef USUARIOS_H_
#define USUARIOS_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Hash.h>
#include <FS.h>
#include "rfid.h"

void inicializa_arquivos_sistema();
void inicializa_vetores_usuarios();
void salvar_usuarios(String dados);
void salvar_dados_arquivos(String dados);
void baixar_dados_arquivos();
String pega_nome_usuario(int id);

#endif
