// ENTRAR NO TERMINAL DO CONTAINER E RODAR MIGRATIONS
// docker exec -it backendAlertaUfes npx sequelize-cli db:migrate

module.exports = {
  dialect: 'postgres',
  host: "postgres.pet.inf.ufes.br",
  port: "10000",
  username: "postgres",
  password: "123456",
  database: "tranca-eletropet",
  define: {
    timestamps: true,
    underscored: true,
  },
};
