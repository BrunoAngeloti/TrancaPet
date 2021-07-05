import './App.css';
import io from 'socket.io-client'
import { useEffect } from 'react'

const socket = io.connect('http://localhost:4000')

function App() {


  useEffect(() => {
    socket.on('mensagem', (info) => {
      console.log(info)
    })
  })

  function enviarMensagem(){
    socket.emit('dados', "Hello World");
  }


  return (
    <div className="App">
      <header className="App-header">
        <button onClick={() => enviarMensagem()}>Enviar</button>
      </header>
    </div>
  );
}

export default App;
