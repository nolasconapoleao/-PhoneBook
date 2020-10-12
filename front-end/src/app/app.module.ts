import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppRoutingModule, routingComponents } from './app-routing.module';
import { AppComponent } from './app.component';
import { TopNavComponent } from './top-nav/top-nav.component';
import { SettingsPageComponent } from './settings-page/settings-page.component';
import { PhoneBookPageComponent } from './phone-book-page/phone-book-page.component';

@NgModule({
  declarations: [
    AppComponent,
    routingComponents,
    TopNavComponent,
    SettingsPageComponent,
    PhoneBookPageComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
