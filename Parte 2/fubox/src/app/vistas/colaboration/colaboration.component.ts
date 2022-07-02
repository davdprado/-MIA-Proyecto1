import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { ColabI } from 'src/app/models/colabora.interface';
import { ResponseCUI } from 'src/app/models/user.interface';
import { ApiService } from 'src/app/servicios/api/api.service';

@Component({
  selector: 'app-colaboration',
  templateUrl: './colaboration.component.html',
  styleUrls: ['./colaboration.component.css']
})
export class ColaborationComponent implements OnInit {
  colaboraciones : ColabI[]|undefined;
  constructor(private api:ApiService,private router:Router) { }

  ngOnInit(): void {
    this.api.getCollabs(Number(this.getToken())).subscribe(data =>{     
      this.colaboraciones = data;
    });
  }

  getToken(){
    return localStorage.getItem('token');
  }
  noColab(id:number){
    this.api.noColab(id).subscribe(data => {
      let dataResponse:ResponseCUI=data;
      if (dataResponse.status=="ok") {
        window.alert(dataResponse.message);
        this.ngOnInit();
        
      }else{
        console.log("Error al dar de alta")
        window.alert("Error: "+dataResponse.message);
      }
    })
  }
}
