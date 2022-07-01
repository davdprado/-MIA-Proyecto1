const express = require("express");
const cors = require("cors");
const bodyParser = require("body-parser");
const fs = require("fs");
let jsonConsole = require("../../Datos.json");

const app = express();

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.use(cors());

app.get("/getAllCarpet", function (req, res) {
  let dataDB = require("./DB.json");
  dataDB.Carpeta = jsonConsole;
  let newjson = JSON.stringify(dataDB, null, 2);
  fs.writeFileSync("DB.json", newjson);
  res.send(dataDB.Carpeta);
});

app.post("/login", function (req, res) {
  let dataDB = require("./DB.json");
  let usuariofake = {
    correo: req.body.correo,
    password: req.body.password,
  };
  const found = dataDB.Usuario.find(
    (usuario) =>
      usuario.correo == usuariofake.correo &&
      usuario.password == usuariofake.password
  );
  let respuesta;
  if (found === undefined) {
    respuesta = {
      mensaje: "El usuario no existe",
      status: -1,
      id: -1,
      rol: "",
      usr: {},
    };
  } else {
    respuesta = {
      mensaje: "Logueado correctamente",
      status: 1,
      id: found.id,
      rol: found.rol,
      usr: found,
    };
  }

  res.send(respuesta);
});

app.get("/", function (req, res) {
  res.send("Holis Esto es una prueba");
});

app.listen(3000, () => {
  console.log("El servidor está inicializado en el puerto 3000");
});
