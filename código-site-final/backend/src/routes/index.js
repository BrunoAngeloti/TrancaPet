const UserController = require('../controllers/UserController');
const router = require('express').Router();

router.post('/users', UserController.store);
router.get('/users', UserController.index);
router.put('/users/:user_id', UserController.update);
router.delete('/users/:user_id', UserController.delete);

module.exports = router;
