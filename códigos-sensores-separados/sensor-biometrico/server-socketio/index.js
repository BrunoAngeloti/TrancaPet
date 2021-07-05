const app = require('express')()
const http = require('http').createServer(app)
const io = require('socket.io')(http)
var port = process.env.PORT || 4000;

io.on('connection', socket => {
    console.log("Nova conexão")
  
    socket.on('cadastrar_biometria', (info) => {
        console.log(info);
        io.emit('cadastrarbiometria', info);
    })  

    socket.on('deletar_biometria', (info) => {
        console.log(info);
        io.emit('deletarbiometria', info);
    })  
})
  
http.listen(port, function () {
    console.log('listening on *:' + port);
});