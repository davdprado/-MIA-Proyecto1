const express = require("express");
const cors = require("cors");
const bodyParser = require("body-parser");
const fs = require("fs");
const nodemailer = require("nodemailer");
let jsonConsole = require("../../Datos.json");

const app = express();

//dddbgbxczifihshn

// create reusable transporter object using the default SMTP transport
let transporter = nodemailer.createTransport({
  host: "smtp.gmail.com",
  port: 465,
  secure: true, // true for 465, false for other ports
  auth: {
    user: "fuboxaj2022@gmail.com", // generated ethereal user
    pass: "dddbgbxczifihshn", // generated ethereal password
  },
});

function enviarEmail(para, asunto, cuerpo) {
  var mailOptions = {
    from: "Remitente",
    to: para,
    subject: asunto,
    text: cuerpo,
  };
  transporter.sendMail(mailOptions, (error, info) => {
    if (error) {
      res.status(500).send(error, message);
    } else {
      console.log("Email Enviado");
    }
  });
}

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.use(cors());

//recuperacion de contra

//permisos de carpeta
app.get("/createProp/:idf/:idusr", function (req, res) {
  let dataDB = require("./DB.json");
  let idfi = req.params.idf;
  let iduser = req.params.idusr;
  //buscar si ya existe
  let respuesta;
  const bs = dataDB.fichero_owner.find((fichero) => fichero.id_fichero == idfi);
  console.log(bs);
  if (bs === undefined) {
    const fichero = dataDB.Carpeta[0].Contenido.find(
      (fichero) => fichero.id == idfi
    );
    const usuario = dataDB.Usuario.find((usuario) => usuario.id == iduser);
    let user_file = {
      id: dataDB.usrfile + 1,
      id_usuario: usuario.id,
      id_fichero: fichero.id,
    };
    dataDB.usrfile = user_file.id;
    dataDB.fichero_owner.push(user_file);
    let newjson = JSON.stringify(dataDB, null, 2);
    fs.writeFileSync("DB.json", newjson);
    respuesta = {
      mensaje: "Se dieron Permisos de Usuario",
      status: "ok",
    };
  } else {
    respuesta = {
      mensaje: "El fichero ya tiene Propietario",
      status: "error",
    };
  }
  res.send(respuesta);
});

app.get("/getAllCarpet", function (req, res) {
  let dataDB = require("./DB.json");
  res.send(dataDB.Carpeta);
});

app.get("/getUser/:stt", function (req, res) {
  let dataDB = require("./DB.json");
  let estado = req.params.stt;
  const lstUsuarios = dataDB.Usuario.filter(
    (usuario) => usuario.status == estado && usuario.rol != "Administrador"
  );
  res.send(lstUsuarios);
});

app.get("/getFichero/:id", function (req, res) {
  let dataDB = require("./DB.json");
  let idfi = req.params.id;
  const fichero = dataDB.Carpeta[0].Contenido.filter(
    (fichero) => fichero.id == idfi
  );
  res.send(fichero);
});

app.get("/alta/:idusr", function (req, res) {
  let dataDB = require("./DB.json");
  let idusuario = req.params.idusr;
  let usariofalso;
  dataDB.Usuario.forEach((usuario) => {
    if (usuario.id == idusuario) {
      usuario.status = 1;
      usariofalso = usuario;
    }
  });
  let newjson = JSON.stringify(dataDB, null, 2);
  fs.writeFileSync("DB.json", newjson);
  let respuesta = {
    mensaje: "El Usuario a sido dado de Alta exitosamente",
    status: "ok",
  };
  enviarEmail(
    usariofalso.correo,
    "Alta Usuario",
    "Se Creo usuario con correo: " +
      usariofalso.correo +
      " ya ha sido dado de alta Puede Ingresar al portal http://localhost:4200/login"
  );
  res.send(respuesta);
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
    if (found.status == 1) {
      respuesta = {
        mensaje: "Logueado correctamente",
        status: 1,
        id: found.id,
        rol: found.rol,
        usr: found,
      };
    } else {
      respuesta = {
        mensaje: "Su Usuario no ha sido dado de alta",
        status: 0,
        id: found.id,
        rol: found.rol,
        usr: found,
      };
    }
  }

  res.send(respuesta);
});

app.post("/createUser", function (req, res) {
  let dataDB = require("./DB.json");
  let dat = new Date();
  //console.log(req.body);
  let usuariofake = {
    id: dataDB.Nouser + 1,
    nombre: req.body.nombre,
    apellido: req.body.apellido,
    telefono: req.body.telefono,
    username: req.body.username,
    fecha_nacimiento: req.body.nacimiento,
    correo: req.body.correo,
    password: req.body.password,
    status: 0,
    rol: "Cliente",
    fecha_registro: dat,
  };
  //buscar si existe el correo
  const encuentro = dataDB.Usuario.find(
    (usuario) => usuario.correo == usuariofake.correo
  );
  let respuesta;
  if (encuentro === undefined) {
    dataDB.Nouser = usuariofake.id;
    dataDB.Usuario.push(usuariofake);
    let newjson = JSON.stringify(dataDB, null, 2);
    fs.writeFileSync("DB.json", newjson);
    respuesta = {
      mensaje: "El Usuario a sido creado exitosamente",
      status: "ok",
    };
    enviarEmail(
      usuariofake.correo,
      "Creacion de Usuario",
      "Se Creo usuario con correo: " +
        usuariofake.correo +
        " y password: " +
        usuariofake.password
    );
  } else {
    respuesta = {
      mensaje: "ya existe el correo",
      status: "error",
    };
  }
  res.send(respuesta);
});

app.get("/", function (req, res) {
  let dataDB = require("./DB.json");
  dataDB.Carpeta = jsonConsole;
  let newjson = JSON.stringify(dataDB, null, 2);
  fs.writeFileSync("DB.json", newjson);
  res.send(dataDB.Carpeta);
});

app.get("/hola", function (req, res) {
  enviarEmail(
    "davdprado@gmail.com",
    "Correo 2 de Prueba",
    "Esto es una prueba otra vez"
  );
  res.send({ status: "todobien" });
});

app.listen(3000, () => {
  console.log("El servidor está inicializado en el puerto 3000");
});
