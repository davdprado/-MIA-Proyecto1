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

//colaboraciones
app.get("/createColab/:idf/:correo", function (req, res) {
  let dataDB = require("./DB.json");
  let idfi = req.params.idf;
  let mailuser = req.params.correo;
  //buscar si ya existe
  let respuesta;

  const fichero = dataDB.Carpeta[0].Contenido.find(
    (fichero) => fichero.id == idfi
  );
  const usuario = dataDB.Usuario.find((usuario) => usuario.correo == mailuser);
  if (usuario === undefined) {
    respuesta = {
      mensaje: "No existe ese correo",
      status: "error",
    };
  } else {
    const sb = dataDB.fichero_colab.find(
      (filec) => filec.id_fichero == idfi && filec.id_usuario == usuario.id
    );
    if (sb === undefined) {
      let file_colab = {
        id: dataDB.contColab + 1,
        id_usuario: usuario.id,
        id_fichero: fichero.id,
      };
      dataDB.contColab = file_colab.id;
      dataDB.fichero_colab.push(file_colab);
      let newjson = JSON.stringify(dataDB, null, 2);
      fs.writeFileSync("DB.json", newjson);
      respuesta = {
        mensaje: "Se a;adio de colaborador a " + usuario.correo,
        status: "ok",
      };
      enviarEmail(
        usuario.correo,
        "Invitacion de Colaboracion",
        "Querido " +
          usuario.nombre +
          '\n es colaborador del fichero: "' +
          fichero.Nombre +
          '"'
      );
    } else {
      respuesta = {
        mensaje: "No se puede hacer colaborador 2 veces",
        status: "error",
      };
    }
  }

  res.send(respuesta);
});

app.get("/noColab/:id", function (req, res) {
  let dataDB = require("./DB.json");
  let idusuario = req.params.id;
  console.log(idusuario);
  const rela = dataDB.fichero_colab.filter(
    (item) => item.id !== Number(idusuario)
  );
  dataDB.fichero_colab = rela;
  let newjson = JSON.stringify(dataDB, null, 2);
  fs.writeFileSync("DB.json", newjson);
  let respuesta = {
    mensaje: "Ya no se es mas colaborador de este archivo",
    status: "ok",
  };
  res.send(respuesta);
});

app.get("/getColabs/:id", function (req, res) {
  let dataDB = require("./DB.json");
  let idusr = req.params.id;
  const usuario = dataDB.fichero_colab.filter(
    (relfich) => relfich.id_usuario == idusr
  );
  let respuestaarr = [];
  usuario.forEach((relacion) => {
    dataDB.Carpeta[0].Contenido.forEach((file) => {
      if (file.id == relacion.id_fichero) {
        let propietarioo = "";
        dataDB.Usuario.forEach((usr) => {
          if (usr.id == relacion.id_usuario) {
            propietarioo = usr.correo;
          }
        });
        let colaboration = {
          id: relacion.id,
          nombre: file.Nombre,
          propietario: propietarioo,
        };
        respuestaarr.push(colaboration);
      }
    });
  });
  res.send(respuestaarr);
});

//recuperacion de contra
app.post("/passRecovery", function (req, res) {
  let dataDB = require("./DB.json");
  let usuariofake = {
    correo: req.body.correo,
  };
  const found = dataDB.Usuario.find(
    (usuario) => usuario.correo == usuariofake.correo
  );
  let respuesta;
  if (found === undefined) {
    respuesta = {
      mensaje: "El usuario no existe",
      status: "error",
    };
  } else {
    enviarEmail(
      found.correo,
      "Recuperacion de Password",
      "Querido " + found.nombre + ":\n tu Password es: " + found.password
    );
    respuesta = {
      mensaje: "Correo con su Password ha sido enviado",
      status: "ok",
    };
  }

  res.send(respuesta);
});
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

app.get("/getUserR/:stt/:id", function (req, res) {
  let dataDB = require("./DB.json");
  let estado = req.params.stt;
  let idusr = req.params.id;
  const lstUsuarios = dataDB.Usuario.filter(
    (usuario) =>
      usuario.status == estado &&
      usuario.rol != "Administrador" &&
      usuario.id != idusr
  );
  res.send(lstUsuarios);
});

app.get("/getReportados", function (req, res) {
  let dataDB = require("./DB.json");
  const lstUsuarios = dataDB.usr_reportados;
  res.send(lstUsuarios);
});

