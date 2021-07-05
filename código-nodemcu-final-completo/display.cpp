#include "display.h"

// Initialize the OLED display using brzo_i2c:
SSD1306Brzo display(0x3c, D1, D4);  // ADDRESS, SDA, SCL


#define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;

void inicializa_display(){
  display.init();

  display.clear();
  display.display();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  Serial.println("Display OLED inicializado");
  imprime_nome("Display on");
  delay(1500);
  
}

void limpa_display(){
  display.clear();
  display.display();
}

void imprime_nome(String nome){
  limpa_display();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, nome);
  
  // write the buffer to the display
  display.display();

  delay(3000);
  limpa_display();
}

void libera_tranca(String nome){
  limpa_display();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, nome);
  
  // write the buffer to the display
  display.display();

  aciona_rele();

  delay(2000);
  limpa_display();
}
