#include "socketio.h"
#include "usuarios.h"
#include "wifi.h"

int ja_baixou_arquivos = 0;

void setup() {
  inicializa_wifi();
  inicializa_socketIO();
  inicializa_arquivos_sistema();
}

void loop() {
  if(verifica_conexao_internet()){
    verifica_socketIO();
  }
  else if(ja_baixou_arquivos == 0) {
    ja_baixou_arquivos++;
    baixar_dados_arquivos();
  }
}
