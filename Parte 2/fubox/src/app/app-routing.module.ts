import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { LoginComponent } from './vistas/login/login.component';
import { DashboardComponent } from './vistas/dashboard/dashboard.component';
import { RegistroComponent } from './vistas/registro/registro.component';
import { PendientesComponent } from './vistas/pendientes/pendientes.component';
import { ReportadosComponent } from './vistas/reportados/reportados.component';
import { EditpermisosComponent } from './vistas/editpermisos/editpermisos.component';
import { RecoveryPassComponent } from './vistas/recovery-pass/recovery-pass.component';
import { ClientpanelComponent } from './vistas/clientpanel/clientpanel.component';
import { MyfileComponent } from './vistas/myfile/myfile.component';
import { ColaborationComponent } from './vistas/colaboration/colaboration.component';
import { ReportsclientComponent } from './vistas/reportsclient/reportsclient.component';
import { SearchComponent } from './vistas/search/search.component';
import { EditcComponent } from './vistas/editc/editc.component';
import { NotfoundComponent } from './vistas/notfound/notfound.component';

const routes: Routes = [
  {path:'',redirectTo:'login',pathMatch:'full'},
  {path:'login',component:LoginComponent},
  {path:'recovery',component:RecoveryPassComponent},
  {path:'dashboard',component:DashboardComponent},
  {path:'editA/:id',component:EditpermisosComponent},
  {path:'editC/:id',component:EditcComponent},
  {path:'dashboard/pendientes',component:PendientesComponent},
  {path:'dashboard/reportados',component:ReportadosComponent},
  {path:'registro',component:RegistroComponent},
  {path:'clientview',component:ClientpanelComponent},
  {path:'clientview/mycarpet',component:MyfileComponent},
  {path:'clientview/colab',component:ColaborationComponent},
  {path:'clientview/rep',component:ReportsclientComponent},
  {path:'clientview/search',component:SearchComponent},
  {path:'**',component:NotfoundComponent},

];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
export const routesComponent =[LoginComponent];