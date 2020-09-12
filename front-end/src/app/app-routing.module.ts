import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { HOMEPAGEComponent } from './home-page/home-page.component';

const routes: Routes = [
  { path: "homepage", component: HOMEPAGEComponent }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
export const routingComponents = [HOMEPAGEComponent];
