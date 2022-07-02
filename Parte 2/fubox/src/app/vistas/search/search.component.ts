import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { ApiService } from 'src/app/servicios/api/api.service';
import { FicheroI } from 'src/app/models/ficheros.interface';

@Component({
  selector: 'app-search',
  templateUrl: './search.component.html',
  styleUrls: ['./search.component.css']
})
export class SearchComponent implements OnInit {

  ficheros : FicheroI[] | undefined;
  ficheross : FicheroI[] | undefined;
  nombre:string = '';
  constructor(private router:Router, private api:ApiService) { }

  ngOnInit(): void {
    this.api.getFile().subscribe(data => {
      this.ficheros = data;
      console.log(this.ficheros);
      
    })
  }

  buscar(name:string){
    this.api.searchFile(name).subscribe(data => {
      this.ficheross = data
    })
  }


}
