
const express = require('express');
const cors = require('cors');
require('./database');
const routes = require('./routes');

class AppController {
  constructor() {
    this.express = express();
    this.middlewares();
    this.routes();
  }

  middlewares() {
    this.express.use(express.json());
    this.express.use(cors());
    this.express.use(express.urlencoded({ extended: true })); // envio de arquivo
  }

  routes() {
    this.express.use(routes);
  }

}

module.exports = new AppController().express;
