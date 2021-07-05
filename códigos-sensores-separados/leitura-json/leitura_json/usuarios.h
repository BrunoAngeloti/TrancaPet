#ifndef USUARIOS_H_
#define USUARIOS_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Hash.h>
#include <FS.h>

void inicializa_arquivos_sistema();
void salvar_usuarios(String dados);
void salvar_dados_arquivos(String dados);
void baixar_dados_arquivos();

#endif
