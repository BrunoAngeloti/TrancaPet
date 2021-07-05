#include "wifi.h"

const char *ssid = "VIVOFIBRA-1C12";
const char *password = "33d7f81c12";


void inicializa_wifi(){
  Serial.begin(115200); // Inicia monitor Serial
  WiFi.begin(ssid, password); // Inicia WiFi
  
  Serial.print("Connecting");

  // ---------- Espera a conexão do WiFi ser feita ------------
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  
  // ---------- Imprime o endereço IP do WiFi ----------
  Serial.println("");
  Serial.println("WiFi conectado!");  
  Serial.println("Endereco IP: ");
  Serial.println(WiFi.localIP());
}
