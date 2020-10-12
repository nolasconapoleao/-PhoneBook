import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { HOMEPAGEComponent } from './home-page/home-page.component';
import { SettingsPageComponent } from './settings-page/settings-page.component';
import { PhoneBookPageComponent } from './phone-book-page/phone-book-page.component';

const routes: Routes = [
  { path: "homepage", component: HOMEPAGEComponent },
  { path: "settings", component: SettingsPageComponent},
  { path: "phonebook", component: PhoneBookPageComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
export const routingComponents = [HOMEPAGEComponent];
