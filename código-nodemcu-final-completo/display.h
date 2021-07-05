#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Arduino.h>
#include <Wire.h>
#include "SSD1306Wire.h"  
#include <brzo_i2c.h>
#include "SSD1306Brzo.h"
#include "rele.h"


// Optionally include custom images
#include "images.h"

void inicializa_display();
void imprime_nome(String nome);
void libera_tranca(String nome);

#endif
