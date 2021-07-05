const app = require('./app');
const User = require('./models/User');
const http = require('http').createServer(app)
const io = require('socket.io')(http)
const port = process.env.PORT || 4000;

io.on('connection', socket => {
    console.log("Nova conexão")

    async function getUsers(){
        // chamar nossa funcao que retorna os dados
        const users = await User.findAll();
        await users.sort(function(a, b) {
            if(a.id < b.id) {
              return -1;
            } else {
              return true;
            }
          });
        io.emit('download_usuarios', users);
    }

    //----------- funcoes dos dados -----------
    socket.on('downloadusuarios', async () => {
        console.log("Pediu dados dos usuarios");
        getUsers();
    })

    socket.on('create_user', async (nameUser) => {
        console.log("Criou novo usuário");
        try{
            // cria um novo usuário
            await User.create({ name: nameUser, biometry: -1 });

            getUsers();
            return io.emit('status', "ok");
        } catch (error) {
            return io.emit('status', error);
        }
    })

    socket.on('delete_user', async (id) => {
        console.log("Deletando um usuário");
        try{
            const user = await User.findByPk(id);

            if (!user) return io.emit('status', "Usuário não encontrado");
            await user.destroy();

            getUsers();
            return io.emit('status', "ok");
        } catch (error) {
            return io.emit('status', error);
        }
    })

    //------------------------------------------





    //---------- funcoes da biometria ---------
    socket.on('cadastrar_biometria', (info) => {
        console.log(info);
        io.emit('cadastrarbiometria', info);
    })

    socket.on('atualizar_biometria', async (biometria, id) => {
        try {
            const user = await User.findByPk(id);
            if (!user) return io.emit('status', "Usuário não encontrado");
            await user.update({biometry: biometria});
            getUsers();
            return io.emit('status', user);
        } catch (error) {
            return io.emit('status', error);
        }
        
    })

    socket.on('deletar_biometria', async (id) => {
        console.log(id);
        try {
            const user = await User.findByPk(id);
            if (!user) return io.emit('status', "Usuário não encontrado");
            io.emit('deletarbiometria', user.biometry);
            await user.update({biometry: -1});
            getUsers();
            return io.emit('status', "ok");
        } catch (error) {
            return io.emit('status', error);
        }
    })
    //------------------------------------------




    //----------- funcoes do cartão ------------
    socket.on('cadastrar_cartao', (info) => {
        console.log(info);
        io.emit('cadastrarcartao', info);
    })

    socket.on('atualizar_cartao', async (info) => {
        console.log(info.card)
        console.log(info.id)
        try {
            const user = await User.findByPk(info.id);
            if (!user) return io.emit('status', "Usuário não encontrado");
            await user.update({card: info.card});
            getUsers();
            return io.emit('status', "ok");
        } catch (error) {
            return io.emit('status', error);
        }
    })

    socket.on('deletar_cartao', async (id) => {
        console.log(id);
        try {
            const user = await User.findByPk(id);
            if (!user) return io.emit('status', "Usuário não encontrado");
            await user.update({card: null});
            io.emit('deletarcartao', id);
            getUsers();
            return io.emit('status', "ok");
        } catch (error) {
            return io.emit('status', error);
        }
    })
    //------------------------------------------

})

const connection = require('./database/index');

connection
    .authenticate()
    .then(() => {
        console.log('Connection has been established successfully.');
    })
    .catch((error) => {
        console.error('Unable to connect to the database:', error);
    });


http.listen(port, function () {
    console.log('listening on port: ' + port);
});