#include "socketio.h"

SocketIOclient socketIO;

static int ja_baixou_arquivos = 0;
static int desconectado = 0;
static int contador = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const long intervalo = 300000;

void inicializa_socketIO(){
  // endereco do servidor e a porta
    socketIO.begin("192.168.15.14", 4000);
//  socketIO.begin("server-tranca.herokuapp.com", 80);

  // event handler
  socketIO.onEvent(socketIOEvent);
  delay(1500);
}

// funcao para verficar se chegou alguma informacao do socketIO
void verifica_socketIO(){
  if(contador >= 5){
    if(ja_baixou_arquivos == 0){
      baixar_dados_arquivos();
      ja_baixou_arquivos = 1;
    }
    if(passou_5_minutos_desconectado() == false){
      return;
    }
  }
  socketIO.loop();
}

boolean passou_5_minutos_desconectado(){
  if(previousMillis == 0){
    previousMillis = millis();
  }
  currentMillis = millis();
  if (currentMillis - previousMillis >= intervalo) {
    previousMillis = 0;
    contador = 0;
    return true;
  }
  return false;
}

// emite um chamado para o servidor
void download_usuarios() {
    String output= "[\"downloadusuarios\"]";
    socketIO.sendEVENT(output);
}

void cadastrar_cartao(String cartao, int id) {
    // creat JSON message for Socket.IO (event)
    DynamicJsonDocument doc(1024);
    JsonArray array = doc.to<JsonArray>();
    
    // add evnet name
    // Hint: socket.on('event_name', ....
    array.add("atualizar_cartao");

    // add payload (parameters) for the event
    JsonObject param1 = array.createNestedObject();
    param1["card"] = cartao;
    param1["id"] = id;

    // JSON to String (serializion)
    String output;
    serializeJson(doc, output);

    // Send event        
    socketIO.sendEVENT(output);
}


void cadastrar_biometria(int biometria, int id) {
    // creat JSON message for Socket.IO (event)
    DynamicJsonDocument doc(1024);
    JsonArray array = doc.to<JsonArray>();
    
    // add evnet name
    // Hint: socket.on('event_name', ....
    array.add("atualizar_biometria");

    // add payload (parameters) for the event
    JsonObject param1 = array.createNestedObject();
    param1["biometria"] = biometria;
    param1["id"] = id;

    // JSON to String (serializion)
    String output;
    serializeJson(doc, output);

    // Send event        
    socketIO.sendEVENT(output);
}


// funcao do socketIO que fica verificando a conexao com o servidor e se chegou algo de la
void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case sIOtype_DISCONNECT:
            Serial.printf("[IOc] Desconectado do servidor!\n");
            desconectado = 1;
            contador++;
            break;
        case sIOtype_CONNECT:
            Serial.printf("[IOc] Connected to url: %s\n", payload);

            desconectado = 0;
            contador = 0;
            // join default namespace (no auto join in Socket.IO V3)
            socketIO.send(sIOtype_CONNECT, "/");
            download_usuarios();
            break;
        case sIOtype_EVENT:
            String text = String((char *)&payload[0]);
            String comando = "";
            String informacao = "";
            int tam = text.length();
            int pos = 0;

//            Serial.println(tam);
//            Serial.println(text);

            while(text[pos] != ',' && pos < tam){
              pos++;
            }
            comando = text.substring(2, pos-1);
//            Serial.println(comando);

            informacao = text.substring(pos+1, tam-1); 
            Serial.println(informacao);

            if(comando == "cadastrarcartao"){
              leitura_cartao("Esperando Cartao Para Cadastro", informacao.toInt());
//              cadastrar_usuario(informacao.toInt());
            }
            else if(comando == "cadastrarbiometria"){
              Serial.println(informacao.toInt());
              cadastraDigital(informacao.toInt());
            }
            else if(comando == "deletarbiometria"){
              Serial.println(informacao.toInt());
              deletaDigital(informacao.toInt());
            }
            else if(comando == "download_usuarios"){
              inicializa_vetores_usuarios();
              inicializa_vetor_cartoes();
              inicializa_vetor_biometrias();
              salvar_dados_arquivos(informacao);
              ja_baixou_arquivos = 1;
            }


                       
            break;
    }
}
