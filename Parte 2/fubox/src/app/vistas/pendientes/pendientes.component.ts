import { Component, OnInit } from '@angular/core';
import { ApiService } from 'src/app/servicios/api/api.service';
import { Router } from '@angular/router';
import { UsuarioI,ResponseCUI } from 'src/app/models/user.interface';

@Component({
  selector: 'app-pendientes',
  templateUrl: './pendientes.component.html',
  styleUrls: ['./pendientes.component.css']
})
export class PendientesComponent implements OnInit {

  usuarios : UsuarioI[] | undefined;
  constructor(private api:ApiService,private router:Router) { }

  ngOnInit(): void {
    this.api.getUsers(0).subscribe(data => {
      this.usuarios = data;
    });
  }

  aprobar(id:number){
    this.api.altaUser(id).subscribe(data => {
      let dataResponse:ResponseCUI=data;
      if (dataResponse.status=="ok") {
        console.log("Alta hecha");
        window.alert("Usuario con id=\""+id+"\" dado de alta");
        this.ngOnInit();
        
      }else{
        console.log("Error al dar de alta")
        window.alert("Error: "+dataResponse.message);
      }
    })
  }

}
