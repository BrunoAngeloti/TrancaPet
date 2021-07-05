#ifndef biometria_h
#define biometria_h

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

void setupFingerprintSensor();
void cadastraDigital(int x);
void deletaDigital(int x);
void leituraBiometrica();

#endif
