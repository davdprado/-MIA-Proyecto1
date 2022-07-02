import { Injectable } from '@angular/core';

import { LoginI,RecuperateI } from "../../models/login.interface";
import { UsuarioI,ResponseCUI, UsuarioCreate } from "../../models/user.interface";
import { ResponseI } from "../../models/response.interface";
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs';
import { CorreoI, FicheroI } from 'src/app/models/ficheros.interface';
import { ColabI } from 'src/app/models/colabora.interface';

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
  recuperar(form:RecuperateI):Observable<ResponseCUI>{
    let direccion = this.url+"passRecovery";
    return this.http.post<ResponseCUI>(direccion,form);
  }

  createUser(form:UsuarioCreate):Observable<ResponseCUI>{
    let direccion = this.url+"createUser";
    return this.http.post<ResponseCUI>(direccion,form);
  }

  getUsers(estado:number):Observable<UsuarioI[]>{
    let direccion = this.url+"getUser/"+estado;
    return this.http.get<UsuarioI[]>(direccion);
  }

  getUser(id:number):Observable<UsuarioI[]>{
    let direccion = this.url+"getUsuario/"+id;
    return this.http.get<UsuarioI[]>(direccion);
  }

  getUserR(id:number,usr:number):Observable<UsuarioI[]>{
    let direccion = this.url+"getUserR/"+id+"/"+usr;
    return this.http.get<UsuarioI[]>(direccion);
  }

 

  putUser(form:UsuarioCreate):Observable<ResponseCUI>{
    let direccion = this.url+"editUser";
    return this.http.put<ResponseCUI>(direccion,form);
  }

  altaUser(id:Number):Observable<ResponseCUI>{
    let direccion = this.url+"alta/"+id;
    return this.http.get<ResponseCUI>(direccion);
  }

  report(id:Number):Observable<ResponseCUI>{
    let direccion = this.url+"reportar/"+id;
    return this.http.get<ResponseCUI>(direccion);
  }
  habilitar(id:Number):Observable<ResponseCUI>{
    let direccion = this.url+"habilitar/"+id;
    return this.http.get<ResponseCUI>(direccion);
  }
  deshabilitar(id:Number):Observable<ResponseCUI>{
    let direccion = this.url+"deshabilitar/"+id;
    return this.http.get<ResponseCUI>(direccion);
  }

  noColab(id:Number):Observable<ResponseCUI>{
    let direccion = this.url+"noColab/"+id;
    return this.http.get<ResponseCUI>(direccion);
  }

  getFile():Observable<FicheroI[]>{
    let direccion = this.url+"getAllCarpet";
    return this.http.get<FicheroI[]>(direccion);
  }
  
  searchFile(name:string):Observable<FicheroI[]>{
    let direccion = this.url+"getFileSe/"+name;
    return this.http.get<FicheroI[]>(direccion);
  }

  getReport():Observable<UsuarioI[]>{
    let direccion = this.url+"getReportados";
    return this.http.get<UsuarioI[]>(direccion);
  }

  getCollabs(id:number):Observable<ColabI[]>{
    let direccion = this.url+"getColabs/"+id;
    return this.http.get<ColabI[]>(direccion);
  }

  getFileP(id:number):Observable<FicheroI[]>{
    let direccion = this.url+"getFiles/"+id;
    return this.http.get<FicheroI[]>(direccion);
  }

  cColab(id:number,correo:string):Observable<ResponseCUI>{
    let direccion = this.url+"createColab/"+id+"/"+correo;
    return this.http.get<ResponseCUI>(direccion);
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
