//#include "rfid.h"
#include "biometria.h"
#include "usuarios.h"
#include "display.h"
#include "socketio.h"
#include "wifi.h"

int ja_baixou_arquivos = 0;

void setup(){
  inicializa_rele();
  inicializa_wifi();
  inicializa_sensor_biometrico();
  inicializa_sensor_rfid();
  inicializa_display();
  inicializa_arquivos_sistema();
  inicializa_socketIO();
}

void loop(){
  verifica_socketIO();

  // BIOMETRIA
  leituraBiometrica(); //funcao para ler a biometria

  // CARTAO
  String content = leitura_cartao_rfid();
  if(content != ""){
    verifica_cartao_rfid_cadastrado(content);
  }

  // JSON e SOCKETIO
  if(verifica_conexao_internet()){
    verifica_socketIO();
  }
  else if(ja_baixou_arquivos == 0) {
    Serial.println("Sem Internet");
    baixar_dados_arquivos();
    ja_baixou_arquivos = 1;
  }
  
}
