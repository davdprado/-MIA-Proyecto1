import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-navclient',
  templateUrl: './navclient.component.html',
  styleUrls: ['./navclient.component.css']
})
export class NavclientComponent implements OnInit {

  constructor(private route:Router) { }

  ngOnInit(): void {
  }
  logOut(){
    localStorage.clear();
    this.route.navigate(['login']);
  }
}
