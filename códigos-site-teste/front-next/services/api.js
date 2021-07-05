import axios from "axios";

const api = axios.create({
  baseURL: "https://apipet.pet.inf.ufes.br/"
});

export default api;
