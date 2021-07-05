const sequelize = require('sequelize');

const { DataTypes } = sequelize;
const { Model } = sequelize;

class User extends Model {
  static init(sequelize) {
    super.init(
      {
        name: DataTypes.STRING,
        card: DataTypes.STRING,
        biometry: DataTypes.INTEGER,
      },
      {
        sequelize,
      }
    );
  }

}

module.exports = User;
