import { Component } from '@angular/core';
import { NavController, Platform, MenuController, IonicPage, ViewController } 	from 'ionic-angular';

import { ServerCom }				from '../../providers/server-com';
import { ConditionDesc, RuleDesc} from '../../app/rule';

const STUBRULE: RuleDesc[] = [{
	ruleID: 100,
	conditions: [{
		endpoint: "endpoint stub1",
		target: "fake target1",
		readValue: 5,
		operator: "gt",
		value: 77,
		concatenationOp: "AND"
	}],
	actionEndpoint: "fake action1",
	actionTarget: "fake action target1"
},
{
	ruleID: 101,
	conditions: [{
		endpoint: "endpoint stub2",
		target: "fake target2",
		readValue: 5,
		operator: "=",
		value: 77,
		concatenationOp: "AND"
	},
	{
		endpoint: "endpoint stub3",
		target: "fake target3",
		readValue: 5,
		operator: "<",
		value: 77,
		concatenationOp: ""
	}],
	actionEndpoint: "fake action2",
	actionTarget: "fake action target2"
}]

@IonicPage()
@Component({
  selector: 'page-rule-page',
  templateUrl: 'rule-page.html',
})
export class RulePage {

  serverRuleDidLoad: boolean = false;
  serverRule: RuleDesc[];

  constructor(public navCtrl: NavController, public menu: MenuController, public viewController: ViewController,
				private serverCom: ServerCom) {

  }

  goToRuleDetail(rule: RuleDesc) {
    this.navCtrl.push('RuleDetail', rule);
  }
  
 
  PostStubRule(){
	this.serverCom.postReqRule(STUBRULE[0]).then(data => data.json());
	this.serverCom.getReqRule().then(data => this.serverRule = data);
	//TODO:this.navCtrl.push('RuleForm')
  }
  
  ionViewDidLoad(){
	this.serverCom.getReqRule().then(data => {
	this.serverRule = data;
	this.serverRuleDidLoad=true;})
	.catch( err => this.serverRuleDidLoad = false
	);
  }
  
  ionViewWillEnter(){
	this.viewController.showBackButton(false);
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
