import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { ApiService } from 'src/app/servicios/api/api.service';
import { FicheroI } from 'src/app/models/ficheros.interface';
import { FormGroup,FormControl,Validators } from '@angular/forms';
import { ResponseCUI } from 'src/app/models/user.interface';

@Component({
  selector: 'app-myfile',
  templateUrl: './myfile.component.html',
  styleUrls: ['./myfile.component.css']
})
export class MyfileComponent implements OnInit {

  correo: string='';
  ficheros : FicheroI[] | any;
  constructor(private router:Router, private api:ApiService) { }

  ngOnInit(): void {

    this.api.getFileP(Number(this.getToken())).subscribe(data => {
      this.ficheros = data;
      console.log(this.ficheros);
    })
  }

  getToken(){
    return localStorage.getItem('token');
  }

  onColab(id:number,correo:string){
    this.api.cColab(id,correo).subscribe(data =>{
      let dataResponse:ResponseCUI=data;
      if (dataResponse.status=="ok") {
        window.alert("Usuario invitado a colaborar");
        
      }else{
        console.log("Error al anadir colaborador")
        window.alert("Error: "+dataResponse.message);
      }
    })
  }
}
