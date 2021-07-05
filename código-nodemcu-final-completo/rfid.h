#ifndef RFID_H_
#define RFID_H_

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h> 
#include <MFRC522.h>
#include "usuarios.h"
#include "display.h"
#include "socketio.h"

    void inicializa_sensor_rfid();
    void inicializa_vetor_cartoes();
    void verifica_cartao_rfid_cadastrado(String content);
    void deletar_usuario(int ID);
    void leitura_cartao(String fraseSerial, int id);
    String leitura_cartao_rfid();
    void add_cartao(int ID, String cartao);

#endif
