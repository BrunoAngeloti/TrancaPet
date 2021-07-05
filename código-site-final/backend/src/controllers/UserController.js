const User = require('../models/User');

module.exports = {
  async store(req, res) {

    const { id, name, card, biometry } = await User.create(
      req.body
    );

    return res.status(201).json({
      id,
      name,
      card,
      biometry
    });
  },

  async index(req, res) {
    try {
      const users = await User.findAll();
      users.map((u) => {
        const { id, name, card, biometry } = u;
        u.dataValues = {
          id,
          name,
          card,
          biometry,
        };
        return u;
      });
      return res.status(200).json({ users });
    } catch (error) {
      return res.json({ error });
    }
  },

  // async show(req, res) {
  //   const { user_id } = req.params;
  //   const user = await User.findByPk(user_id);
  //   if (!user) throw new AppError('Usuário não existe!', Status.NOT_FOUND);

  //   const { id, nome, card, biometry } = user;

  //   return res.status(Status.OK).json({
  //     id,
  //     nome,
  //     card,
  //     biometry
  //   });
  // },

  async update(req, res) {
    console.log("Entrou")
    // console.log(req);
    const { id } = req;

    try {
      const user = await User.findByPk(id);
      if (!user) return res.status(404).json({ message: 'Usuário não existe!' });
      await user.update(req);
      console.log(req);
      return res.status(200).json({ user });
    } catch (error) {
      return res.json({ error });
    }
  },

  async delete(req, res) {
    const { user_id } = req.params;
    const user = await User.findByPk(user_id);

    if (!user) return res.status(404).json({ message: 'Usuário não existe!' });
    await user.destroy();

    return res
      .status(200)
      .json({ message: 'Usuário deletado com sucesso!' });
  },
};
