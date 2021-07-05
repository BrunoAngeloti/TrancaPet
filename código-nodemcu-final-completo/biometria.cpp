#include "biometria.h"

#define TAM 30 //quantidade média de pessoas no banco de dados
static int idsBiometria[TAM];

const uint32_t password = 0x0;

// D2=TX, D3=RX
SoftwareSerial mySerial(D2, D3);

Adafruit_Fingerprint fingerprintSensor = Adafruit_Fingerprint(&mySerial);


void inicializa_sensor_biometrico()
{
  
  //Inicializa o sensor
  fingerprintSensor.begin(57600);

  //Verifica se a senha está correta
  if(!fingerprintSensor.verifyPassword())
  {
    //Se chegou aqui significa que a senha está errada ou o sensor está problemas de conexão
    Serial.println(F("Não foi possível conectar ao sensor biometrico. Verifique a senha ou a conexão"));
    while(true);
  }
  Serial.println("Sensor biometrico inicializado");
  delay(1500);
}


void inicializa_vetor_biometrias(){
  for (int i = 0; i < TAM-1; i++) {
    idsBiometria[i] = -1;
  }
}

void add_biometria(int pos, int idBiometria){
  idsBiometria[pos] = idBiometria;
  Serial.println("Biometria adicionada");
}


int encontra_posicao_biometria(int idBiometria){
  for (int i = 0; i < TAM-1; i++) {
    if(idsBiometria[i] == idBiometria){
      return i;
    }
  }
  return -1;
}


int encontraPosicaoVazia(){

  uint8_t p;
  uint8_t id = 0;
  
  for(int i = 0; i<127; i++, id++){

    p = fingerprintSensor.loadModel(id);
    
    if (p == FINGERPRINT_OK) {
      Serial.print(F("Digital com ID #"));
      Serial.print(id);
      Serial.println(F(" cadastrado"));
    }
    else {
      return i;
    }
  }
  return -1;
}


void cadastraDigital(int idUser)
{

  int x = encontraPosicaoVazia();
  
  //Verifica se a posição é válida ou não
  if(x < 0 || x > 127)
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
  cadastrar_biometria(x, idUser);
}


void deletaDigital(int x)
{
  //Verifica se a posição é válida ou não
  if(x < 0 || x > 127)
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
    imprime_nome("NEGADO");
    return;
  }
  
  //Encontrou uma digital!
  else {
      libera_tranca("LIBERADO");
      Serial.print("Biometria encontrada, ID: ");
      Serial.println(fingerprintSensor.fingerID);
      int pos = encontra_posicao_biometria(fingerprintSensor.fingerID);
      if(pos != -1){
        imprime_nome(pega_nome_usuario(pos));
      }
  } 

}

void mostraDigitaisCadastradas(){
  
//funcao para mostrar as digitais ja cadastradas

  uint8_t p;
  uint8_t id = 0;
  
  for(int i = 0; i<127; i++, id++){

    p = fingerprintSensor.loadModel(id);
    
    if (p == FINGERPRINT_OK) {
      Serial.print(F("Digital com ID #"));
      Serial.print(id);
      Serial.println(F(" cadastrado"));
    }
  }
}
