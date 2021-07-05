const app = require('express')()
const http = require('http').createServer(app)
const io = require('socket.io')(http)
var port = process.env.PORT || 4000;

io.on('connection', socket => {
    console.log("Nova conexão")
  
    socket.on('cadastrar_cartao', (info) => {
        console.log(info);
        io.emit('cadastrarcartao', info);
    })  

    socket.on('deletar_cartao', (info) => {
        console.log(info);
        io.emit('deletarcartao', info);
    })  
})
  
http.listen(port, function () {
    console.log('listening on *:' + port);
});
