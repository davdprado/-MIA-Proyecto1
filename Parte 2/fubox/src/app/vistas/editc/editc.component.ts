import { Component, OnInit } from '@angular/core';
import { Router,ActivatedRoute } from '@angular/router';
import { ApiService } from 'src/app/servicios/api/api.service';
import { FicheroI } from 'src/app/models/ficheros.interface';
import { ResponseCUI, UsuarioCreate, UsuarioI } from 'src/app/models/user.interface';
import { FormControl, FormGroup, Validators } from '@angular/forms';

@Component({
  selector: 'app-editc',
  templateUrl: './editc.component.html',
  styleUrls: ['./editc.component.css']
})
export class EditcComponent implements OnInit {

  usuario : UsuarioCreate | any;
  editForm = new FormGroup({
    nombre: new FormControl(''),
    apellido: new FormControl(''),
    username: new FormControl(''),
    correo: new FormControl(''),
    telefono: new FormControl(''),
    nacimiento: new FormControl(''),
    password: new FormControl(''),
  });
  constructor(private activerrouter:ActivatedRoute,private api:ApiService,private router:Router) { }

  ngOnInit(): void {
    let usarioeID =this.activerrouter.snapshot.paramMap.get('id');
    this.api.getUser(Number(usarioeID)).subscribe(data =>{
      this.usuario = data[0];
      this.editForm.setValue({
        'nombre' : this.usuario.nombre,
        'apellido' : this.usuario.apellido,
        'username': this.usuario.username,
        'correo':this.usuario.correo,
        'telefono':this.usuario.telefono,
        'nacimiento':this.usuario.fecha_nacimiento,
        'password':this.usuario.password
      });
      console.log(this.editForm.value);
      
    })
  }

  postForm(form:any){
    this.api.putUser(form).subscribe( data =>{
      let dataResponse:ResponseCUI=data;
      if (dataResponse.status=="ok") {
        window.alert("Usuario Editado");
      }else{
        console.log("Error al Editar")
        window.alert("Error: "+dataResponse.message);
      }
    })
  }


}
