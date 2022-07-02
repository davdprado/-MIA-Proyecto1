import { Component, OnInit } from '@angular/core';

import { FormGroup,FormControl,Validators } from '@angular/forms';

import { ApiService } from "../../servicios/api/api.service";
import { LoginI,RecuperateI } from "../../models/login.interface";
import { Router } from '@angular/router';
import { ResponseI } from 'src/app/models/response.interface';
import { ResponseCUI } from 'src/app/models/user.interface';

@Component({
  selector: 'app-recovery-pass',
  templateUrl: './recovery-pass.component.html',
  styleUrls: ['./recovery-pass.component.css']
})
export class RecoveryPassComponent implements OnInit {

  recoveryForm = new FormGroup({
    correo: new FormControl('',Validators.required)
  })

  constructor(private api:ApiService, private router:Router) { }

  ngOnInit(): void {
  }

  onRecovery(form: any){
    this.api.recuperar(form).subscribe(data => {
      let dataResponse: ResponseCUI = data;
      if (dataResponse.status=="ok") {
        console.log("Se envio el correo");
        window.alert("Se envio un Correo con sus credenciales");
        this.router.navigate(['login']);
        
      }else{
        console.log("Error al recuperar")
        window.alert("Error: "+dataResponse.message);
        this.router.navigate(['login']);
      }
    })
  }

}
