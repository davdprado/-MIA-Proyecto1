import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { LoginComponent } from './vistas/login/login.component';
import { DashboardComponent } from './vistas/dashboard/dashboard.component';
import { RegistroComponent } from './vistas/registro/registro.component';
import { PendientesComponent } from './vistas/pendientes/pendientes.component';
import { ReportadosComponent } from './vistas/reportados/reportados.component';
import { EditpermisosComponent } from './vistas/editpermisos/editpermisos.component';

const routes: Routes = [
  {path:'',redirectTo:'login',pathMatch:'full'},
  {path:'login',component:LoginComponent},
  {path:'dashboard',component:DashboardComponent},
  {path:'editA/:id',component:EditpermisosComponent},
  {path:'dashboard/pendientes',component:PendientesComponent},
  {path:'dashboard/reportados',component:ReportadosComponent},
  {path:'registro',component:RegistroComponent},
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
export const routesComponent =[LoginComponent];