#ifndef BIOMETRIA_H_
#define BIOMETRIA_H_

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include "usuarios.h"
#include "display.h"
#include "socketio.h"

void inicializa_sensor_biometrico();
void inicializa_vetor_biometrias();
void add_biometria(int pos, int idBiometria);
int encontraPosicaoVazia();
void cadastraDigital(int idUser);
void deletaDigital(int x);
void leituraBiometrica();
void mostraDigitaisCadastradas();
int encontra_posicao_biometria(int idBiometria);

#endif
