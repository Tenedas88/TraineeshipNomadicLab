import { BrowserModule } from '@angular/platform-browser';
import { ErrorHandler, NgModule } from '@angular/core';
import { IonicApp, IonicErrorHandler, IonicModule, IonicPageModule } from 'ionic-angular';
import { SplashScreen } from '@ionic-native/splash-screen';
import { StatusBar } from '@ionic-native/status-bar';

import { MyApp } from './app.component';
import { HomeModule } from '../pages/home/home.module';
import { RulePageModule } from '../pages/rule-page/rule-page.module';

import { HttpModule, JsonpModule } from '@angular/http';

import { ServerCom } from '../providers/server-com';

@NgModule({
  declarations: [
    MyApp
  ],
  imports: [
    BrowserModule,
	HttpModule,
	HomeModule,
	RulePageModule,
    IonicModule.forRoot(MyApp)
  ],
  bootstrap: [IonicApp],
  entryComponents: [
    MyApp
  ],
  providers: [
    StatusBar,
    SplashScreen,
	ServerCom,
    {provide: ErrorHandler, useClass: IonicErrorHandler}
  ]
})
export class AppModule {}
