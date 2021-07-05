#define SS_PIN D4  //PINO SDA
#define RST_PIN D1 //PINO DE RESET

#include "sensor_rfid.h"

// Cria instancia MFRC522 (Leitor de cartão RFID).
MFRC522 mfrc522(SS_PIN, RST_PIN);

// ---------- Variáveis de armanezamento dos cadastrados ----------
#define tamCadastrados 30
static String cartoesCadastrados[tamCadastrados];

void iniciaLeitor(){
  SPI.begin();        // Inicia SPI bus
  mfrc522.PCD_Init(); 
  Serial.println("Sensor RFID inicializado");
}


void verifica_cartao_rfid_cadastrado(String content){
  
  // -------------- Faz a varredura para encontrar o cartão lido no vetor de cartões cadastrados --------------
  for (int i = 0; i < tamCadastrados-1; i++) {
    if (content.substring(1) == cartoesCadastrados[i]){
      Serial.println("-------------- Access Granted --------------");
      Serial.println("------------- Welcome Linda(o) -------------");
      delay(3000);
      return;
    }
  }
  Serial.println("-------------- Access Denied --------------");
  delay(3000);
 
}


// ---------- Função usada para ler o RFID, retorna o valor do mesmo no formato String ----------
String leitura_cartao(String fraseSerial){
  String content = "";
  
  while (1){
    delay(500);
    Serial.println(fraseSerial);
    
    // Procura por novos cartões
    if (!mfrc522.PICC_IsNewCardPresent()){
      continue;
    }
    
    // Seleciona um dos cartões
    if (!mfrc522.PICC_ReadCardSerial()){
      continue;
    }
    break;
  }
 
  for (byte i = 0; i < mfrc522.uid.size; i++){
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  return content;
}

//---------- Função chamada para cadastrar novo usuario ----------
void cadastrar_usuario(int ID){
  String content = leitura_cartao("Esperando Cartao Para Cadastro");

  //---------- Adiciona o cartão no vetor de cadastrados e aumenta 1 em seu índice ----------
  cartoesCadastrados[ID] = content.substring(1);
  
  Serial.println("Cadastrado");
}

//---------- Função chamada para deletar novo usuario ----------
void deletar_usuario(int ID){
  cartoesCadastrados[ID] = "";
  Serial.println("Deletado");
}

String leitura_cartao_rfid(){
  
  // Procura por novos cartões
  if (!mfrc522.PICC_IsNewCardPresent()){
    return "";
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()){
    return "";
  }
  
  // ----------- LEITURA DO CARTÃO -------------

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++){
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();
  return content;
}
