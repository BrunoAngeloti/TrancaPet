#include "socketio.h"

SocketIOclient socketIO;

void inicializa_socketIO(){
  // endereco do servidor e a porta
    socketIO.begin("192.168.15.3", 4000);

    // event handler
    socketIO.onEvent(socketIOEvent);
}

// funcao para verficar se chegou alguma informacao do socketIO
void verifica_socketIO(){
  socketIO.loop();
}

// emite um chamado para o servidor
void pegarDados() {
    String output= "[\"usuarios\"]";
    socketIO.sendEVENT(output);
}

// pegar os dados em formato de string e separa eles para salvar no vetor
void salvarDados(String dados){
  DynamicJsonDocument doc1(1024);
  deserializeJson(doc1, dados);

  String nome1 = doc1[0]["nome"];

  Serial.println(nome1);
  
}

// funcao do socketIO que fica verificando a conexao com o servidor e se chegou algo de la
void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case sIOtype_DISCONNECT:
            Serial.printf("[IOc] Disconnected!\n");
            break;
        case sIOtype_CONNECT:
            Serial.printf("[IOc] Connected to url: %s\n", payload);

            // join default namespace (no auto join in Socket.IO V3)
            socketIO.send(sIOtype_CONNECT, "/");
            pegarDados();
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

            if(comando == "ultimos_dados"){
              salvarDados(informacao);
            }
                       
            break;
    }
}
