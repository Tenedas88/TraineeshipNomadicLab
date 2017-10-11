import { Component } 				from '@angular/core';
import { NavController, Platform, MenuController, IonicPage, ViewController } 	from 'ionic-angular';
import { DeviceDetail }				from '../device-detail/device-detail';

import { Http, Headers, Response }			from '@angular/http';
import { ServerCom }				from '../../providers/server-com';

import { EndPointDesc, ObjectLinkDesc} from '../../app/ipso';
import { ConditionDesc, RuleDesc} from '../../app/rule';

import 'rxjs/add/operator/map';
import 'rxjs/add/operator/catch';

@IonicPage()
@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {

  serverEndPointDidLoad : boolean = false;
  serverRes : EndPointDesc[];

  constructor(public navCtrl: NavController, public menu: MenuController, public viewController: ViewController,
				private http: Http, private serverCom: ServerCom) {

  }

  goToDeviceDetail(endPointDesc: EndPointDesc) {
    this.navCtrl.push('DeviceDetail', endPointDesc);
  }

  ionViewWillEnter(){
	this.viewController.showBackButton(false);
  }

  ionViewDidLoad(){
	  this.serverCom.getReq().then(data =>{
      this.serverRes = data;
	  this.serverEndPointDidLoad=true;
	  }
    )
	.catch( err => this.serverEndPointDidLoad = false
	);
  }

  openMenu(){
	this.menu.open();
  }

  closeMenu(){
	this.menu.close();
  }

  toggleMenu(){
	this.menu.toggle();
  }

}
