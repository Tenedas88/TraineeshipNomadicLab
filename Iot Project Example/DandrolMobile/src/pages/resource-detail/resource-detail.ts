import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams, MenuController } from 'ionic-angular';

import { Http }			from '@angular/http';

import { EndPointDesc, ObjectLinkDesc, ObjectDesc, ContentDesc, ResourceDesc} from '../../app/ipso';
import { ServerCom }				from '../../providers/server-com';

const FAKERES: ObjectDesc = {
	status: 'loading...',
	content: {
		id: 0,
		resources: [
		{id: 0, value: 0}]
	}
};

@IonicPage()
@Component({
  selector: 'page-resource-detail',
  templateUrl: 'resource-detail.html',
})
export class ResourceDetail {

	serverResDidLoad: boolean = false;
	currentResPath: string;
	currentResDetail: ObjectDesc = FAKERES;
	currentResArray: ResourceDesc[] = this.currentResDetail.content.resources;

  constructor(public navCtrl: NavController, public navParams: NavParams,
				public menu: MenuController, private serverCom: ServerCom, private http: Http) {
				this.currentResPath = this.navParams.get('currentPath') as string;
  }

  updateResource(){
	this.serverCom.getResReq(this.currentResPath).then( data => {
	this.currentResDetail=data;
	this.currentResArray = this.currentResDetail.content.resources;
	this.serverResDidLoad=true;})
	.catch( err => this.serverResDidLoad = false);
  }
  
  ionViewDidLoad() {
  	this.serverCom.getResReq(this.currentResPath).then( data => {
		this.currentResDetail=data;
		this.currentResArray = this.currentResDetail.content.resources;
		this.serverResDidLoad = true;})
		.catch( err => this.serverResDidLoad = false);
  }

}
