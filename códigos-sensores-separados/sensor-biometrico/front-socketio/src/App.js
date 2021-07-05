import './App.css';
import io from 'socket.io-client'
import { useEffect } from 'react'

// const socket = io.connect('http://localhost:4000')
const socket = io.connect('https://server-tranca.herokuapp.com/')

function App() {

  useEffect(() => {
    socket.on('mensagem', (info) => {
      console.log(info)
    })
  })

  function cadastrarBiometria(id){
    socket.emit('cadastrar_biometria', id)
  }

  function deletarBiometria(id){
    socket.emit('deletar_biometria', id)
  }

  return (
    <div className="App">
      <header className="App-header">
        <div className="card">
          <p>André Cunha</p>
          <button onClick={() => cadastrarBiometria(1)}>Cadastrar Biometria</button>
          <button onClick={() => deletarBiometria(1)}>Deletar Biometria</button>
        </div>

        <div className="card">
          <p>Joana</p>
          <button onClick={() => cadastrarBiometria(2)}>Cadastrar Biometria</button>
          <button onClick={() => deletarBiometria(2)}>Deletar Biometria</button>
        </div>

        <div className="card">
          <p>Bruno</p>
          <button onClick={() => cadastrarBiometria(3)}>Cadastrar Biometria</button>
          <button onClick={() => deletarBiometria(3)}>Deletar Biometria</button>
        </div>
        
      </header>
    </div>
  );
}

export default App;
