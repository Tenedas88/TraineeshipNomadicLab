import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams, MenuController } from 'ionic-angular';

import { Device, EndPointDesc, ObjectLinkDesc } from '../../app/ipso';

@IonicPage()
@Component({
  selector: 'page-device-detail',
  templateUrl: 'device-detail.html',
})
export class DeviceDetail {

  resources: ObjectLinkDesc[];
  endpoint : string;
  resPath: string;

  constructor(public navCtrl: NavController, public navParams: NavParams,
				public menu: MenuController) {
				this.resources = this.navParams.get('objectLinks');
				this.endpoint = this.navParams.get('endpoint');
  }
  
  goToResourceDetail(resource: ObjectLinkDesc){
	this.resPath = `/${this.endpoint}${resource.url}`;
	this.navCtrl.push('ResourceDetail', {currentPath: this.resPath});
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad DeviceDetail');
  }

}
