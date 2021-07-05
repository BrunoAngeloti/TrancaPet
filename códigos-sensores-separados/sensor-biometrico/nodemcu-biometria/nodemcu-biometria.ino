#include "biometria.h"
#include "wifi.h"
#include "socketio.h"

int idVerifica;

void setup() {
  inicializa_wifi();
  inicializa_socketIO();
  setupFingerprintSensor();
}

void loop() {
  verifica_socketIO();
  
  leituraBiometrica(); //funcao para ler a biometria

}
