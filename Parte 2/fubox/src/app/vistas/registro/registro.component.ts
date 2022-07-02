import { Component, OnInit } from '@angular/core';

import { FormGroup,FormControl,Validators } from '@angular/forms';

import { ApiService } from "../../servicios/api/api.service";
import { UsuarioCreate,ResponseCUI } from "../../models/user.interface";
import { Router } from '@angular/router';


@Component({
  selector: 'app-registro',
  templateUrl: './registro.component.html',
  styleUrls: ['./registro.component.css']
})
export class RegistroComponent implements OnInit {

  registreForm = new FormGroup({
    nombre: new FormControl('',Validators.required),
    apellido: new FormControl('',Validators.required),
    username: new FormControl('',Validators.required),
    correo: new FormControl('',Validators.required),
    telefono: new FormControl('',Validators.required),
    nacimiento: new FormControl('',Validators.required),
    password: new FormControl('',Validators.required),
  })

  constructor(private router:Router, private api:ApiService) { }
  errorStatus:boolean=false;
  erroMsj:any="";

  ngOnInit(): void {
  }

  goBack(): void {
    this.router.navigate(['login']);
  }

  onRegis(form: any){
    this.api.createUser(form).subscribe(data =>{
      let dataResponse:ResponseCUI=data;
      if (dataResponse.status=="ok") {
        console.log("Registrado Correctamente");
        window.alert("Su Usuario ha sido creado, espere a que el administrador le habilite su cuenta");
        this.router.navigate(['login']);
        
      }else{
        console.log("Error al crear")
        window.alert("Error: "+dataResponse.message);
      }
    });
  }
}
