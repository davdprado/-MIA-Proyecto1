import { Component, OnInit } from '@angular/core';
import { ApiService } from 'src/app/servicios/api/api.service';
import { Router } from '@angular/router';
import { UsuarioI,ResponseCUI } from 'src/app/models/user.interface';

@Component({
  selector: 'app-reportsclient',
  templateUrl: './reportsclient.component.html',
  styleUrls: ['./reportsclient.component.css']
})
export class ReportsclientComponent implements OnInit {

  usuarios : UsuarioI[] | undefined;
  constructor(private api:ApiService,private router:Router) { }

  ngOnInit(): void {
    this.api.getUserR(1,Number(this.getToken())).subscribe(data => {
      this.usuarios = data;
    });
  }
  getToken(){
    return localStorage.getItem('token');
  }
  reportar(id:number){
    this.api.report(id).subscribe(data => {
      let dataResponse:ResponseCUI=data;
      if (dataResponse.status=="ok") {
        console.log("Reporte hecho");
        window.alert(dataResponse.message+" Usuario Reportado");
        this.ngOnInit();
        
      }else{
        console.log("Error al dar de alta")
        window.alert("Error: "+dataResponse.message);
      }
    })
  }

}
