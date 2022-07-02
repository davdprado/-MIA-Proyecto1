import { Component, OnInit } from '@angular/core';
import { Router,ActivatedRoute } from '@angular/router';
import { ApiService } from 'src/app/servicios/api/api.service';
import { FicheroI } from 'src/app/models/ficheros.interface';
import { ResponseCUI, UsuarioI } from 'src/app/models/user.interface';

@Component({
  selector: 'app-editpermisos',
  templateUrl: './editpermisos.component.html',
  styleUrls: ['./editpermisos.component.css']
})
export class EditpermisosComponent implements OnInit {

  ficheroActual:FicheroI | any;
  usuarios : UsuarioI[] | undefined;
  constructor(private activerouter:ActivatedRoute, private router:Router, private api:ApiService) { }

  ngOnInit(): void {
    let idfichero = this.activerouter.snapshot.paramMap.get('id');
    this.api.getSingleFile(Number(idfichero)).subscribe(data => {
      this.ficheroActual = data[0];
    });
    this.api.getUsers(1).subscribe(data => {
      this.usuarios = data;
    });
  }

  createPermisos(id:Number,idusr:Number){
    this.api.crearpropietario(id,idusr).subscribe(data => {
      let dataResponse:ResponseCUI=data;
      if (dataResponse.status=="ok") {
        console.log("Propiedad Creada");
        window.alert("Usuario con id=\""+id+"\" es propietario de fichero_id: "+idusr);
      }else{
        console.log("Error al crear Propietario")
        window.alert("Error: "+dataResponse.message);
      }
    })
  }

}
