import { Component, OnInit } from '@angular/core';
import { ApiService } from 'src/app/servicios/api/api.service';
import { Router } from '@angular/router';
import { UsuarioI,ResponseCUI } from 'src/app/models/user.interface';

@Component({
  selector: 'app-reportados',
  templateUrl: './reportados.component.html',
  styleUrls: ['./reportados.component.css']
})
export class ReportadosComponent implements OnInit {
  usuarios : UsuarioI[] | undefined;
  constructor(private api:ApiService,private router:Router) { }

  ngOnInit(): void {
    this.api.getReport().subscribe(data => {
      this.usuarios = data;
    });
  }
  getToken(){
    return localStorage.getItem('token');
  }
  deshabilitar(id:number){
    var resultado = window.confirm('Estas seguro?');
    if (resultado === true) {
        window.alert('Okay, si estas seguro.');
        this.api.deshabilitar(id).subscribe(data => {
          let dataResponse:ResponseCUI=data;
          if (dataResponse.status=="ok") {
            console.log("borrado hecho");
            window.alert(dataResponse.message+" Usuario Borrado");
            this.ngOnInit();
            
          }else{
            console.log("Error al desabilitar")
            window.alert("Error: "+dataResponse.message);
          }
        })
    } else { 
        window.alert('Pareces indeciso');
    }
  }
  habilitar(id:number){
    this.api.habilitar(id).subscribe(data => {
      let dataResponse:ResponseCUI=data;
      if (dataResponse.status=="ok") {
        console.log("Reporte hecho");
        window.alert(dataResponse.message+" Usuario Habilitado");
        this.ngOnInit();
        
      }else{
        console.log("Error al Habilitar")
        window.alert("Error: "+dataResponse.message);
      }
    })
  }
}