app.get("/reportar/:idusr", function (req, res) {
  let dataDB = require("./DB.json");
  let idusuario = req.params.idusr;
  const usuarioRep = dataDB.Usuario.find((element) => element.id == idusuario);
  const rela = dataDB.Usuario.filter((item) => item.id !== Number(idusuario));
  dataDB.Usuario = rela;
  dataDB.usr_reportados.push(usuarioRep);
  let newjson = JSON.stringify(dataDB, null, 2);
  fs.writeFileSync("DB.json", newjson);
  enviarEmail(
    usuarioRep.correo,
    "Reportado",
    "Lamentamos informar que su usuario ha sido reportado y por ende ha sido bloqueado temporalmente"
  );
  let respuesta = {
    mensaje: "El Usuario ha sido Reportado",
    status: "ok",
  };
  res.send(respuesta);
});

app.get("/habilitar/:idusr", function (req, res) {
  let dataDB = require("./DB.json");
  let idusuario = req.params.idusr;
  const usuarioRep = dataDB.usr_reportados.find(
    (element) => element.id == Number(idusuario)
  );
  const rela = dataDB.usr_reportados.filter(
    (item) => item.id !== Number(idusuario)
  );
  dataDB.usr_reportados = rela;
  dataDB.Usuario.push(usuarioRep);
  let newjson = JSON.stringify(dataDB, null, 2);
  fs.writeFileSync("DB.json", newjson);
  enviarEmail(
    usuarioRep.correo,
    "Habilitado",
    "Tu Usuario ha sido habilitado de nuevo"
  );
  let respuesta = {
    mensaje: "El Usuario habilitado",
    status: "ok",
  };
  res.send(respuesta);
});

app.get("/deshabilitar/:idusr", function (req, res) {
  let dataDB = require("./DB.json");
  let idusuario = req.params.idusr;
  let usuarioRep = dataDB.usr_reportados.find(
    (element) => element.id == Number(idusuario)
  );
  //borrar de los usuarios
  const borrarep = dataDB.usr_reportados.filter(
    (element) => element.id !== Number(idusuario)
  );
  const newProper = dataDB.fichero_owner.filter(
    (item) => item.id_usuario !== Number(idusuario)
  );
  const newcolabs = dataDB.fichero_colab.filter(
    (item) => item.id_usuario !== Number(idusuario)
  );
  dataDB.usr_reportados = borrarep;
  dataDB.fichero_owner = newProper;
  dataDB.fichero_colab = newcolabs;
  let newjson = JSON.stringify(dataDB, null, 2);
  fs.writeFileSync("DB.json", newjson);
  enviarEmail(usuarioRep.correo, "Borrado", "Tu Usuario ha sido dado de baja");
  let respuesta = {
    mensaje: "El Usuario habilitado",
    status: "ok",
  };
  res.send(respuesta);
});

app.get("/getFichero/:id", function (req, res) {
  let dataDB = require("./DB.json");
  let idfi = req.params.id;
  const fichero = dataDB.Carpeta[0].Contenido.filter(
    (fichero) => fichero.id == idfi
  );
  res.send(fichero);
});
//obtener solo el usuario deseado
app.get("/getUsuario/:id", function (req, res) {
  let dataDB = require("./DB.json");
  let estado = req.params.id;
  const usuario = dataDB.Usuario.filter(
    (usuario) => usuario.id == estado && usuario.rol != "Administrador"
  );
  res.send(usuario);
});

//obtener carpetas que son due;os
app.get("/getFiles/:id", function (req, res) {
  let dataDB = require("./DB.json");
  let idusr = req.params.id;
  const usuario = dataDB.fichero_owner.filter(
    (relfich) => relfich.id_usuario == idusr
  );
  let respuestaarr = [];
  usuario.forEach((relacion) => {
    dataDB.Carpeta[0].Contenido.forEach((file) => {
      if (file.id == relacion.id_fichero) {
        respuestaarr.push(file);
      }
    });
  });
  res.send(respuestaarr);
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

//editar usuario
app.put("/editUser", function (req, res) {
  let dataDB = require("./DB.json");
  //console.log(req.body);
  let usuariofake = {
    nombre: req.body.nombre,
    apellido: req.body.apellido,
    telefono: req.body.telefono,
    username: req.body.username,
    fecha_nacimiento: req.body.nacimiento,
    correo: req.body.correo,
    password: req.body.password,
  };
  //buscar si existe el correo
  dataDB.Usuario.forEach((usuario) => {
    if (usuario.correo == usuariofake.correo) {
      usuario.nombre = usuariofake.nombre;
      usuario.apellido = usuariofake.apellido;
      usuario.telefono = usuariofake.telefono;
      usuario.username = usuariofake.username;
      usuario.fecha_nacimiento = usuariofake.fecha_nacimiento;
      usuario.correo = usuariofake.correo;
      usuario.password = usuariofake.password;
    }
  });
  let newjson = JSON.stringify(dataDB, null, 2);
  fs.writeFileSync("DB.json", newjson);
  let respuesta = {
    mensaje: "El Usuario a sido Actualizado",
    status: "ok",
  };

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
