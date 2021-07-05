import socketIOClient from "socket.io-client";

const socket = socketIOClient("localhost:4000");
// const socket = socketIOClient("pet-enigmas-api.herokuapp.com");

export default socket;