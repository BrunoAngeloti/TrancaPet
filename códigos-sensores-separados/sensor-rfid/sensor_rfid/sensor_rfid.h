#ifndef sensor_rfid
#define sensor_rfid

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h> 
#include <MFRC522.h>

    void iniciaLeitor();
    void verifica_cartao_rfid_cadastrado(String content);
    void cadastrar_usuario(int ID);
    void deletar_usuario(int ID);
    String leitura_cartao(String fraseSerial);
    String leitura_cartao_rfid();

#endif
