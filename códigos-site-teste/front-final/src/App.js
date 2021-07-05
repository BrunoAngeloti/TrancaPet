import './App.css';
import io from 'socket.io-client'
import { useEffect } from 'react'

const socket = io.connect('http://localhost:4000')
//const socket = io.connect('https://server-tranca.herokuapp.com/')

function App() {

  useEffect(() => {
    socket.on('mensagem', (info) => {
      console.log(info)
    })
  })

  function cadastrarCartao(id){
    socket.emit('cadastrar_cartao', id)
  }

  function deletarCartao(id){
    socket.emit('deletar_cartao', id)
  }

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
          <button onClick={() => cadastrarCartao(0)}>Cadastrar cartao</button>
          <button onClick={() => deletarCartao(0)}>Deletar cartao</button>
          <button onClick={() => cadastrarBiometria(0)}>Cadastrar Biometria</button>
          <button onClick={() => deletarBiometria(0)}>Deletar Biometria</button>
        </div>

        <div className="card">
          <p>André Louis</p>
          <button onClick={() => cadastrarCartao(1)}>Cadastrar cartao</button>
          <button onClick={() => deletarCartao(1)}>Deletar cartao</button>
          <button onClick={() => cadastrarBiometria(1)}>Cadastrar Biometria</button>
          <button onClick={() => deletarBiometria(1)}>Deletar Biometria</button>
        </div>

        <div className="card">
          <p>Bruno</p>
          <button onClick={() => cadastrarCartao(2)}>Cadastrar cartao</button>
          <button onClick={() => deletarCartao(2)}>Deletar cartao</button>
          <button onClick={() => cadastrarBiometria(2)}>Cadastrar Biometria</button>
          <button onClick={() => deletarBiometria(2)}>Deletar Biometria</button>
        </div>
        
      </header>
    </div>
  );
}

export default App;
