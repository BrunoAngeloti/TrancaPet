// arquivo para fazer a conexão com o banco de dados

require('dotenv').config();
const dbConfig = require('../config/database');

const Sequelize = require('sequelize');

const User = require('../models/User');
const connection = new Sequelize(dbConfig)
User.init(connection);


module.exports = connection;
