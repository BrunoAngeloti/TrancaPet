import axios from "axios";

const apilogin = axios.create({
  baseURL: "https://apipet.pet.inf.ufes.br/"
});

export default apilogin;
