#include "biometria.h"

const uint32_t password = 0x0;

// D2=TX, D3=RX
SoftwareSerial mySerial(D2, D3);

Adafruit_Fingerprint fingerprintSensor = Adafruit_Fingerprint(&mySerial, password);


void setupFingerprintSensor()
{
  
  //Inicializa o sensor
  fingerprintSensor.begin(57600);

  //Verifica se a senha está correta
  if(!fingerprintSensor.verifyPassword())
  {
    //Se chegou aqui significa que a senha está errada ou o sensor está problemas de conexão
    Serial.println(F("Não foi possível conectar ao sensor. Verifique a senha ou a conexão"));
    while(true);
  }
}
void cadastraDigital(int x)
{
  //Verifica se a posição é válida ou não
  if(x < 1 || x > 127)
  {
    //Se chegou aqui a posição digitada é inválida, então abortamos os próximos passos
    Serial.println(F("Posição inválida"));
    return;
  }

  Serial.println(F("Encoste o dedo no sensor"));

  //Espera até pegar uma imagem válida da digital
  while (fingerprintSensor.getImage() != FINGERPRINT_OK);
  
  //Converte a imagem para o primeiro padrão
  if (fingerprintSensor.image2Tz(1) != FINGERPRINT_OK)
  {
    //Se chegou aqui deu erro, então abortamos os próximos passos
    Serial.println(F("Erro image2Tz 1"));
    return;
  }
  
  Serial.println(F("Tire o dedo do sensor"));

  delay(2000);

  //Espera até tirar o dedo
  while (fingerprintSensor.getImage() != FINGERPRINT_NOFINGER);

  //Antes de guardar precisamos de outra imagem da mesma digital
  Serial.println(F("Encoste o mesmo dedo no sensor"));

  //Espera até pegar uma imagem válida da digital
  while (fingerprintSensor.getImage() != FINGERPRINT_OK);

  //Converte a imagem para o segundo padrão
  if(fingerprintSensor.image2Tz(2) != FINGERPRINT_OK)
  {
    //Se chegou aqui deu erro, então abortamos os próximos passos
    Serial.println(F("Erro image2Tz 2"));
    return;
  }

  //Cria um modelo da digital a partir dos dois padrões
  if(fingerprintSensor.createModel() != FINGERPRINT_OK)
  {
    //Se chegou aqui deu erro, então abortamos os próximos passos
    Serial.println(F("Erro createModel"));
    return;
  }

  //Guarda o modelo da digital no sensor
  if(fingerprintSensor.storeModel(x) != FINGERPRINT_OK)
  {
    //Se chegou aqui deu erro, então abortamos os próximos passos
    Serial.println(F("Erro storeModel"));
    return;
  }

  //Se chegou aqui significa que todos os passos foram bem sucedidos
  Serial.println(F("Sucesso!!!"));
}
void deletaDigital(int x)
{
  //Verifica se a posição é válida ou não
  if(x < 1 || x > 127)
  {
    //Se chegou aqui a posição digitada é inválida, então abortamos os próximos passos
    Serial.println(F("Posição inválida"));
    return;
  }

  //Apaga a digital nesta posição
  if(fingerprintSensor.deleteModel(x) != FINGERPRINT_OK)
  {
    Serial.println(F("Erro ao apagar digital"));
  }
  else
  {
    Serial.println(F("Digital apagada com sucesso!!!"));
  }
}
//funcao para ler uma digital e verificar se ela esta registrada

void leituraBiometrica() {
  uint8_t p = fingerprintSensor.getImage();
  if (p != FINGERPRINT_OK){
    return;
  }

  p = fingerprintSensor.image2Tz();
  if (p != FINGERPRINT_OK) {
    return;
  }

  p = fingerprintSensor.fingerFastSearch();
  if (p != FINGERPRINT_OK) {
    Serial.println("Biometria nao cadastrada");
    return;
  }
  
  //Encontrou uma digital!
  else {
      Serial.print("Biometria encontrada, ID: ");
      Serial.println(fingerprintSensor.fingerID);
  } 
}
