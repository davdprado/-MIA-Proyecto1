import { Injectable } from '@angular/core';

import { LoginI } from "../../models/login.interface";
import { UsuarioI,ResponseCUI, UsuarioCreate } from "../../models/user.interface";
import { ResponseI } from "../../models/response.interface";
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs';
import { FicheroI } from 'src/app/models/ficheros.interface';

@Injectable({
  providedIn: 'root'
})
export class ApiService {
  url:string = "http://localhost:3000/"
  constructor(private http:HttpClient) { }

  loginByEmail(form:LoginI):Observable<ResponseI>{
    let direccion = this.url+"login";
    return this.http.post<ResponseI>(direccion,form);
  }

  createUser(form:UsuarioCreate):Observable<ResponseCUI>{
    let direccion = this.url+"createUser";
    return this.http.post<ResponseCUI>(direccion,form);
  }

  getUsers(estado:number):Observable<UsuarioI[]>{
    let direccion = this.url+"getUser/"+estado;
    return this.http.get<UsuarioI[]>(direccion);
  }

  altaUser(id:Number):Observable<ResponseCUI>{
    let direccion = this.url+"alta/"+id;
    return this.http.get<ResponseCUI>(direccion);
  }

  getFile():Observable<FicheroI[]>{
    let direccion = this.url+"getAllCarpet";
    return this.http.get<FicheroI[]>(direccion);
  }

  getSingleFile(id:Number):Observable<FicheroI[]>{
    let direccion = this.url+"getFichero/"+id;
    return this.http.get<FicheroI[]>(direccion);
  }

  crearpropietario(id:Number,idus:Number):Observable<ResponseCUI>{
    let direccion = this.url+"createProp/"+id+"/"+idus;
    return this.http.get<ResponseCUI>(direccion);
  }
  
}
