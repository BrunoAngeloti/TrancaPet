#include "sensor_rfid.h"
#include "socketio.h"
#include "wifi.h"

void setup(){
  inicializa_wifi();
  iniciaLeitor();
  inicializa_socketIO();
}

void loop(){
  verifica_socketIO();

  String content = leitura_cartao_rfid();
  if(content != ""){
    verifica_cartao_rfid_cadastrado(content);
  }
  
}
