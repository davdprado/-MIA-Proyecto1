import { Component, OnInit } from '@angular/core';

import { FormGroup,FormControl,Validators } from '@angular/forms';

import { ApiService } from "../../servicios/api/api.service";
import { LoginI } from "../../models/login.interface";
import { Router } from '@angular/router';
import { ResponseI } from 'src/app/models/response.interface';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {

  loginForm = new FormGroup({
    correo: new FormControl('',Validators.required),
    password: new FormControl('',Validators.required)
  })

  constructor(private api:ApiService, private router:Router) { }

  ngOnInit(): void {
  }

  onLogin(form: any){
    this.api.loginByEmail(form).subscribe(data =>{
      let dataResponse:ResponseI=data;
      if (dataResponse.status!=-1) {
        localStorage.setItem("token",dataResponse.usr);
        if (dataResponse.rol=="Administrador") {
          this.router.navigate(['dashboard']);
        }
      }
    });
  }

}