import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { ApiService } from 'src/app/servicios/api/api.service';
import { FicheroI } from 'src/app/models/ficheros.interface';

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.css']
})
export class DashboardComponent implements OnInit {
  ficheros : FicheroI[] | undefined;

  constructor(private router:Router, private api:ApiService) { }

  ngOnInit(): void {
    this.api.getFile().subscribe(data => {
      this.ficheros = data;
      console.log(this.ficheros);
      
    })
  }

  editarAcces(id:number){
    this.router.navigate(['editA',id])
  }

}
