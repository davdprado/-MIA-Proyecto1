import { Component, OnInit } from '@angular/core';
import { Router,ActivatedRoute } from '@angular/router';
import { ApiService } from 'src/app/servicios/api/api.service';
import { ResponseCUI, UsuarioI } from 'src/app/models/user.interface';

@Component({
  selector: 'app-clientpanel',
  templateUrl: './clientpanel.component.html',
  styleUrls: ['./clientpanel.component.css']
})
export class ClientpanelComponent implements OnInit {

  usuario : UsuarioI | any;
  constructor(private router:Router, private api:ApiService) { }

  ngOnInit(): void {
    this.api.getUser(Number(this.getToken())).subscribe(data => {
      console.log(data[0]);
      this.usuario = data[0];
      
    })
  }

  getToken(){
    return localStorage.getItem('token');
  }

  editarInfo(id:Number){
    this.router.navigate(['editC',id]);
  }

}
