import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { HOMEPAGEComponent } from './home-page/home-page.component';
import { SettingsPageComponent } from './settings-page/settings-page.component';

const routes: Routes = [
  { path: "homepage", component: HOMEPAGEComponent },
  { path: "settings", component: SettingsPageComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
export const routingComponents = [HOMEPAGEComponent];
