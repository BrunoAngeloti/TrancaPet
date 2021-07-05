const app = require('express')()
const http = require('http').createServer(app)
const io = require('socket.io')(http)
var port = process.env.PORT || 4000;

let dados = [
{
    nome: "André Cunha",
    cartao: "32:80:CD:F2"
},
{
    nome: "André Louis",
    cartao: "12:30:CW:G2"
},
{
    nome: "Bruno",
    cartao: "01:02:03:04"
},
{
    nome: "Emerson",
    cartao: "1E:1B:2A:61"
},  
{
    nome: "Ultima Pessoa",
    cartao: "11:22:33:44"
},           
]

io.on('connection', socket => {
    console.log("Nova conexão")

    //socket.emit('mensagem', dados)

    socket.on('usuarios', () => {
        console.log("Pediu os dados dos usuários");
        socket.emit('ultimos_dados', dados);
    })
  
    socket.on('dados', (info) => {
        console.log(info);
        io.emit('mensagem', info);
    })  
})
  
http.listen(port, function () {
    console.log('listening on *:' + port);
});