import { Component } from '@angular/core';
import { Platform, App, MenuController } from 'ionic-angular';
import { StatusBar } from '@ionic-native/status-bar';
import { SplashScreen } from '@ionic-native/splash-screen';

import { HomePage } from '../pages/home/home';

@Component({
  templateUrl: 'app.html'
})
export class MyApp {
  rootPage:any = HomePage;
  mycontent = {name: "Device", URL: "DeviceDetail"}

  constructor(platform: Platform, statusBar: StatusBar, splashScreen: SplashScreen,
				public appCtrl: App, public menu: MenuController) {
    platform.ready().then(() => {
      // Okay, so the platform is ready and our plugins are available.
      // Here you can do any higher level native things you might need.
      statusBar.styleDefault();
      splashScreen.hide();
    });
  }
  
  PushRulePage(){
	this.appCtrl.getRootNav().push('RulePage');
	this.menu.close();
  }
  
  PushHomePage(){
	this.appCtrl.getRootNav().push('HomePage');
	this.menu.close();
  }
}

