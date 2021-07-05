#include "rele.h"

#define RELE D8

void inicializa_rele(){
    pinMode(RELE, OUTPUT);
    digitalWrite(RELE, LOW);
    delay(250);
}

void aciona_rele(){
  digitalWrite(RELE, HIGH);
  delay(300);
  digitalWrite(RELE, LOW);
}
