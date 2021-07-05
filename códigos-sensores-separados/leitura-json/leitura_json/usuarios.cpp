#include "usuarios.h"

#define TAM 30 //quantidade média de pessoas no banco de dados

DynamicJsonDocument usuarios_json(1024);

static String cartoesCadastrados[TAM];
static String nomesCadastrados[TAM];
static String tamanho;

const char *filename = "/dados.txt"; //arquivo salvo no nodemcu

void inicializa_arquivos_sistema(){
  //Inicializando sistema de acesso a arquivo
  if (SPIFFS.begin())
  {
    Serial.println("SPIFFS Inicializado");
  }
  else
  {
    Serial.println("SPIFFS com problema de inicializacao");
  }
  delay(3000);
}


// pegar os dados em formato de string e separa eles para salvar no vetor
void salvar_usuarios(String dados){
  deserializeJson(usuarios_json, dados);

  for(int i = 0; i < usuarios_json.size(); i++){
    String nome = usuarios_json[i]["nome"];
    String cartao = usuarios_json[i]["cartao"];

    nomesCadastrados[i] = nome;
    cartoesCadastrados[i] = cartao;
    
    Serial.print(nomesCadastrados[i]);
    Serial.print(" - ");
    Serial.println(cartoesCadastrados[i]);
  }
}

void salvar_dados_arquivos(String dados){
  // ---------------ESCREVENDO NO ARQUIVO-------------------
  File f = SPIFFS.open(filename, "w");

  if (!f){
    Serial.println("Problema na abertura do arquivo");
  }else{
    //ESCRITA COMO STRING
    Serial.println("Escrevendo no arquivo como string");
    f.println(dados);
    Serial.println(dados);

    Serial.println("Dados salvos!!");
  }
  f.close();
  salvar_usuarios(dados);
}


void baixar_dados_arquivos(){
  Serial.println("LEITURA SEM INTERNET!");

  //---------------LENDO ARQUIVO---------------
  File f = SPIFFS.open(filename, "r");

  if (!f){
    Serial.println("Problema na leitura do arquivo");
  }else{
    Serial.println("Lendo dados do arquivo:");

    char vet[f.size() + 1];
    for (int i = 0; i < f.size(); i++)
    {
      vet[i] = (char)f.read();
    }
    String dados = vet;
    salvar_usuarios(dados);
    

    Serial.println("IMPRESSAO FEITA!");
   }
   
  f.close(); //Close file
  Serial.println("Fechando Arquivo");
}
