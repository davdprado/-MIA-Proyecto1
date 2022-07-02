import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { LoginComponent } from './vistas/login/login.component';

import { ReactiveFormsModule, FormsModule } from '@angular/forms';

import { HttpClientModule } from '@angular/common/http';
import { DashboardComponent } from './vistas/dashboard/dashboard.component';
import { RegistroComponent } from './vistas/registro/registro.component';
import { PendientesComponent } from './vistas/pendientes/pendientes.component';
import { ReportadosComponent } from './vistas/reportados/reportados.component';
import { NavbarComponent } from './plantillas/navbar/navbar.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import {MatTreeModule} from '@angular/material/tree';
import { EditpermisosComponent } from './vistas/editpermisos/editpermisos.component';
import { RecoveryPassComponent } from './vistas/recovery-pass/recovery-pass.component';
import { ClientpanelComponent } from './vistas/clientpanel/clientpanel.component';
import { MyfileComponent } from './vistas/myfile/myfile.component';
import { ColaborationComponent } from './vistas/colaboration/colaboration.component';
import { ReportsclientComponent } from './vistas/reportsclient/reportsclient.component';
import { SearchComponent } from './vistas/search/search.component';
import { NavclientComponent } from './plantillas/navclient/navclient.component';
import { EditcComponent } from './vistas/editc/editc.component';
import { NotfoundComponent } from './vistas/notfound/notfound.component';

@NgModule({
  declarations: [
    AppComponent,
    LoginComponent,
    DashboardComponent,
    RegistroComponent,
    PendientesComponent,
    ReportadosComponent,
    NavbarComponent,
    EditpermisosComponent,
    RecoveryPassComponent,
    ClientpanelComponent,
    MyfileComponent,
    ColaborationComponent,
    ReportsclientComponent,
    SearchComponent,
    NavclientComponent,
    EditcComponent,
    NotfoundComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    ReactiveFormsModule,
    FormsModule,
    HttpClientModule,
    BrowserAnimationsModule,
    MatTreeModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
