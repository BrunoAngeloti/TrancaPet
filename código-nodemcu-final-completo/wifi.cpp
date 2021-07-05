#include "wifi.h"

const char *ssid = "VIVOFIBRA-1C12";
const char *password = "33d7f81c12";

void inicializa_wifi(){
  Serial.begin(115200); // Inicia monitor Serial
  WiFi.begin(ssid, password); // Inicia WiFi
  
  Serial.print("Connecting");
  int tentativas = 0;

  // ---------- Espera a conexão do WiFi ser feita ------------
  while (WiFi.status() != WL_CONNECTED && tentativas < 60){
    delay(500);
    tentativas++;
    Serial.print(".");
  }

  if(tentativas >= 60 ){
    Serial.println("Nao foi possivel conectar ao WiFi");
    return;
  }
  
  // ---------- Imprime o endereço IP do WiFi ----------
  Serial.println("");
  Serial.println("WiFi conectado!");  
  Serial.println("Endereco IP: ");
  Serial.println(WiFi.localIP());
}


boolean verifica_conexao_internet(){
  if (WiFi.status() == WL_CONNECTED){
    return true;
  }
  return false;
}
