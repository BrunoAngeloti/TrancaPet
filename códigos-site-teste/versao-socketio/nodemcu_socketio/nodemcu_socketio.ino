#include "socketio.h"
#include "wifi.h"


void setup() {
  inicializa_wifi();
  inicializa_socketIO();
}

void loop() {
  verifica_socketIO();
}
